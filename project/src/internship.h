#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>


namespace internship {
    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount);
    long getDaysBetweenDates(std::string date1, std::string date2);
    bool versionComparator(nlohmann::json j1, nlohmann::json j2);
    std::vector<nlohmann::json_abi_v3_11_2::json> findLongestSupportedOS(const std::string jsonFileName, int elementsCount);
}