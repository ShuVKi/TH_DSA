#include<iostream>
using namespace std;

int linearSearch(int a[], int n, int k) {
	for (int i = 0;i < n;i++) {
		if (a[i] == k) return i;
	}
	return -1;
}

int main()
{
	int n;
	cout << "Nhap so phan tu mang: ";
	cin >> n;
	int* a = new int[n];
	cout << "Nhap mang: ";
	for (int i = 0;i < n;i++)
	{
		cin >> a[i];
	}
	int k;
	cout << "Nhap k: "; 
	cin >> k;

	cout << "Position of k: " << linearSearch(a, n, k);

	delete[] a;
	return 0;
}