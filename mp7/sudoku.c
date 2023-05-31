#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

//Group: ribhavs2, akshat4

/* 
* This mp is designed to simulate the solving of a sudoku puzzle using recursive backtracking.
* The system firstr generates a few random places at certain cells of the sudoku matrix, 
* following which the code is supposed to generate a corresponding solution to the puzzle
* based on certain conditions.
*
* int is_val_in_row(const int val, const int i, const int sudoku[9][9]):
* This function basically checks if it is safe to place "val" in the cell based
* on the condition that the same value has not already placed in the same row.
* To do this, I looped through all the columns of the sudoku matrix but kept the row constant.
* I then checked if any of the cells already contained the value "val". If it did I return 1,
* indicating that a value has been found in the row. If "val" is not found in any of these cells, then
* I return 0, indicating that the value has not been found in the row.
* 
* int is_val_in_col(const int val, const int j, const int sudoku[9][9]):
* This function basically checks if it is safe to place "val" in the cell based
* on the condition that the same value has not already placed in the same column.
* To do this, I looped through all the rows of the sudoku matrix but kept the column constant.
* I then checked if any of the cells already contained the value "val". If it did I return 1,
* indicating that a value has been found in the column. If "val" is not found in any of these cells, then
* I return 0, indicating that the value has not been found in the column.
*
* int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]):
* This function basically checks if it is safe to place "val" in the cell based
* on the condition that the same value has not already placed in its corresponding 3x3 zone,
* since the entire sudoku matrix is divided into 9 3x3 zones. I do this by first finding the
* starting and ending row and column indices for the corresponding zone. To find the starting 
* row and column indices, I divide the cell's row/column index with 3 and floor the value and then
* multiply with 3. This turns any value in the range 0-2 -> 0, 3-5 -> 3, and 6-8 -> 6.
* For the ending row/column indices i just add 2 to the starting indicies since the 
* zone size is 3x3. I then loop through these ranges to check if "val" already exists in the zone
* If it does I return 1, if it doesn't I return 0.
* 
* int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]):
* This function basically checks the above 3 conditions by calling all the 3 related functions. 
* If all the above 3 functions return 0, indicating that it is safe to place the value in the given cell,
* I return 1, otherwise if even one of above 3 conditions are violated, I return 0.
*
* int solve_sudoku(int sudoku[9][9]):
* This function is used to solve the sudoku using recursion.
* For the base case, I check if all cells of the sudoku matrix have been filled.
* If they have, the puzzle has been solved and it returns 1. If not, we proceed
* to the recursive case. For this, I first search for an empty cell. Once found, 
* I run a loop from values 1-9 to check what value is safe to be placed in the empty cell.
* This is checked by invoking the is_val_valid() function. If it is safe, then the value
* is placed there and next iteration of recursion proceeds with the updated sudoku matrix.
* If however, in any of these iterations a scenario is found where none of the values from
* 0-9 can be be placed, then we backtrack to the previous step and undo it and try the next
* possible value. If a value cannot be placed in this step as well, then we backtrack again
* and keep doing this until we find a valid scenario, uopn which we proceed with solving the
* sudoku again with that configuration.
*/

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int col;
  for(col = 0; col < 9; col++)
  {
    if(sudoku[i][col] == val) //search if value is present in any cell in given row
      return 1;
    else
      continue;
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int row;
  for(row = 0; row < 9; row++)
  {
    if(sudoku[row][j] == val) // search if value is present in any cell in given column
      return 1;
    else
      continue;
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int row, col;
  int row_start, row_end, col_start, col_end;

  row_start = 3 * (i/3); // to set starting row index of 3x3 zone
  col_start = 3 * (j/3); // to set starting column index of 3x3 zone

  row_end = row_start + 2; // to set ending row index of 3x3 zone
  col_end = col_start + 2; // to set ending column index of 3x3 zone

  for(row = row_start; row <= row_end; row ++)
  {
    for(col = col_start; col <= col_end; col++)
    {
      if(sudoku[row][col] == val) // check if value is present in any cell in the 3x3 zone
        return 1;
      else 
        continue;
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  int row_check = is_val_in_row(val, i, sudoku); // row check
  int col_check = is_val_in_col(val, j, sudoku); // column check
  int zone_check = is_val_in_3x3_zone(val, i, j, sudoku); // 3x3 zone check
  if((row_check == 0) && (col_check == 0) && (zone_check == 0)) // check whether its safe to fill value based on all 3 conditions
    return 1;
  else
    return 0;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j;
  int check = 1; // variable to check if all cells in the sudoku matrix have been filled
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
	  {
	    if(sudoku[i][j] == 0) // even if one empty cell found, check variable is set to 0
	     check = 0;
	  }
  }
  
  if(check == 1) // if no empty cells have been found
  {
    return 1;
  }
  else
  {
    int num;
    //looping through each cell
    for(i = 0; i<9; i++)
    {
      for(j = 0; j<9; j++)
      {
        if(sudoku[i][j] == 0) //finding an empty cell
        {
          for(num = 1; num <= 9; num++ ) //looping through nos. 1-9 to fill in the cell
          {
            if(is_val_valid(num,i,j,sudoku) == 1) //cehcking if it is safe to place the current value of num in the cell
            {
              sudoku[i][j] = num;
              if(solve_sudoku(sudoku) == 1) //moving on to next instance of fillinf the sudoku
                return 1; // sudoku has been solved
              
              sudoku[i][j] = 0; // previous decision is unmade if invalid sudoku configuration is reached
            }
          }
          return 0; // no valid value found to be filled in the cell, so 0 returned to backtrack to the previos decision
        }
      }
    }
    return 1; // this line will never be reached but had to be written to prevent a warning
  }
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
