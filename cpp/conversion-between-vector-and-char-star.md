> @Date    : 2020-06-03 15:49:53
> @Author  : Lewis Tian (taseikyo@gmail.com)
> @Link    : github.com/taseikyo

## vector 与 char* 相互转换

```c++
// http://www.cplusplus.com/reference/vector/vector/insert/
template <class InputIterator>
void insert (iterator position, InputIterator first,
             InputIterator last);
```

```c++
// char* --> vector<char>
char *str = "1234";
vector<char> vec;

vec.insert(vec.end(), str, str + strlen(str));
```

```c++
// vector<char> --> char*
char *str = &vec[0];

```

```c++
// a case

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstring>

using namespace std;

void printVector(const vector<char>& v) {
	cout << "vector content: ";
	for_each(v.cbegin(), v.cend(), [](const char& val)->void{cout << val; });
	cout << endl;
}

int main(int argc, char const *argv[]) {
	vector<char> vdata;
	const char* in = "test1";
	vdata.insert(vdata.end(), in, in + strlen(in));
	vdata.insert(vdata.end(), 'a');
	printVector(vdata);
	cout << endl;

	char* out = &vdata[0];
	cout << "vector<char> --> char* : " << out << endl;
	out[0] = 'j';//can changes the vector's content
	cout << "vector<char> --> char* after change content: " << out <<
	     endl;
	printVector(vdata);

	cout << endl;
	cout << "get copied char* from vector<char>..." << endl;
	char *buffer = new char[vdata.size()];
	std::copy(vdata.begin(), vdata.end(), buffer);
	cout << "vector<char> --> char* : " << buffer << endl;
	buffer[0] = 'z';//can changes the vector's content
	cout << "vector<char> --> char* after change content: " << buffer <<
	     endl;
	printVector(vdata);

	return 0;
}
```