cmake_minimum_required(VERSION 3.13)
project(VocabQuiz CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
find_package(curl REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

add_executable(VocabQuiz VocabQuiz.cpp VocabQuiz.hpp Quiz.cpp Quiz.hpp Database.cpp Database.hpp WebDict.cpp WebDict.hpp)


target_link_libraries(VocabQuiz PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(VocabQuiz PRIVATE ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(VocabQuiz PRIVATE ${LIBBSONCXX_LIBRARIES})
target_link_libraries(VocabQuiz PRIVATE ${CURL_LIBRARIES})
