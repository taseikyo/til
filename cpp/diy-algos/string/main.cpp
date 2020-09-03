/**
 * @date    2020-09-03 16:56:20
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

#include <iostream>
#include "tstring.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	tstring a("abcxyz123");
	tstring b;
	b = a;
	tstring c(b);
	tstring d(move(tstring("taseikyo")));
	tstring e;
	e = move(c);
	cout << "a " << a << endl;
	cout << "b " << b << endl;
	cout << "c " << c << endl;
	cout << "d " << d << endl;
	cout << "e " << e << endl;
	e[2] = '*';
	e[754] = '+';
	for (int i = 0; i < e.size(); ++i) {
		cout << e[i] << " ";
	}
	cout << endl;
	return 0;
}