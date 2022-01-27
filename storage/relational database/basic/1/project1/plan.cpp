#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "fmt/core.h"
#include "SQLParser.h"

namespace plan {

enum Type {
    nullType,
    boolType,
    intType,
    floatType,
    strType,
};

class Val {
public:
    friend Val operator+(const Val &lhs, const Val &rhs);
    friend Val operator-(const Val &lhs, const Val &rhs);
    friend bool operator==(const Val &lhs, const Val &rhs);
    friend bool operator!=(const Val &lhs, const Val &rhs);
    friend bool operator<(const Val &lhs, const Val &rhs);
    friend bool operator<=(const Val &lhs, const Val &rhs);
    friend bool operator>(const Val &lhs, const Val &rhs);
    friend bool operator>=(const Val &lhs, const Val &rhs);
    friend Val operator&&(const Val &lhs, const Val &rhs);
    friend Val operator||(const Val &lhs, const Val &rhs);
    friend Val operator-(const Val &val);
    friend Val operator!(const Val &val);
    friend std::ostream &operator<<(std::ostream &os, const Val &val);

    Type type;
    bool boolVal {false};
    int intVal {0};
    float floatVal {0};
    std::string strVal;

    Val() : type(nullType) {}
    Val(bool val) : type(boolType), boolVal(val) {}
    Val(int val) : type(intType), intVal(val) {}
    Val(float val) : type(floatType), floatVal(val) {}
    Val(std::string val) : type(strType), strVal(std::move(val)) {}

    operator bool() const;
    operator int() const;
    operator float() const;
    operator std::string() const;

    std::string typeStr() const;
    std::string valStr() const;
    std::string repr() const;
};

Val operator+(const Val &lhs, const Val &rhs) {
    if (lhs.type != rhs.type) {
        throw std::logic_error(fmt::format("different type for {} and {}", lhs.repr(), rhs.repr()));
    }
    switch (lhs.type) {
        case nullType: throw std::logic_error(fmt::format("{} not support +", lhs.typeStr()));
        case boolType: throw std::logic_error(fmt::format("{} not support +", lhs.typeStr()));
        case intType: return lhs.intVal + rhs.intVal;
        case floatType: return lhs.floatVal + rhs.floatVal;
        case strType: return lhs.strVal + rhs.strVal;
    }
}

Val operator-(const Val &lhs, const Val &rhs) {
    if (lhs.type != rhs.type) {
        throw std::logic_error(fmt::format("different type for {} and {}", lhs.repr(), rhs.repr()));
    }
    switch (lhs.type) {
        case nullType: throw std::logic_error(fmt::format("{} not support -", lhs.typeStr()));
        case boolType: throw std::logic_error(fmt::format("{} not support -", lhs.typeStr()));
        case intType: return lhs.intVal - rhs.intVal;
        case floatType: return lhs.floatVal - rhs.floatVal;
        case strType: return lhs.strVal - rhs.strVal;
    }
}

bool operator==(const Val &lhs, const Val &rhs) {
    if (lhs.type != rhs.type) {
        throw std::logic_error(fmt::format("different type for {} and {}", lhs.repr(), rhs.repr()));
    }
    switch (lhs.type) {
        case nullType: return true;
        case boolType: return lhs.boolVal == rhs.boolVal;
        case intType: return lhs.intVal == rhs.intVal;
        case floatType: return lhs.floatVal == rhs.floatVal;
        case strType: return lhs.strVal == rhs.strVal;
    }
}

bool operator!=(const Val &lhs, const Val &rhs) {
    return !(lhs == rhs);
}

bool operator<(const Val &lhs, const Val &rhs) {
    if (lhs.type != rhs.type) {
        throw std::logic_error(fmt::format("different type for {} and {}", lhs.repr(), rhs.repr()));
    }
    switch (lhs.type) {
        case nullType: throw std::logic_error(fmt::format("{} not support <", lhs.typeStr()));
        case boolType: throw std::logic_error(fmt::format("{} not support <", lhs.typeStr()));
        case intType: return lhs.intVal < rhs.intVal;
        case floatType: return lhs.floatVal < rhs.floatVal;
        case strType: return lhs.strVal < rhs.strVal;
    }
}

bool operator<=(const Val &lhs, const Val &rhs) {
    if (lhs.type != rhs.type) {
        throw std::logic_error(fmt::format("different type for {} and {}", lhs.repr(), rhs.repr()));
    }
    switch (lhs.type) {
        case nullType: throw std::logic_error(fmt::format("{} not support <=", lhs.typeStr()));
        case boolType: throw std::logic_error(fmt::format("{} not support <=", lhs.typeStr()));
        case intType: return lhs.intVal <= rhs.intVal;
        case floatType: return lhs.floatVal <= rhs.floatVal;
        case strType: return lhs.strVal <= rhs.strVal;
    }
}

bool operator>(const Val &lhs, const Val &rhs) {
    if (lhs.type != rhs.type) {
        throw std::logic_error(fmt::format("different type for {} and {}", lhs.repr(), rhs.repr()));
    }
    switch (lhs.type) {
        case nullType: throw std::logic_error(fmt::format("{} not support >", lhs.typeStr()));
        case boolType: throw std::logic_error(fmt::format("{} not support >", lhs.typeStr()));
        case intType: return lhs.intVal > rhs.intVal;
        case floatType: return lhs.floatVal > rhs.floatVal;
        case strType: return lhs.strVal > rhs.strVal;
    }
}

bool operator>=(const Val &lhs, const Val &rhs) {
    if (lhs.type != rhs.type) {
        throw std::logic_error(fmt::format("different type for {} and {}", lhs.repr(), rhs.repr()));
    }
    switch (lhs.type) {
        case nullType: throw std::logic_error(fmt::format("{} not support >=", lhs.typeStr()));
        case boolType: throw std::logic_error(fmt::format("{} not support >=", lhs.typeStr()));
        case intType: return lhs.intVal >= rhs.intVal;
        case floatType: return lhs.floatVal >= rhs.floatVal;
        case strType: return lhs.strVal >= rhs.strVal;
    }
}

Val operator&&(const Val &lhs, const Val &rhs) {
    if (lhs.type != rhs.type) {
        throw std::logic_error(fmt::format("different type for {} and {}", lhs.repr(), rhs.repr()));
    }
    if (lhs.type != boolType) {
        throw std::logic_error(fmt::format("{} not support &&", lhs.typeStr()));
    }
    return lhs.boolVal && rhs.boolVal;
}

Val operator||(const Val &lhs, const Val &rhs) {
    if (lhs.type != rhs.type) {
        throw std::logic_error(fmt::format("different type for {} and {}", lhs.repr(), rhs.repr()));
    }
    if (lhs.type != boolType) {
        throw std::logic_error(fmt::format("{} not support ||", lhs.typeStr()));
    }
    return lhs.boolVal || rhs.boolVal;
}

Val operator-(const Val &val) {
    switch (val.type) {
        case nullType: throw std::logic_error(fmt::format("{} not support -", val.typeStr()));
        case boolType: throw std::logic_error(fmt::format("{} not support -", val.typeStr()));
        case intType: return -val.intVal;
        case floatType: return -val.floatVal;
        case strType: return -val.strVal;
    }
}

Val operator!(const Val &val) {
    if (val.type != boolType) {
        throw std::logic_error(fmt::format("{} not support !", val.typeStr()));
    }
    return !val.boolVal;
}

std::ostream &operator<<(std::ostream &os, const Val &val) {
    return os << val.repr();
}

Val::operator bool() const {
    if (type != boolType) {
        throw std::logic_error(fmt::format("{} is not bool", typeStr()));
    }
    return boolVal;
}

Val::operator int() const {
    if (type != intType) {
        throw std::logic_error(fmt::format("{} is not int", typeStr()));
    }
    return intVal;
}

Val::operator float() const {
    if (type != floatType) {
        throw std::logic_error(fmt::format("{} is not float", typeStr()));
    }
    return floatVal;
}

Val::operator std::string() const {
    if (type != strType) {
        throw std::logic_error(fmt::format("{} is not str", typeStr()));
    }
    return strVal;
}

std::string Val::typeStr() const {
    switch (type) {
        case nullType: return "null";
        case boolType: return "bool";
        case intType: return "int";
        case floatType: return "float";
        case strType: return "str";
    }
}

std::string Val::valStr() const {
    switch (type) {
        case nullType: return "null";
        case boolType: return std::to_string(boolVal);
        case intType: return std::to_string(intVal);
        case floatType: return std::to_string(floatVal);
	    case strType: return strVal;
    }
}

std::string Val::repr() const {
    return "{ " + fmt::format("type: {}, value: {}", typeStr(), valStr()) + " }";
}

class Row {
public:
    Row(std::vector<Val> vals_ = {}) : vals(std::move(vals_)) {}

