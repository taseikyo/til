/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-31 22:21:40
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<int> diStringMatch(string S) {
		vector<int> res;
		int i = 0, j = S.size();
		for (char c : S) {
			if (c == 'I')  res.push_back(i++);
			else res.push_back(j--);
		}
		res.push_back(i);
		return res;
	}
};