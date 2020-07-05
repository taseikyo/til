/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-03 22:14:47
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int removeElement(vector<int>& nums, int val) {
		int i = 0;
		while (i < nums.size()) {
			if (nums[i] == val) {
				nums.erase(nums.begin() + i, nums.begin() + i + 1);
			} else {
				++i;
			}
		}
		return nums.size();
	}
};

class Solution {
  public:
	int removeElement(vector<int>& nums, int val) {
		int i = 0;
		for (int j = 0; j < nums.size(); j++) {
			if (nums[j] != val) {
				nums[i] = nums[j];
				i++;
			}
		}

		return i;
	}
};