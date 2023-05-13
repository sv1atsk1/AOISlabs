#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;
struct trigger {
	bool g;
	bool l;
};

vector <vector <bool>> get_random() {
	vector<bool> number;
	vector<vector<bool>> table;
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 10; i++) {
			if (rand() % 2 == 1) number.push_back(1);
			else number.push_back(0);
		}
		table.push_back(number);
		number.resize(0);
	}
	return table;
}

trigger recursive_func(string argument, vector <bool> word, int i) {
	trigger final_state_of_variables;
	trigger initial_state_of_varibales;
	if (i + 1 == word.size())
	{
		initial_state_of_varibales.g = false;
		initial_state_of_varibales.l = false;
	}
	else
	{
		initial_state_of_varibales = recursive_func(argument, word, i + 1);
	}
	if (initial_state_of_varibales.g || (argument[i] == '0' && word[i] == 1 && !initial_state_of_varibales.l))
		final_state_of_variables.g = true;
	else
		final_state_of_variables.g = false;
	if (initial_state_of_varibales.l || (argument[i] == '1' && word[i] == 0 && !initial_state_of_varibales.g))
		final_state_of_variables.l = true;
	else
		final_state_of_variables.l = false;
	return final_state_of_variables;
};

void matching_search(vector <vector <bool>> book, vector <bool> word)
{
	vector <vector <bool>> best_matches;
	vector <size_t> best_match_numb;
	size_t best_match_discharge = 0;
	size_t current_best_match_discharge;

	for (size_t each_word = 0; each_word < book.size(); each_word++)
	{
		if (word != book[each_word])
		{
			current_best_match_discharge = 0;
			for (size_t each_letter = 0; each_letter < word.size(); each_letter++)
			{
				if (word[each_letter] == book[each_word][each_letter])
				{
					current_best_match_discharge = each_letter + 1;
				}
				else
				{
					each_letter = book[each_word].size() + 1;
				}
			}
			if (current_best_match_discharge > best_match_discharge)
			{
				best_match_discharge = current_best_match_discharge;
				best_match_numb.clear();
				best_matches.clear();
				best_match_numb.push_back(each_word);
				best_matches.push_back(book[each_word]);
			}
			else if (current_best_match_discharge == best_match_discharge)
			{
				best_match_numb.push_back(each_word);
				best_matches.push_back(book[each_word]);
			}
		}
	}

	for (size_t each_word = 0; each_word < best_matches.size(); each_word++)
	{
		cout << "[" << best_match_numb[each_word] << "] ";
		for (size_t each_letter = 0; each_letter < best_matches[each_word].size(); each_letter++)
		{
			cout << best_matches[each_word][each_letter];
		}
		cout << endl;
	}

	cout << "Max matches discharge: " << best_match_discharge << endl;
}

bool booleanSearch(const vector<vector<bool>>& book, const string& argument, bool (*boolFunction)(const vector<bool>&))
{
	for (size_t i = 0; i < book.size(); i++)
	{
		const vector<bool>& word = book[i];
		if (boolFunction(word))
		{
			cout << "[" << i << "] ";
			for (bool bit : word)
			{
				cout << bit;
			}
			cout << endl;
		}
	}

	return true;
}

bool booleanFunctionAND(const vector<bool>& word)
{
	return word[0] && word[1] && word[2];
}

bool booleanFunctionOR(const vector<bool>& word)
{
	return word[0] || word[1] || word[2];
}

bool booleanFunctionXOR(const vector<bool>& word)
{
	return (word[0] && !word[1] && !word[2]) || (!word[0] && word[1] && !word[2]) || (!word[0] && !word[1] && word[2]);
}


int main() {
	setlocale(LC_ALL, "Russian");
	vector<vector<bool>> dictionary = get_random();
	for (int i = 0; i < dictionary.size(); i++) {
		cout << "[" << i << "] ";
		for (int j = 0; j < dictionary[i].size(); j++) {
			cout << dictionary[i][j];
		}
		cout << endl;
	}
	int choice;
	cout << "Выберите операцию:" << "\n" << "1 - Поиск по соответствию " << "\n" << "2 - Поиск на основе булевых функций" << endl;
	cin >> choice;
	if (choice == 1)
	{
		cout << endl << "Enter the number of word to search matching: ";
		int matching;
		cin >> matching;
		matching_search(dictionary, dictionary[matching]);
		cout << endl << "Enter the word to search: ";
		string a;
		cin >> a;
		for (int i = 0; i < dictionary.size(); i++) {
			cout << "[" << i << "]";
			trigger compare = recursive_func(a, dictionary[i], 0);
			cout << compare.g << " " << compare.l << endl;
		}
	}
	else
	{
		cout << endl << "Enter the word to search: ";
		string a;
		cin >> a;
		int operation;
		cout << "Выберите операцию для поиска:" << endl;
		cout << "1 - И" << endl;
		cout << "2 - ИЛИ" << endl;
		cout << "3 - Исключающее ИЛИ" << endl;
		cin >> operation;
		bool (*boolFunction)(const vector<bool>&) = nullptr;
		switch (operation)
		{
		case 1:
			boolFunction = booleanFunctionAND;
			break;
		case 2:
			boolFunction = booleanFunctionOR;
			break;
		case 3:
			boolFunction = booleanFunctionXOR;
			break;
		default:
			cout << "Недопустимая операция" << endl;
			return 0;
		}

		booleanSearch(dictionary, a, boolFunction);
		return 0;
	}
}