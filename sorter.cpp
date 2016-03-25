/*	Oniel Toledo
	CS 302 Section 1001
	Assignment 5
	Program Overview:
		The following program performs 2 types of sorts (selection or quick) on a 
		specified sized random list of numbers.
		The program will only perform 1 action at a time so as to allow use of the 
		linux "time" command. In the command line the user will need to specify
		the type of sort they would like and the size of the list to sort.
	Command Line Argument Format:
		./a.out <sort type> <size>
		For <sort type> possible commands are "selection" or "quick" all lowercase
		For <size> possible commands are "2000", "4000", "6000", "8000", "10000"
	For more documentation information refer to comments below
	To Find Execution time enter:
		time ./a.out <sort type> <size>
		will return real, usr, and cpu time
	
	Command Line Execution (copy and paste to terminal)
		g++ sorter.cpp -o sorter
		time ./sorter selection 2000
		time ./sorter selection 4000
		time ./sorter selection 6000
		time ./sorter selection 8000
		time ./sorter selection 10000
		time ./sorter quick 2000
		time ./sorter quick 4000
		time ./sorter quick 6000
		time ./sorter quick 8000
		time ./sorter quick 10000
*/

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

//prototypes
 	void selectionSort(int list[], int size);
 	int minLocation(int list[], int first, int last);
 	void swap(int list[], int first, int second);
 	void quickSort(int list[], int size);
 	int partition(int list[], int first, int last);
 	void recQuickSort(int list[], int first, int last);

//main function
int main(int argc, char *argv[]){

	//verify proper command line arguments
	if(argc!=3){
		cout << "Usage ./sorter <sort type (selection or quick)> <size (2000,4000,6000,8000, or 10000)>" << endl;
		return 0;
		}
    if(string(argv[1])!="selection" && string(argv[1])!="quick"){
        cout << "Error, sort types permitted are 'selection' or 'quick'." << endl;
        return 0;
        }


    //convert string to an int to determine the size
    std::string myString = argv[2];
    int size = atoi(myString.c_str());

 	//create the object vector and populate it with random numbers from 0-~32,000
 	int list[size];
 	for(int i=0; i<size;i++)
 		list[i] = rand();

 	//perform appropriate sort type
 	if(string(argv[1])=="selection")
 		selectionSort(list, size);
 	else
 		quickSort(list, size);

 	//done, terminate
 	return 0;
 }

//-----------------------selection sort----------------------------
void selectionSort(int list[], int size){
	int loc, minIndex;
	//do comparison for all index locations
	for(loc=0; loc<size;loc++){
		//find the smallest value's index
		minIndex = minLocation(list, loc, size-1);
		//swap the larger and smaller value
		swap(list, loc, minIndex);
		}
	}
//find smallest
int minLocation(int list[], int first, int last){
	int loc, minIndex;
	
	minIndex = first;
	for(loc = first+1; loc <= last; loc++)
		if(list[loc] < list[minIndex])
			minIndex = loc;

	return minIndex;
	}

//swap function
void swap(int list[], int first, int second){
	int temp;

	temp = list[first];
	list[first] = list[second];
	list[second] = temp;
	}

//-----------------------quick sort----------------------------
//quick sort function, calls the recursive functon recQuickSort to perform
//quick sort operations
void quickSort(int list[], int size){
	recQuickSort(list, 0, size-1);
	}

//recursive quick sort function finds a pivot location then performs
//recQuickSort on the first and second partition, this is done
//continuously until the whole list has been sorted
void recQuickSort(int list[], int first, int last){
	int pivotLocation;

	if(first < last){
		pivotLocation = partition(list, first, last);
		recQuickSort(list, first, pivotLocation-1);
		recQuickSort(list, pivotLocation+1, last);
		}
	}

//function to partition and sort the list with range first-last
int partition(int list[], int first, int last){
	//function variables
	int index, smallIndex;
	int pivot;
	//swap array at first and (first+last)/2
	swap(list, first, (first+last)/2);

	pivot = list[first];
	smallIndex = first;

	for(index = first+1; index <= last; index++)
		if(list[index] < pivot){
			smallIndex++;
			swap(list, smallIndex, index);
		}

	swap(list, first, smallIndex);
	
	return smallIndex;
	}