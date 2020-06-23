/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-23 17:06:49
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
	vector<int> postorder(Node* root) {
		if (!root) {
			return {};
		}
		vector<int> v;
		foo(root, v);
		return v;
	}
	void foo(Node*root, vector<int> &v) {
		if (root) {
			if (root->children.size()) {
				for (auto p : root->children) {
					foo(p, v);
				}
			}
			v.push_back(root->val);
		}
	}
};