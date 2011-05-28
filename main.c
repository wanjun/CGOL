#include <stdio.h>
#include <stdlib.h>


/*
 this program takes a five by five input array and calculates the result to an output 
 array of the same size according to the rules of Conway's Game of Life.
 
 Rules for Conway's Game of life
 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
 2. Any live cell with two or three live neighbours lives on to the next generation.
 3. Any live cell with more than three live neighbours dies, as if by overcrowding.
 4. Any dead cell with exactly three live neighbours becomes a livecell, as if by reproduction.
 
 
 The process is then iterated the Game of Life reaches an equilibrium state.
 */


/* the anyalive function takes an input array, the width of the array and the length of the array
 and iterates through each element of the array and returns the total number of live cells
 this is used to end the program once the game of life reaches an equilibrium state
 */

//the input array is initialized to ones and zeroes with one representing life and zero death
int input[5][5]=
{{1,0,1,1,0},
	{1,0,0,0,0},
	{1,0,0,0,1},
	{0,0,1,0,1},
	{0,0,0,0,0}};

int anyalive (int *ar1, int x, int y){
	int sum=0;
	for (int i=0; i<x*y; i++) {
		sum+=*(ar1+i);
	}
	return sum;
	
}


//gameoflife is a function that an input array 
//and then calculates the output array using the rules defined in Conway's game of life
//and puts the result in an output array

int* gameoflife (int *ar1, int x, int y){
	
	//allocates memory for the output array by calculating the width and length of the input array
	int *ar2 = malloc(sizeof(int)*x*y);
	
	//iterate through each cell to evaluate neighbors	
	//replace indices with referenced pointers from width x and length y
	int down_index, up_index, left_index, right_index;
	for (int yidx=0; yidx<y; yidx++) {
		
		down_index= yidx+1;
		up_index= yidx-1;
		
		if (down_index>=y)
			down_index=0;
		if (up_index<0) {
			up_index=y-1;
		}
		
		for (int xidx=0; xidx<x; xidx++){
			//take the values of the adjacent matrices and store them initialize to zero
			left_index = xidx-1;
			right_index = xidx+1;
			
			if (left_index<0) {
				left_index=x-1;
			}
			if (right_index>=x) {
				right_index=0;
			}
			//if at the end of a column, add the top or bottom side
			
			//if at the beginning or end of a row, add the left or right side
			
			//sum values of the adjacent matrices
			//neighbors map:
			// 0,-1, 0,-1 1,-1
			// -1,0    --   1,0
			// -1,1   0,1   1,1
			
			
			int sumneighbors = *(ar1+(x*up_index)+left_index);//[up_index][left_index];
			
			sumneighbors+= *(ar1+(x*up_index)+xidx);//[up_index][xidx];
			sumneighbors+= *(ar1+(x*up_index)+right_index);//[up_index][right_index];
			sumneighbors+= *(ar1+(x*yidx)+left_index);//[yidx][left_index];
			sumneighbors+= *(ar1+(x*yidx)+right_index);//[yidx][right_index];
			sumneighbors+= *(ar1+(x*down_index)+left_index);//[down_index][left_index];
			sumneighbors+= *(ar1+(x*down_index)+xidx);//[down_index][xidx];
			sumneighbors+= *(ar1+(x*down_index)+right_index);//[down_index][right_index];
			/*printf("%i %i %i %i %i %i %i %i\n",
				   (x*up_index)+left_index, (x*up_index)+xidx, (x*up_index)+right_index,
				   (x*yidx)+left_index, (x*yidx)+right_index, (x*down_index)+left_index,
				   (x*down_index)+xidx, (x*down_index)+right_index);
			
			printf("%i %i %i %i %i %i %i %i\n",
				   *(ar1+(x*up_index)+left_index), *(ar1+(x*up_index)+xidx), *(ar1+(x*up_index)+right_index),
				   *(ar1+(x*yidx)+left_index), *(ar1+(x*yidx)+right_index), *(ar1+(x*down_index)+left_index),
				   *(ar1+(x*down_index)+xidx), *(ar1+(x*down_index)+right_index));*/
			
			
			
			//if 2 or 3 its living
			//write 1 to the second array
			//else death
			//write 0 to the the second array
			
			if ((*(ar1+(x*yidx)+xidx))==0) {
				*(ar2+(yidx*x)+xidx)= (sumneighbors==3?1:0);
			}
			else *((ar2+(yidx*x)+xidx)) =(sumneighbors==2||sumneighbors==3)?1:0;
			
		}
	}
	
	
		
	return ar2;
	
}

void printboard(int* ar, int x, int y){
	//print out the second array
	printf("-------\n");
	for (int i=0; i<y; i++) {
		for (int j=0; j<x; j++) {
			printf("%i", *(ar+(i*x)+j));
		}
		printf("\n");

	}
	printf("-------\n\n");

}	

int main(int argc, char** argv)
{
	
	
	int *arr = input;
	
	while (anyalive(arr, 5, 5)>3) {
		arr=gameoflife (arr, 5, 5);
		printboard(arr, 5, 5);
	
	}
		
	return 0;
}







