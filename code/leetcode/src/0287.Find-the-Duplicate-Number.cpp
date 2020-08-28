/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 16:37:51
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int findDuplicate(vector<int>& nums) {
		// Find the intersection point of the two runners.
		int tortoise = nums[0];
		int hare = nums[0];
		do {
			tortoise = nums[tortoise];
			hare = nums[nums[hare]];
		} while (tortoise != hare);

		// Find the "entrance" to the cycle.
		int ptr1 = nums[0];
		int ptr2 = tortoise;
		while (ptr1 != ptr2) {
			ptr1 = nums[ptr1];
			ptr2 = nums[ptr2];
		}

		return ptr1;
	}
};