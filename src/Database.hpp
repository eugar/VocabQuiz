//
// Created by eugene on 2020-10-27.
//

#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>


#include "../lib/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;


class Database {
public:
    Database(std::string database, std::string collection);
    void insertDocument(json j);
    int documentExists(json j);
    std::vector<json> printDocs();

    mongocxx::cursor all() {return coll.find({}); } //debugging

private:
    mongocxx::database db;
    mongocxx::collection coll;
    mongocxx::client client;
};


#endif //DATABASE_HPP
