/**
 * @date    2020-08-23 20:42:50
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> res;
		map<string, vector<string>> M;
		for (int i = 0; i < strs.size(); i++) {
			string key = strs[i];
			sort(key.begin(), key.end());
			M[key].push_back(strs[i]);
		}
		for (auto ite = M.begin(); ite != M.end(); ite++)
			res.push_back(ite->second);
		return res;
	}
};