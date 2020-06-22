/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 20:01:01
 * @link    github.com/taseikyo
 */

class node {
  public:
	int val;
	node* next;
	node(int v) {
		val = v;
		next = nullptr;
	}
};

class MyLinkedList {
  public:
	node* head;
	int size;
	/** Initialize your data structure here. */
	MyLinkedList() {
		size = 0;
		head = nullptr;
	}

	/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
	int get(int index) {
		if (size == 0 || index >= size || index < 0) {
			return -1;
		}
		node *p = head;
		while (index--) {
			p = p->next;
		}
		return p->val;
	}

	/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
	void addAtHead(int val) {
		if (!head) {
			head = new node(val);
		} else {
			node *p = new node(val);
			p->next = head;
			head = p;
		}
		size++;
	}

	/** Append a node of value val to the last element of the linked list. */
	void addAtTail(int val) {
		if (!head) {
			head = new node(val);
		} else {
			node *p = head;
			while (p->next) {
				p = p->next;
			}
			p->next = new node(val);
		}
		size++;
	}

	/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
	void addAtIndex(int index, int val) {
		if (index > size) {
			return;
		} else if (index == size) {
			addAtTail(val);
		} else if (index == 0) {
			addAtHead(val);
		} else {
			node* p = head;
			while (--index) {
				p = p->next;
			}
			node*tmp = new node(val);
			tmp->next = p->next;
			p->next = tmp;
			size++;
		}
	}

	/** Delete the index-th node in the linked list, if the index is valid. */
	void deleteAtIndex(int index) {
		if (index >= size) {
			return;
		} else if (index == 0) {
			if (size == 1) {
				delete head;
				head = nullptr;
			} else {
				node*p = head;
				head = head->next;
				delete p;
			}
			size--;
		} else {
			node* p = head;
			while (--index) {
				p = p->next;
			}
			node*tmp = p->next;
			p->next = tmp->next;
			delete tmp;
			size -= 1;
		}
	}
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */