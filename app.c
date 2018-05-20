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
	
		printf("The arguments have been inserted.(Testing the main arguments)\n");
	fgets(name,20,stdin);
	
	
	//Initializing the array to teest STACK
	int arr [100000];
	int i=0;
	for(i=0; i<100000;i++){
  		arr[i]=i;
  	}
	 
  	//CALL RECURSIVE FUMCTION -- TO TEST STACK
	arr_sum(arr, 1000,0);  
    
	printf(" Recursive function has been called.(Testing the Stack)\n");
	fgets(name,20,stdin);

    //Allocating to test heap 
    int *arrr = (int *)malloc(12800* sizeof(int));
	int *arr1 = (int *)malloc(12800*sizeof(int));
	int *arr2 = (int *)malloc(12800*sizeof(int));
	int *arr3 = (int *)malloc(12800* sizeof(int));
	int *arr4 = (int *)malloc(12800* sizeof(int));
	int *arr5 = (int *)malloc(12800*sizeof(int));
	int *arr6 = (int *)malloc(12800*sizeof(int));
	int *arr7 = (int *)malloc(12800* sizeof(int));
	int *arr8 = (int *)malloc(12800* sizeof(int));
	int *arr9 = (int *)malloc(12800*sizeof(int));
	int *arr22 = (int *)malloc(12800*sizeof(int));
	int *arr33 = (int *)malloc(12800* sizeof(int));
	int *arr232 = (int *)malloc(12800*sizeof(int));
	int *arr333 = (int *)malloc(12800* sizeof(int));
	
	
	printf("THe malloc has been executed (To test HEAP) \n");
	fgets(name,20,stdin);
	
	//DECLARE AND INITIALIZE 18 STATIC VARIABLES -- TO TEST DATA 
	static int v1 = 4;
	static int v2 = 4;
	static int v3 = 4;
	static int v4 = 4;
	static int v5 = 4;
	static int v6 = 4;
	static int v7 = 4;
	static int v8 = 4;
	static int v9 = 4;
	static int v10= 3;
	static int v11= 4; 
	static int v12= 4;
	static int v13= 4;
	static int v14= 4;
	static int v15= 4;
	static int v16= 4;
	static int v17= 4;
	static int v18= 4;
	static int v19= 4;
	static int v20= 4;
	static int v21= 4;
	static int v22= 3;
	static int v23= 4; 
	static int v24= 4;
	static int v25= 4;
	static int v26= 4;
	static int v27= 4;
	static int v28= 4;
	static int v29= 4;
	static int v30= 4;
	
/*
	//Environment variables 
	static char *var = "HOME=/usr/home";
	int res =  putenv (var);
	
	static char *var1 = "USER=/usr/user";
	int res1 =  putenv (var1);
	
	static char *var2 = "EDITOR=/editor/home";
	int res2 =  putenv (var2);
*/
	
	printf("Initialization of data has been executed (To test DATA) \n");
	fgets(name,20,stdin);  
	
	
	printf("Bye! Have a nice day!, %s", name);
	
	return 0;

} 
