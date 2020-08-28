/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 13:44:47
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	bool validateStackSequences(vector<int>& pushed,
	                            vector<int>& popped) {
		if (pushed.empty()) {
			return true;
		}
		stack<int> st;
		int i, j;
		i = j = 0;
		while (i < pushed.size()) {
			if (pushed[i] != popped[j]) {
				st.push(pushed[i++]);
			} else {
				++i, ++j;
				while (!st.empty() && st.top() == popped[j]) {
					st.pop();
					++j;
				}
			}
		}
		return st.empty();
	}
};