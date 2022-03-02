#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstring>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define PAGE_SIZE 4096
#define TABLE_MAX_PAGES 100

class Row {
public:
    friend std::ostream &operator<<(std::ostream &os, const Row &row);

    std::uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1]{'\0'};
    char email[COLUMN_EMAIL_SIZE + 1]{'\0'};
};

std::ostream &operator<<(std::ostream &os, const Row &row) {
    return os << "(" << row.id << " " << row.username << " " << row.email << ")";
}

const std::uint32_t ID_SIZE = sizeof(Row::id);
const std::uint32_t USERNAME_SIZE = sizeof(Row::username);
const std::uint32_t EMAIL_SIZE = sizeof(Row::email);
const std::uint32_t ID_OFFSET = 0;
const std::uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const std::uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const std::uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void serialize_row(Row *src, char *dest) {
    std::memcpy(dest + ID_OFFSET, &(src->id), ID_SIZE);
    std::memcpy(dest + USERNAME_OFFSET, &(src->username), USERNAME_SIZE);
    std::memcpy(dest + EMAIL_OFFSET, &(src->email), EMAIL_SIZE);
}

void deserialize_row(char *src, Row *dest) {
    std::memcpy(&(dest->id), src + ID_OFFSET, ID_SIZE);
    std::memcpy(&(dest->username), src + USERNAME_OFFSET, USERNAME_SIZE);
    std::memcpy(&(dest->email), src + EMAIL_OFFSET, EMAIL_SIZE);
}

enum NodeType {
    NODE_INTERNAL,
    NODE_LEAF
};

// Common Node Header Layout
const std::uint32_t NODE_TYPE_SIZE = sizeof(std::uint8_t);
const std::uint32_t NODE_TYPE_OFFSET = 0;
const std::uint32_t IS_ROOT_SIZE = sizeof(std::uint8_t);
const std::uint32_t IS_ROOT_OFFSET = NODE_TYPE_SIZE + NODE_TYPE_OFFSET;
const std::uint32_t PARENT_POINTER_SIZE = sizeof(std::uint32_t);
const std::uint32_t PARENT_POINTER_OFFSET = IS_ROOT_SIZE + IS_ROOT_OFFSET;
const std::uint32_t COMMON_NODE_HEADER_SIZE = NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;

NodeType get_node_type(const char *node) {
    return (NodeType) *static_cast<std::uint8_t *>(static_cast<void *>(const_cast<char *>(node + NODE_TYPE_OFFSET)));
}

void set_node_type(char *node, NodeType type) {
    *static_cast<std::uint8_t *>(static_cast<void *>(node + NODE_TYPE_OFFSET)) = (std::uint8_t) type;
}

bool is_node_root(const char *node) {
    return (bool) *static_cast<std::uint8_t *>((static_cast<void *>(const_cast<char *>(node + IS_ROOT_OFFSET))));
}

void set_node_root(char *node, bool is_root) {
    *static_cast<std::uint8_t *>(static_cast<void *>(node + IS_ROOT_OFFSET)) = (std::uint8_t) is_root;
}

std::uint32_t *node_parent(char *node) {
    return static_cast<std::uint32_t *>(static_cast<void *>(node + PARENT_POINTER_OFFSET));
}

// Internal Node Header Layout
const std::uint32_t INTERNAL_NODE_NUM_CELLS_SIZE = sizeof(std::uint32_t);
const std::uint32_t INTERNAL_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
const std::uint32_t INTERNAL_NODE_RIGHT_CHILD_SIZE = sizeof(std::uint32_t);
const std::uint32_t INTERNAL_NODE_RIGHT_CHILD_OFFSET = INTERNAL_NODE_NUM_CELLS_OFFSET + INTERNAL_NODE_NUM_CELLS_SIZE;
const std::uint32_t INTERNAL_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + INTERNAL_NODE_NUM_CELLS_SIZE + INTERNAL_NODE_RIGHT_CHILD_SIZE;

// Internal Node Body Layout
const std::uint32_t INTERNAL_NODE_CHILD_SIZE = sizeof(std::uint32_t);
const std::uint32_t INTERNAL_NODE_KEY_SIZE = sizeof(std::uint32_t);
const std::uint32_t INTERNAL_NODE_CELL_SIZE = INTERNAL_NODE_CHILD_SIZE + INTERNAL_NODE_KEY_SIZE;

