//In this MP, we will implement a C program to print a row from Pascal’s triangle. Pascal’s triangle is an array that consists of binomial coefficients and the figure below shows the first five rows of Pascal’s triangle.
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n;
  int k;
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  unsigned long int coef = 1; 
  if (row == 0)
  { 
    printf("1");
  }
  if (row>=1)
  {
    printf("1 ");  
    for (n = 1 ; n<=row ; n++)
    {
    for (k=1 ; k<=n ; k++)
      {
        coef = coef *(row +1 - k)/(k);
      }
      printf("%lu",coef);
      printf(" ");
      coef = 1;
    }
  }
  return 0;
}
