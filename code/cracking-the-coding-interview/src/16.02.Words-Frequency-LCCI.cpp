/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-19 19:14:18
 * @link    github.com/taseikyo
 */

class WordsFrequency {
  public:
	WordsFrequency(vector<string>& book) {
		for (auto word : book) {
			++map[word];
		}
	}

	int get(string word) {
		return map[word];
	}
  private:
	unordered_map<string, int> map;
};

/**
 * Your WordsFrequency object will be instantiated and called as such:
 * WordsFrequency* obj = new WordsFrequency(book);
 * int param_1 = obj->get(word);
 */