// Internal Node
const std::uint32_t INTERNAL_NODE_MAX_CELLS = 3;
const std::uint32_t INTERNAL_NODE_RIGHT_SPLIT_COUNT = (INTERNAL_NODE_MAX_CELLS + 1) / 2;
const std::uint32_t INTERNAL_NODE_LEFT_SPLIT_COUNT = (INTERNAL_NODE_MAX_CELLS + 1) - INTERNAL_NODE_RIGHT_SPLIT_COUNT;

std::uint32_t *internal_node_num_cells(char *node) {
    return static_cast<std::uint32_t *>(static_cast<void *>(node + INTERNAL_NODE_NUM_CELLS_OFFSET));
}

std::uint32_t *internal_node_right_child(char *node) {
    return static_cast<std::uint32_t *>(static_cast<void *>(node + INTERNAL_NODE_RIGHT_CHILD_OFFSET));
}

char *internal_node_cell(char *node, std::uint32_t cell_num) {
    return node + INTERNAL_NODE_HEADER_SIZE + cell_num * INTERNAL_NODE_CELL_SIZE;
}

std::uint32_t *internal_node_child(char *node, std::uint32_t cell_num) {
    return static_cast<std::uint32_t *>(static_cast<void *>(internal_node_cell(node, cell_num)));
}

std::uint32_t *internal_node_key(char *node, std::uint32_t cell_num) {
    return static_cast<std::uint32_t *>(static_cast<void *>(internal_node_cell(node, cell_num) + INTERNAL_NODE_CHILD_SIZE));
}

void initialize_internal_node(char *node) {
    set_node_type(node, NODE_INTERNAL);
    set_node_root(node, false);
    *node_parent(node) = TABLE_MAX_PAGES;

    *internal_node_num_cells(node) = 0;
    *internal_node_right_child(node) = TABLE_MAX_PAGES;
}

std::uint32_t internal_node_find_child(char *node, std::uint32_t key) {
    // min_index = min { cn | key_cn >= key } | num_cells
    std::uint32_t num_cells = *internal_node_num_cells(node);
    std::uint32_t min_index = 0;
    std::uint32_t max_index = num_cells;
    while (min_index != max_index) {
        std::uint32_t index = min_index + (max_index - min_index) / 2;
        std::uint32_t key0 = *internal_node_key(node, index);
        if (key0 >= key) {
            max_index = index;
        } else {
            min_index = index + 1;
        }
    }
    return min_index;
}

void update_internal_node_key(char *node, std::uint32_t old_key, std::uint32_t new_key) {
    std::uint32_t old_index = internal_node_find_child(node, old_key);
    *internal_node_key(node, old_index) = new_key;
}

// Leaf Node Header Layout
const std::uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(std::uint32_t);
const std::uint32_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
const std::uint32_t LEAF_NODE_NEXT_LEAF_SIZE = sizeof(std::uint32_t);
const std::uint32_t LEAF_NODE_NEXT_LEAF_OFFSET = LEAF_NODE_NUM_CELLS_OFFSET + LEAF_NODE_NUM_CELLS_SIZE;
const std::uint32_t LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE + LEAF_NODE_NEXT_LEAF_SIZE;

// Leaf Node Body Layout
const std::uint32_t LEAF_NODE_KEY_SIZE = sizeof(std::uint32_t);
const std::uint32_t LEAF_NODE_KEY_OFFSET = 0;
const std::uint32_t LEAF_NODE_VALUE_SIZE = ROW_SIZE;
const std::uint32_t LEAF_NODE_VALUE_OFFSET = LEAF_NODE_KEY_SIZE + LEAF_NODE_KEY_OFFSET;
const std::uint32_t LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE;

// Leaf Node
const std::uint32_t LEAF_NODE_SPACE_FOR_CELLS = PAGE_SIZE - LEAF_NODE_HEADER_SIZE;
const std::uint32_t LEAF_NODE_MAX_CELLS = LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;
const std::uint32_t LEAF_NODE_RIGHT_SPLIT_COUNT = (LEAF_NODE_MAX_CELLS + 1) / 2;
const std::uint32_t LEAF_NODE_LEFT_SPLIT_COUNT = (LEAF_NODE_MAX_CELLS + 1) - LEAF_NODE_RIGHT_SPLIT_COUNT;

std::uint32_t *leaf_node_num_cells(char *node) {
    return static_cast<std::uint32_t *>(static_cast<void *>(node + LEAF_NODE_NUM_CELLS_OFFSET));
}

std::uint32_t *leaf_node_next_leaf(char *node) {
    return static_cast<std::uint32_t *>(static_cast<void *>(node + LEAF_NODE_NEXT_LEAF_OFFSET));
}

char *leaf_node_cell(char *node, std::uint32_t cell_num) {
    return node + LEAF_NODE_HEADER_SIZE + cell_num * LEAF_NODE_CELL_SIZE;
}

std::uint32_t *leaf_node_key(char *node, std::uint32_t cell_num) {
    return static_cast<std::uint32_t *>(static_cast<void *>(leaf_node_cell(node, cell_num)));
}

char *leaf_node_value(char *node, std::uint32_t cell_num) {
    return leaf_node_cell(node, cell_num) + LEAF_NODE_KEY_SIZE;
}

void initialize_leaf_node(char *node) {
    set_node_type(node, NODE_LEAF);
    set_node_root(node, false);
    *node_parent(node) = TABLE_MAX_PAGES;

    *leaf_node_num_cells(node) = 0;
    *leaf_node_next_leaf(node) = TABLE_MAX_PAGES;
}

std::uint32_t leaf_node_find_child(char *node, std::uint32_t key) {
    // min_index = min { cn | key_cn >= key } | num_cells
    std::uint32_t num_cells = *leaf_node_num_cells(node);
    std::uint32_t min_index = 0;
    std::uint32_t max_index = num_cells;
    while (min_index != max_index) {
        std::uint32_t index = min_index + (max_index - min_index) / 2;
        std::uint32_t key0 = *leaf_node_key(node, index);
        if (key0 >= key) {
            max_index = index;
        } else {
            min_index = index + 1;
        }
    }
    return min_index;
}

std::uint32_t get_node_max_key(char *node) {
    switch (get_node_type(node)) {
        case NODE_INTERNAL:
            return *internal_node_key(node, *internal_node_num_cells(node) - 1);
        case NODE_LEAF:
            return *leaf_node_key(node, *leaf_node_num_cells(node) - 1);
    }
}

void print_constants() {
    std::cout << "ROW_SIZE: " << ROW_SIZE << std::endl;
    std::cout << "COMMON_NODE_HEADER_SIZE: " << COMMON_NODE_HEADER_SIZE << std::endl;
    std::cout << "INTERNAL_NODE_HEADER_SIZE: " << INTERNAL_NODE_HEADER_SIZE << std::endl;
    std::cout << "INTERNAL_NODE_CELL_SIZE: " << INTERNAL_NODE_CELL_SIZE << std::endl;
    std::cout << "LEAF_NODE_HEADER_SIZE: " << LEAF_NODE_HEADER_SIZE << std::endl;
    std::cout << "LEAF_NODE_CELL_SIZE: " << LEAF_NODE_CELL_SIZE << std::endl;
    std::cout << "LEAF_NODE_SPACE_FOR_CELLS: " << LEAF_NODE_SPACE_FOR_CELLS << std::endl;
    std::cout << "LEAF_NODE_MAX_CELLS: " << LEAF_NODE_MAX_CELLS << std::endl;
}

class Pager {
public:
    FILE *file;
    std::uint32_t file_length;
    std::uint32_t num_pages;
    char *pages[TABLE_MAX_PAGES]{nullptr};

    Pager(const char *filename);
    ~Pager();

    std::uint32_t get_unused_page_num() const;
    char *get_page(std::uint32_t page_num);
    void flush_page(std::uint32_t page_num);
};

