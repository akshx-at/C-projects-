#include "game.h"
//partners: akshat4, ribhavs2
/*For this MP, you will be implementing the game on a variable sized grid.  Upon launching the game, the program will ask the user for dimensions. This
 input is expected as 2 integers (rows and columns) separated by a space (e.g. '4 4' for the standard 4x4 grid).  After configuring board size, the game 
beings.  In addition to the directional controls (w,a,s,d), your version will use n to reset the game, and q to quit the game.  'n' will recreate the 
game board with new dimensions, setting all cells to negative one, and randomly adding one tile. 'q' will output a "Quitting.." message and terminate the
 program.
*/
game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;
    //initializing the value
    mygame->cols = cols;
    //initializing the values
    mygame->score = 0;
    int i,j;
    for(i=0;i<rows;i++)
    {
        for(j=0; j<cols ; j++)
        {
            mygame->cells[i*cols + j] = -1;
        }
    }
    //creating a double for loop to assign -1 to cells

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows;
    // same as the previos function
    (*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)->score = 0;

    for(int i = 0; i<new_rows ;i++)
    {
        for(int j = 0; j<new_cols ; j++)
        {
            (*_cur_game_ptr)->cells[i*new_cols + j] = -1;
        }
    }
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if((row >= cur_game->rows) | (row < 0) | (col >= cur_game->cols) | (col < 0))
        return NULL;
    else
    {
        cell* cur_cell = (cur_game->cells) + (row*cur_game->cols) + col;
        return cur_cell;        
    }
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int row = cur_game->rows;
    int col = cur_game->cols;
    int i,j, ind,limit;
    //int tile_merge_check
    cell cur_cell, above_cell;
    int valid = 0;// flag to check if the swap is taken place or not 
    for(j = 0; j < col; j++)
      { 
      limit = 0;
        for(i = 1;i < row; i++)
	  { // double for loop to traverse through the list
	  // tile_merge_check = 0;
            ind = i;
            while(ind>limit)
	      { // creating  a while loop to ensure double adding doesnt take place
                cur_cell = cur_game->cells[ind*col + j];
                above_cell = cur_game->cells[(ind - 1)*col + j];
		if(cur_cell != (-1))
		  { // condition for swaping 
		    if(above_cell == (-1))
		      {
			cur_game->cells[(ind - 1)*col + j] = cur_cell;
			cur_game->cells[ind*col + j] = -1;
			valid = 1;
		      }
		    else if(above_cell == cur_cell)
		      {   // another condition for swapping
			cur_game->cells[(ind - 1)*col + j] += cur_cell;
			cur_game->cells[ind*col + j] = -1;
			cur_game->score += cur_game->cells[(ind - 1)*col + j];
			        // tile_merge_check = 1;
			valid = 1;
		        limit = ind;
		      }
		  }
                ind -= 1;
            }
        }      
    }
    return valid;
};
// All other functinos follow the same logic as above 
int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int row = cur_game->rows;
    int col = cur_game->cols;
    int i,j, limit, ind;
    cell cur_cell, below_cell;
    int valid = 0;
    for(j = 0; j < col; j++)
    {
        limit = row - 1;
        for(i = row - 2;i >= 0; i--)
        {
            ind = i;
            while(ind<limit)
            {
                cur_cell = cur_game->cells[ind*col + j];
                below_cell = cur_game->cells[(ind + 1)*col + j];
		if(cur_cell != (-1))
		  {
		    if(below_cell == (-1))
		      {
			cur_game->cells[(ind + 1)*col + j] = cur_cell;
			cur_game->cells[ind*col + j] = -1;
			valid = 1;
		      }
		    else if(below_cell == cur_cell)
		      {
			cur_game->cells[(ind + 1)*col + j] += cur_cell;
			cur_game->cells[ind*col + j] = -1;
			cur_game->score += cur_game->cells[(ind - 1)*col + j];
			limit = ind;
			valid = 1;
                    
		      }
		  }
                ind += 1;
            }
        }      
    }
    return valid;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int row = cur_game->rows;
    int col = cur_game->cols;
    int i,j, limit, ind;
    cell cur_cell, left_cell;
    int valid = 0;
    for(i = 0; i < row; i++)
    {
        limit = 0;
        for(j = 1;j < col; j++)
        {
            ind = j;
            while(ind>limit)
            {
                cur_cell = cur_game->cells[i*col + ind];
                left_cell = cur_game->cells[i*col + ind - 1];
		if(cur_cell != (-1))
		  {
		    if(left_cell == (-1))
		      {
			cur_game->cells[i*col + ind - 1] = cur_cell;
			cur_game->cells[i*col + ind] = -1;
			valid = 1;
		      }
		    else if(left_cell == cur_cell)
		      {
			
			cur_game->cells[i*col + ind - 1] += cur_cell;
			cur_game->cells[i*col + ind] = -1;
			cur_game->score += cur_game->cells[i*col + ind - 1];
			limit = ind;
			valid = 1;
                    
		      }
		  }
                ind -= 1;
            }
        }      
    }
    return valid;   
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int row = cur_game->rows;
    int col = cur_game->cols;
    int i,j, limit, ind;
    cell cur_cell, right_cell;
    int valid = 0;
    for(i = 0; i < row; i++)
    {
        limit = col - 1;
        for(j = col - 2;j >= 0; j--)
        {
            ind = j;
            while(ind<limit)
            {
                cur_cell = cur_game->cells[i*col + ind];
                right_cell = cur_game->cells[i*col +(ind + 1)];
		if(cur_cell != (-1))
		  {
		    if(right_cell == (-1))
		      {
			cur_game->cells[i*col + (ind + 1)] = cur_cell;
			cur_game->cells[i*col + ind] = -1;
			valid = 1;
		      }
		    else if(right_cell == cur_cell)
		      {
                    
			cur_game->cells[i*col + (ind + 1)] += cur_cell;
                        cur_game->cells[i*col + ind] = -1;
                        cur_game->score += cur_game->cells[i*col + (ind + 1)];
                        limit = ind;
                        valid = 1;
                    
		      }
		  }
                ind += 1;
            }
        }      
    }
    return valid;   
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    game* copy_game = make_game(cur_game->rows,cur_game->cols);
    int i,j;
    int row = copy_game->rows;
    int col = copy_game->cols;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col ;j++)
        {
            copy_game->cells[i*col + j] = cur_game->cells[i*col + j];
        }
    }
    if((move_a(copy_game) == 1) | (move_d(copy_game) == 1) | (move_s(copy_game) == 1) | (move_w(copy_game) == 1))
    {
        destroy_game(copy_game);
        return 1;
    }
    else
    {
        destroy_game(copy_game);
        return 0;
    }
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
