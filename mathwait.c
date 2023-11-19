/*Cameron Atkins
 *CompSci 2750-02
 *Project 04 Due Monday, November 21, 2022 by 11:59 PM
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char** argv){
	
	FILE *fptr1;

	fptr1 = fopen(argv[1],"a+");
	
	int yes = 0;
	int no = 0;
	pid_t childPid = fork();
	if (childPid == 0){
	    
	     int *nums = 0;//pointer for the dynamically created array

	     //allocates enough memory for an array of integers
             nums = malloc(sizeof(int)*(argc-2));
 
             if (nums <= 0){
                  printf("Could not allocate memory");
                  return 1;
             }
 
	     //Array size will be determined by the amount of arguments minus 2 (executable & file where program will write to)
	     int size = argc-2;
	    
	     int i,j,x,y,z=19;
	     
	     //convert the array of characters into integers
	     for(i = 0; i < size; i++){
		nums[i]=atoi(argv[i+2]);
	
	     }
	     
	     //Print Child PID and array of numbers
	     fprintf(fptr1, "%s %d", "Child:", getpid());
	     
	     for (j=0; j < size; j++){
	          fprintf(fptr1, " %d ", nums[j]);	
	     }
		
             //Embedded for-loop to test if any 2 numbers sum to 19
	     fprintf(fptr1, "%s","\n");
	     for (x = 0; x < (size-1); x++){
		 for (y = (x+1); y < size; y++){
		     if (nums[x] + nums[y] == z){
    			 fprintf(fptr1,"%s %d %d ","Pair:",nums[x],nums[y]);
			 yes++;	         
		     }
		     else{no++;}
		     
		 }
	     }	     
	     
	     if (yes > 0 )
		return EXIT_SUCCESS;
	     else {return EXIT_FAILURE;}
	    
	     fprintf(fptr1,"%s","\n");             
	     //Free the dynamically allocated memory
	     free(nums);
	     nums = 0; //Make nums a null pointer
	   
	     
	 }//end of child process

      else{

	 int stat;

	 wait(&stat);

	if (WIFEXITED(stat)){
             int exitStatus = WEXITSTATUS(stat);
	     fprintf(fptr1, "%s %s %d %d\n","\n","Parent:",getpid(),exitStatus);
	}
	fclose(fptr1);

	}//end of parent process
	
	return EXIT_SUCCESS;



}//end of main 
