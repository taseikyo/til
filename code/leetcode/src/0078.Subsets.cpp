/**
 * @date    2020-08-16 18:37:10
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 回溯
class Solution {
	int n;
	vector<vector<int>> ans;
  public:

	void backtrack(int first, vector<int>& nums, int num,
	               vector<int>& path) {
		// num 是这一轮要求的子集的规模
		if (path.size() == num) {
			ans.push_back(path);
		}
		for (int i = first; i < n; i++) {
			// 如果path没满，再从first之后的某个位置，添加一个元素
			path.push_back(nums[i]);
			backtrack(i + 1, nums, num, path);
			// 注意，这里放i+1,作用是，保证一个path里面的元素的
			// 顺序，在原来nums里面的对应顺序是一样的。自动起到
			// 去重的功能。
			path.pop_back();//准备迎接下一个候选nums[i]。
		}
	}

	vector<vector<int>> subsets(vector<int>& nums) {
		ans.clear();
		n = nums.size();
		// 枚举元素数目i
		for (int i = 0; i <= n; i++) {
			vector<int> path;// 空的
			backtrack(0, nums, i, path);
		}
		return ans;
	}
};

// dfs
class Solution {
  public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector<vector<int>> result;
		vector<int> tmp;
		getResult(result, nums, 0, tmp);
		return result;
	}

	void getResult(vector<vector<int>>& result,
	               vector<int> nums, int startPoint, vector<int> tmp) {
		result.push_back(tmp);
		for (int i = startPoint; i < nums.size(); i++) {
			tmp.push_back(nums[i]);
			getResult(result, nums, i + 1, tmp);
			tmp.pop_back();
		}
	}
};

// 很强的一个方法
class Solution {
  public:
	vector<vector<int>> subsets(vector<int>& nums) {
		vector< vector<int> > ans;
		ans.push_back(vector<int> {});

		vector<int> temp;

		// 枚举 nums 的每个元素，加到 ans 的每个元素里面
		for (int i = 0; i < nums.size(); ++i) {
			int sz = ans.size();
			for (int j = 0; j < sz; ++j) {
				temp = ans[j]; //然后往 temp 里面加元素 nums[i]
				temp.push_back(nums[i]);
				ans.push_back(temp);
			}
		}
		return ans;
	}
};