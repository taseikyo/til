/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-06 22:06:38
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/00de97733b8e4f97a3fb5c680ee10720?tpId=13&&tqId=11207&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。
 *
 * 如果当前字符流没有存在出现一次的字符，返回#字符。
 */

// 队列+哈希
// 队列保证顺序，哈希保证次数
class Solution {
  public:
	//Insert one char from stringstream
	queue<char> q;
	unordered_map<char, int> mp;
	void Insert(char ch) {
		// 如果是第一次出现， 则添加到队列中
		if (mp.find(ch) == mp.end()) {
			q.push(ch);
		}
		// 不管是不是第一次出现，都进行计数
		++mp[ch];
	}
	//return the first appearence once char in current stringstream
	char FirstAppearingOnce() {
		while (!q.empty()) {
			char ch = q.front();
			// 拿出头部，如果是第一次出现，则返回
			if (mp[ch] == 1) {
				return ch;
			}
			// 不是第一次出现，则弹出，然后继续判断下一个头部
			else {
				q.pop();
			}
		}
		return '#';
	}
};