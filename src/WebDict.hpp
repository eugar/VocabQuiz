//
// Created by eugene on 2020-10-27.
//

#ifndef WEBDICT_HPP
#define WEBDICT_HPP

#include <curl/curl.h>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include "../lib/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;
const u_short g_max_entries = 8;


namespace web {
    size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);
    json getDefinitions(std::string word);
    int prettyPrint(json entry_data);
    void removeEmpties(json& entry_data);
    bool keyExists(const json& j, const std::string& key);
}


#endif //WEBDICT_HPP
