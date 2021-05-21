/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    vector<std::string> word_list;

    ifstream wordsFile(word_list_fname);
    std::string word;
    if (wordsFile.is_open()){
      while (getline(wordsFile, word)){
        word_list.push_back(word);
      }
    }

    for (auto word : word_list){
       std::string word_original = word; //erase will change the orginial word, so we have to copy the original one
       std::string first_removed = word.substr(1, word.size()-1);
       std::string second_removed = word.erase(1, 1);
       if (d.homophones(word, first_removed) && d.homophones(word, second_removed)){
           ret.push_back(std::make_tuple(word_original, first_removed, second_removed));
       }       
    }   

    return ret;
}
