/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 22:41:24
 * @link    github.com/taseikyo
 */

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
  public:
	vector<vector<int>> levelOrder(Node* root) {
		if (!root) {
			return {};
		}
		vector<Node*> s{root};
		vector<vector<int>> v;
		foo(s, v);
		return v;
	}
	void foo(vector<Node*> s, vector<vector<int>> &v) {
		if (s.size()) {
			vector<int> ans;
			vector<Node*> tmp_s;
			for (auto p : s) {
				ans.push_back(p->val);
				for (auto c : p->children) {
					tmp_s.push_back(c);
				}
			}
			v.push_back(ans);
			foo(tmp_s, v);
		}
	}
};