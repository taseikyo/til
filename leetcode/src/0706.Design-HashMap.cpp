/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 20:00:29
 * @link    github.com/taseikyo
 */

// 参考 https://leetcode.com/problems/design-hashmap/discuss/326081/cpp-solution-with-Linked-List

#define ARRAY_SIZE 10007

class MyHashMap {
  public:
	struct Node {
		int key, val;
		Node *next;
		Node(int x, int y): key(x), val(y), next(nullptr) {}
	};
	Node *array[ARRAY_SIZE];
	/** Initialize your data structure here. */
	MyHashMap() {
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			array[i] = nullptr;
		}
	}

	/** value will always be non-negative. */
	void put(int key, int value) {
		int idx = key % ARRAY_SIZE;
		Node *cur = array[idx];
		while (cur) {
			if (cur->key == key) {
				cur->val = value;
				return;
			}
			cur = cur->next;
		}
		Node *node = new Node(key, value);
		node->next = array[idx];
		array[idx] = node;
	}

	/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
	int get(int key) {
		int idx = key % ARRAY_SIZE;
		Node *cur = array[idx];
		while (cur) {
			if (cur->key == key) {
				return cur->val;
			}
			cur = cur->next;
		}
		return -1;
	}

	/** Removes the mapping of the specified value key if this map contains a mapping for the key */
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
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */