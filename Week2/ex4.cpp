#include<iostream>
using namespace std;

bool canShip(int weight[],int n,int capacity,int days)
{
	int currweight = 0, currday = 1;
	for (int i = 0;i < n;i++)
	{// total wieight den khi >= capacity thi tang days
		if (currweight + weight[i] > capacity)
		{
			currday++;
			currweight = weight[i];
		}
		else
			currweight+= weight[i];
		if (currday > days) return false;
	}
	return true;
}

int minWeightShipinDays(int weight[], int n, int days) {
	//tinh maxcapacity va mincapacity
	int maxWeight=weight[n-1];
	int sumWeight = 0;
	for (int i = 0;i < n;i++) 
	{
		sumWeight += weight[i];
	}
	//search binary
	int left = maxWeight, right = sumWeight;
	while (left<=right)
	{
		int mid = left + (right - left) / 2;
		if (left == right) return left;
		if (canShip(weight, n, mid, days)) //neu mid du thi ben phai cung du-> bo ben phai
			right = mid;
		else							//neu mid khong du thi ben trai cung khong du-> bo ben trai
			left = mid + 1;
	}

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
	int days;
	cout << "Nhap days: ";
	cin >> days;

	cout << "Min capacity ship within "<<days<<" days: " << minWeightShipinDays(a, n, days);

	delete[] a;
	return 0;
}