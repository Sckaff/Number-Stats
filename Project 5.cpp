//Fernando Sckaff
//COP2000.0M1
//This program will read a list of random numbers and determine a set of information
//based on the random numbers. (considering that all numbers in the file are integers)
#include<iostream>
#include<iomanip>
#include<fstream>

using std::ifstream;

//Prototypes
void openFile(ifstream&);
void testFile(ifstream&);
void readFile(ifstream&, int&, int&, int&, int&, int&, int&, int&);
void min(int, int&);
void max(int, int&);
void oddEven(int, int&, int&, int&);
void calcAverage(ifstream& in, int& sum, int& NumberNums, float& average);
void display(int numberNums, int sum, float average, int minValue, int maxValue, int oddCall, int evenCall, int zeroCall);

int main() 
{
	//Variables
	int minValue,
		maxValue,
		oddCall = 0,
		evenCall = 0,
		zeroCall = 0,
		numberNums = 0,  //Number of numbers
		sum = 0;
	float average;

	ifstream readValue;

	//Order of execution
	openFile(readValue);

	readFile(readValue, minValue, maxValue, oddCall, evenCall, zeroCall, numberNums, sum);

	calcAverage(readValue, sum, numberNums, average);

	display(numberNums, sum, average, minValue, maxValue, oddCall, evenCall, zeroCall);

	system("pause");
	return 0;
}


//Open and read the file
void openFile(ifstream& read)
{
	read.open("Random.txt");
	
	testFile(read);
}

//Test to see if the file was open properly
void testFile(ifstream& test) 
{
	if (!test)
	{
		using std::cerr;
		using std::endl;

		cerr << "The file did not open properly" << endl << endl;
		exit(101);		
	}
}

//Read the file to determine the number of numbers, minimum value, maximum value, number of odd numbers,
//number of even numbers, number of zeroes and the sum. All in one run.
void readFile(ifstream& in, int& minimum, int& maximum, int& oddCall, int& evenCall, int& zeroCall, int& numberNums, int& sum)
{
	//Local variable (the random number)
	int inputNum;

	//Loop to determine minimum and maximum value
	while (in >> inputNum)
	{
		//First run of the loop
		if (numberNums == 0)
		{
			minimum = inputNum;
			maximum = inputNum;
		}

		//See if it is a max
		min(inputNum, minimum);

		//See if it is a min
		max(inputNum, maximum);

		//See if the value odd, even or a zero
		oddEven(inputNum, oddCall, evenCall, zeroCall);
		
		sum += inputNum;			 //The sum of all the numbers

		numberNums++;				 //The counter (number of numbers)
	}
}

//Minimum value function to implement inside readFile
void min(int in, int& min) 
{
	if (in <= min)
		min = in;
}

//Maximum value function to implement inside readFile
void max(int in, int& max)
{
	if (in >= max)
		max = in;
}

//Counting the number of zeroes, evens and odds
void oddEven(int in, int& odd, int& even, int& zero)
{
	if (in == 0)		  //Rule out the zeroes just so it does not combine with evens
		zero++;
	else if (in % 2 == 0) //Rule out evens
		even++;
	else if (in % 2 == 1) //Rule out odd numbers essentially covering them all
		odd++;
}

//Calculating the average based on the sum calculated while reading the file
void calcAverage(ifstream& in, int& sum, int& NumberNums, float& average)
{
	average = static_cast<float>(sum) / static_cast<float>(NumberNums); //Had to make them float in order
}																		//to view the decimals

//Displaying all the information calculated previously
void display(int numberNums, int sum, float average, int minValue, int maxValue, int oddCall, int evenCall, int zeroCall)
{
	using std::cout;
	using std::endl;

	//Beginning statment
	cout << "File Statistics" << endl << endl;

	//Actual information
	cout << "Number of numbers: " << numberNums << endl
		<< "Sum of the Numbers: " << sum << endl
		<< "Average of Numbers: " << average << endl
		<< "Minimum Number: " << minValue << endl
		<< "Maximum Number: " << maxValue << endl
		<< "Number of odd numbers: " << oddCall << endl
		<< "Number of even numbers: " << evenCall << endl
		<< "Number of zeroes: " << zeroCall << endl;

	//Ending statment
	cout << endl << "Thank you for using this application." << endl << endl;
}