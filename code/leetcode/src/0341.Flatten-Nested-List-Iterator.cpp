/**
 * @date    2020-08-23 20:22:56
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
  public:
	vector<int> v;
	int index = 0;
	NestedIterator(vector<NestedInteger> &nestedList) {
		dfs(nestedList);
	}
	int next() {
		return v[index++];
	}
	bool hasNext() {
		if (index == v.size()) return false;
		else return true;
	}
	void dfs(vector<NestedInteger> &nestedList) {
		for (int i = 0; i < nestedList.size(); i++) {
			if (nestedList[i].isInteger())
				v.push_back(nestedList[i].getInteger());
			else dfs(nestedList[i].getList());
		}
	}
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */