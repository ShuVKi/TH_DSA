#include<iostream>
using namespace std;

int fibonacci(int n);

int main() {
	int n;
	do {
		cout << "Nhap n khong am: ";
		cin >> n;
	} while (n < 0);
	cout << "The series Fibonacci number to " << n << "th : ";
	for (int i = 0;i < n;i++)
		cout << fibonacci(i) <<" ";
	return 0;
}

int fibonacci(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return fibonacci(n - 1) + fibonacci(n - 2);
}