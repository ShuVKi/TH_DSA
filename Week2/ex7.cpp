#include<iostream>
using namespace std;

bool isDup(int result[], int temp[],int m )
{	
	//check each triplet
	for (int j = 0;j < m;j += 3)
	{
		int cnt = 0;
		for (int i = 0;i < 3;i++)
		{ //check each elements in triplet
			if (temp[i] == result[j] || temp[i] == result[j + 1] || temp[i] == result[j + 2])
				cnt++;
			if (cnt == 3) return true;
		}
	}
	return false;
}

void searchTriplet(int a[], int n)
{
	int* result = new int[n*n];
	int m = 0;
	// Duyet all triplet
	for (int i = 0;i < n - 2;i++)
	{
		for (int j = i + 1;j < n - 1;j++)
		{
			for (int k = j + 1;k < n;k++)
			{
				if (a[i] + a[j] + a[k] == 0)
				{//add into temp array so that check DUP
					int temp[3];
					temp[0] = a[i];
					temp[1] = a[j];
					temp[2] = a[k];
					if (!isDup(result,temp,m))// check duplicate
					{ //add into result array
						result[m++] = a[i];
						result[m++] = a[j];
						result[m++] = a[k];
					}
				}
			}
		}
	}
	if (m != 0)
	{
		for (int l = 0;l < m;l += 3)
		{
			cout << "[" << result[l] << "," << result[l + 1] << "," << result[l + 2] << "]" << " ";
		}
	}
	else cout << "No triplet have total equal 0\n";
	delete[] result;
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

	searchTriplet(a, n);

	delete[] a;
	return 0;
}