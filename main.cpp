/*
 Lab 5: Using recursion to find the numbers larger than a certain target in an
 array and load them into another.
 
 Author: Willy O'Hanley
 Date: October 3, 2011
 Last modified: October 10, 2011
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

/*
 Get numbers from a file. Get the file name from the user, read in the numbers,
 and load them into an array. The array is dynamically allocated assuming the
 first number in the file indicates its length.
 */
float* getInput(int &length)
{
	string filename;
	
	cout << "Enter the name of the file containing the numbers." << endl;
	cin >> filename;
	
	ifstream inFile(filename.c_str());
	assert(inFile);
	
	inFile >> length;
	
	float* numbers = new float[length];
	
	for (int i = 0; i < length && inFile.peek() != EOF; i++)
	{
		inFile >> *(numbers + i);
	}
	
	return numbers;
}

/*
 Count how many numbers in an array are larger than a certain number (target).
 
 Algorithm:
 1. If array size is 0, return 0. This is a special case that should only occur
 if the array passed in has size 0 to begin with.
 2. If array size is 1, compare the single number in it and return 1 if it is
 larger than the target and 0 otherwise. Else:
 3. Search each half of the array for numbers larger than target.
 
 The parameters are an array of floats to search, an array of floats to put
 the found numbers in, the length of the array to search, and a target number
 to search for numbers larger than. All the numbers found in the first array
 larger than target are placed in the second array and a count of them is
 returned.
 */
int countLarger(float* numbers, float* found, int length, float target)
{
	assert(length >= 0);
	
	if (length == 0)
		return 0;
	else if (length == 1)
	{
		if (*numbers > target)
		{
			*found++ = *numbers;
			return 1;
		}
		else
			return 0;
	}
	else
	{
		int leftCount = countLarger(numbers, found, length/2, target);
		int rightCount = countLarger(numbers + length/2, found + leftCount,
						length - length/2, target);
		return leftCount + rightCount;
	}
}

/*
 Read numbers in, ask for a target, find the numbers larger than target, and
 load them into a separate array. This array is then printed.
 */
int main(int argc, char* argv[])
{
	// number of numbers read
	int length;
	// array containing numbers read from the file
	float* numbers = getInput(length);
	// array to hold numbers larger than the target
	float* found = new float[length];
	
	// number to search for numbers larger than
	float target;
	cout << "What number are you searching for?" << endl;
	cin >> target;
	
	int count = countLarger(numbers, found, length, target);
	
	cout << "Found " << count << " larger numbers:" << endl;
	for (int i = 0; i < count; i++)
	{
		cout << *(found + i) << endl;
	}
	
	char ch;
	cin >> ch;
	
	return 0;
}
