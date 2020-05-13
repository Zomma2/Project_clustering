#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <chrono> 
using namespace std;
using namespace std::chrono;
#define NUM_THREADS 10


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

const int m = 12;
const int n = 12;
int no_of_small [NUM_THREADS]= { 0 };

int arr[n][m] = {};  // create  data array of size nxm
bool very_small[n][m] = {false}; // create  boolean array of size nxm indicating nodes that is satisfied
void printarray(int(&arr)[n][m]); //decleration of printarray function

void *threadfunction(void *threadid) {
	/*

This function takes in a thread number and use it to change an array inner values to give thier final temperature values
Where each thread is responsible to the outcomes of one row in the array 
*/


	long tid;
	tid = (int)threadid;
	int i = tid + 1;
	int temp;
	while (no_of_small[tid] <10)
	{
		for (int j = 1; j < 11; j++)
		{
			if (very_small[i][j] == false) {

				temp = arr[i][j];
				arr[i][j] = 0.2 * (arr[i][j] + arr[i][j - 1] + arr[i - 1][j] + arr[i][j + 1] + arr[i + 1][j]);

			}

			if (arr[i][j] - temp < 0.1 && arr[i][j] > 0 && temp > 0)
			{
				very_small[i][j] == true;
				no_of_small[tid]++;
			}

		}
		cout << "thread no" << tid << "  modified the array"  <<endl;
		pthread_mutex_lock(&mutex);
		printarray(arr);
		cout << "-------------------------------------------" << endl;
		pthread_mutex_unlock(&mutex);
	
	}

	pthread_exit(NULL);
	return NULL;
}

void Seqfunction(int (&arr)[n][m]) {

	/*

This function takes in a 2D  integar array and change it's inner values to give thier final temperature values

*/





	int no_of_small_all = 0; // This integar is indicator to how many nodes/points is satisfied 
	int temp[n][m]; // This integar array  is used to save older temperature values to compare them to new ones 
	int i;
	
		while (no_of_small_all < 100)
		{
			for (int i = 1; i < 11; i++)
			{
				if (no_of_small[i] > 10)
				{
				
					break;
				
				}
				for (int j = 1; j < 11; j++)
				{
					if (very_small[i][j] == false) {

						temp[i][j] = arr[i][j];
						arr[i][j] = 0.2 * (arr[i][j] + arr[i][j - 1] + arr[i - 1][j] + arr[i][j + 1] + arr[i + 1][j]);

					}
				}
			}

				for (int i = 1; i < 11; i++)
				{
					for (int j = 1; j < 11; j++)
					{


						if (arr[i][j] - temp[i][j] < 0.1 && arr[i][j] > 0 && temp[i][j] > 0)
						{
							very_small[i][j] == true;
							no_of_small[i]++;
							no_of_small_all++; 
						}

					}
				}
			
			printarray(arr);
			cout << "-------------------------------------------" << endl;

		}
	
}







































void intialize_temperature(int(&arr)[n][m])
{
	/*

This function takes in a 2D  integar array and change it's outermost values to given temperature values 

*/




	for (int i = 0; i < n ;i++)
	{
	
		for (int j = 0 ; j<m ; j++)
		{
			if (i == 0)
			{
			
				arr[i][j] = 100;

			}
		
			if (j == 0)
			{
				arr[i][j] = 400;
			
			}
		
		
			if (i == n-1)
			{

				arr[i][j] = 300;

			}

			if (j == m-1)
			{
				arr[i][j] = 200;

			}
		
		
		
		
		}
	
	
	
	
	}







}



void printarray(int(&arr)[n][m])

{

	/*

This function takes in a 2D integar  array and print it

*/




	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{

			cout << arr[i][j] << "\t";

		}

		cout << endl;

	}



}



void printarraybool(bool (&arr)[n][m])


/*

This function takes in a 2D  boolean array and print it 

*/




{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{

			cout << arr[i][j] << "\t";

		}

		cout << endl;

	}



}





void resetarraybool(bool(&arr)[n][m])




/*

This function takes in a 2D boolean  array and reset it to false value to all values in it

*/

{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{

			 arr[i][j] = false ;

		}


	}



}





void resetarrayint(int(&arr)[n][m])



/*

This function takes in a 2D array and reset it to zero values to all values in it

*/


{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{

			arr[i][j] = 0;

		}


	}



}







void reset_1D_arrayint(int(&arr)[NUM_THREADS])

/*

This function takes in a 1D array and reset it to zero values to all values in it

*/



{

	for (int i = 0; i < NUM_THREADS; i++)
	{
		

			arr[i] = 0;

		


	}



}






















int main() {

printarraybool(very_small);
cout << "-----------------------------------------------------------------" << endl;

printarray(arr);
cout << "-----------------------------------------------------------------" << endl;

intialize_temperature(arr);
printarray(arr);
cout << "-----------------------------------------------------------------" << endl;

cout << "-----------------------------------------------------------------" << endl;
cout << "-----------------------------------------------------------------" << endl;

auto start = high_resolution_clock::now();
Seqfunction(arr); 
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);
cout << "---------------------------------------------------------------" << endl;
cout << "---------------------------------------------------------------" << endl;

cout << "---------------------------------------------------------------" << endl;
printarray(arr);

cout << "---------------------------------------------------------------" << endl;
cout << "---------------------------------------------------------------" << endl;
cout << "Time taken by seq threads : "
<< duration.count() / 1000000 << " seconds" << endl;


cout << "---------------------------------------------------------------" << endl;
cout << "---------------------------------------------------------------" << endl;
cout << "---------------------------------------------------------------" << endl;
cout << "---------------------------------------------------------------" << endl;
cout << "---------------------------------------------------------------" << endl;
cout << "---------------------------------------------------------------" << endl;

resetarrayint(arr);
printarraybool(very_small);
intialize_temperature(arr);
reset_1D_arrayint(no_of_small);
cout << "---------------------------------------------------------------" << endl;
printarraybool(very_small);
cout << "-----------------------------------------------------------------" << endl;

printarray(arr);
cout << "-----------------------------------------------------------------" << endl;


	pthread_t threads[NUM_THREADS];
	int rc; // satus of thread after creation 
	int i; // to index

	auto start_parallel = high_resolution_clock::now();
	for (i = 0; i < NUM_THREADS; i++) {

		rc = pthread_create(&threads[i], NULL, threadfunction, (void *)i);
		cout << "mai  created thread " << i << endl ;
		// creation of threads 
		if (rc) {
			printf("Error:unable to create thread, %d", rc);
			exit(-1);
		}


	}

	// Wait for all threads to complete then print global counts 
	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}
	auto stop_parallel = high_resolution_clock::now();
	auto duration_parallel = duration_cast<microseconds>(stop_parallel - start_parallel);

	cout << "---------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "Time taken by Parallel threads : "
		<< duration_parallel.count()/1000000 << " seconds" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------" << endl;

	cout << "---------------------------------------------------------------" << endl;



	printarray(arr);

	pthread_exit(NULL);

}