Pager::Pager(const char *filename) {
    file = fopen(filename, "r+b");
    if (file == nullptr) {
        std::cout << "Unable to open file." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        std::cout << "Error seeking." << std::endl;
        exit(EXIT_FAILURE);
    }

    file_length = ftell(file);
    if (file_length == -1) {
        std::cout << "Error telling." << std::endl;
        exit(EXIT_FAILURE);
    }

    num_pages = file_length / PAGE_SIZE;

    if (file_length % PAGE_SIZE != 0) {
        std::cout << "Db file is not a whole number of pages. Corrupt file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

Pager::~Pager() {
    for (auto &page: pages) {
        delete[] page;
    }

    if (fclose(file) != 0) {
        std::cout << "Error closing db file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

std::uint32_t Pager::get_unused_page_num() const {
    return num_pages;
}

char *Pager::get_page(std::uint32_t page_num) {
    if (page_num > TABLE_MAX_PAGES) {
        std::cout << "Tried to fetch page number out of bounds. " << page_num << " > " << TABLE_MAX_PAGES << "." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (pages[page_num] == nullptr) {
        char *page = new char[PAGE_SIZE]{'\0'};

        if (page_num < file_length / PAGE_SIZE) {
            if (fseek(file, static_cast<long>(page_num) * PAGE_SIZE, SEEK_SET) != 0) {
                std::cout << "Error seeking." << std::endl;
                exit(EXIT_FAILURE);
            }

            if (fread(page, sizeof(char), PAGE_SIZE, file) < PAGE_SIZE) {
                std::cout << "Error reading file." << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        pages[page_num] = page;

        if (page_num >= num_pages) {
            num_pages = page_num + 1;
        }
    }

    return pages[page_num];
}

void Pager::flush_page(std::uint32_t page_num) {
    if (pages[page_num] == nullptr) {
        std::cout << "Tried to flush null page." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (fseek(file, static_cast<long>(page_num) * PAGE_SIZE, SEEK_SET) != 0) {
        std::cout << "Error seeking." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (fwrite(pages[page_num], sizeof(char), PAGE_SIZE, file) < PAGE_SIZE) {
        std::cout << "Error writing." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void indent(std::uint32_t level) {
    for (std::uint32_t i = 0; i < level; i++) {
        std::cout << "  ";
    }
}

void print_tree(Pager *pager, std::uint32_t page_num, std::uint32_t indentation_level) {
    char *node = pager->get_page(page_num);
    std::uint32_t num_cells;
    std::uint32_t child;

    switch (get_node_type(node)) {
        case NODE_INTERNAL:
            num_cells = *internal_node_num_cells(node);
            indent(indentation_level);
            std::cout << "- internal (size " << num_cells << ")" << std::endl;
            for (std::uint32_t i = 0; i < num_cells; i++) {
                child = *internal_node_child(node, i);
                print_tree(pager, child, indentation_level + 1);
                indent(indentation_level + 1);
                std::cout << "- key " << *internal_node_key(node, i) << std::endl;
            }
            child = *internal_node_right_child(node);
            print_tree(pager, child, indentation_level + 1);
            break;
        case NODE_LEAF:
            num_cells = *leaf_node_num_cells(node);
            indent(indentation_level);
            std::cout << "- leaf (size " << num_cells << ")" << std::endl;
            for (std::uint32_t i = 0; i < num_cells; i++) {
                indent(indentation_level + 1);
                std::cout << "- key " << *leaf_node_key(node, i) << std::endl;
            }
            break;
    }
}

class Table {
public:
    Pager *pager;
    std::uint32_t root_page_num;

    Table(const char *filename);
    ~Table();

    class Cursor {
    public:
        Table *table;
        std::uint32_t page_num;
        std::uint32_t cell_num;
        bool end_of_table;

        Cursor(Table *table0, std::uint32_t page_num0, std::uint32_t cell_num0, bool end_of_table0) : table(table0), page_num(page_num0), cell_num(cell_num0), end_of_table(end_of_table0) {}

        Cursor &operator++() {
            if (end_of_table) {
                return *this;
            }
            char *node = table->pager->get_page(page_num);
            if (++cell_num >= *leaf_node_num_cells(node)) {
                std::uint32_t next_page_num = *leaf_node_next_leaf(node);
                if (next_page_num == TABLE_MAX_PAGES) {
                    end_of_table = true;
                } else {
                    page_num = next_page_num;
                    cell_num = 0;

                    char *next_node = table->pager->get_page(next_page_num);
                    std::uint32_t next_num_cells = *leaf_node_num_cells(next_node);
                    end_of_table = cell_num == next_num_cells && *leaf_node_next_leaf(next_node) == TABLE_MAX_PAGES;
                }
            }
            return *this;
        };
        Cursor operator++(int) { Cursor cursor = *this; ++(*this); return cursor; };

        char *value() const {
            char *page = table->pager->get_page(page_num);
            return leaf_node_value(page, cell_num);
        }

        void create_new_root(std::uint32_t right_child_page_num, std::uint32_t key) const {
            char *root = table->pager->get_page(table->root_page_num);

            std::uint32_t left_child_page_num = table->pager->get_unused_page_num();
            char *left_child_node = table->pager->get_page(left_child_page_num);
            std::memcpy(left_child_node, root, PAGE_SIZE);
            *node_parent(left_child_node) = table->root_page_num;
            set_node_root(left_child_node, false);

            char *right_child_node = table->pager->get_page(right_child_page_num);
            *node_parent(right_child_node) = table->root_page_num;

            initialize_internal_node(root);
            set_node_root(root, true);
            *internal_node_num_cells(root) = 1;
            *internal_node_child(root, 0) = left_child_page_num;
            *internal_node_key(root, 0) = key;
            *internal_node_right_child(root) = right_child_page_num;
        }

        void internal_node_split_and_insert(std::uint32_t parent_page_num, std::uint32_t child_page_num) const {
            char *old_node = table->pager->get_page(parent_page_num);
            std::uint32_t old_key = get_node_max_key(old_node);

            char *child_node = table->pager->get_page(child_page_num);
            std::uint32_t child_key = get_node_max_key(child_node);

            // right child
            std::uint32_t right_child_page_num = *internal_node_right_child(old_node);
            char *right_child_node = table->pager->get_page(right_child_page_num);
            std::uint32_t right_child_key = get_node_max_key(right_child_node);
            if (child_key > right_child_key) {
                // new node
                std::uint32_t new_page_num = table->pager->get_unused_page_num();
                char *new_node = table->pager->get_page(new_page_num);
                initialize_internal_node(new_node);

                *internal_node_child(new_node, INTERNAL_NODE_RIGHT_SPLIT_COUNT - 1) = right_child_page_num;
                *internal_node_key(new_node, INTERNAL_NODE_RIGHT_SPLIT_COUNT - 1) = right_child_key;
                for (std::uint32_t i = 0; i < INTERNAL_NODE_RIGHT_SPLIT_COUNT - 1; i++) {
                    std::memcpy(internal_node_cell(new_node, i), internal_node_cell(old_node, i + INTERNAL_NODE_LEFT_SPLIT_COUNT), INTERNAL_NODE_CELL_SIZE);
                }

                *internal_node_right_child(new_node) = child_page_num;
                *internal_node_num_cells(new_node) = INTERNAL_NODE_RIGHT_SPLIT_COUNT;
                *node_parent(new_node) = *node_parent(old_node);

                // old node
                std::uint32_t new_key = *internal_node_key(old_node, INTERNAL_NODE_LEFT_SPLIT_COUNT - 1);
                std::uint32_t new_right_child_page_num = *internal_node_child(old_node,INTERNAL_NODE_LEFT_SPLIT_COUNT - 1);
                *internal_node_right_child(old_node) = new_right_child_page_num;
                *internal_node_num_cells(old_node) = INTERNAL_NODE_LEFT_SPLIT_COUNT - 1;

                // insert new node
                if (is_node_root(old_node)) {
                    create_new_root(new_page_num, new_key);
                } else {
                    std::uint32_t old_node_parent_page_num = *node_parent(old_node);
                    char *parent_node = table->pager->get_page(old_node_parent_page_num);
                    update_internal_node_key(parent_node, old_key, new_key);
                    internal_node_insert(old_node_parent_page_num, new_page_num);
                }
                return;
            }

            // no right child
            // new node
            std::uint32_t new_page_num = table->pager->get_unused_page_num();
            char *new_node = table->pager->get_page(new_page_num);
            initialize_internal_node(new_node);

            std::uint32_t index = internal_node_find_child(old_node, child_key);
            for (int j = INTERNAL_NODE_MAX_CELLS; j > -1; j--) {
                std::uint32_t i = j;
                char *destination_node;
                std::uint32_t index_within_node;

                if (i < INTERNAL_NODE_LEFT_SPLIT_COUNT) {
                    destination_node = old_node;
                    index_within_node = i;
                } else {
                    destination_node = new_node;
                    if (INTERNAL_NODE_LEFT_SPLIT_COUNT == INTERNAL_NODE_RIGHT_SPLIT_COUNT) {
                        index_within_node = i % INTERNAL_NODE_RIGHT_SPLIT_COUNT;
                    } else {
                        index_within_node = (i - 1) % INTERNAL_NODE_RIGHT_SPLIT_COUNT;
                    }
                }

                char *destination = internal_node_cell(destination_node, index_within_node);
                if (i == index) {
                    *internal_node_child(destination_node, index_within_node) = child_page_num;
                    *internal_node_key(destination_node, index_within_node) = child_key;
                } else if (i > index) {
                    std::memcpy(destination, internal_node_cell(old_node, i - 1), INTERNAL_NODE_CELL_SIZE);
                } else {
                    std::memcpy(destination, internal_node_cell(old_node, i), INTERNAL_NODE_CELL_SIZE);
                }
            }

            *internal_node_right_child(new_node) = *internal_node_right_child(old_node);
            *internal_node_num_cells(new_node) = INTERNAL_NODE_RIGHT_SPLIT_COUNT;
            *node_parent(new_node) = *node_parent(old_node);

            // old node
            std::uint32_t new_key = *internal_node_key(old_node, INTERNAL_NODE_LEFT_SPLIT_COUNT - 1);
            std::uint32_t new_right_child_page_num = *internal_node_child(old_node,INTERNAL_NODE_LEFT_SPLIT_COUNT - 1);
            *internal_node_right_child(old_node) = new_right_child_page_num;
            *internal_node_num_cells(old_node) = INTERNAL_NODE_LEFT_SPLIT_COUNT - 1;

            // insert new node
            if (is_node_root(old_node)) {
                create_new_root(new_page_num, new_key);
            } else {
                std::uint32_t old_node_parent_page_num = *node_parent(old_node);
                char *parent_node = table->pager->get_page(old_node_parent_page_num);
                update_internal_node_key(parent_node, old_key, new_key);
                internal_node_insert(old_node_parent_page_num, new_page_num);
            }
        }

        void internal_node_insert(std::uint32_t parent_page_num, std::uint32_t child_page_num) const {
            char *parent_node = table->pager->get_page(parent_page_num);
            std::uint32_t num_cells = *internal_node_num_cells(parent_node);
            if (num_cells >= INTERNAL_NODE_MAX_CELLS) {
                internal_node_split_and_insert(parent_page_num, child_page_num);
                return;
            }

            char *child_node = table->pager->get_page(child_page_num);
            std::uint32_t child_key = get_node_max_key(child_node);

            // right child
            std::uint32_t right_child_page_num = *internal_node_right_child(parent_node);
            char *right_child_node = table->pager->get_page(right_child_page_num);
            std::uint32_t right_child_key = get_node_max_key(right_child_node);
            if (child_key > right_child_key) {
                *internal_node_child(parent_node, num_cells) = right_child_page_num;
                *internal_node_key(parent_node, num_cells) = right_child_key;
                *internal_node_right_child(parent_node) = child_page_num;
                *internal_node_num_cells(parent_node) += 1;
                return;
            }

            // no right child
            std::uint32_t index = internal_node_find_child(parent_node, child_key);
            for (std::uint32_t i = num_cells; i > index; i--) {
                std::memcpy(internal_node_cell(parent_node, i), internal_node_cell(parent_node, i - 1), INTERNAL_NODE_CELL_SIZE);
            }
            *internal_node_child(parent_node, index) = child_page_num;
            *internal_node_key(parent_node, index) = child_key;
            *internal_node_num_cells(parent_node) += 1;
        }

        void leaf_node_split_and_insert(std::uint32_t key, Row *value) const {
            char *old_node = table->pager->get_page(page_num);
            std::uint32_t old_key = get_node_max_key(old_node);

            // new node
            std::uint32_t new_page_num = table->pager->get_unused_page_num();
            char *new_node = table->pager->get_page(new_page_num);
            initialize_leaf_node(new_node);

            for (int j = LEAF_NODE_MAX_CELLS; j > -1; j--) {
                std::uint32_t i = j;
                char *destination_node;
                std::uint32_t index_within_node;

                if (i < LEAF_NODE_LEFT_SPLIT_COUNT) {
                    destination_node = old_node;
                    index_within_node = i;
                } else {
                    destination_node = new_node;
                    if (LEAF_NODE_LEFT_SPLIT_COUNT == LEAF_NODE_RIGHT_SPLIT_COUNT) {
                        index_within_node = i % LEAF_NODE_RIGHT_SPLIT_COUNT;
                    } else {
                        index_within_node = (i - 1) % LEAF_NODE_RIGHT_SPLIT_COUNT;
                    }
                }

                char *destination = leaf_node_cell(destination_node, index_within_node);
                if (i == cell_num) {
                    *leaf_node_key(destination_node, index_within_node) = key;
                    serialize_row(value, leaf_node_value(destination_node, index_within_node));
                } else if (i > cell_num) {
                    std::memcpy(destination, leaf_node_cell(old_node, i - 1), LEAF_NODE_CELL_SIZE);
                } else {
                    std::memcpy(destination, leaf_node_cell(old_node, i), LEAF_NODE_CELL_SIZE);
                }
            }

            *leaf_node_next_leaf(new_node) = *leaf_node_next_leaf(old_node);
            *leaf_node_num_cells(new_node) = LEAF_NODE_RIGHT_SPLIT_COUNT;
            *node_parent(new_node) = *node_parent(old_node);

            // old node
            *leaf_node_next_leaf(old_node) = new_page_num;
            *leaf_node_num_cells(old_node) = LEAF_NODE_LEFT_SPLIT_COUNT;
            std::uint32_t new_key = get_node_max_key(old_node);

            // insert new node
            if (is_node_root(old_node)) {
                create_new_root(new_page_num, new_key);
            } else {
                std::uint32_t parent_page_num = *node_parent(old_node);
                char *parent_node = table->pager->get_page(parent_page_num);
                update_internal_node_key(parent_node, old_key, new_key);
                internal_node_insert(parent_page_num, new_page_num);
            }
        }

        void leaf_node_insert(std::uint32_t key, Row *value) const {
            char *node = table->pager->get_page(page_num);
            std::uint32_t num_cells = *leaf_node_num_cells(node);
            if (num_cells >= LEAF_NODE_MAX_CELLS) {
                leaf_node_split_and_insert(key, value);
                return;
            }

            for (std::uint32_t i = num_cells; i > cell_num; i--) {
                memcpy(leaf_node_cell(node, i), leaf_node_cell(node, i - 1), LEAF_NODE_CELL_SIZE);
            }
            *leaf_node_key(node, cell_num) = key;
            serialize_row(value, leaf_node_value(node, cell_num));
            *leaf_node_num_cells(node) += 1;
        }
    };

    Cursor begin() { return find(0); }
    Cursor internal_node_find(std::uint32_t page_num, std::uint32_t key) {
        char *node = pager->get_page(page_num);
        std::uint32_t min_index = internal_node_find_child(node, key);
        std::uint32_t num_cells = *internal_node_num_cells(node);
        if (min_index < num_cells) {
            return find(*internal_node_child(node, min_index), key);
        } else {
            return find(*internal_node_right_child(node), key);
        }
    }
    Cursor leaf_node_find(std::uint32_t page_num, std::uint32_t key) {
        char *node = pager->get_page(page_num);
        std::uint32_t min_index = leaf_node_find_child(node, key);
        std::uint32_t num_cells = *leaf_node_num_cells(node);
        bool end_of_table = min_index == num_cells && *leaf_node_next_leaf(node) == TABLE_MAX_PAGES;
        return Cursor(this, page_num, min_index, end_of_table);
    }
    Cursor find(std::uint32_t page_num, std::uint32_t key) {
        char *node = pager->get_page(page_num);
        switch (get_node_type(node)) {
            case NODE_INTERNAL:
                return internal_node_find(page_num, key);
            case NODE_LEAF:
                return leaf_node_find(page_num, key);
        }
    }
    Cursor find(std::uint32_t key) {
        return find(root_page_num, key);
    }
};

Table::Table(const char *filename) {
    pager = new Pager(filename);
    root_page_num = 0;
    if (pager->num_pages == 0) {
        char *root_node = pager->get_page(0);
        initialize_leaf_node(root_node);
        set_node_root(root_node, true);
    }
}

Table::~Table() {
    for (std::uint32_t i = 0; i < pager->num_pages; i++) {
        if (pager->pages[i] != nullptr) {
            pager->flush_page(i);
        }
    }
    delete pager;
}

enum MetaCommandResult {
    META_COMMAND_EXIT,
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
};

enum PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_UNRECOGNIZED_STATEMENT
};

enum ExecuteResult {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_DUPLICATE_KEY
};

enum StatementType {
    STATEMENT_INSERT,
    STATEMENT_SELECT
};

class Statement {
public:
    StatementType type{STATEMENT_INSERT};
    Row row;
};

MetaCommandResult do_meta_command(const std::string &buffer, Table *table) {
    if (buffer == ".exit") {
        return META_COMMAND_EXIT;
    }
    if (buffer == ".constants") {
        std::cout << "Constants:" << std::endl;
        print_constants();
        return META_COMMAND_SUCCESS;
    }
    if (buffer == ".btree") {
        std::cout << "Tree:" << std::endl;
        print_tree(table->pager, 0, 0);
        return META_COMMAND_SUCCESS;
    }
    return META_COMMAND_UNRECOGNIZED_COMMAND;
}

PrepareResult prepare_insert(const std::string &buffer, Statement *statement) {
    statement->type = STATEMENT_INSERT;

    std::strtok(const_cast<char *>(buffer.c_str()), " ");
    char *id_str = std::strtok(nullptr, " ");
    char *username = std::strtok(nullptr, " ");
    char *email = std::strtok(nullptr, " ");
    if (id_str == nullptr || username == nullptr || email == nullptr) {
        return PREPARE_SYNTAX_ERROR;
    }

    int id = std::atoi(id_str);
    if (id < 0) {
        return PREPARE_NEGATIVE_ID;
    }
    if (std::strlen(username) > COLUMN_USERNAME_SIZE || std::strlen(email) > COLUMN_EMAIL_SIZE) {
        return PREPARE_STRING_TOO_LONG;
    }

    statement->row.id = id;
    std::strncpy(statement->row.username, username, USERNAME_SIZE + 1);
    std::strncpy(statement->row.email, email, EMAIL_SIZE + 1);
    return PREPARE_SUCCESS;
}

PrepareResult prepare_statement(const std::string &buffer, Statement *statement) {
    if (buffer.rfind("insert", 0) == 0) {
        return prepare_insert(buffer, statement);
    }
    if (buffer == "select") {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult execute_insert(Statement *statement, Table *table) {
    Row *row = &(statement->row);
    std::uint32_t key = row->id;
    Table::Cursor cursor = table->find(key);

    char *node = table->pager->get_page(cursor.page_num);
    std::uint32_t num_cells = *leaf_node_num_cells(node);
    if (cursor.cell_num < num_cells && *leaf_node_key(node, cursor.cell_num) == key) {
        return EXECUTE_DUPLICATE_KEY;
    }

    cursor.leaf_node_insert(key, row);
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *statement, Table *table) {
    for (Table::Cursor cursor = table->begin(); !cursor.end_of_table; cursor++) {
        Row row{};
        deserialize_row(cursor.value(), &row);
        std::cout << row << std::endl;
    }
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *statement, Table *table) {
    switch (statement->type) {
        case STATEMENT_INSERT:
            return execute_insert(statement, table);
        case STATEMENT_SELECT:
            return execute_select(statement, table);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Must supply a database filename." << std::endl;
        exit(EXIT_FAILURE);
    }

    Table *table = new Table(argv[1]);

    std::string buffers[] = {
        "insert 0 user person@example.com",
        "insert 1 user person@example.com",
        "insert 2 user person@example.com",
        "insert 3 user person@example.com",
        "insert 4 user person@example.com",
        "insert 5 user person@example.com",
        "insert 6 user person@example.com",
        "insert 7 user person@example.com",
        "insert 8 user person@example.com",
        "insert 9 user person@example.com",
        "insert 10 user person@example.com",
        "insert 11 user person@example.com",
        "insert 12 user person@example.com",
        "insert 13 user person@example.com",
        "insert 21 user person@example.com",
        "insert 22 user person@example.com",
        "insert 23 user person@example.com",
        "insert 24 user person@example.com",
        "insert 25 user person@example.com",
        "insert 26 user person@example.com",
        "insert 27 user person@example.com",
        "insert 28 user person@example.com",
        "insert 29 user person@example.com",
        "insert 30 user person@example.com",
        "insert 31 user person@example.com",
        "insert 32 user person@example.com",
        "insert 33 user person@example.com",
        "insert 34 user person@example.com",
        "insert 14 user person@example.com",
        "insert 15 user person@example.com",
        "insert 16 user person@example.com",
        "insert 17 user person@example.com",
        "insert 18 user person@example.com",
        "insert 19 user person@example.com",
        "insert 20 user person@example.com",

    };
    int i = 0;
    int N = 35;

    while (true) {
        std::string buffer;

        if (i < N) {
            buffer = buffers[i];
        } else {
            std::cout << "db > " << std::flush;
            std::getline(std::cin, buffer);
        }
        i += 1;

        if (buffer.rfind('.', 0) == 0) {
            switch (do_meta_command(buffer, table)) {
                case META_COMMAND_EXIT:
                    delete table;
                    return 0;
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    std::cout << "Unrecognized command '" << buffer << "'." << std::endl;
                    continue;
            }
        }

        Statement statement{};
        switch (prepare_statement(buffer, &statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_SYNTAX_ERROR:
                std::cout << "Syntax error. Could not parse statement." << std::endl;
                continue;
            case PREPARE_NEGATIVE_ID:
                std::cout << "ID must be positive." << std::endl;
                continue;
            case PREPARE_STRING_TOO_LONG:
                std::cout << "String is too long." << std::endl;
                continue;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                std::cout << "Unrecognized keyword at start of '" << buffer << "'." << std::endl;
                continue;
        }

        switch (execute_statement(&statement, table)) {
            case EXECUTE_SUCCESS:
                std::cout << "Executed." << std::endl;
                break;
            case EXECUTE_TABLE_FULL:
                std::cout << "Error: Table full." << std::endl;
                break;
            case EXECUTE_DUPLICATE_KEY:
                std::cout << "Error: Duplicate key." << std::endl;
                break;
        }
    }
}
