#include<iostream>
using namespace std;

int linearSearchse(int a[], int n, int k) 
{
	//dat linh canh cuoi mang
	int last = a[n - 1];
	a[n - 1] = k;
	int i = 0;
	while (a[i] != k) {
		i++;
	}
	//tra lai phan tu cuoi
	a[n - 1] = last;
	if (i < n - 1 || a[n - 1] == k)
		return i;
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

	cout << "Position of k: " << linearSearchse(a, n, k);

	delete[] a;
	return 0;
}