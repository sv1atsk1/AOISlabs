#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

class HashTable
{
private:
	const int tableSize = 20;
public:
	struct Element {
		string key;
		string info;
		int numNext;
		int numPrev;
		bool isLast;
		bool isEmpty;
	};
	HashTable() {
		table.resize(tableSize);
		for (int i = 0; i < tableSize; i++) {
			table[i].key = "";
			table[i].info = "";
			table[i].numNext = -1;
			table[i].numPrev = -1;
			table[i].isLast = 0;
			table[i].isEmpty = 1;
		}
	}
	vector<Element> table;
	void add(string key, string info);
	void remove(string key);
	string find(string key);
	int hashFunction(string key);
	void print();
};

