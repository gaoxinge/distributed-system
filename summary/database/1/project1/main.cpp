#include <string>
#include <iostream>

#include "SQLParser.h"
#include "util/sqlhelper.h"

#include "plan.cpp"

int main(int argc, char *argv[]) {
    plan::Table table = {
            {"a", "b"},
            {plan::intType, plan::floatType},
            {
                {1, 2.0f},
                {9, 9.0f},
	            {3, 4.0f},
	            {2, 4.0f},
	            {1, 4.0f},
                {3, 5.0f},
                {6, 7.0f}
            }
    };
    plan::DB db = {{
        {"t", table},
    }};
    std::cout << "====================================" << std::endl;
    std::cout << table << std::endl;

    std::string query = "select a, b from t where a > 1 order by a limit 3 offset 1;";
    hsql::SQLParserResult result;
    hsql::SQLParser::parse(query, &result);

    if (result.isValid()) {
        std::cout << "====================================" << std::endl;
        for (size_t i = 0; i < result.size(); ++i) {
            hsql::printStatementInfo(result.getStatement(i));
        }

        std::cout << "====================================" << std::endl;
        const hsql::SQLStatement *statement = result.getStatement(0);
        eval(statement, db);
    }

    std::cout << "====================================" << std::endl;
    return 0;
}
