#include<iostream>
using namespace std;

int sumarr(int a[],int start, int end) {//total elements from start to end
	int s = 0;
	for (int i = start;i <= end;i++) {
		s = s + a[i];
	}
	return s;
}

int lengthmin(int nums[],int n, int target) 
{// check especialy case
	int check = sumarr(nums, 0, n - 1);
	if (check < target) return 0;//total elements in array is lower than target->lengthmin = 0
	if (check == target) return n;//total elements in array equal target->lenghtmin = n

	//check from array have 1 elements to array have n-1 elements
	int length = 1;//count length
	while (length <= n - 1) {
		int s = 0, e = s + length - 1;
		while (e <= n - 1) 
		{
			if (sumarr(nums, s, e) >= target) return length;
			s++;
			e = s + length - 1;
		}
		length++;
	}
}

int main() {
	int n;
	cout << "Nhap so phan tu mang: ";
	cin >> n;
	int* nums = new int[n];
	cout << "Nhap mang duong: ";
	for (int i = 0;i < n;i++)
	{
		cin >> nums[i];
	}
	int target;
	cout << "Nhap target: ";
	cin >> target;
	
	cout << "Length min: " << lengthmin(nums, n, target);

	delete[] nums;
	return 0;
}