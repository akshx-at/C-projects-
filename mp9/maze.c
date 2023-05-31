#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include <string.h>

// ribhavs2, akshat4

/* 
* The goal of this MP is to implement a maze solver using a recursive depth-first search.
* To do this we first create a maze using the function createMaze(). This function
* dynamically allocating space for the maze structure and the maze itself. The paramters are read
* from a file, whose first line contains the dimensions of the maze, and the lines after
* contain the maze itself. After initializing all parameters of the maze strucutre and the
* maze itslef, this fucntion returns a pointer to the maze structure.
* We have also created a function to destroy the maze destroyMaze(), which basically
* frees up the space occupied by the maze and the maze strucutre, and a fucntion printMaze,
* which is used to print the current form of the Maze to the console.
* Our final function which actually finds the correct path throught the maze is called
* solveMazeDFS which uses a recursive depth first search to find the solution. 
* The base cases involve checking for success (end point has been reached),
* exceeding bounds of maze, and accessing an already occupied cell.
* The iterative steps involve checking possible paths by selecting the next cell in
* the down, right, up or left directions. Whenever an invalid position is reached, we backtrack to the last step
* and choose another cell. If a final path is found, 1 is returned, if not 0 is returned.
*/




/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int i,j;    
    maze_t* maze = malloc(sizeof(maze_t)); // Allocating memeory for maze_t structure

    FILE* file = fopen(fileName, "r"); //Opening file containg maze in read-only mode
    fscanf(file, "%d %d", &(maze->width), &(maze->height)); //reading 1st line fo file containing width and height of maze
 
    // Allocating memory for cells
    maze->cells = (char**)malloc(maze->height * sizeof(char*)); 
    for(i=0;i<maze->height;i++)
    {
        maze->cells[i] = (char*)malloc(maze->width * sizeof(char));
    }

    char line[100];
    fgets(line, sizeof(line), file); // to get past 1st line
    
    for(i = 0; i < maze->height; i++)
    {
    
        fgets(line, sizeof(line), file); //reads each line from file

	    strcpy(maze->cells[i], line); // stores each line of file into each row of maze

        // Checking for starting and ending positions
	    for(j = 0; j < maze->width; j++)
	    {   
	        if(line[j] == 'S')
            {
                maze->startRow = i;
                maze->startColumn = j;
            }
            
	        if(line[j] == 'E')
            {
                maze->endRow = i;
                maze->endColumn = j;
            }
	    }

        
    }

    return maze; // returning pointer to maze
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for( i = 0; i < maze->height; i++)
    {
        free(maze->cells[i]); // freeing up columns of maze
    }
    free(maze->cells); // freeing up rows
    free(maze); // freeing up maze structure
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i,j;

    //printing maze to console
    for(i = 0; i < maze->height; i++)
    {
        for( j = 0; j < maze->width; j++)
        {
	        putchar(maze->cells[i][j]); 
        }
        printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.

    // Base cases
    if((row == maze->endRow) && (col == maze->endColumn)) // Success condition
        return 1;
    if((col < 0) | (col >= maze->width) | (row < 0) | (row >= maze->height)) // Out of bounds of maze condition
        return 0;
    if(!((maze->cells[row][col] == ' ' ) | (( col == maze->startColumn) && (row == maze->startRow)))) // Not empty and not start cell condition
        return 0;
    
    // Recursive cases
    if(!(( col == maze->startColumn) && (row == maze->startRow)))
        maze->cells[row][col] = '*';
    if(solveMazeDFS(maze, col, row+1)) // exploring in down direction
        return 1;
    if(solveMazeDFS(maze, col + 1, row)) //exploring in right direction
        return 1;
    if(solveMazeDFS(maze, col, row - 1)) // exploring in up direction
        return 1;
    if(solveMazeDFS(maze, col - 1, row)) // exporing in left direction
        return 1;

    maze->cells[row][col] = '~'; //Unmarking step and setting cell as visited
    return 0;
}