    Val &operator[](std::size_t i);
    const Val &operator[](std::size_t i) const;

    size_t size() const;

private:
    std::vector<Val> vals;
};

Val &Row::operator[](std::size_t i) {
    return vals[i];
}

const Val &Row::operator[](std::size_t i) const {
    return vals[i];
}

size_t Row::size() const {
    return vals.size();
}

class Table {
public:
    friend std::ostream &operator<<(std::ostream &os, const Table &table);

    std::vector<std::string> names;
    std::vector<Type> types;

    Table(std::vector<std::string> names_, std::vector<Type> types_) :
        names(std::move(names_)), types(std::move(types_)) { constructNameMap(); }
    Table(std::vector<std::string> names_, std::vector<Type> types_, std::vector<Row> rows_) :
        names(std::move(names_)), types(std::move(types_)), rows(std::move(rows_)) { constructNameMap(); }
    Table(std::vector<std::string> names_, std::vector<Type> types_, const std::vector<std::vector<Val>> &rows_) :
        names(std::move(names_)), types(std::move(types_)) { constructRow(rows_); constructNameMap(); }

    Row &operator[](std::size_t i);
    const Row &operator[](std::size_t i) const;

    std::vector<Row>::iterator begin();
    std::vector<Row>::iterator end();
    std::vector<Row>::const_iterator begin() const;
    std::vector<Row>::const_iterator end() const;

    void insert(const Row &row);
    void update(std::size_t i, const std::string &name, const Val &val);
    void update(std::size_t i, std::size_t j, const Val &val);
    void delete0(std::size_t i);
    std::size_t getColIdxByName(const std::string &) const;
    std::size_t size() const;

private:
    std::map<std::string, std::size_t> nameMap;
    std::vector<Row> rows;

    void constructRow(const std::vector<std::vector<Val>> &rows_);
    void constructNameMap();
};

std::ostream &operator<<(std::ostream &os, const Table &table) {
    std::vector<std::size_t> widths;
    for (std::size_t j = 0; j < table.names.size(); j++) {
        std::size_t width = table.names[j].size();
        for (std::size_t i = 0; i < table.size(); i++) {
            width = std::max(width, table[i][j].valStr().size());
        }
        widths.push_back(width);
    }

    for (std::size_t j = 0; j < table.names.size(); j++) {
        os << std::right << '|' << std::setw(static_cast<int>(widths[j])) << std::setfill(' ') << table.names[j];
    }
    os << '|';

    for (std::size_t i = 0; i < table.size(); i++) {
        os << std::endl;
        for (std::size_t j = 0; j < table.names.size(); j++) {
            os << std::right << '|' << std::setw(static_cast<int>(widths[j])) << std::setfill(' ')
                << table[i][j].valStr();
        }
        os << '|';
    }

    return os;
}

Row &Table::operator[](std::size_t i) {
    return rows[i];
}

const Row &Table::operator[](std::size_t i) const {
    return rows[i];
}

std::vector<Row>::iterator Table::begin() {
    return rows.begin();
}

std::vector<Row>::const_iterator Table::begin() const {
    return rows.begin();
}

std::vector<Row>::iterator Table::end() {
    return rows.end();
}

std::vector<Row>::const_iterator Table::end() const {
    return rows.end();
}

void Table::insert(const Row &row) {
    rows.emplace_back(row);
}

void Table::update(std::size_t i, const std::string &name, const Val &val) {
    std::size_t j = getColIdxByName(name);
    rows[i][j] = val;
}

void Table::update(std::size_t i, std::size_t j, const Val &val) {
    rows[i][j] = val;
}

void Table::delete0(std::size_t i) {
    rows.erase(rows.begin() + static_cast<int>(i));
}

std::size_t Table::getColIdxByName(const std::string &name) const {
    return nameMap.at(name);
}

std::size_t Table::size() const {
    return rows.size();
}

void Table::constructRow(const std::vector<std::vector<Val>> &rows_) {
    for (const std::vector<Val> &row_: rows_) {
        rows.emplace_back(row_);
    }
}

void Table::constructNameMap() {
    for (std::size_t i = 0; i < names.size(); i++) {
        nameMap[names[i]] = i;
    }
}

class DB {
public:
    DB(std::map<std::string, Table> tables_) : tables(std::move(tables_)) {}

