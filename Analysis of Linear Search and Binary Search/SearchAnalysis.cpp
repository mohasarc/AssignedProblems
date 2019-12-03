// Author : Mohammed S. Yaseen
// Version    : 0.1
// Date       : 27/11/2019

#include <iostream>
#include <chrono>
#include <string>
#include <tgmath.h>
#include <fstream>
#include <windows.h>
using namespace std;
using namespace std::chrono;

int sequentialSearch( int* arr, int N, int value ){
	for ( int i = 0; i < N; i++)
		if ( arr[i] == value )
			return i;
	return -1;
}

int binarySearch( int* arr, int N, int value ){
	int low = 0, high = N - 1;
	while ( low <= high ) {
		int mid = (low + high) / 2;
		if ( arr[ mid ] < value )
			low = mid + 1;
		else if ( arr[ mid ] > value )
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

// makes an array of size size and initialize it with accending values
// atarting with 0
bool makeArray(int size, int* &array){
	if (size <= 0)
		return false;

	array = new int[size];

	for (int i = 0; i < size; i++){
		array[i] = i+1;
	}

	return true;
}

template <typename T>
bool saveToFile(T** &array, int Dim1Size, int Dim2Size, string fileName){
	ofstream resultsFile;
	resultsFile.open( fileName + ".txt");

	for (int i = 0; i < Dim1Size; i++){
		for (int j = 0; j < Dim2Size; j++){
			resultsFile<< " "<< array[i][j];
			//cout<< " "<< array[i][j];
		}
		resultsFile<<"\n";
	}
	resultsFile.close();

	return true;
}

int main(){
	// the pointer that will store the array
	int* anArray;
	const long maxSizeOfArray = 100000000; // size of the largest array
	const long smallestSizeOfArray = 10;
	const long increment = 50000;
	const int numOFInputToTest = 4; // the number of search values
	int currentArray = 0; // stores temporary values about the index of current array
	int numToFind = 0; // the value to be searched (temporary)

	// make a 2d array to store the results in the form of XY points
	// first dim will be curespondent to the input size
	// second dim will be curespondent to the time taken by diferent 
	// search values and different algorithms, i.e. value 1 algo 1 -> index 1 ...
	// value 4 algo 2 -> index [numOFInputToTest*2 - 1]
	int firstDimSize = log10(maxSizeOfArray) - log10(smallestSizeOfArray) + 1;
	int secondDimSize = numOFInputToTest*2 + 1; // index 0 will be populated by input size values
	double** results = new double*[firstDimSize];
	for (int i = 0; i < firstDimSize; i++){
		results[i] = new double[secondDimSize];

		for (int j = 0; j < secondDimSize; j++)
			results[i][j] = 0;
	}

	double** theoResults = new double*[firstDimSize];
	for (int i = 0; i < firstDimSize; i++){
		theoResults[i] = new double[secondDimSize];

		for (int j = 0; j < secondDimSize; j++)
			theoResults[i][j] = 0;
	}

	//cout << log10(maxSizeOfArray);

	// repeate the whole process twice (once for Binary Search, once for linear)
	for (int select = 0; select < 2; select++){
		// making [log(maxSizeOfArray) base 10] arrays of size 10^(loop cycle number)
		for (long size= smallestSizeOfArray; size <= maxSizeOfArray; size*=10){

			//cleaning up the memory *************************************************| PROBLAMATIC !!!!!
			if (anArray != NULL)
				delete [] anArray;

			// make an array of size size and store it in anArray
			makeArray(size, anArray);
			int n; // it is used to store the number of repetitions
			          // of the search algorithms to be able to overcome
			          // the 0 time problem
			double m;

				// cout << "\n<<--------Testing " << size << " sized array with ";
				// if(!select)
				// 	cout<< "Binary ";
				// else
				// 	cout<< "Linear ";
				// cout<< "searching-------->>"<< endl;

				// to search numOFInputToTest different numbers in the array
				// the 3 different numbers (excluding the first) are
				// custumized for each array to be in the locations
				// desired: middle, end, outside the array size.
				for (int j = 0; j < numOFInputToTest; j++){
					n = 10000000; // reinitializing the repetition
					m = 1000;
					currentArray = log10(size) - (int)log10(smallestSizeOfArray); // the index of the current array
					
					// deciding which number to look for
					numToFind = 0;
					theoResults[currentArray][0] = size;

					// to find value at the begining
					if (j == 0){
						numToFind = 1;

						// calculating theoretical values
						if (select == 0) // binary
							theoResults[currentArray][j+1] = log(size);
						else // linear
							theoResults[currentArray][j+numOFInputToTest+1] = numToFind;
					}
					// to find value in the middle
					if (j == 1){
						numToFind = size/2;

						// calculating theoretical values
						if (select == 0) // binary
							theoResults[currentArray][j+1] = 1;
						else // linear
							theoResults[currentArray][j+numOFInputToTest+1] = numToFind;
					}
					// to find value at the end
					if (j == 2){
						numToFind = size;

						// calculating theoretical values
							if (select == 0) // binary
						theoResults[currentArray][j+1] = log(numToFind);
							else // linear
						theoResults[currentArray][j+numOFInputToTest+1] = numToFind;
					}
					// to find a non-existing value
					if (j == 3){
						numToFind = size+1;

						// calculating theoretical values
						if (select == 0) // binary
							theoResults[currentArray][j+1] = log(numToFind);
						else // Linear
							theoResults[currentArray][j+numOFInputToTest+1] = numToFind;
					}

					// initialize the timers
					auto start = high_resolution_clock::now();
					auto stop  = high_resolution_clock::now();

					// deciding which type of search to use
					if (!select){

						start = high_resolution_clock::now();
						for (int i = 0; i < n; i++) // to increase the delay
							binarySearch(anArray, size, numToFind);
						stop  = high_resolution_clock::now();
					}
					else {
						if (numToFind < n)
							n = n/numToFind; // dividing the repetitions by the number
						                 	 // to speed up the process for large numbers, and not 
						                	 // affecting the repetitions for small numbers
						else
							n = 1;  // making repetition 1 for very large arrays
									// when numToFind exceeds n in size

						start = high_resolution_clock::now();
						for (int i = 0; i < n; i++)
							sequentialSearch(anArray, size, numToFind);
						stop  = high_resolution_clock::now();
					}
					
					// calculating the time between start and stop
					auto duration = duration_cast<microseconds>(stop - start);
					
					// cout << "Searching " << numToFind << " : ";
					// if (!select)
					// 	cout << binarySearch(anArray, size, numToFind)<< "\t";
					// else
					// 	cout << sequentialSearch(anArray, size, numToFind)<< "\t";
					// //using (time found / n) to get the time spent per search not (n * searches)
					// cout << " the duration : "<< duration.count();//n<< endl;

					results[currentArray][0] = size;//pow(2, log10(size) - 1 );
					if (!select)
						results[currentArray][j+1] = duration.count()/(double)n;
					else
						results[currentArray][j+numOFInputToTest+1] = duration.count()/(double)n;
				}
		}

		// cout << "\n\n\t********\n";
	}

	// save the data in text file to plot them later
	// the data should be in the followig format:
	// the x value in the first column and all y values 
	// curresponding to it in the same row but in different columns
	// i.g. X Y Y Y Y Y Y Y Y
	saveToFile<double>(results, firstDimSize, secondDimSize, "results");

	// saving the theoretical values to file
	saveToFile<double>(theoResults, firstDimSize, secondDimSize, "theoretical");

	// cleaning memory
	for (int i = 0; i < firstDimSize; i++){
		delete []results[i];
	}

	delete []results;

	// run the python code that makes the grphs
	// ShellExecute(NULL, "open", ".\\plotXYResults.py", NULL, NULL, SW_SHOWDEFAULT);
	// ShellExecute(NULL, "open", ".\\plotXYTheoretical.py", NULL, NULL, SW_SHOWDEFAULT);

	return 0;
}