
/*The universe of the Game of Life is a two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead.
 *Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent.
 *At each step in time, the following transitions occur:
 *    Any live cell with fewer than two live neighbours dies, as if caused by under-population.
 *   Any live cell with two or three live neighbours lives on to the next generation.
 *   Any live cell with more than three live neighbours dies, as if by over-population.
 *   Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction
 *
 * Funtions:
 *
 *
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  // initializing the variables 
  int alive,i,j;
  int location1;
  alive=0; // setting the initial condition of alive cells as 0 
  for(i=row-1;i<=row+1;i++){ // This for loop to check for one row behind and one row infront
    if(i>=0 && i<boardRowSize){ // edge case 
      for(j=(col-1);j<=col+1;j++){ // this for loop to check for one coloumn up and up coloumn down
	location1=(boardColSize*i)+j; // Index interms of a 1D array 
	if(j>=0 && j<boardColSize){ // Edge case
	  if(i!=row || j!=col){ // to not check the current row or coloumn
	    if(board[location1]==1){ // if its alive incremnet the counter
	      alive++;
	    }
	  }
	}	
      }
    }
  }
  return alive;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  // initializing variables
  int i;
  int number_alive;
  int location;
  int total;
  // finding total number of elements in a 1d array to create a temp array 
  total=boardRowSize*boardColSize;
  int temp_board[total];
  // creating a temporary array so that we can reflect the changes 
  for(i=0;i<boardRowSize;i++){
    for(int j=0;j<boardColSize;j++){
      // Creating variable 'location' to find index interm of a 1D array
      location = ((boardColSize*i)+j);
      number_alive= countLiveNeighbor( board, boardRowSize, boardColSize, i,j);
      if (board[location]==1){ // starting to check if the cell is alive
	 if ((number_alive==2)||(number_alive==3)){
	   temp_board[location]=1; // alive stays alive due to the above condition
	     }
	 else{
	   temp_board[location]=0; // alive becomes dead if the above condition is not satisfied
	 }
      }
      else if(board[location]==0){ //Now the condition for dead cells
         if(number_alive==3){
	   temp_board[location]=1; // dead become alive if there are exactly three alive neighbors
                }
         else{
	   temp_board[location]=0; // dead remains dead if the above condition is not met
	 }
      }
    }
  }
  for(i=0;i<boardRowSize;i++){
    for(int j=0;j<boardColSize;j++){
      location = ((boardColSize*i)+j); // copying the terms of the temporary array onto the original array
      board[location]=temp_board[location];
    }
  }
}
/* aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  // initializing variables
  int i,j;
  int location;
  int flag=0;
  int number_alive;
  // creating a double for loop to access the values
  for(i=0;i<boardRowSize;i++){
    for(j=0;j<boardColSize;j++){
      // creating the address for in terms of a 1D array
      location = ((boardColSize*i)+j);
      // calling the Count neighbor function to find when changes take place
      number_alive= countLiveNeighbor(board, boardRowSize, boardColSize, i,j);
      if (board[location]==1){
	 if (number_alive< 2 || number_alive >3){
	   flag=1; //flag is 1 when the board is changed because live becomes dead 
	     }
      }
      else if(board[location]==0){
         if(number_alive==3){
	   flag=1 ; //dead becomes alive so flag changes to 1
	 } 
      }
    }
  }
  if(flag==1){
    return 0; //returning 0 to show change in the board as asked by the code
  }
   return 1;
}
