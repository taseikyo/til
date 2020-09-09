/**
 * @date    2020-09-09 19:54:19
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class RandomizedSet {
  private:
	unordered_map<int, int> map;
	vector<int> arr;
  public:
	/** Initialize your data structure here. */
	RandomizedSet() {}

	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		auto it = map.find(val);
		if (it != map.end()) return false;
		map[val] = arr.size();
		arr.push_back(val);
		return true;
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	// 很棒的几个技巧，将最后一个值赋值给要移除的位置，这时只需要 pop_back 即可
	bool remove(int val) {
		auto it = map.find(val);
		if (it == map.end()) return false;
		int size = arr.size();
		int loc = map[val];

		map[arr[size - 1]] = loc;
		arr[loc] = arr[size - 1];
		arr.pop_back();
		map.erase(val);
		return true;
	}

	/** Get a random element from the set. */
	int getRandom() {
		int size = arr.size();
		if (size == 0) return 0;
		return arr[rand() % size];
	}
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
