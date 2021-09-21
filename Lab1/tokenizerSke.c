/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
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
	char *copy = (char*) malloc(sizeof(str));
	copy = str;
	if(non_delim_character(*copy))
	    return copy;
	//Goes until it finds a whitespace characted
	while(non_delim_character(*copy) ){
		copy++;
	}
	//goes until whitespace ends
	while( delim_character(*copy) ) {
		copy++;
	}
	return copy++; //since the last loop ends at the final whitespace we need to move up one
    }

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
    char *copy = (char*) malloc(sizeof(str));
	copy = str;
	if(delim_character(*copy))
	    return copy;
	//Goes until it finds a non-whitespace character
	while(delim_character(*copy) ){
		copy++;
	}
	//goes until non-whitespace characters end
	while( non_delim_character(*copy) ) {
		copy++;
	}
	return copy++; //since the last loop ends at the final non-whitespace character we need to move up one

}
// counts the number of words or tokens
int count_tokens(char* str){
    //makes a copy of the char pointer
    char *copy = (char*) malloc(sizeof(*str));
	copy = str;
	//initializes counter
	int count = 0;
	
	//loops until the pointer points to nothing
	while(*copy != 0){
    	copy = end_word(copy); //points to the end of the first token
    	count++;            // increments since one token is found
    	copy = word_start(copy); // points to the beginning of the next token
	}
	return count;

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
    char *copy = (char*) malloc(sizeof(*inStr) * (len) );
    for(int i =0; i <len;i++){
        //"+i" works the same as [i] when refering to an index in an array
        *(copy+i) = *(inStr+i);
    }
    //adds the zero-terminating part to the end of the pointer
    *(copy+len) = '\0';
    return copy;
} 
char** tokenize(char* str){
    int tokenCount = count_tokens(str);
    char **pointers = (char**) malloc(sizeof(*str) * (tokenCount));
    char *start;
    char *end;
    start = word_start(str); //eliminates any possible whitespace at the beginning of the sentence
    for(int i = 0; i < tokenCount; i++){
        end = end_word(start);
        *(pointers+i)/*token location*/ = copy_str(start, end-start);
        start = word_start(end); //resets pointer to the next word to eliminate whitespace
    }
    return pointers;
}

void print_all_tokens(char** tokens){
    int counter = 0;
    while(*tokens != 0){
        printf("Tokens[%i]: %s\n",counter, *tokens );
        tokens++;
        counter++;
    }
}
int main(){
    char input = "";
    while(input != '$'){
        printf("Please enter an input string(to exit input '$'):\n$");
        scanf("%c", input);
        printf("%c", input);
    }
}
