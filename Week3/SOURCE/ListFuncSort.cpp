#include<iostream>
using namespace std;

void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

//Selection Sort
int findMin(int a[], int n,int low)
{
	int min = low;
	for (int i = low + 1;i < n;i++)
	{
		if (a[i] < a[min])
			min = i;
	}
	return min;
}

void selectionSort(int a[], int n)
{
	for (int i = 0;i < n;i++)
	{
		int min = findMin(a, n, i);
		swap(a, i, min);
	}
}

//Insertion Sort
void insertionSort(int a[], int n)
{
	for (int i = 0;i < n;i++)
	{
		int j = i-1;
		int temp = a[i];
		while (j >= 0 && a[j] > temp)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
	}
}

//Buble Sort
void bubleSort(int a[], int n)
{
	for (int i = 0;i < n - 1;i++)
	{
		int swapped = 0;
		for (int j = 0;j < n - 1 - i;j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a, j, j + 1);
				swapped = 1;
			}
		}
		if (swapped == 0) break;//nếu không có bất kì swap nào thì mảng đã được sắp
	}
}

//Heap Sort
void Heapify(int a[], int n,int largest)
{
	int i = largest; //root is largest
	int left = 2 * i + 1; // left child
	int right = 2 * i + 2; //right child

	//find index largest from root and left,right child
	if (left < n && a[largest] < a[left])
		largest = left;
	if (right < n && a[largest] < a[right])
		largest = right;

	//If largest is not root, swap and recrusive
	if (largest != i)
	{
		swap(a, largest, i);
		Heapify(a, n, largest);
	}
}

void heapSort(int a[], int n)
{
	//Bulid a max Heap
	for (int i = n / 2 - 1;i >= 0;i--)
		Heapify(a, n, i);

	//Extract elements one by one from heap
	for (int i = n - 1;i >= 0;i--)
	{
		swap(a, i, 0);
		Heapify(a, i, 0);
	}
}

//Merg Sort
void Merg(int a[],int left,int mid,int right)
{
	int i = left;
	int j = mid+1;
	int *temp= new int[right - left + 1];
	int k = 0;

	while (i <= mid && j <= right)
	{
		if (a[i] < a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}

	while (i <= mid)
		temp[k++] = a[i++];
	while (j <= right)
		temp[k++] = a[j++];

	for (int c = 0;c < k;c++)
		a[left + c] = temp[c];

	delete[] temp;
}

void mergSort(int a[], int left,int right)
{
	if (left < right)
	{
		//Sort firt and second halves
		int mid = left + (right - left) / 2;
		mergSort(a, left, mid);
		mergSort(a, mid + 1, right);

		//Merg 2 array sorted
		Merg(a, left, mid, right);
	}
}

//Quick Sort
int partition(int a[], int low, int high)
{
	int randomIdx = low + rand() % (high - low + 1);
	swap(a, randomIdx, high); // đưa pivot về cuối mảng

	int pivot = a[high];
	int i = low - 1;//vi tri phan tu <= pivot
	for (int j = low;j < high;j++)
	{
		if (a[j] <= pivot)
		{
			i++;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, high);
	return i + 1;
}

void quickSort(int a[], int low,int high)
{
	if (low < high)
	{
		int pivot = partition(a, low, high);//vi tri pivot
		quickSort(a, low, pivot - 1);
		quickSort(a, pivot + 1, high);
	}
}

//Radix Sort
int getMax(int a[], int n)
{
	int max = a[0];
	for (int i = 0;i < n;i++)
		if (max < a[i])
			max = a[i];
	return max;
}

void countingSort(int a[], int n, int exp)
{
	int* output = new int[n];
	int count[10] = { 0 };
	//dem so lan xuat hien
	for (int i = 0;i < n;i++)
		count[a[i] / exp % 10]++;
	//mang cong don so lan xuat hien-> xac dinh vi tri cua cac phan tu
	for (int i = 1;i <= 9;i++)
		count[i] += count[i - 1];
	//sap xep vao mang output
	for (int i = n - 1;i >= 0;i--)
	{
		int idx = a[i] / exp % 10;
		output[count[idx] - 1] = a[i];
		count[idx]--;
	}
	//copy vao a[]
	for (int i = 0;i < n;i++)
		a[i] = output[i];
}

void radixSort(int a[], int n)
{
	int max = getMax(a, n);
	for (int exp = 1;max / exp > 0;exp *= 10)
		countingSort(a, n, exp);
}