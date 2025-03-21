#include <iostream>
#include <string> 
using namespace std;

int main() {
	string name = "Alice";
	cout << "Original: " << name << endl;
	name.append(" Wonderland");
	cout << "Updated: " << name << endl; // Output: Alice Wonderland
	cout << "Length: " << name.length() << endl;
	return 0;
}