#include "HashTable.h"
#include<iomanip>
void HashTable::add(string key, string info) {
	for (int i = 0; i < tableSize; i++) {
		if (key == table[i].key) {
			throw exception("такой ключ уже существует\n");
		}
	}
	int num = hashFunction(key);
	while (table[num].numNext != -1) {
		num = table[num].numNext;
	}
	if (table[num].isEmpty) {
		table[num].key = key;
		table[num].info = info;
		table[num].isEmpty = 0;
		table[num].numNext = -1;
		table[num].isLast = 1;
	}
	else {
		int newNum = num;
		while (!table[newNum].isEmpty)
		{
			newNum++;
			newNum %= tableSize;
		}
		table[newNum].key = key;
		table[newNum].info = info;
		table[newNum].isEmpty = 0;
		table[newNum].numNext = -1;
		table[newNum].isLast = 1;
		table[num].isLast = false;
		table[num].numNext = newNum;
		table[newNum].numPrev = num;
	}
}
void HashTable::remove(string key) {
	int num = hashFunction(key);
	if (table[num].key != key) {
		while (table[num].key != key) {
			num = table[num].numNext;
		}
	}
	if (table[num].numNext != -1 && table[num].numPrev == -1) {	//если элемент первый в цепочке коллизии
		int cnt = table[num].numNext;
		table[num] = table[cnt];
		table[num].numPrev = -1;
		table[cnt].key = "";
		table[cnt].info = "";
		table[cnt].isEmpty = 1;
		table[cnt].isLast = 0;
		table[cnt].numNext = -1;
		table[cnt].numPrev = -1;
	}
	if (table[num].numNext != -1 && table[num].numPrev != -1) {	//если элемент в середине цепочки
		table[table[num].numPrev].numNext = table[num].numNext;
		table[table[num].numNext].numPrev = table[num].numPrev;
		table[num].key = "";
		table[num].info = "";
		table[num].isEmpty = 1;
		table[num].isLast = 0;
		table[num].numNext = -1;
		table[num].numPrev = -1;
	}
	if (table[num].numNext == -1 && table[num].numPrev != -1) {	//если элемент в конце цепочки
		table[table[num].numPrev].numNext = -1;
		table[num].key = "";
		table[num].info = "";
		table[num].isEmpty = 1;
		table[num].isLast = 0;
		table[num].numNext = -1;
		table[num].numPrev = -1;
	}
	if (table[num].numNext == -1 && table[num].numPrev == -1) {	//если элемент не в цепочке
		table[num].key = "";
		table[num].info = "";
		table[num].isEmpty = 1;
		table[num].isLast = 0;
		table[num].numNext = -1;
		table[num].numPrev = -1;

	}
}

string HashTable::find(string key) {
	int num = hashFunction(key);
	if (table[num].key != key) {
		while (num!=-1&&table[num].key != key) {
			num = table[num].numNext;
		}
	}
	if (num == -1)return "";
	cout << "Искомое значение"  << ":" <<  table[num].info << "\n";
	return table[num].info;
}

int HashTable::hashFunction(string key) {
	int V = 0;
	string alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	for (string::iterator it = key.begin(); it != key.end(); it++){
		*it = tolower(*it);
	}
	int num;
	int p;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < alphabet.size(); j++) {
			if (key[i] == alphabet[j]) {
				num = j + 1;
				break;
			}
		}
		if (i == 0) p = 2;
		if (i == 1) p = 1;
		if (i == 2) p = 0;
		V += num * pow(33, p);
	}
	int hash;
	hash = V % tableSize;
	return hash;
}
void HashTable::print() {
	cout << setw(15)<<"ключ" << setw(4) << "С" << setw(3)<< "П"<< setw(2) << "L" <<setw(2) << "E" << "| значение" << endl;
	for (int i = 0; i < table.size(); i++) {
		cout << setw(15) << table[i].key <<"|" << setw(3) << table[i].numNext << setw(3) << table[i].numPrev << setw(2) << table[i].isLast << setw(2) << table[i].isEmpty << "| " << table[i].info << endl;
	}
}
