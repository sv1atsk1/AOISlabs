#include <string>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

vector<string> fragmentationAND(string sourceString) {
	vector<string> result;
	while (sourceString != "")
	{
		if (sourceString.find("*") == -1)
		{
			result.push_back(sourceString);
			sourceString = "";
		}
		else
		{
			result.push_back(sourceString.substr(0, sourceString.find("*")));
			sourceString.erase(0, sourceString.find("*") + 1);
		}
	};
	return result;
}

vector<string> fragmentationAND2(string sourceString) {
	vector<string> result;
	while (sourceString != "")
	{
		result.push_back(sourceString.substr(1, sourceString.find(")") - 1));
		sourceString.erase(0, sourceString.find(")") + 2);
	};
	return result;
}

string checkAreNeighboursSDNF(string s1, string s2) {
	vector<string> a = fragmentationAND(s1);
	vector<string> b = fragmentationAND(s2);
	string minNeighboursResult = "";
	int k = 0;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			if (a[i] == b[j]) {
				if (minNeighboursResult == "")
				{
					minNeighboursResult += a[i];
				}
				else
				{
					minNeighboursResult += "*" + a[i];
				}
				break;
			}
			if (j == b.size() - 1 && a[i] != b[j])
			{
				k++;
			}
		}
		if (k > 1)
		{
			return "";
		}
	}
	return minNeighboursResult;
}

vector<string> fragmentationOR(string sourceString) {
	if (sourceString[0] == '(')
	{
		sourceString = sourceString.substr(1, sourceString.length() - 2);
	}
	vector<string> fragments;
	while (sourceString != "")
	{
		if (sourceString.find("+") == -1)
		{
			fragments.push_back(sourceString);
			sourceString = "";
		}
		else
		{
			fragments.push_back(sourceString.substr(0, sourceString.find("+")));
			sourceString.erase(0, sourceString.find("+") + 1);
		}
	};
	return fragments;
}

string gluingSDNF(string sourceString) {
	string resultOfGluing = "";
	vector<string> fragments = fragmentationOR(sourceString);
	for (int i = 0; i < fragments.size(); i++)
	{
		for (int j = i + 1; j < fragments.size(); j++)
		{
			if (checkAreNeighboursSDNF(fragments[i], fragments[j]) != "")
			{
				if (resultOfGluing == "")
				{
					resultOfGluing += checkAreNeighboursSDNF(fragments[i], fragments[j]);
				}
				else
				{
					resultOfGluing += "+" + checkAreNeighboursSDNF(fragments[i], fragments[j]);
				}
			}
		}
	}
	return resultOfGluing;
}

string reverse(string sourceString) {
	if (sourceString[0] == '!')
	{
		return sourceString.substr(1, sourceString.length());
	}
	else
	{
		return "!" + sourceString;
	}
}

bool find(vector<string> sourceString, string stringToFind) {
	for (int i = 0; i < sourceString.size(); i++) {
		if (sourceString[i] == stringToFind)
		{
			return true;
		}
	}
	return false;
}

bool checkExcess(vector<string> sourceConstituents, int q) {
	vector<vector<string>> fragmentedConstituents;
	vector<string> fragmentsAnalyzingVector;
	for (int i = 0; i < sourceConstituents.size(); i++)
	{
		vector<string> fragmentsAnalyzingVector = fragmentationAND(sourceConstituents[i]);
		fragmentedConstituents.push_back(fragmentsAnalyzingVector);
	}
	vector<string> k = fragmentedConstituents[q];
	for (int i = 0; i < k.size(); i++) {
		for (int j = 0; j < fragmentedConstituents.size(); j++)
		{
			if (j != q)
			{
				if (find(fragmentedConstituents[j], reverse(k[i])))
				{
					fragmentedConstituents.erase(fragmentedConstituents.begin() + j);
				}
			}
		}
	}

	for (int i = 0; i < fragmentedConstituents.size(); i++)
	{
		if (i != q)
		{
			for (int j = 0; j < fragmentedConstituents[i].size(); j++)
			{
				if (!find(k, fragmentedConstituents[i][j]))
				{
					fragmentsAnalyzingVector.push_back(fragmentedConstituents[i][j]);
				}
			}
		}
	}

	for (int i = 0; i < fragmentsAnalyzingVector.size(); i++)
	{
		if (!find(fragmentsAnalyzingVector, reverse(fragmentsAnalyzingVector[i])))
		{
			return false;
		}
	}
	return true;
}

