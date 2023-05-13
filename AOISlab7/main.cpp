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

vector<vector<bool>> findBestMatches(const vector<vector<bool>>& book, const vector<bool>& word)
{
	vector<vector<bool>> bestMatches;
	vector<size_t> bestMatchIndices;
	size_t bestMatchDischarge = 0;
	size_t currentBestMatchDischarge;

	for (size_t eachWord = 0; eachWord < book.size(); eachWord++)
	{
		if (word != book[eachWord])
		{
			currentBestMatchDischarge = 0;
			for (size_t eachLetter = 0; eachLetter < word.size(); eachLetter++)
			{
				if (word[eachLetter] == book[eachWord][eachLetter])
				{
					currentBestMatchDischarge = eachLetter + 1;
				}
				else
				{
					eachLetter = book[eachWord].size() + 1;
				}
			}
			if (currentBestMatchDischarge > bestMatchDischarge)
			{
				bestMatchDischarge = currentBestMatchDischarge;
				bestMatchIndices.clear();
				bestMatches.clear();
				bestMatchIndices.push_back(eachWord);
				bestMatches.push_back(book[eachWord]);
			}
			else if (currentBestMatchDischarge == bestMatchDischarge)
			{
				bestMatchIndices.push_back(eachWord);
				bestMatches.push_back(book[eachWord]);
			}
		}
	}

	return bestMatches;
}

void printMatches(const vector<vector<bool>>& matches, const vector<size_t>& matchIndices, size_t bestMatchDischarge)
{
	for (size_t eachWord = 0; eachWord < matches.size(); eachWord++)
	{
		cout << "[" << matchIndices[eachWord] << "] ";
		for (size_t eachLetter = 0; eachLetter < matches[eachWord].size(); eachLetter++)
		{
			cout << matches[eachWord][eachLetter];
		}
		cout << endl;
	}

	cout << "Max matches discharge: " << bestMatchDischarge << endl;
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
	cout << "Choose an operation:" << "\n" << "1 - Search by match " << "\n" << "2 - Search based on Boolean function" << endl;
	cin >> choice;
	if (choice == 1)
	{
		cout << endl << "Enter the number of word to search matching: ";
		size_t matching;
		cin >> matching;
		vector<vector<bool>> matches = findBestMatches(dictionary, dictionary[matching]);
		printMatches(matches, vector<size_t>{matching}, matches.size() > 0 ? matches[0].size() : 0);
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
		cout << "Select an operation to search:" << endl;
		cout << "1 - AND" << endl;
		cout << "2 - OR" << endl;
		cout << "3 - XOR" << endl;
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
			cout << "Invalid operation" << endl;
			return 0;
		}

		booleanSearch(dictionary, a, boolFunction);
		return 0;
	}
}
