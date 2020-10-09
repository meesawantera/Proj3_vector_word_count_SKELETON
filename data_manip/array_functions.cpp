/*
 * functionstocomplete.h
 *
 *  Created on: Sep 10, 2017
 *      Author: Tera Meesawan1
 */
#define ARRAY_FUNCTIONS_H_
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>

#include <vector>
#include "../includes/constants.h"
using namespace constants;
/*============================================================================
 * The following are declarations for functions that I will test
 * Please provide the definitions in the
 * included cpp file, do not erase the stuff I put in there please
 * DO NOT MODIFY THIS FILE, I WILL USE MY OWN COPY
 /============================================================================*/

namespace KP {
//zero out vector that tracks words and their occurrences
void clear(std::vector<constants::entry> &entries) {
	entries.clear();
}

//how many unique words are in the vector
int getSize(std::vector<constants::entry> &entries) {
	return entries.size();
}

//get data at a particular location, if i>size() then get the last value in the vector
//(this is lazy, should throw an exception instead)
std::string getWordAt(std::vector<constants::entry> &entries, int i) {
	if (i > entries.size())
		return entries[entries.size() - 1].word;
	return entries[i].word;
}

int getNumbOccurAt(std::vector<constants::entry> &entries, int i) {
	if (i > entries.size())
		return entries[entries.size() - 1].number_occurences;
	return entries[i].number_occurences;
}

/*Keep track of how many times each token seen*/
void processToken(std::vector<constants::entry> &entries, std::string &token) {
	for (int i = 0; i < entries.size(); i++) {
		if (token == entries[i].word) {
			entries[i].number_occurences++;
			return;
		}
	}
	entry new_word;
	new_word.word = token;
	new_word.number_occurences = 1;
	entries.push_back(new_word);
}

/*take 1 line and extract all the tokens from it
 feed each token to processToken for recording*/
void processLine(std::vector<constants::entry> &entries,std::string &myString){
	std::stringstream wap(myString);
	std::string tempToken;
	while(getline(wap, tempToken, ' ')){
		processToken(entries, tempToken);
	}

}

/*loop through whole file, one line at a time
 * call processLine on each line from the file
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::vector<constants::entry> &entries,
		std::fstream &myfstream) {
	std::string hoe;
	if (myfstream.is_open()==false){
		return false;
	}
	if (myfstream.is_open() == true) {
		while (getline(myfstream, hoe)) {
			KP::processLine(entries, hoe);
		}
	}
	if (myfstream.is_open() == true){
		myfstream.close();
		return true;
	}
}



/*
 * Sort myEntryArray based on so enum value.
 * Please provide a solution that sorts according to the enum
 * The presence of the enum implies a switch statement based on its value
 * See the course lectures and demo project for how to sort a vector of structs
 */
bool upWords(entry wordOne, entry wordTwo){wordOne.word < wordTwo.word;}
bool downWords(entry wordOne, entry wordTwo){wordOne.word > wordTwo.word;}
bool sortNums(entry wordOne, entry wordTwo){wordOne.number_occurences < wordTwo.number_occurences;}

void sort(std::vector<constants::entry> &entries, constants::sortOrder so) {
	switch(so){
	case ASCENDING:
		sort(entries.begin(), entries.end(), upWords);
		break;
	case DESCENDING:
		sort(entries.begin(), entries.end(), downWords);
		break;
	case NUMBER_OCCURRENCES:
		sort(entries.begin(), entries.end(), sortNums);
		break;
	case NONE:
		break;
	}
}
}