string toTDF(string sourceString) {
	vector<string> r = fragmentationOR(sourceString);
	for (int i = 0; i < r.size(); i++)
	{
		if (checkExcess(r, i))
		{
			sourceString.erase(sourceString.find(r[i]), r[i].length() + 1);
		}
	}
	return sourceString;
}

string checkAreNeighboursSKNF(string s1, string s2) {
	vector<string> a = fragmentationOR(s1);
	vector<string> b = fragmentationOR(s2);
	string ret = "(";
	int k = 0;
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < b.size(); j++)
		{
			if (a[i] == b[j])
			{
				if (ret == "(")
				{
					ret += a[i];
				}
				else
				{
					ret += "+" + a[i];
				}
				break;
			}
			if (j == b.size() - 1 && a[i] != b[j])
			{
				k++;
			}
		}
		if (k > 1)
		{
			return "";
		}
	}
	ret += ")";
	return ret;
}

string gluingSKNF(string sourceString) {
	string gluingResult = "";
	vector<string> fragments = fragmentationAND2(sourceString);
	for (int i = 0; i < fragments.size(); i++)
	{
		for (int j = i + 1; j < fragments.size(); j++)
		{
			if (checkAreNeighboursSKNF(fragments[i], fragments[j]) != "")
				if (gluingResult == "")
				{
					gluingResult += checkAreNeighboursSKNF(fragments[i], fragments[j]);
				}
				else
				{
					gluingResult += "*" + checkAreNeighboursSKNF(fragments[i], fragments[j]);
				}
		}
	}
	return gluingResult;
}

bool checkExcess2(vector<string> s, int q) {
	vector<vector<string>> r;
	vector<string> d;

	for (int i = 0; i < s.size(); i++) {
		vector<string> t = fragmentationOR(s[i]);
		r.push_back(t);
	}
	vector<string> k = r[q];

	for (int i = 0; i < k.size(); i++)
	{
		for (int j = 0; j < r.size(); j++)
		{
			if (j != q)
			{
				if (find(r[j], reverse(k[i])))
				{
					r.erase(r.begin() + j);
				}
			}
		}
	}

	for (int i = 0; i < r.size(); i++)
	{
		if (i != q)
		{
			for (int j = 0; j < r[i].size(); j++)
			{
				if (!find(k, r[i][j]))
				{
					d.push_back(r[i][j]);
				}
			}
		}
	}

	for (int i = 0; i < d.size(); i++)
	{
		if (find(d, reverse(d[i])))
		{
			return true;
		}
	}

	return false;
}

string toTKF(string sourceString) {
	vector<string> r = fragmentationAND2(sourceString);
	for (int i = 0; i < r.size(); i++) {
		if (checkExcess2(r, i))
		{
			sourceString.erase(sourceString.find(r[i]), r[i].length() + 3);
		}
	}
	return sourceString;
}

bool isInclude(string s1, string s2) {
	vector<string> v = fragmentationAND(s1);
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].length() == 2)
		{
			if (s2.find("*" + v[i]) == -1 && s2.find("+" + v[i]) == -1 && s2.find(v[i]) != 0)
			{
				return false;
			}
		}
		else
		{
			if (s2.find(v[i]) == -1)
			{
				return false;
			}
		}
	}
	return true;
}

