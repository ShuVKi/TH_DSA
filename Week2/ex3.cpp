#include<iostream>
using namespace std;

int Searchminarray(int a[], int left, int right) 
{
	while (left <= right) 
	{
		int mid = left + (right - left) / 2;
		if (left == right) return a[left]; //mid=left=right=min
		if (a[mid] < a[right])  //mang ben phai is sorted-> min=mid || ben trai
			right = mid;
		else					//mang ben trai is sorted-> min ben phai
			left = mid + 1;
	}
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

	cout << "Min = "<<Searchminarray(a,0,n-1);

	delete[] a;
	return 0;
}