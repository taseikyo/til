/**
 * @date    2020-08-25 20:25:51
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	int findClosest(vector<string>& words, string word1,
					string word2) {
		int ans = INT_MAX;
		int pos1 = -1, pos2 = -1;

		for (int i = 0; i < words.size(); ++i) {
			if (words[i] == word1) {
				pos1 = i;
			}
			if (words[i] == word2) {
				pos2 = i;
			}
			if (pos1 != -1 && pos2 != -1) {
				ans = min(ans, abs(pos1 - pos2));
			}
		}
		return ans;
	}
};