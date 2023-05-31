
// ribhavs2, akshat4

/*
* The goal of this mp was to make a sparse matrix using linked lists
* and perfrom certain operations on thsi matrix. The first task was to read
* the matrix from the file. this was done using the load_tuples function. I also had
* to keep in mind that whenever I read a tuple from the file, it had to be placed in 
* the correct order of its row and column in the linked list.
* Some other function were also created to return the value at a given coordinate of
* the matrx, delete the whole structure, and save the matrix and its dimensions in a 
* file. We also ahd to write a function to add 2 sparse matrices and store it a new
* sparse matrix.*/


#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


sp_tuples * load_tuples(char* input_file)
{
    
    FILE* file = fopen(input_file, "r"); // opening file
    

    sp_tuples* info = (sp_tuples*)malloc(sizeof(sp_tuples)); //

    info->nz = 0; //Initializing non 0 entries

    fscanf(file, "%d %d", &(info->m), &(info->n)); // Reading and storing dimension of matrix from file

    info->tuples_head = NULL;
   
    int temprow, tempcol;
    double tempval;
    while(fscanf(file, "%d %d %lf", &temprow, &tempcol, &tempval) != EOF) //Reading each tuple from file
    {
        if(tempval != 0) //only adding tuple with non 0 values
        {

            if(info->tuples_head == NULL) // adding first node to list
            {
	            info->tuples_head = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); // dynamically allocating space for tuple
                info->tuples_head->col = tempcol;
                info->tuples_head->row = temprow;
                info->tuples_head->value = tempval;
                info->tuples_head->next = NULL;
                info->nz += 1;
               continue;
            }

            
            sp_tuples_node* new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
            new_node->row = temprow;
            new_node->col = tempcol;
            new_node->value = tempval;


            insert_node(info, new_node); // inserting tuple in correct place in list
            
        }

    }

    fclose(file);
    return info;
}



double gv_tuples(sp_tuples * mat_t,int row,int col) 

{
    sp_tuples_node* temp = mat_t->tuples_head;
    while(temp !=NULL)
    {
        if((temp->row == row) && (temp->col == col)) // non zero element found at the coordinates
            return temp->value; 
    }
    return 0; // 0 found at the coordinates
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if(value != 0)
    {
        if(mat_t->tuples_head == NULL) // adding node as head node if list is empty
        {
            mat_t->tuples_head->col = col;
            mat_t->tuples_head->row = row;
            mat_t->tuples_head->value = value;
            mat_t->tuples_head->next = NULL;
            mat_t->nz += 1;
            return;
        }

        sp_tuples_node* new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //creating new node
        new_node->row = row;
        new_node->col = col;
        new_node->value = value;

        insert_node(mat_t, new_node); // adding node to list
        return;
    }
    else
    {
        sp_tuples_node* current = mat_t->tuples_head;
        sp_tuples_node* temp;

        if((current->row == row) && (current->col == col)) // in case head node needs to be deleted
        {
            mat_t->tuples_head = current->next;
            free(current);
            return;
        }

        while(current->next != NULL) // searching for node with the speicific coordinates
        {
            if((current->next->row == row) && (current->next->col == col))
            {
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                return;
            }
            current = current->next;
        }
        return; // if node with these coordinates doesn't exist
    }
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE* fp = fopen(file_name, "w"); // Opening file to write to

    fprintf(fp, "%d %d\n", mat_t->m, mat_t->n); // Writing dimensions of matrix to file

    sp_tuples_node* current = mat_t->tuples_head;

    while(current != NULL)
    {
        fprintf(fp, "%d %d %lf\n", current->row, current->col, current->value); // Writing all tuples to file
	current = current->next;
    }
    
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

    if(!((matA->m == matB->m) && (matA->n == matB->n)))
    {
        return NULL; //dimensions of mat A and mat B do not match
    }
    
    sp_tuples* C = (sp_tuples*)malloc(sizeof(sp_tuples)); // Dynamically Allocating space for new matrix to hold the sum
    C->m = matA->m;
    C->n = matA->n;
    C->nz = 0;
    C->tuples_head = NULL;

    sp_tuples_node* curA = matA->tuples_head;
   
    sp_tuples_node* curC = NULL;

    while(curA != NULL)
    {
        // Adding nodes of A to the C list
        sp_tuples_node* new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
        new_node->col = curA->col;
        new_node->row = curA->row;
        new_node->value = curA->value;
        C->nz += 1;

        if(curA == matA->tuples_head)
            C->tuples_head = new_node; // If head node of A being added
        else
            curC->next = new_node; // If node other than head node being added

        curC = new_node; //updating pointer to current node in C
        curA = curA->next; //updating pointer to next node in A
    }

    curC->next = NULL; // pointing last node to NULL

    curC = C->tuples_head; // resetting pointer to head node of C
    sp_tuples_node* prevC = C->tuples_head; // another pointer

    sp_tuples_node* curB = matB->tuples_head; // pointer to nodes in B

    // Adding nodes of B to existing or new node in C
    while(curB != NULL) // to traverse each node in B
    {
        while(curC !=NULL) // to traverse nodes already present in C
        {
            if((curB->row == curC->row) && (curB->col == curC->col))
            { // node already present in C
                curC->value += curB->value; // adding B(i,j) if C(i,j) (non 0) already exists
                if(curC->value == 0)
                { //delete if sum = 0
                    C->nz -= 1;
                    if(curC == C->tuples_head)
                    {
                        C->tuples_head = curC->next;
                        free(curC);
                        curC = C->tuples_head;
                        prevC = curC;
                        break;
                    }
                    else
                    {
                        prevC->next = curC->next;
                        free(curC);
                        curC = prevC->next;
                        break;
                    }
                }
                prevC = curC;
                curC = curC->next;
                
                break; // moving to next node in B
            }
            if(((curC->row == curB->row) && (curC->col > curB->col)) | (curC->row > curB->row)) //inserting B(i,j) if C(i,j) doesnt exist
            {
	        sp_tuples_node* new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
                new_node->col = curB->col;
                new_node->row = curB->row;
                new_node->value = curB->value;

                if(curC == C->tuples_head) // if inserting at head node
                    C->tuples_head = new_node; // changing pointer to head node to point to new node
                else
                    prevC->next = new_node; // pointing previous node to new node
                
                new_node->next = curC; // pointing new node to next node
                prevC = new_node;
                break; //moving to next node in B
            }   

            prevC = curC;
            curC = curC->next;      
        }
        if(curC == NULL) // if B(i,j) needs to be added at the last node
        {
	    sp_tuples_node* new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
            new_node->col = curB->col;
            new_node->row = curB->row;
            new_node->value = curB->value;

            prevC->next = new_node;
            new_node->next = NULL;
            prevC = new_node; // updating prevC to point to this node so that in next iteration, this node can point to the next new node
        }
        curB = curB->next;
    }
	return C;
}

	
void destroy_tuples(sp_tuples * mat_t){
    delete(mat_t->tuples_head);
    free(mat_t);
    return;
}  

