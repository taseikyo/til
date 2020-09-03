/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-09-03 22:18:54
 * @link    github.com/taseikyo
 */

class Finder {
  public:
	int findKth(vector<int> a, int n, int K) {
		priority_queue<int, vector<int>, greater<int>> pq;
		for (auto x : a) {
			pq.push(x);
			if (pq.size() > K) {
				pq.pop();
			}
		}
		return pq.top();
	}
};