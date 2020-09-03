/**
 * @date    2020-09-03 16:23:21
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

#include <cstring>
#include <iostream>
#include "tstring.hpp"

/**
 * 变相理解了【私有变量在类内访问】这么一点
 * 
 * 比如下面拷贝构造函数中
 * 可以直接访问 str 参数的 tsize 和 tstr 私有成员
 */

// 返回字符串的 size
size_t tstring::size() const {
	return tsize;
}

// 返回字符串
const char* tstring::c_str() const {
	return tstr;
}

// 构造函数
tstring::tstring(const char *str) {
	if (!str) {
		tstr = new char[1];
		*tstr = '\0';
		tsize = 0;
	} else {
		tsize = strlen(str) + 1;
		tstr = new char[tsize];
		strcpy(tstr, str);
	}
	std::cout << "constructor called!\n";
}

// 析构函数
tstring::~tstring() {
	delete[] tstr;
	tstr = nullptr;
	tsize = 0;
}

// 拷贝构造
tstring::tstring(const tstring &str) {
	std::cout << "copy constructor called!\n";
	tsize = str.tsize;
	tstr = new char[tsize];
	strcpy(tstr, str.c_str());
}

// 移动构造
tstring::tstring(tstring &&str) noexcept : tstr(str.tstr),
	tsize(str.tsize) {
	std::cout << "move constructor called!\n";
	str.tstr = nullptr;
	str.tsize = 0;
}

// 赋值运算符
tstring& tstring::operator=(const tstring &str) {
	std::cout << "assignment operator called!\n";
	if (this != &str) {
		delete[] tstr;
		tsize = str.tsize;
		tstr = new char[tsize];
		strcpy(tstr, str.c_str());
	}
	return *this;
}

// 移动赋值
tstring& tstring::operator=(tstring &&str) noexcept {
	std::cout << "move assignment operator called!\n";
	if (this != &str) {
		delete[] tstr;
		tsize = str.tsize;
		tstr = str.tstr;
		str.tstr = nullptr;
		str.tsize = 0;
	}
	return *this;
}

// 重载 cout
std::ostream& operator<<(std::ostream &out,
                         const tstring &str) {
	if (str.tstr) {
		out << str.tsize << " " << str.tstr;
	} else {
		out << "empty tstring!";
	}
	return out;
}

// 重载 []
char& tstring::operator[] (size_t idx) {
	if (idx >= tsize) {
		return tstr[0];
	}
	return tstr[idx];
}