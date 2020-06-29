/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 17:10:35
 * @link    github.com/taseikyo
 */

class Logger {
  public:
	unordered_map<string, int> m;
	Logger() {}

	bool shouldPrintMessage(int timestamp, string message) {
		if (!m.count(message)) {
			m[message] = timestamp;
			return true;
		}
		if (timestamp - m[message] >= 10) {
			m[message] = timestamp;
			return true;
		}
		return false;
	}
};

// 下面这个更精简，m[message] 默认返回 0？
// 试了下，果然是返回 0
class Logger {
  public:
	Logger() {}

	bool shouldPrintMessage(int timestamp, string message) {
		if (timestamp < m[message]) return false;
		m[message] = timestamp + 10;
		return true;
	}

  private:
	unordered_map<string, int> m;
};

int main(int argc, char const *argv[]) {
	unordered_map<string, int> m;
	cout<<m["abc"]<<endl;
	return 0;
}