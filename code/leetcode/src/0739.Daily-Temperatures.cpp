/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 13:36:26
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> dailyTemperatures(vector<int>& T) {
		if (T.empty()) {
			return {};
		}
		stack<int> s;
		vector<int> v(T.size(), 0);
		int i = 0;
		while (i < T.size()) {
			while (s.size() && T[s.top()] < T[i]) {
				v[s.top()] = i - s.top();
				s.pop();
			}
			s.push(i++);
		}
		return v;
	}
};