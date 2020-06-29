/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 17:29:16
 * @link    github.com/taseikyo
 */

class BrowserHistory {
  public:
	int currIdx;
	vector<string > trackHistory;
	int mostUpToDateIdx;

	BrowserHistory(string homepage) {
		trackHistory.push_back(homepage);
		currIdx = 0;
		mostUpToDateIdx = 0;
	}

	void visit(string url) {
		if (currIdx + 1 < trackHistory.size())
			trackHistory[currIdx + 1] = url;
		else {
			trackHistory.push_back(url);
		}
		currIdx++;
		mostUpToDateIdx = currIdx;
	}

	string back(int steps) {
		currIdx = max(0, currIdx - steps);
		return trackHistory[currIdx];
	}

	string forward(int steps) {
		currIdx = min(mostUpToDateIdx, currIdx + steps);
		return trackHistory[currIdx];
	}
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */