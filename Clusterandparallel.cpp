#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <chrono> 
using namespace std;
using namespace std::chrono;
#define NUM_THREADS 10


int counts = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

const int m = 12;
const int n = 12;
int no_of_small [NUM_THREADS]= { 0 };

int arr[n][m] = {};
bool very_small[n][m] = {false};
void printarray(int(&arr)[n][m]);

void *threadfunction(void *threadid) {

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

	
	int temp;
	int i;
	for (int k = 0; k < 10 ; k++)
	{
		 i = k + 1;
		while (no_of_small[i] < 10)
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
					no_of_small[i]++;
				}

			}
			
			printarray(arr);
			cout << "-------------------------------------------" << endl;

		}
	}
}







































void intialize_temperature(int(&arr)[n][m])
{

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
cout << "Time taken by Parallel threads : "
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