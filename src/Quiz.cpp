//
// Created by eugene on 2020-10-27.
//

#include "Quiz.hpp"

Quiz::Quiz()
{
    int i = 1;
    //stuff that happens when new quiz object is created will go here
    //like grabbing a list of words from db, etc.

}

void Quiz::start()
{
    int num_words = 0;
    int num_correct = 0;
    //maybe map would be better here
    //std::vector<std::string> quizWords;

    std::cout << "How many words would you like to quiz yourself on? ";
    std::cin >> num_words;

    for (int i = 0; i < num_words; i++)
    {

    }
}

