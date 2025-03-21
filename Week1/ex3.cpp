#include<iostream>
#include<string>
using namespace std;

void generateBinaryStrings(int n, string str);

int main() {
	int n;
	do {
		cout << "Nhap n khong am: ";
		cin >> n;
	} while (n < 0);
	generateBinaryStrings(n, "");
	return 0;
}

void generateBinaryStrings(int n, string str) {
	if (n == 0) {
		cout << str << endl;
		return;
	}
	generateBinaryStrings(n - 1, str + "0");//add 0 into str
	generateBinaryStrings(n - 1, str + "1");//add 1 into str
}