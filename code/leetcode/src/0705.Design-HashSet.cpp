/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 20:12:42
 * @link    github.com/taseikyo
 */


//跟实现 哈希表类似，只不过不需要存 value

#define ARRAY_SIZE 10007

class MyHashSet {
public:
	struct Node {
		int key;
		Node *next;
		Node(int x): key(x), next(nullptr) {}
	};
	Node *array[ARRAY_SIZE];
    /** Initialize your data structure here. */
    MyHashSet() {
        for (int i = 0; i < ARRAY_SIZE; ++i) {
			array[i] = nullptr;
		}
    }
    
    void add(int key) {
        int idx = key % ARRAY_SIZE;
		Node *cur = array[idx];
		while (cur) {
			if (cur->key == key) {
				return;
			}
			cur = cur->next;
		}
		Node *node = new Node(key);
		node->next = array[idx];
		array[idx] = node;
    }
    
    void remove(int key) {
        int idx = key % ARRAY_SIZE;
		Node *cur = array[idx];
		if (!cur) {
			return;
		}
		if (cur->key == key) {
			array[idx] = cur->next;
			delete cur;
			return;
		}
		Node *tmp;
		while (cur->next) {
			if (cur->next->key == key) {
				tmp = cur->next;
				cur->next = tmp->next;
				delete tmp;
				return;
			}
			cur = cur->next;
		}
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int idx = key % ARRAY_SIZE;
		Node *cur = array[idx];
		while (cur) {
			if (cur->key == key) {
				return true;
			}
			cur = cur->next;
		}
		return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */