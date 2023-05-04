#include "functions.h"
#include <string>
#include <vector>
#include <iostream>
#include <math.h>


using namespace std;

int main(void)
{
	string SDNF = "!x1*!x2*x3+!x1*x2*!x3+!x1*x2*x3+x1*x2*!x3";
	string SKNF = "(x1+x2+x3)*(!x1+x2+x3)*(!x1+x2+!x3)*(!x1+!x2+!x3)";

	string DNF = gluingSDNF(SDNF);
	string TDF = toTDF(DNF);
	cout << "TDF: " << TDF << endl;

	string KNF = gluingSKNF(SKNF);
	string TKF = toTKF(KNF);
	cout << "KNF: " << TKF << endl;

	for (int i = 0; i < 80; cout << '.', i++);
	cout << "\n\n";

	TDF = MCClassSDNF(SDNF, DNF);
	cout << "\n\n" << TDF << "\n\n";
	TKF = MCClassSKNF(SKNF, KNF);
	cout << "\n\n" << TKF << "\n\n";

	for (int i = 0; i < 80; cout << '.', i++);
	cout << "\n\n";

	TDF = WeichCarno(SDNF, 3);
	cout << "\n\n" << TDF << "\n\n";
	TKF = WeichCarno2(SKNF, 3);
	cout << "\n\n" << TKF << '\n';

	system("pause > NUL");
	return 0;
}