#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */

int get_length(const char* word){
	for(int i = 0; ; i++)
		if(word[i] == '\0')
			return i;
}

bool valid_step(const char *source, const char* target){
	int source_length = get_length(source);
	int target_length = get_length(target);
	if(source_length != target_length)
		return false;

	if(!dictionary_search(target))
		return false;

	bool single_letter_diff = false;
	for(int i = 0; i < source_length; i++){
		if(source[i] != target[i]){
			if(single_letter_diff)
				return false;
			single_letter_diff = true;
		}
	}
	if(!single_letter_diff)
		return false;

	return true;
}

int get_chain_length(const char *chain[MAX_STEPS]){
	int chain_length = 0;
	for(; chain[chain_length] != NULL; chain_length++);
	return chain_length;
}

bool display_chain(const char *chain[MAX_STEPS], ostream& os){
	int chain_length = get_chain_length(chain);

	if(!(os << chain[0] << endl))
		return false;
	for(int link = 1; link < chain_length - 1; link++){
		for(const char* ch_ptr = chain[link]; *ch_ptr != '\0'; ch_ptr++)
			if(!(os << static_cast<char>(*ch_ptr + 32)))
				return false;
		if(!(os << endl))
			return false;
	}
	if(!(os << chain[chain_length-1] << endl))
		return false;
	return true;
}

bool valid_chain(const char* chain[MAX_STEPS]){
	int chain_length = get_chain_length(chain);
	for(int link = 1; link < chain_length - 1; link++){
		for(int prev_link = 0; prev_link < link; prev_link++)
			if(strcmp(chain[prev_link], chain[link]) == 0)
				return false;

		if(!valid_step(chain[link-1], chain[link]))
			return false;
	}

	return true;
}

bool find_chain(const char* source, const char* target, const char* answer[100],
				int steps, int depth){
	if( strcmp(source, target) == 0 ){
		return true;
	}

	if(depth + 1 >= steps)
		return false;

	char possible_word[20];
	for(int index = 0; source[index] != '\0'; index++){
		strcpy(possible_word, source);
		for(int 
	}

}
