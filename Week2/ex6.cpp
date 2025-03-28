#include<iostream>
using namespace std;

bool searchSum(int a[], int n,int k) {
	int left = 0, right = n - 1;
	while (left < right)
	{
		int temp = a[left] + a[right];
		if (temp == k) return true;
		if (temp > k) right--;
		if (temp < k) left++;
	}
	return false;
}


int main() {
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

	if (searchSum(a,n,k)) cout << "YES";
	else cout << "NO";

	delete[] a;
	return 0;
}