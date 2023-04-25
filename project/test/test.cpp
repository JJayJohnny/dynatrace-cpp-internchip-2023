#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "../src/internship.h"

TEST(DateDifferenceTest, HandlesPositiveInput){
    EXPECT_EQ(internship::getDaysBetweenDates("2020-10-11", "2020-11-10"), 31);
    EXPECT_EQ(internship::getDaysBetweenDates("2020-10-11", "2020-10-12"), 2);
    EXPECT_EQ(internship::getDaysBetweenDates("2020-10-12", "2020-10-10"), 3);
    EXPECT_EQ(internship::getDaysBetweenDates("2020-10-12", "2020-10-12"), 1);
}

TEST(DateDifferenceTest, HandlesWrongData){ 
        try{
            internship::getDaysBetweenDates("2020-10-11", "not a date");
            FAIL();
        }
        catch(std::runtime_error const &e){
            EXPECT_EQ( std::string("Error parsing dates"), e.what() );
        }catch(...){
            FAIL();
        }
}

TEST(VersionComparatorTest, HandlesPositiveInput){
    nlohmann::json_abi_v3_11_2::json j1 = {
        {"osName", "Windows"},
        {"days", 20}
    };
    nlohmann::json_abi_v3_11_2::json j2 = {
        {"osName", "Linux"},
        {"days", 10}
    };
    nlohmann::json_abi_v3_11_2::json j3 = {
        {"osName", "Linux2"},
        {"days", 10}
    };
    EXPECT_TRUE(internship::versionComparator(j1, j2));
    EXPECT_FALSE(internship::versionComparator(j2, j1));
    EXPECT_FALSE(internship::versionComparator(j2, j3));
}

TEST(VersionComparatorTest, HandlesWrongData){
    nlohmann::json_abi_v3_11_2::json j1 = {
        {"osName", "Windows"}
    };
    nlohmann::json_abi_v3_11_2::json j2 = {
        {"osName", "Linux"},
        {"days", 10}
    };
    nlohmann::json_abi_v3_11_2::json j3 = {
        {"osName", "Linux"},
        {"days", "not a number"}
    };

    try{
        internship::versionComparator(j1, j2);
        FAIL();
    }catch(std::runtime_error const &e){
        EXPECT_EQ( std::string("Days field is nan"), e.what() );
    }catch(...){
        FAIL();
    }
    try{
        internship::versionComparator(j3, j2);
        FAIL();
    }catch(std::runtime_error const &e){
        EXPECT_EQ( std::string("Days field is nan"), e.what() );
    }catch(...){
        FAIL();
    }
}

TEST(findLongestSupportedOSTest, HandlesPositiveInput){
    
    std::vector<nlohmann::json_abi_v3_11_2::json> result = internship::findLongestSupportedOS("test/test.json", 3);
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0]["osName"].get<std::string>(), "operatingSystem1");
    EXPECT_EQ(result[0]["cycle"].get<std::string>(), "9");
    EXPECT_EQ(result[0]["days"], 6);
    EXPECT_EQ(result[1]["osName"].get<std::string>(), "operatingSystem2");
    EXPECT_EQ(result[1]["cycle"].get<std::string>(), "9");
    EXPECT_EQ(result[1]["days"], 4);
    EXPECT_EQ(result[2]["osName"].get<std::string>(), "operatingSystem1");
    EXPECT_EQ(result[2]["cycle"].get<std::string>(), "8");
    EXPECT_EQ(result[2]["days"], 1);

}

TEST(findLongestSupportedOSTest, HandlesNegativeInput){
    std::vector<nlohmann::json_abi_v3_11_2::json> result = internship::findLongestSupportedOS("test/test.json", 10);
    EXPECT_EQ(result.size(), 3);
    result = internship::findLongestSupportedOS("test/test.json", 0);
    EXPECT_EQ(result.size(), 0);
    result = internship::findLongestSupportedOS("test/test.json", -5);
    EXPECT_EQ(result.size(), 0);
}

//TODO tests for findLongestSupportedOS function

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
