#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

int arr_sum( int arr[], int n, int sum )
{ // must be recursive

    if (n < 0) {
         return sum;
    }

    sum += arr[n];

    return arr_sum(arr, --n, sum);
}

int main(int argc, char **argv){

	//PRINTING THE ID OF THE PROCESS
	fprintf(stderr,"The pid of the process is %d\n", getpid());
    
    char name[20];
    printf("The process is in the initial state.\n");
	fgets(name,20,stdin);
	
	
	//TAKING ARGUMENTS
	int argument1 = atoi(argv[0]);
	int argument2 = atoi(argv[1]);
	int argument3 = atoi(argv[2]);
	int argument4 = atoi(argv[3]);
