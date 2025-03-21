#include<iostream>
using namespace std;

void TowerofHaNoi(int n, char source, char targer, char aux);

int main(){
	int n;
	cout << "Number of disks: ";
	cin >> n;
	TowerofHaNoi(n, 'A', 'C', 'B');
	return 0;
}

void TowerofHaNoi(int n, char source, char targer, char aux) {
	if (n > 0) {
		TowerofHaNoi(n - 1, source, aux, targer); //move n-1 disks above from source to auxiliry
		cout << "Move disk " << n << " from " << source << " to " << targer << endl; //move the biggest disk from source to target
		TowerofHaNoi(n - 1, aux, targer, source); //move n-1 disks remaining from auxiliry to target
	}
}