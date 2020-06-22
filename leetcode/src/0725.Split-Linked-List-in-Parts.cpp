/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-22 17:49:20
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<ListNode*> splitListToParts(ListNode* root, int k) {
		vector<ListNode*> v;
		int n = len(root);
		if (k >= n) {
			for (int i = 0; i < k; ++i) {
				if (root) {
					v.push_back(root);
					ListNode* tmp = root->next;
					root->next = nullptr;
					root = tmp;
				} else {
					v.push_back(nullptr);
				}
			}
		} else {
			int x = n / k;
			if (x * k != n) {
				int z = n - x * k;
				while (z--) {
					v.push_back(root);
					for (int i = 1; i < x + 1; ++i) {
						root = root->next;
					}
					ListNode* tmp = root->next;
					root->next = nullptr;
					root = tmp;
				}
			}
			while (root) {
				v.push_back(root);
				for (int j = 1; j < x; ++j) {
					cout << root->val << " ";
					root = root->next;
				}
				ListNode* tmp = root->next;
				root->next = nullptr;
				root = tmp;
			}
		}
		return v;
	}
	int len(ListNode* root) {
		int  ans = 0;
		while (root) {
			ans++;
			root = root->next;
		}
		return ans;
	}
};