string MCClassSDNF(string SDNF, string DNF) {
	vector<string> fragmentedSDNF = fragmentationOR(SDNF);
	vector<string> fragmentedDNF = fragmentationOR(DNF);
	vector<vector<char>> table;
	vector<string> preResult;
	table.resize(fragmentedDNF.size());
	for (int i = 0; i < table.size(); i++) {
		table[i].resize(fragmentedSDNF.size());
	};
	for (int i = 0; i < fragmentedDNF.size(); i++)
		for (int j = 0; j < fragmentedSDNF.size(); j++)
		{
			if (isInclude(fragmentedDNF[i], fragmentedSDNF[j]))
				table[i][j] = 'X';
		};

	for (int i = 0; i < fragmentedSDNF.size(); i++)
	{
		cout << "\t  " << fragmentedSDNF[i];
	}

	for (int i = 0; i < fragmentedDNF.size(); i++)
	{
		cout << endl;
		cout << fragmentedDNF[i] << "     ";
		for (int j = 0; j < fragmentedSDNF.size(); j++)
			cout << table[i][j] << "\t\t     ";
	}

	for (int i = 0; i < fragmentedDNF.size(); i++) {
		bool u = false;
		for (int j = 0; j < fragmentedSDNF.size(); j++)
		{

			if (table[i][j] == 'X')
			{
				for (int k = 0; k < fragmentedDNF.size(); k++)
				{
					if (table[k][j] == 'X')
					{
						if (k != i)
							break;
					}
					else
						if (k + 2 == fragmentedDNF.size())
						{
							u = true;
							break;
						}
				}

			}
			if (u)
				break;
		}
		if (!u)
			preResult.push_back(fragmentedDNF[i]);
	}

	for (int i = 0; i < preResult.size(); i++) {
		if (!DNF.find(preResult[i]))
		{
			DNF.erase(0, preResult[i].length() + 1);
		}
		else
		{
			DNF.erase(DNF.find(preResult[i]) - 1, preResult[i].length() + 1);
		}
	}

	return  DNF;
}

bool isInclude2(string s1, string s2) {
	vector<string> v = fragmentationOR(s1);
	for (int i = 0; i < v.size(); i++) {
		if (v[i].length() == 2)
		{
			if (s2.find("+" + v[i]) == -1 && s2.find(v[i]) != 0)
				return false;
		}
		else
			if (s2.find(v[i]) == -1)
				return false;
	}
	return true;
}

string MCClassSKNF(string SKNF, string KNF) {
	vector<string> h = fragmentationAND2(SKNF);
	vector<string> l = fragmentationAND2(KNF);
	vector<vector<char>> table;
	vector<string> r;
	table.resize(l.size());

	for (int i = 0; i < table.size(); i++) {
		table[i].resize(h.size());
	};

	for (int i = 0; i < l.size(); i++)
	{
		for (int j = 0; j < h.size(); j++)
		{
			if (isInclude2(l[i], h[j]))
				table[i][j] = 'X';
		};
	}

	for (int i = 0; i < h.size(); i++)
	{
		cout << "\t  " << h[i];
	}

	for (int i = 0; i < l.size(); i++)
	{
		cout << '\n' << l[i] << "     ";
		for (int j = 0; j < h.size(); j++)
			cout << table[i][j] << "\t\t     ";
	}

	for (int i = 0; i < l.size(); i++) {
		bool u = false;
		for (int j = 0; j < h.size(); j++)
		{

			if (table[i][j] == 'X')
			{
				for (int k = 0; k < l.size(); k++)
				{
					if (table[k][j] == 'X')
					{
						if (k != i)
							break;
					}
					else
						if (k + 2 == l.size())
						{
							u = true;
							break;
						}
				}

			}
			if (u)
				break;
		}
		if (!u)
			r.push_back(l[i]);
	}
	for (int i = 0; i < r.size(); i++) {
		if (!KNF.find(r[i]))
			KNF.erase(0, r[i].length() + 1);
		else
			KNF.erase(KNF.find(r[i]) - 1, r[i].length() + 3);
	}
	return  KNF;
}

vector<vector<int>> makeDiagram(int countOfArguments) {
	int horizontalO;
	vector<vector<int>> diagram;
	if (countOfArguments % 2 == 0)
	{
		diagram.resize(pow(2, countOfArguments / 2));
		horizontalO = pow(2, countOfArguments / 2);
	}
	else
	{
		diagram.resize(pow(2, (countOfArguments - 1) / 2));
		horizontalO = pow(2, (countOfArguments + 1) / 2);
	}
	for (int i = 0; i < diagram.size(); i++)
	{
		vector<int> t(horizontalO);
		diagram[i] = t;
	}
	return diagram;
}

int GrayCode(unsigned int code) {
	return code ^ (code >> 1);
}

string twoten(int x, int n) {
	string k;
	int i = 0;
	long int c = 0;
	while (x != 0) {
		while (x - pow(2, i + 1) >= 0)
		{
			i++;
		}
		x -= pow(2, i);
		c += pow(10, i);
		i = 0;
	};
	k = to_string(c);
	while (k.length() < n)
	{
		k = '0' + k;
	}
	return k;
}

bool isInclude3(string s, string str) {
	vector<string> Str = fragmentationOR(str);
	for (int i = 0; i < Str.size(); i++) {
		if (isInclude(s, Str[i]))
		{
			return true;
		}
	};
	return false;
}

