#include <gtest/gtest.h>
#include <iostream>
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


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
