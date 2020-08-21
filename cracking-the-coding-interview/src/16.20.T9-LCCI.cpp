/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-19 19:59:01
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	vector<string> getValidT9Words(string num, vector<string>& words) {
		unordered_map<char, bool> hp[10];
		vector<string> res;
		hp[2]['a'] = hp[2]['b'] = hp[2]['c'] = true;
		hp[3]['d'] = hp[3]['e'] = hp[3]['f'] = true;
		hp[4]['g'] = hp[4]['h'] = hp[4]['i'] = true;
		hp[5]['j'] = hp[5]['k'] = hp[5]['l'] = true;
		hp[6]['m'] = hp[6]['n'] = hp[6]['o'] = true;
		hp[7]['p'] = hp[7]['q'] = hp[7]['r'] = hp[7]['s'] = true;
		hp[8]['t'] = hp[8]['u'] = hp[8]['v'] = true;
		hp[9]['w'] = hp[9]['x'] = hp[9]['y'] = hp[9]['z'] = true;
		int l = words.size();
		for (int i = 0; i < l; i++) {
			int ll = words[i].size();
			if (ll == num.size()) {
				int j = 0;
				while (j < ll && hp[num[j] - '0'][words[i][j]]) j = j + 1;
				if (j >= ll) res.push_back(words[i]);
			}
		}
		return res;
	}
};

