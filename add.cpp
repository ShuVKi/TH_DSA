#include<iostream>
using namespace std;

int add(int a, int b) {
	return a + b;
}
int main() {
	int a, b;
	cout << "Nhap 2 so a va b: ";
	cin >> a >> b;
	cout << "Tong cua " << a << " va " << b << " la: " << add(a, b) << endl;
	return 0;
}