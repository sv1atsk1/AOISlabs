#include "HashTable.h"

int main() {
	system("chcp 1251");
	HashTable table;
	table.add("����", "�");
	try {
		table.add("����", "��");
	}
	catch (const exception& e) {
		cout << e.what();
	}
	table.add("���� ����", "�");
	table.add("�������", "��");
	table.add("�����", "�");
	table.add("�����", "��");
	table.add("����������", "�");
	table.add("��������", "�/�");
	table.add("��������", "��");
	table.add("�����", "��");
	table.add("��������", "��");
	table.add("����������", "�");
	table.add("�������", "��");
	table.add("�����", "��");
	table.add("�������������", "��");
	table.print();
	//table.remove("���� ����������");
	//cout << table.find("���� ����������");
	return 0;
}