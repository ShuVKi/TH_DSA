#include<iostream>
#include<fstream>
#include<time.h>
#include "Header.h"
using namespace std;

//func read file
bool readFile(const char* filename, int*& a, int& n)
{
	ifstream iFile(filename);
	if (!iFile)
	{
		cout << "Khong the mo file input!";
		return false;
	}
	iFile >> n;
	a = new int[n];
	for (int i = 0;i < n;i++)
	{
		iFile >> a[i];
	}
	iFile.close();
	return true;
}

//func write file
bool writeFile(const char* filename, int a[], int n)
{
	ofstream oFile(filename);
	if (!oFile)
	{
		cout << "Khong the mo file output!";
		return false;
	}
	oFile << n;
	oFile << endl;
	for (int i = 0;i < n;i++)
	{
		oFile << a[i]<<" ";
	}
	oFile << endl;

	oFile.close();
	return true;
}

int main(int argc, char* argv[]) 
{
	srand(time(NULL));

	const char* inputFile = nullptr;
	const char* outputFile = nullptr;
	const char* algorithm = nullptr;

	//xac dinh cac tham so dau vao
	for (int i = 1;i < argc;i++)
	{
		if (strcmp(argv[i], "-a") == 0 && i + 1 < argc)
			algorithm = argv[i + 1];
		else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc)
			inputFile = argv[i + 1];
		else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
			outputFile = argv[i + 1];
	}
	if (!inputFile || !outputFile || !algorithm)
	{
		cout << "Thieu tham so dau vao!" << endl;
		cout << "Use: ./main.exe -a <algorithm> -i <file-input> -o <file-output>" << endl;
		return 1;
	}

	//doc mang tu file input
	int n;
	int* a;
	if (!readFile(inputFile, a, n)) return 1;

	//su dung thuat toan sap xep
	if (strcmp(algorithm, "selection-sort") == 0)
		selectionSort(a, n);
	else if (strcmp(algorithm, "insertion-sort") == 0)
		insertionSort(a, n);
	else if (strcmp(algorithm, "buble-sort") == 0) 
		bubleSort(a, n);
	else if (strcmp(algorithm, "heap-sort") == 0) 
		heapSort(a, n);
	else if (strcmp(algorithm, "merge-sort") == 0) 
		mergSort(a, 0, n - 1);
	else if (strcmp(algorithm, "quick-sort") == 0) 
		quickSort(a, 0, n - 1);
	else if (strcmp(algorithm, "radix-sort") == 0)
		radixSort(a, n);
	else
	{
		cout << "Algorithm "<< algorithm<<" is not supported!"<< endl;
		cout << "Algorithms: selection-sort insertion-sort buble-sort heap-sort merge-sort quick-sort radix-sort" << endl;
		return 1;
	}
	
	//ghi mang da sap xep vao file output
	if (!writeFile(outputFile, a, n)) return 1;    
	
	delete[] a; 
	return 0;
}



