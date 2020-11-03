#include "VocabQuiz.hpp"


int main() {
    try {
        static mongocxx::instance instance{};
        //establish connection to db
        Database db("projects", "personalDict"); //this will store the words the user has entered
        //this will store all the words the program processes
        //to cover for those times the API is unresponsive due to too many requests
        Database all_words("projects", "allDict");

        std::cout << "Connected to dbs successfully\n";


        int choice = 0;
        std::string word;

        //basic menu for now
        while (true) {
            std::cout << "(1) Start quiz\n(2) Add word\n(3) View word list\n(4) Delete word\n(5) Exit\n\n";
            std::cin >> choice;
            if (choice == 5) {
                break;
            } else if (choice == 1) {
                //    std::map<std::string, json> m = j.get<std::map <std::string, json>>();

                //start a new quizx
            } else if (choice == 2) {
                std::cin.ignore();
                std::cout << "What word would you like to add to your dictionary? ";
                if (!getline(std::cin, word)) exit(EXIT_FAILURE);
                json result = web::getDefinitions(word);

                if (!result.empty()) {
                    web::prettyPrint(result); //TODO: come back and add the ability to strip the definition of html tags
                    int def_num = 0;
                    std::cout << "Which definition would you like to add? (0) to skip: ";
                    std::cin >> def_num;

                    if (def_num > 0 && def_num < g_max_entries) {
                        //store the word to both dbs

                        if (db.documentExists(result[def_num -1]))
                        {
                            std::cout << "That word/definition combination already exists in the database\n\n";
                        } else {
                            db.insertDocument(result[def_num - 1]);
                            all_words.insertDocument(result[def_num - 1]);
                            std::cout << "Word has been added to dictionary.\n\n" << std::endl;
                        }
                    }
                }
            } else if (choice == 3) {
                //db.
            }
        }
    } catch(const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}