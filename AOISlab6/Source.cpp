#include "HashTable.h"

int main() {
	system("chcp 1251");
	HashTable table;
	table.add("сила", "Н");
	try {
		table.add("сила", "Дж");
	}
	catch (const exception& e) {
		cout << e.what();
	}
	table.add("сила тока", "А");
	table.add("энергия", "Дж");
	table.add("время", "с");
	table.add("масса", "кг");
	table.add("расстояние", "м");
	table.add("скорость", "м/с");
	table.add("мощность", "Вт");
	table.add("заряд", "Кл");
	table.add("давление", "Па");
	table.add("напряжение", "В");
	table.add("частота", "Гц");
	table.add("поток", "Вб");
	table.add("сопротивление", "Ом");
	table.print();
	//table.remove("сила притяжения");
	//cout << table.find("сила притяжения");
	return 0;
}