    Table &operator[](const std::string &name);
    const Table &operator[](const std::string &name) const;

private:
    std::map<std::string, Table> tables;
};

Table &DB::operator[](const std::string &name) {
    return tables.at(name);
}

const Table &DB::operator[](const std::string &name) const {
    return tables.at(name);
}

Val evalExpr(const hsql::Expr *expr, const DB &db, const Table &table, Row row) {
    if (expr->type == hsql::kExprLiteralNull) {
        return {};
    }
    if (expr->type == hsql::kExprLiteralInt) {
        return static_cast<int>(expr->ival);
    }
    if (expr->type == hsql::kExprLiteralFloat) {
        return static_cast<float>(expr->fval);
    }
    if (expr->type == hsql::kExprLiteralString) {
        return expr->name;
    }
    if (expr->type == hsql::kExprColumnRef) {
        std::string colName = expr->name;
        std::size_t colIdx = table.getColIdxByName(colName);
        return row[colIdx];
    }
    if (expr->type == hsql::kExprOperator) {
        if (expr->opType == hsql::kOpPlus) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left + right;
        }
        if (expr->opType == hsql::kOpMinus) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left - right;
        }
        if (expr->opType == hsql::kOpEquals) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left == right;
        }
        if (expr->opType == hsql::kOpNotEquals) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left != right;
        }
        if (expr->opType == hsql::kOpLess) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left < right;
        }
        if (expr->opType == hsql::kOpLessEq) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left <= right;
        }
        if (expr->opType == hsql::kOpGreater) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left > right;
        }
        if (expr->opType == hsql::kOpGreaterEq) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left >= right;
        }
        if (expr->opType == hsql::kOpAnd) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left && right;
        }
        if (expr->opType == hsql::kOpOr) {
            Val left = evalExpr(expr->expr, db, table, row);
            Val right = evalExpr(expr->expr2, db, table, row);
            return left || right;
        }
        if (expr->opType == hsql::kOpUnaryMinus) {
            Val val = evalExpr(expr->expr, db, table, row);
            return -val;
        }
        if (expr->opType == hsql::kOpNot) {
            Val val = evalExpr(expr->expr, db, table, row);
            return !val;
        }
        if (expr->opType == hsql::kOpIsNull) {
            Val val = evalExpr(expr->expr, db, table, row);
            return val.type == nullType;
        }
    }
    return {};
}

class Operator {
public:
    virtual Table process(const DB &db, Table table) = 0;
};

class FilterOperator: public Operator {
public:
    FilterOperator(hsql::Expr *expr_) : expr(expr_) {}

    Table process(const DB &db, Table table) override;

private:
    hsql::Expr *expr;
};

Table FilterOperator::process(const DB &db, Table table) {
    Table table1(table.names, table.types);
    for (const Row &row: table) {
        Val val = evalExpr(expr, db, table, row);
        if (val) {
            table1.insert(row);
        }
    }
    return table1;
}

class SortOperator: public Operator {
public:
    SortOperator(std::vector<hsql::OrderDescription *> * orderDescriptions_) : orderDescriptions(orderDescriptions_) {}

    Table process(const DB &db, Table table) override;

private:
    std::vector<hsql::OrderDescription *> *orderDescriptions;
};

