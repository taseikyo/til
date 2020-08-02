/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-02 17:32:50
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int findKthLargest(vector<int>& nums, int k) {
		// 小顶堆 min heap
		priority_queue<int, vector<int>, greater<int>> mh;
		for (auto i : nums) {
			mh.push(i);
			if (mh.size() > k) {
				mh.pop();
			}
		}
		return mh.top();
	}
};