string FindTDF(string s1, string s2) {
	string d = "";
	for (int i = 0; i < s1.length(); i++) {
		if (s1[i] == '0' && s2[i] == '0')
			d += "*!x" + to_string(i + 1);
		if (s1[i] == '1' && s2[i] == '1')
			d += "*x" + to_string(i + 1);
	}
	d.erase(0, 1);
	return d;
}

vector<string> normal(vector<string> s) {
	vector<string> t;
	for (int i = 0; i < s.size(); i++) {
		if (!find(t, s[i]))
			t.push_back(s[i]);
	};
	for (int i = 0; i < t.size(); i++) {
		vector<string> fr = fragmentationAND(t[i]);
		bool g = false;
		for (int k = 0; k < t.size(); k++)
		{
			if (k != i)
				if ((isInclude(fr[0], t[k]) && isInclude(fr[1], t[k + 1])) ||
					(isInclude(fr[1], t[k]) && isInclude(fr[0], t[k + 1])))
				{
					t.erase(t.begin() + i);
					g = true;
					break;
				}
		}
		if (g)
		{
			break;
		}
	};
	return t;
}

string WeichCarno(string SDNF, int countOfArguments) {
	vector<vector<int>> diagram = makeDiagram(countOfArguments);
	vector<string> v;
	vector<string> g;
	vector<string> answer;
	string TF;
	int horizontalO = 0;
	int verticalO = 0;
	if (countOfArguments % 2 == 0) {
		horizontalO = pow(2, countOfArguments / 2);
		verticalO = pow(2, countOfArguments / 2);
	}
	else {
		horizontalO = pow(2, (countOfArguments + 1) / 2);
		verticalO = pow(2, (countOfArguments - 1) / 2);
	}
	for (int i = 0; i < verticalO; i++)
		v.push_back(twoten(GrayCode(i), log2(verticalO)));
	for (int i = 0; i < horizontalO; i++)
		g.push_back(twoten(GrayCode(i), log2(horizontalO)));
	for (int i = 0; i < diagram.size(); i++)
		for (int j = 0; j < diagram[i].size(); j++)
		{
			string s = v[i] + g[j];
			string b = "";
			for (int k = 0; k < s.length(); k++)
			{

				if (s[k] == '0')
					if (b == "")
						b += "!x" + to_string(k + 1);
					else
						b += "*!x" + to_string(k + 1);
				else
					if (b == "")
						b += "x" + to_string(k + 1);
					else
						b += "*x" + to_string(k + 1);
			}
			if (!isInclude3(b, SDNF))
				diagram[i][j] = 0;
			else
				diagram[i][j] = 1;
		}

	for (int i = 0; i < g.size(); i++)
	{
		cout << "\t" << g[i];
	}

	for (int i = 0; i < v.size(); i++)
	{
		cout << '\n' << v[i] << "      ";
		for (int j = 0; j < g.size(); j++)
		{
			cout << diagram[i][j] << "\t ";
		}
	}

	for (int i = 0; i < diagram.size(); i++)
	{
		for (int j = 0; j < diagram[i].size(); j++)
		{
			if (diagram[i][j] == 1)
			{
				if (i + 1 < diagram.size())
					if (diagram[i + 1][j] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i + 1] + g[j]));
				if (i - 1 >= 0)
					if (diagram[i - 1][j] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i - 1] + g[j]));
				if (j - 1 >= 0)
				{
					if (diagram[i][j - 1] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i] + g[j - 1]));
				}
				else
				{
					if (diagram[i][g.size() - 1] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i] + g[g.size() - 1]));
				}
				if (j + 1 < g.size())
				{
					if (diagram[i][j + 1] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i] + g[j + 1]));
				}
				else
				{
					if (diagram[i][0] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i] + g[0]));
				}

			}
		}
	}
	answer = normal(answer);

	for (int i = 0; i < diagram.size(); i++)
	{
		TF += "+" + answer[i];
	}

	TF.erase(0, 1);
	return TF;
}

bool isInclude4(string s, string str) {
	vector<string> Str = fragmentationAND2(str);
	for (int i = 0; i < Str.size(); i++)
	{
		if (isInclude2(s, Str[i]))
		{
			return true;
		}
	};
	return false;
}

