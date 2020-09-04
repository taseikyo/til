/**
 * @date    2020-09-04 09:38:10
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

#include <iostream>

#include "tshared_ptr.hpp"

using namespace std;

template<class T>
struct ListNode {
	ListNode(T value)
		: _value(value) {
		cout << "ListNode()" << endl;
	}
	~ListNode() {
		cout << "~ListNode()" << endl;
	}
	T _value;
	tshared_ptr<ListNode<T>> _prev;
	tshared_ptr<ListNode<T>> _next;
};

int main(int argc, char* argv[]) {
	tshared_ptr<ListNode<int>> p1(new ListNode<int>(1));
	tshared_ptr<ListNode<int>> p2(new ListNode<int>(2));
	cout << p1.use_count() << endl;
	cout << p2.use_count() << endl;
	p1->_next = p2;
	p2->_prev = p1;
	cout << p1.use_count() << endl;
	cout << p2.use_count() << endl;
	return 0;
}