//
// Created by eugene  on 2020-10-27.
//

#include "WebDict.hpp"

size_t web::writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data)
{
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

json web::getDefinitions(const std::string word)
{
    const std::string base_URL("http://api.wordnik.com/v4/word.json/");
    std::string api_key = ""; //TODO: add check here - if string is empty, tell user to enter api key
    std::string lookup_URL = base_URL + word + "/" +
                            "definitions?limit=" + std::to_string(g_max_entries) + "&includeRelated=false&sourceDictionaries=ahd-legacy&useCanonical=false&includeTags=false&api_key=" +
                            api_key;
    CURLcode res;
    std::string content;
    std::string header;
    long http_code = 0;
    json result;


    CURL *curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, lookup_URL.c_str()); //set the URL
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);//only try IPv4 (speed up DNS resolution time)
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); //follow http redirects
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, web::writeFunction); //set up data handling function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content); //set up data container
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);

        res = curl_easy_perform(curl); //perform the HTTP GET

        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code); //capture the HTTP response code

            if (http_code == 200) { //check that the GET was successful
                std::cout << "\nGot successful response from " << base_URL << std::endl;

                result = json::parse(content);


                //std::cout << result.dump(4) << std::endl;

                std::cout << header << "\n\n" << std::endl;
            } else if (http_code == 429) {
                std::cout << "Too many requests to API" << std::endl;
                std::cout << header << std::endl;
            } else { //some other "unsuccessful" http status code

                std::cout << "\nReceiving response from " << lookup_URL
                    << " was unsuccessful. HTTP response status code: " << http_code << "\n" << std::endl;
            }
        } else {
            std::cout << "curl_easy_perform() failed." << std::endl;
        }
        curl_easy_cleanup(curl); //cleanup
        return result;

    }
    else {
        exit(EXIT_FAILURE);
    }
}

int web::prettyPrint(json entry_data)
{
    int i = 1;

    //std::cout << result.dump(4) << std::endl;

    for (auto j : entry_data) {

        std::string word = "word not found in json";
        std::string pos = "part of speech not found in json";
        std::string def;
        j.at("text").get_to(def); // don't have to check for "text" - already handled by removeEmpties()

        if (keyExists(j, "word")) {
            j.at("word").get_to(word);
        }

        if (keyExists(j, "partOfSpeech")) {
            j.at("partOfSpeech").get_to(pos);

        }
        std::cout << i << ". " << word << " (" << pos << "): " << def << std::endl;
        i++;
    }
    std::cout << "\n\n" << std::endl;
    return i;
}

void web::removeEmpties(json& j)
{
    auto iter = j.begin();

    for (; iter != j.end(); ) {
        if (!keyExists(iter.value(), "text")) {
            iter = j.erase(iter); //make sure we don't go out of bound by traversing this way
        } else {
            ++iter;
        }
    }
//    for (auto iter = entry_data.begin(); iter != entry_data.end(); iter++)
//    {
//        if (!keyExists(iter.value(), "text"))
//            entry_data.erase(iter);
//
//    }
}

bool web::keyExists(const json& j, const std::string& key)
{
    return j.find(key) != j.end();
}