/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 22:29:01
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
// 递归版本很简单
class Solution {
  public:
	vector<int> preorder(Node* root) {
		if (!root) {
			return {};
		}
		vector<int> v;
		foo(root, v);
		return v;
	}
	void foo(Node*root, vector<int> &v) {
		if (root) {
			v.push_back(root->val);
			if (root->children.size()) {
				for (auto p : root->children) {
					foo(p, v);
				}
			}
		}
	}
};

// 迭代版本
class Solution {
  public:
	vector<int> preorder(Node* root) {
		if (!root) {
			return {};
		}
		vector<int> v;
		vector<Node*> s;
		while (root || s.size()) {
			if (root) {
				v.push_back(root->val);
				if (root->children.size()) {
					for (int i = root->children.size() - 1; i > 0; --i) {
						s.push_back(root->children[i]);
					}
					root = root->children[0];
				} else {
					root = nullptr;
				}
			} else if (s.size()) {
				root = s.back();
				s.pop_back();
			}
		}
		return v;
	}
};