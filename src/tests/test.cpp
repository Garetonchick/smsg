#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <pqxx/pqxx>
#include "../util.h"

TEST(MyTestSuite, MyTestCase) {
    std::string json4 = R"({
  "name": "John Doe",
  "age": 30,
  "city": "New York",
  "isStudent": false,
  "hobbies": ["reading", "traveling", "photography"],
  "address": {
    "street": "123 Main St",
    "zipcode": "10001"
  }
})";
    std::ofstream ofs("4.json");
    ofs << json4;
    ofs.close();

    Json::Value test4 = LoadJson("4.json");
    ASSERT_STREQ(test4["name"].asCString(), "John Doe");
    ASSERT_EQ(test4["age"].asInt(), 30);
    ASSERT_STREQ(test4["address"]["street"].asCString(), "123 Main St");

}

TEST(MyTestSuite, DBTest){
    try {
        pqxx::connection c;
        std::cout << "Connected to " << c.dbname() << '\n';

        pqxx::work tx{c};

        for (auto [name, salary] : tx.query<std::string, int>(
            "SELECT name, salary FROM employee ORDER BY name"))
        {
            std::cout << name << " earns " << salary << ".\n";
        }

        for (auto [name, salary] : tx.stream<std::string_view, int>(
            "SELECT name, salary FROM employee"))
        {
            std::cout << name << " earns " << salary << ".\n";
        }

        std::cout << "Doubling all employees' salaries...\n";
        tx.exec0("UPDATE employee SET salary = salary*2");

        int my_salary = tx.query_value<int>(
            "SELECT salary FROM employee WHERE name = 'Me'");
        std::cout << "I now earn " << my_salary << ".\n";

        auto [top_name, top_salary] = tx.query1<std::string, int>(
            R"(
                SELECT name, salary
                FROM employee
                WHERE salary = max(salary)
                LIMIT 1
            )");
        std::cout << "Top earner is " << top_name << " with a salary of "
                  << top_salary << ".\n";

        pqxx::result res = tx.exec("SELECT * FROM employee");
        std::cout << "Columns:\n";
        for (pqxx::row_size_type col = 0; col < res.columns(); ++col)
            std::cout << res.column_name(col) << '\n';

        std::cout << "Making changes definite: ";
        tx.commit();
        std::cout << "OK.\n";
    } catch(...) {
        // ok
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
