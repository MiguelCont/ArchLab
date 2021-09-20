#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c){
	if(c == '\t' || c == ' '){
		return true;
	}
	return false;
}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c){
	if(c == '\0'){
		return false;
	}
	return !delim_character(c);
}

/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char* str){
	char* copy = (char*) malloc(sizeof(str));
	copy = str;
	//Goes until it finds a whitespace characted
	while(non_delim_character(*copy) ){
		copy++;
	}
	//goes until whitespace ends
	while( delim_character(*copy) ) {
		copy++;
	}
	return copy++; //since the last loop ends at the final whitespace we need to more up one
	

    }

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){

}
// counts the number of words or tokens
int count_tokens(char* str){


}
/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char *copy_str(char *inStr, short len){

}

char** tokenize(char* str){
}


void print_all_tokens(char** tokens){
}
int main(){
	return 0;
}
