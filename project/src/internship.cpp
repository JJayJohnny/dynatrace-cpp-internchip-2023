#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include <date/date.h>
#include <nlohmann/json.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>


#include "internship.h"

using json = nlohmann::json;
using namespace boost;

namespace internship {

    long getDaysBetweenDates(std::string date1, std::string date2){
        try{
            gregorian::date d1(gregorian::from_simple_string(date1));
            gregorian::date d2(gregorian::from_simple_string(date2));
            gregorian::date_period dp(d1, d2);
            return abs(dp.length().days())+1;       
        }catch(...){
            throw std::runtime_error("Error parsing dates");
        }    
    }

    bool versionComparator(json j1, json j2){
        try{
            long d1 = j1["days"].get<long>();
            long d2 = j2["days"].get<long>();
            return d1 > d2;
        }catch(...){
            throw std::runtime_error("Days field is nan");
        }
    }

    std::vector<json> findLongestSupportedOS(const std::string jsonFileName, int elementsCount){
        std::ifstream f(jsonFileName);
        json data = json::parse(f);

        std::vector<json> products;

        for(const auto& [id, product] : data.items()) {
            if(product["os"] == true){
                if(!product.contains("name") || !product["name"].is_string() ||  product["name"] == "")
                            continue;
                for(json version : product["versions"]){
                    json j;  
                    try{
                        if(!version.contains("cycle") || !version["cycle"].is_string() || version["cycle"] == "")
                            continue;
                        j["osName"] = product["name"];
                        j["cycle"]=version["cycle"];
                        j["days"]=getDaysBetweenDates(version["releaseDate"], version["eol"]);
                    }catch(...){
                        continue;
                    }
                    products.push_back(j);
                }
            }
        }
        sort(products.begin(), products.end(), [](const json j1, const json j2){
            return versionComparator(j1, j2);
        });
        
        if(elementsCount < 0)
            elementsCount = 0;
        if(elementsCount > products.size())
            elementsCount = products.size();
        
        std::vector<json> result = {products.begin(), products.begin()+elementsCount};

        return result;
    }

    void internshipTask(const std::string jsonFileName, int elementsCount){
        std::vector<json> products = findLongestSupportedOS(jsonFileName, elementsCount);

        for(int i=0; i<products.size(); i++){
            json j = products[i];
            std::cout<<j["osName"].get<std::string>()<<" "<<j["cycle"].get<std::string>()<<" "<<j["days"]<<"\n";
        }
    }

    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount) {
        // put the call to your solution here
        internshipTask(jsonFileName, elementsCount);
    }
}