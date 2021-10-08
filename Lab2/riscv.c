#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file
#include "string.h"

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}
void print_reg(){
	int col_size = 10;
	for(int i = 0; i< 8; i++){
		printf("X%02i:%.*lld ", i, col_size, (long long int) reg[i]);
		printf("X%02i:%.*lld ", i+8, col_size, (long long int) reg[i+8]);
		printf("X%02i:%.*lld ", i+16, col_size, (long long int) reg[i+16]);
		printf("X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);

	}
	printf("\n");
}

int getActualLocation(char* s){ //change X## to just ##
	int i = 0;
	char pos[2];
	while( *(s+i) != '\0' ){
		i++;
	}
	//the addition of 1 from the beginning index removes the X
	if(i >= 3){
		pos[0] = *(s+1);
	       	pos[1] = *(s+2);
	}
	else
		pos[0] = *(s+1); //for single digit register

	return atoi(pos); //makes the string of nums to an int
}


bool equal(char* s1, char* s2){ // checks if two strings are equal
  char* temp1 = s1;
  char* temp2 = s2;
  int c1 = 0;
  int c2 = 0;

  while (*(temp1+c1) != '\0'){ 
	  c1++;
  }
  while (*(temp2+c2) != '\0'){
    c2++;
  }
  if (c1 != c2){return false;}
  
  int i = 0;
  while (*(s1+i) != '\0' && *(s2+i) != '\0'){
    if (*(s1+i) != *(s2+i))
      return false;
    i++;
  }
  return true;
}

int instructionCases(char* s){ //handles cases for the instruction type
  if (equal(s, "LW")) {return 0;}
  else if (equal(s, "SW")) {
	  return 1;}
  else if (equal(s, "ADD")) {
	  return 2;}
  else if (equal(s, "ADDI")) {
	  return 3;}
  else if (equal(s, "AND")) {
	  return 4;}
  else if (equal(s, "OR")) {
	  return 5;}
  else if (equal(s, "XOR")) {
	  return 6;}
  else
    return -1;
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char *instr){
	char *txt = "mem.txt"; //loads the mem.txt file so we can read it
	char **tokens;
	tokens = tokenize(instr, ' ');	//gets the tokens seperated by space
	
	int instructNum = instructionCases(tokens[0]);
	//implement a switch case for each instruction and act accordording to the instruction
	switch(instructNum){
		case 0: 		//LW Case
			printf("LW\n");
			int saveLocation = getActualLocation( *(tokens+1) );  //location where the info will be loaded
			char** LwLastTokenSplit = tokenize( *(tokens+2), '('); //removes the first (
			char** LwLastTokens = tokenize( *(LwLastTokenSplit+1), ')'); //removes last (
			
			int regLocation = getActualLocation(*LwLastTokens); //int location of register for reg array
			int32_t LwLocation = atoi(*LwLastTokenSplit) + regLocation;

			reg[saveLocation] = read_address(LwLocation, txt); //updates loaction on arr
			break;
		case 1:            //SW Case
			printf("SW\n");
			saveLocation = getActualLocation( *(tokens+1)); //location for where info will be saved
			char** SwLastTokenSplit = tokenize(*(tokens+2), '(');
			char** SwLastTokens = tokenize( *(SwLastTokenSplit+1), ')' );
			
			regLocation = getActualLocation(*SwLastTokens); //int location for store register
			
			int32_t SW_write = reg[saveLocation]; //location where info will be written
			int32_t SwLocation = atoi(*SwLastTokenSplit)+regLocation; //location of info
			int32_t SwWrite = write_address(SW_write, SwLocation, txt); //writes info
			break;
		case 2:		//ADD case
			printf("ADD\n");
			saveLocation = getActualLocation( *(tokens+1) ); //int location of save register
			int r1 = getActualLocation( *(tokens + 2 ) ); //int location of first value
			int r2 = getActualLocation( *(tokens + 3 ) ); //int location of second value

			reg[saveLocation] = reg[r1] + reg[r2];
			printf("Result: %d\n", reg[saveLocation]);
			break;
		case 3: 
			printf("ADDI\n");
			saveLocation = getActualLocation(*(tokens+1) );//int location of save register
			r1 = getActualLocation(*(tokens+2)); //int location of first register
			r2 = atoi( *(tokens+3) ); //int value of the imm value

			reg[saveLocation] = reg[r1] + r2;
			printf("Result: %d\n",reg[saveLocation]);
			break;	
		default:
			printf("Error\n");
			return false;	
	}
	print_reg();
	return true;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();
	print_reg();
	char a[100];
	while(1){
		printf("Please enter an instruction, to exit enter z\n");
		fgets(a,sizeof(a), stdin);
		if(*a == 'z' || *a == 'Z'){
			break;
		}
		interpret(a);
		printf("\n");
	}
	print_reg();
}

