/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

//helper function to identify the anagram
bool AnagramDict::isAnagram(string word1, string word2){
   std::sort(word1.begin(), word1.end());
   std::sort(word2.begin(), word2.end());

   if (word1.compare(word2) == 0) return true;
   else return false;

}


/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{

    /* Your code goes here! */
    vector<string> word_list;
    
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
       while (getline(wordsFile, word)) {
          word_list.push_back(word);
       }
     }

    for (size_t i = 0; i < word_list.size(); i++){
       for (size_t j = 0; j < word_list.size(); j++){
         if ( isAnagram (word_list[i], word_list[j]) && dict.find(word_list[j]) == dict.end()) {
            dict[word_list[i]].push_back(word_list[j]);
         }
       }
    }
 
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (size_t i = 0; i < words.size(); i++){
       for (size_t j = 0; j < words.size(); j++){
         if ( isAnagram (words[i], words[j]) && dict.find(words[j]) == dict.end()) {
            dict[words[i]].push_back(words[j]);
         }
       }
    }

}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    if (dict.find(word) == dict.end()) return vector<string>();
    return dict.at(word);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> result;

    for (auto & word : dict){
       if (word.second.size() > 1) {result.push_back(word.second);}
    }
    return result;

    //return vector<vector<string>>();
}
