#include<iostream>
using namespace std;

bool isSorted(int arr[], int n);

int main() {
	int n;
	cout << "Nhap so phan tu mang: "; // so phan tu trong mang
	cin >> n;
	int* arr = new int[n];
	for (int i = 0;i < n;i++){  //nhap mang
		cout << "Nhap a[" << i << "]: ";
		cin >> arr[i];
	}
	cout << "Xuat mang: "; //xuat mang
	for (int i = 0;i < n;i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	if (isSorted(arr, n))
		cout << "The array is sorted.\n";
	else
		cout << "The array is NOT sorted.\n";
	delete[] arr;
	return 0;
}

bool isSorted(int arr[], int n) {
	if (n == 0 || n == 1) return true; // n=0 or n=1 array is sorted
	if (arr[0] > arr[1]) return false; // the first element > the second element => array is not sorted
	return isSorted(arr + 1, n - 1); // recursive call to check remaining elements
}