string FindTKF(string s1, string s2) {
	string d = "(";
	for (int i = 0; i < s1.length(); i++) {
		if (s1[i] == '0' && s2[i] == '0')
			d += "+x" + to_string(i + 1);
		if (s1[i] == '1' && s2[i] == '1')
			d += "+!x" + to_string(i + 1);
	}
	d.erase(1, 1);
	d += ")";
	return d;
}

vector<string> normal2(vector<string> s) {
	vector<string> t;
	for (int i = 0; i < s.size(); i++)
	{
		if (!find(t, s[i].substr(1, s[i].length() - 2)))
		{
			t.push_back(s[i].substr(1, s[i].length() - 2));
		}
	};
	for (int i = 0; i < t.size(); i++)
	{
		vector<string> fr = fragmentationOR(t[i]);
		bool g = false;
		int u = 0;
		for (int k = 0; k < t.size(); k++)
		{
			if (k != i)
			{
				if (isInclude2(fr[u], t[k]))
				{
					u++;
				}
			}
			if (u == 2)
			{
				t.erase(t.begin() + i);
				g = true;
				break;
			}
		}
		if (g)
		{
			break;
		}
	};
	return t;
}

string WeichCarno2(string SKNF, int n) {
	vector<vector<int>> diagram = makeDiagram(n);
	vector<string> v;
	vector<string> g;
	vector<string> answer;
	string TF;
	int horizontalO;
	int verticalO;
	if (n % 2 == 0) {
		horizontalO = pow(2, n / 2);
		verticalO = pow(2, n / 2);
	}
	else {
		horizontalO = pow(2, (n + 1) / 2);
		verticalO = pow(2, (n - 1) / 2);
	}
	for (int i = 0; i < verticalO; i++)
		v.push_back(twoten(GrayCode(i), log2(verticalO)));
	for (int i = 0; i < horizontalO; i++)
		g.push_back(twoten(GrayCode(i), log2(horizontalO)));
	for (int i = 0; i < diagram.size(); i++)
	{
		for (int j = 0; j < diagram[i].size(); j++)
		{
			string s = v[i] + g[j];
			string b = "";
			for (int k = 0; k < s.length(); k++)
			{

				if (s[k] == '0')
				{
					if (b == "")
					{
						b += "x" + to_string(k + 1);
					}
					else
					{
						b += "+x" + to_string(k + 1);
					}
				}
				else
				{
					if (b == "")
					{
						b += "!x" + to_string(k + 1);
					}
					else
					{
						b += "+!x" + to_string(k + 1);
					}
				}
			}
			if (isInclude4(b, SKNF))
				diagram[i][j] = 0;
			else
				diagram[i][j] = 1;
		}
	}
	for (int i = 0; i < g.size(); i++)
		cout << "\t" << g[i];
	for (int i = 0; i < v.size(); i++)
	{
		cout << '\n' << v[i] << "      ";
		for (int j = 0; j < g.size(); j++)
			cout << diagram[i][j] << "\t ";
	}
	for (int i = 0; i < diagram.size(); i++)
	{
		for (int j = 0; j < diagram[i].size(); j++)
		{
			if (!diagram[i][j])
			{
				if (i + 1 < diagram.size())
					if (!diagram[i + 1][j])
						answer.push_back(FindTKF(v[i] + g[j], v[i + 1] + g[j]));
				if (i - 1 >= 0)
					if (!diagram[i - 1][j])
						answer.push_back(FindTKF(v[i] + g[j], v[i - 1] + g[j]));
				if (j - 1 >= 0)
				{
					if (!diagram[i][j - 1])
						answer.push_back(FindTKF(v[i] + g[j], v[i] + g[j - 1]));
				}
				else
				{
					if (!diagram[i][g.size() - 1])
						answer.push_back(FindTKF(v[i] + g[j], v[i] + g[g.size() - 1]));
				}
				if (j + 1 < g.size())
				{
					if (!diagram[i][j + 1])
						answer.push_back(FindTKF(v[i] + g[j], v[i] + g[j + 1]));
				}
				else
				{
					if (!diagram[i][0])
						answer.push_back(FindTKF(v[i] + g[j], v[i] + g[0]));
				}

			}
		}
	}
	answer = normal2(answer);
	for (int i = 0; i < diagram.size(); i++)
	{
		TF += ")*(" + answer[i];
	}
	TF.erase(0, 2);
	TF += ')';
	return TF;
}