Table SortOperator::process(const DB &db, Table table) {
    Table table1(table);
    std::sort(table1.begin(), table1.end(), [this, db, table1](const Row& row1, const Row& row2) {
       for (const hsql::OrderDescription *orderDescription: *orderDescriptions) {
           Val val1 = evalExpr(orderDescription->expr, db, table1, row1);
           Val val2 = evalExpr(orderDescription->expr, db, table1, row2);
           if (orderDescription->type == hsql::kOrderAsc) {
               if (val1 < val2) {
                   return true;
               }
               if (val1 > val2) {
                   return false;
               }
           }
           if (orderDescription->type == hsql::kOrderDesc) {
               if (val1 < val2) {
                   return false;
               }
               if (val1 > val2) {
                   return true;
               }
           }
       }
       return true;
    });
    return table1;
}

class LimitOperator: public Operator {
public:
    LimitOperator(hsql::LimitDescription *limit_) : limit(limit_) {}

    Table process(const DB &db, Table table) override;

private:
    hsql::LimitDescription *limit;
};

Table LimitOperator::process(const DB &db, Table table) {
    Val limitVal;
    if (limit->limit != nullptr) {
        limitVal = evalExpr(limit->limit, db, table, {});
    } else {
        limitVal = static_cast<int>(table.size());
    }
    Val offsetVal;
    if (limit->offset != nullptr) {
        offsetVal = evalExpr(limit->offset, db, table, {});
    } else {
        offsetVal = 0;
    }

    std::size_t begin = static_cast<int>(offsetVal);
    std::size_t end = std::min<std::size_t>(table.size(), static_cast<int>(offsetVal + limitVal));
    Table table1(table.names, table.types);
    for (std::size_t i = begin; i < end; i += 1) {
        table1.insert(table[i]);
    }
    return table1;
}

class ProjectionOperator: public Operator {
public:
    ProjectionOperator(std::vector<hsql::Expr *> *selectList_) : selectList(selectList_) {}

    Table process(const DB &db, Table table) override;

private:
    std::vector<hsql::Expr *> *selectList;
};

Table ProjectionOperator::process(const DB &db, Table table) {
    std::vector<Val> row1;
    for (const Type &type: table.types) {
        switch (type) {
            case nullType: row1.emplace_back(Val{}); break;
            case boolType: row1.emplace_back(false); break;
            case intType: row1.emplace_back(1); break;
            case floatType: row1.emplace_back(1.0f); break;
            case strType: row1.emplace_back(); break;
        }
    }
    Table table1 = {
            table.names,
            table.types,
            {Row(row1)},
    };

    std::vector<std::string> names2;
    std::vector<Type> types2;
    for (std::size_t i = 0; i < selectList->size(); i++) {
        names2.emplace_back("a" + std::to_string(i));
        Val val = evalExpr((*selectList)[i], db, table1, table1[0]);
        types2.emplace_back(val.type);
    }

    Table table2(names2, types2);
    for (const Row &row: table) {
        std::vector<Val> row2;
        for (const hsql::Expr *expr: *selectList) {
            Val val = evalExpr(expr, db, table, row);
            row2.emplace_back(val);
        }
        table2.insert(row2);
    }
    return table2;
}

Table evalSelect(const hsql::SelectStatement *sm, const DB &db) {
    std::string name;
    if (sm->fromTable->type == hsql::kTableName) {
        name = sm->fromTable->name;
    }

    Table table = db[name];
    if (sm->whereClause != nullptr) {
        table = FilterOperator(sm->whereClause).process(db, table);
    }
    if (sm->order != nullptr) {
        table = SortOperator(sm->order).process(db, table);
    }
    if (sm->limit != nullptr) {
        table = LimitOperator(sm->limit).process(db, table);
    }
    return ProjectionOperator(sm->selectList).process(db, table);
}

void eval(const hsql::SQLStatement *sm, const DB &db) {
    if (sm->type() == hsql::kStmtSelect) {
        const hsql::SelectStatement *sm1 = static_cast<const hsql::SelectStatement *>(sm);
        Table table = evalSelect(sm1, db);
        std::cout << table << std::endl;
    }
}

}