void insert_node(sp_tuples* info, sp_tuples_node* new_node)
{

    sp_tuples_node* current = info->tuples_head; // Initializing 2 pointers to search for correct place to insert new node
    sp_tuples_node* prev = info->tuples_head;

    while(current->row < new_node->row) // finding correct row
    {
        prev = current;
        current = current->next;
	if(current == NULL){break;}
    }

    if(current == NULL) // deepest row with non 0 value  has not yet been added to list
    {
        prev->next = new_node;    
        new_node->next = NULL;
        info->nz += 1; // Updating # of non 0 values
        return; // non zero element has been placed
    }           
    if(current->row != new_node->row) // row of new node does not exist in this list though rows above and below it exist in the list
    {
       if(current == info->tuples_head)
	 {
            info->tuples_head = new_node;
	 }
       else
	 {
             prev->next = new_node;
	 }
       new_node->next = current;
       info->nz += 1;
       return;
    }


    // current->row = new_node->row (i.e row of new node does exist in the current list)
    do
    {
        
        if(current->col == new_node->col) // if coordinate is already present, overwrite the older value
        {
            current->value = new_node->value;
            free(new_node);
            return;
        }
        if(current->col > new_node->col) // found position in the row to place
        {
            new_node->next = current;
            if(current == info->tuples_head) // in case we are placing in the first row and column
                info->tuples_head = new_node;
            else
                prev->next = new_node;
            info->nz += 1;
            return;
        }
        prev = current;
        current = current->next; //Updating pointer

        if(current == NULL) // adding node to last position in list (placing non 0 element in last non 0 row and last appropriate column)
        {
            prev->next = new_node;    
            new_node->next = NULL;
            info->nz += 1;
            return; // non zero element has been placed
        }

        else  if(current->row != prev->row) // any non zero element has not been placed in the row beyond this column
        {
            new_node->next = current;
            prev->next = new_node;
            info->nz += 1;
            return;
        }
    } while (current->row == prev->row);
}

void delete(sp_tuples_node* cur) // To delete entire LL
{
    if(cur == NULL)
        return;
    
    else
    {
        sp_tuples_node* temp = cur;
        delete(cur->next);
        free(temp);
    }
}
