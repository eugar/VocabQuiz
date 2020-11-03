//
// Created by eugene on 2020-10-27.
//

#include "Database.hpp"



Database::Database(std::string database, std::string collection) {
    //connect to a running mongodb instance
    this->client = {mongocxx::uri{"mongodb://localhost:27017"}};
    //access the project database and dictionary collection
    this->db = client[database];
     this-> coll = db[collection];
}

void Database::insertDocument(json j)
{


    auto doc = bsoncxx::builder::basic::document{};

//    std::map<std::string, json> m = j.get<std::map <std::string, json>>();
    //std::cout << m.at("word") << " " << m.at("text") << std::endl;
    bsoncxx::document::value val = bsoncxx::from_json(j.dump());

    auto result = this->coll.insert_one(std::move(val));
}

int Database::documentExists(json j) {
    //depending on the word id that is returned by the API here. since we only use ahd dictionary we know all words will have one
    //this is better than searching for the word since we can have one word with multiple definitions in the dbs
    if (this->coll.find_one(bsoncxx::builder::stream::document{} << "id" << j["id"].get<std::string>() << bsoncxx::builder::stream::finalize)) {
        return 1;
    } else {
        return 0;
    }
}

void Database::printDB() {
    mongocxx::cursor list = this->all();

    //for (<bsoncxx::BSO)
}