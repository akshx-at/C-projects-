/* partners: akshat4,adnanmc2,aa69			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * This week is to implement some of the logic and process the user inputs for a code-breaking game. The codebreaking game is very similar to the board game *Mastermind, but played with numbers from 1-8.

 *To play the game, the user first enters a "seed" value, which is an integer. This seed value initializes a pseudo-random number generator. Using the pseud*o-random number generator, a solution code sequence of four numbers from 1 to 8 is chosen at "random." This solution is kept hidden from the player.

 *The player then has 12 guesses to get the sequence of four numbers correct. Guesses are typed into the terminal. After each guess, the player is given fee*dback on the number of perfect matches and misplaced matches, which is printed to the screen.

 *The values of the guess that appear in the same place in the solution code are called perfect matches. The number of values that appear somewhere in the s*olution code but in a different place in the solution code are called misplaced matches. If the player manages to guess the correct sequence in twelve or f*ewer guesses, they win the game. Otherwise, they lose.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;
int solution_arr[4]; // I made an array of solution so that it helps me to compare it with the guessed value

int set_seed (const char seed_str[])
{
    int seed;
    char post[2];
    int ret;
    //    The sscanf statement below reads the integer into seed.
    // We utilize the sscanf to unpack 'post' and store it in 'seed' and then check if it returns exactly one value 
    ret = sscanf(seed_str, "%d%1s", &seed, post);
    if (ret==1){
		srand(seed);
		  return 1;
    }
    else{
      printf("set_seed: invalid seed\n"); // if the return value is anything other than 1 we return an error
	 return 0 ;
    }
}
void start_game (int* one, int* two, int* three, int* four)
{
  // If we do % by 8 we ensure that the remainder is always less than 8
  solution1 = rand()%8+1; 
  solution2 = rand()%8+1;
  solution3 = rand()%8+1;
  solution4 = rand()%8+1;
  // Filling the values inside the arr that we created earlier for comparision purposes
  solution_arr[0]=solution1;
  solution_arr[1]=solution2;
  solution_arr[2]=solution3;
  solution_arr[3]=solution4;
  
  *one = solution1;
  *two = solution2;
  *three = solution3;
  *four = solution4;
  guess_number = 1;
}

int make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
  // initilaizing the variables as needed by us in the code below
  int misplace_counter=0;
  int right_counter=0;
  int w,x,y,z,ret_user;
  char post[2];
  int i,j;
  int temp_sol_arr[4];
  int temp_guess_arr[4];
  // unpacking the guess_str arr gives by the user to get the guess value
  ret_user = sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
  //Now we are checking if the arr we unpacked contains the right values and conditions specified by the program
  if ((ret_user==4 && w>=1 && w<=8 && x>=1 && x<=8 && y>=1 && y<=8 && z>=1 && z<=8)){
    //If true we are creating a temporaray arr for comparision purposes
    temp_guess_arr[0]= w;
    temp_guess_arr[1]= x;
    temp_guess_arr[2]= y;
    temp_guess_arr[3]= z;
    *one=w;
    *two=x;
    *three=y;
    *four=z;
    for(i=0;i<4;i++){
      // similaryly we are creating another temporary arr for the comparision purposes 
      temp_sol_arr[i]=solution_arr[i];
    }
  }
    else{
      // if the previous condition fails it means that we the entered guess is in an incorrect format so we return an error
      printf("make_guess: invalid guess\n");
      return 0;
    }
    for(i=0;i<4;i++){
      // Creating a for loop to check for the perfectly placed characters
	if(temp_sol_arr[i]==temp_guess_arr[i]){
	  temp_sol_arr[i]=9; // if true we assign a diff value to the sol_arr so that it helps us prevent repition while checking for mismatched places
	  temp_guess_arr[i]=0; // same as above
	  right_counter++;
	}
      }
      for(i=0;i<4;i++){
	for(j=0;j<4;j++){
	  // creating a double for loop so it allows us to compare with each place of the second array
	  if(temp_sol_arr[i]==temp_guess_arr[j]){
	    temp_guess_arr[j]=0;
	    misplace_counter++;
	    continue;
	  }
	}
      }
      printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number,right_counter,misplace_counter);
      guess_number ++;
      return 1;
}

