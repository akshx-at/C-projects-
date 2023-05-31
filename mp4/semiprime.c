//We detected 5 errors in the given file and they are as follows:
// 1. Changing the return value of the 'is_prime' function; Earlier the function would return 1 if the remainder was 0 which is opposite of what we want.
//    Prime numbers are defined as the one having divisibility with the number itself and 1. So by changing the retrun value to 0, we are ensuring that as
//    soon as we encounter that the remainder is 0 we return 0 and tell that its not prime
// 2. Changing the return value from 0 to 1 outside the if{} in 'is_prime'. By doing so we are making sure that if the number is not divisible by any of the
//    numbers it returns 1, indicating that it is a prime number
// 3. Changing the operator that caluculates the value of 'K'. As k will always be 0 due to the if condition earlier so changed the operator form '%' to '/
// 4. Adding a break function after 'printf' so the semi-prime numbers are not printed more than once  
// 5. set ret as 1 so that it returns 1 as we need it if its a semi prime

#include <stdlib.h>
#include <stdio.h>


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //changed the condition; for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
	  return 0; // We change this return value to 0; Because if its divisible by any number integer less than the 'number' then its not prime
        }
    }
    return 1; // Changing this return value to 1 because if the number is not divisible by any integer then it's prime
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
		  k = i/j; // As k will always be 0 due to the if condition earlier so change dteh operator form '%' to '/' 
		  if (is_prime(k)) {
		       printf("%d ", i);
<<<<<<< HEAD
		       ret = 1 ; //set ret as 1
=======
		       ret = 1; //set ret as 1 
>>>>>>> 399bfee440851a08504a9704cdfdec9309c27a05
		       break; //added a break function so the semi-prime numbers are not printed more than once
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
