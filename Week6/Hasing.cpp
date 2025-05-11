#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
const int m = 2000;
const int p = 31;
using namespace std;
struct Company {
	string name;
	string profit_tax;
	string address;
	Company() : name(""), profit_tax(""), address("") {}
};
struct HashTable {
	vector<Company*> table;
	bool occupied[m] = {};
	HashTable() : table(m) 
	{
		for (int i = 0;i < table.size(); i++)
			table[i] = new Company;
	}
};
bool readFile(const char* filename,vector<string>& inputList)
{
	ifstream iFile(filename);
	if (!iFile)
	{
		cout << "Cannot open file " << filename;
		return false;
	}

	string temp;
	while (getline(iFile, temp))
	{
		inputList.push_back(temp);
	}
	cout << "Read file " << filename << " success\n";
	return true;
}
bool writeFile(const char* filename, vector<string> outputList)
{
	ofstream oFile(filename);
	if (!oFile)
	{
		cout << "Cannot open file " << filename;
		return false;
	}

	for (int i = 0;i < (int)outputList.size();i++)
	{
		oFile << outputList[i] << endl;
	}
	cout << "Write file "<<filename<<" success\n";
	return true;
}
vector<Company> readCompanyList(const char* filename)
{
	vector<Company> ListCompany;
	ifstream iFile(filename);
	if (!iFile)
	{
		cout << "Cannot open file "<<filename;
	}
	else
	{
		string line;
		getline(iFile, line); //skip line describe
		while (getline(iFile, line))
		{
			stringstream ss(line);
			Company company;
			getline(ss, company.name, '|');
			getline(ss, company.profit_tax, '|');
			getline(ss, company.address, '|');
			ListCompany.push_back(company);
		}
	}
	cout << "Read file " << filename << " success\n";
	return ListCompany;
}

long long hashString(string company_Name)
{
	long long result = 0;
	long long power = 1;
	if (company_Name.length() > 20) 
		company_Name = company_Name.substr(company_Name.length() - 20);
	for (int i = 0;i < company_Name.length(); i++)
	{
		result = (result + company_Name[i] * power) % m;
		power = (power * p) % m;
	}
	return result % m;
}
HashTable* createHashTable(vector<Company> ListCompany)
{
	HashTable* hashtable = new HashTable;
	for (int i = 0;i < (int)ListCompany.size(); i++)
	{
		long long original_index = hashString(ListCompany[i].name);
		long long index = original_index;
		while (hashtable->occupied[index])
		{
			if (hashtable->table[index] && hashtable->table[index]->name == ListCompany[i].name) break;// name is inserted
			index = (index + 1) % m;
			if (index == original_index) break;
		}
		if (!hashtable->occupied[index])
		{
			hashtable->table[index]->name = ListCompany[i].name;
			hashtable->table[index]->profit_tax = ListCompany[i].profit_tax;
			hashtable->table[index]->address = ListCompany[i].address;
			hashtable->occupied[index] = true;
		}
	}
	return hashtable;
}

Company* search(HashTable* hashtable, string company_Name)
{
	long long original_index = hashString(company_Name);
	long long index = original_index;
	while (hashtable->occupied[index])
	{
		if (hashtable->table[index] && hashtable->table[index]->name == company_Name)
			return hashtable->table[index];
		index = (index + 1) % m;
		if (index == original_index) break;
	}
	return nullptr;
}

int main(int argc,char* argv[]) {
	if (argc != 4)
	{
		cout << "Usage: main MST.txt input.txt output.txt\n";
		return 1;
	}
	const char* MSTFile = argv[1];
	const char* inputFile = argv[2];
	const char* outputFile = argv[3];

	vector<Company> ListCompany = readCompanyList(MSTFile);

	HashTable* hashtable=createHashTable(ListCompany);

	vector<string> input_CompanyName;
	if (!readFile(inputFile, input_CompanyName)) return 1;

	vector<string> outputSearch;
	for (int i = 0;i < (int)input_CompanyName.size();i++)
	{
		Company* result=search(hashtable, input_CompanyName[i]);
		string temp = "";
		if (result)
			temp = result->name + '|' + result->profit_tax + '|' + result->address;
		else
			temp = "NULL";
		outputSearch.push_back(temp);
	}
	if (!writeFile(outputFile, outputSearch)) return 1;

	return 0;
}