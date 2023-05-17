#include <iostream>
#include <vector>
#include <string>

using namespace std;

class asoc_memo
{
private:
	vector <vector <bool>> tbl;
	vector <vector <bool>> buff;
	vector <bool> addition(vector <bool> a, vector <bool> b)
	{
		vector <bool> res;
		bool trans = false;
		for (size_t i = a.size(); i > 0; i--)
		{
			if (a[i - 1] == 0 && b[i - 1] == 0 && trans == false)
			{
				res.emplace(res.begin(), 0);
				trans = false;
			}
			else if (a[i - 1] == 0 && b[i - 1] == 0 && trans == true)
			{
				res.emplace(res.begin(), 1);
				trans = false;
			}
			else if (a[i - 1] == 1 && b[i - 1] == 0 && trans == false)
			{
				res.emplace(res.begin(), 1);
				trans = false;
			}
			else if (a[i - 1] == 1 && b[i - 1] == 0 && trans == true)
			{
				res.emplace(res.begin(), 0);
				trans = true;
			}
			else if (a[i - 1] == 0 && b[i - 1] == 1 && trans == false)
			{
				res.emplace(res.begin(), 1);
				trans = false;
			}
			else if (a[i - 1] == 0 && b[i - 1] == 1 && trans == true)
			{
				res.emplace(res.begin(), 0);
				trans = true;
			}
			else if (a[i - 1] == 1 && b[i - 1] == 1 && trans == false)
			{
				res.emplace(res.begin(), 0);
				trans = true;
			}
			else if (a[i - 1] == 1 && b[i - 1] == 1 && trans == true)
			{
				res.emplace(res.begin(), 1);
				trans = true;
			}
		}
		return res;
	}
public:
	asoc_memo()
	{
		vector <bool> nl;
		for (size_t i = 0; i < 16; i++)
		{
			nl.push_back(0);
		}
		for (size_t i = 0; i < 16; i++)
		{
			tbl.push_back(nl);
		}
		for (size_t i = 0; i < 16; i++)
		{
			buff.push_back(nl);
		}
	}
	void print_tbl()
	{
		cout << " ASSOTIATIVE MEMORY" << endl;
		cout << "____________________" << endl;
		for (size_t i = 0; i < 16; i++)
		{
			cout << "| ";
			for (size_t j = 0; j < 16; j++)
			{
				cout << tbl[i][j];
			}
			cout << " |";
			cout << endl;
		}
		cout << "____________________" << endl;
	}
	void add_el(string word)
	{
		vector <bool> bool_word;
		for (size_t i = 0; i < 16 - word.size(); i++)
		{
			bool_word.insert(bool_word.begin() + i, 0);
		}
		for (size_t i = 16 - word.size(); i < 16; i++)
		{
			if (word[i - 16 + word.size()] == '1')
			{
				bool_word.insert(bool_word.begin() + i, 1);
			}
			else
			{
				bool_word.insert(bool_word.begin() + i, 0);
			}
		}
		buff.insert(buff.begin(), bool_word);
		buff.pop_back();
		tbl.clear();

		vector <bool> nl;
		for (size_t i = 0; i < 16; i++)
		{
			nl.push_back(0);
		}
		for (size_t i = 0; i < 16; i++)
		{
			tbl.push_back(nl);
		}
		size_t offset = 0;
		for (size_t i = 0; i < 16; i++)
		{
			int _i = 0 - offset;
			if (_i < 0)
			{
				_i = 16 + _i;
			}
			else
			{
				_i = i;
			}
			for (size_t j = 0; j < 16; j++)
			{
				tbl[j][i] = buff[_i][j];
				_i++;
				if (_i > 15)
				{
					_i = 0;
				}
			}
			offset++;
		}
	}
	string get_el(size_t numb)
	{
		string out = "";
		for (size_t i = 0; i < 16; i++)
		{
			out += to_string(buff[numb][i]);
		}
		return out;
	}
	void F5_and_F10(size_t i, size_t j)
	{
		string str_i = get_el(i);
		string str_j = get_el(j);
		vector <bool> bool_i;
		vector <bool> bool_j;
		vector <bool> _bool_j;
		vector <bool> res;
		string str_res = "";

		for (size_t i = 0; i < str_i.size(); i++)
		{
			if (str_i[i] == '1')
			{
				bool_i.push_back(1);
			}
			else
			{
				bool_i.push_back(0);
			}
		}
		for (size_t i = 0; i < str_i.size(); i++)
		{
			if (str_i[i] == '1')
			{
				bool_i.push_back(1);
			}
			else
			{
				bool_i.push_back(0);
			}
		}

		for (size_t i = 0; i < bool_j.size(); i++)
		{
			_bool_j.push_back(!bool_j[i]);
		}

		res = addition(_bool_j, bool_j);
		for (size_t i = 0; i < res.size(); i++)
		{
			str_res += to_string(res[i]);
		}
		add_el(str_res);
	}
	void F0_and_F15(size_t i, size_t j)
	{
		vector <bool> one = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		vector <bool> zero = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		vector <bool> res;
		string str_res = "";

		res = addition(one, zero);
		for (size_t i = 0; i < res.size(); i++)
		{
			str_res += to_string(res[i]);
		}
		add_el(str_res);
	}
	void matching_search(string wrd)
	{
		vector <vector <bool>> best_matches;
		vector <size_t> best_mutch_numb;
		size_t best_mutch_discharge = 0;
		size_t current_best_mutch_discharge;
		vector <bool> word;

		for (size_t i = 0; i < wrd.size(); i++)
		{
			if (wrd[i] == '1')
			{
				word.push_back(1);
			}
			else
			{
				word.push_back(0);
			}
		}

		for (size_t each_word = 0; each_word < tbl.size(); each_word++)
		{
			if (word != tbl[each_word])
			{
				current_best_mutch_discharge = 0;
				for (size_t each_letter = 0; each_letter < word.size(); each_letter++)
				{
					if (word[each_letter] == tbl[each_word][each_letter])
					{
						current_best_mutch_discharge = each_letter + 1;
					}
					else
					{
						each_letter = tbl[each_word].size() + 1;
					}
				}
				if (current_best_mutch_discharge > best_mutch_discharge)
				{
					best_mutch_discharge = current_best_mutch_discharge;
					best_mutch_numb.clear();
					best_matches.clear();
					best_mutch_numb.push_back(each_word);
					best_matches.push_back(tbl[each_word]);
				}
				else if (current_best_mutch_discharge == best_mutch_discharge)
				{
					best_mutch_numb.push_back(each_word);
					best_matches.push_back(tbl[each_word]);
				}
			}
		}

		for (size_t each_word = 0; each_word < best_matches.size(); each_word++)
		{
			cout << "[" << best_mutch_numb[each_word] << "] ";
			for (size_t each_letter = 0; each_letter < best_matches[each_word].size(); each_letter++)
			{
				cout << best_matches[each_word][each_letter];
			}
			cout << endl;
		}
	}
	void ariphmetics()
	{
		for (size_t i = 0; i < tbl.size(); i++)
		{
			if (int(tbl[i][0]) + int(tbl[i][1]) + int(tbl[i][2]) < 3)
			{
				vector <bool> A;
				A.push_back(tbl[i][0]);
				A.push_back(tbl[i][1]);
				A.push_back(tbl[i][2]);
				A.push_back(tbl[i][3]);

				vector <bool> B;
				B.push_back(tbl[i][4]);
				B.push_back(tbl[i][5]);
				B.push_back(tbl[i][6]);
				B.push_back(tbl[i][7]);

				vector <bool> S = addition(A, B);
				for (size_t j = 0; j < 5 - S.size(); j++)
				{
					S.push_back(0);
				}

				vector <bool> new_vect;

				for (size_t j = 0; j < 3; j++)
				{
					new_vect.push_back(tbl[i][j]);
				}
				for (size_t j = 0; j < 4; j++)
				{
					new_vect.push_back(A[j]);
				}
				for (size_t j = 0; j < 4; j++)
				{
					new_vect.push_back(B[j]);
				}
				for (size_t j = 0; j < 5; j++)
				{
					new_vect.push_back(S[j]);
				}
				tbl[i] = new_vect;
			}
		}
	}
};

int main()
{
	asoc_memo tb;
	tb.print_tbl();
	tb.add_el("1111111111111111");
	cout << endl;
	tb.print_tbl();
	tb.add_el("1010101011010101");
	cout << endl;
	tb.print_tbl();
	tb.ariphmetics();
	cout << endl;
	tb.print_tbl();
	system("pause");
	return 0;
}