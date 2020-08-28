/**
 * @date    2020-08-23 21:11:09
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	int kthSmallest(vector<vector<int>>& matrix, int k) {
		priority_queue<int> pq;
		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < matrix[0].size(); ++j) {
				pq.push(matrix[i][j]);
				if (pq.size() > k) pq.pop();
			}
		}
		return pq.top();
	}
};