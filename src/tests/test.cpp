#include <gtest/gtest.h>
#include <string>
#include <fstream>
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}