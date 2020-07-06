/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-06 22:39:22
 * @link    github.com/taseikyo
 */

class Solution {
  public:
	//翻转str从s到e的部分
	void ReverseWord(string &str, int s, int e) {
		while (s < e)
			swap(str[s++], str[e--]);
	}

	string ReverseSentence(string str) {
		ReverseWord(str, 0, str.size() - 1); //先整体翻转
		int s = 0, e = 0;
		int i = 0;
		while (i < str.size()) {
			while (i < str.size() && str[i] == ' ') //空格跳过
				i++;
			e = s = i; //记录单词的第一个字符的位置
			//不是空格 找单词最后一个字符的位置
			while (i < str.size() && str[i] != ' ') {
				i++;
				e++;
			}
			ReverseWord(str, s, e - 1); //局部翻转
		}
		return str;
	}
};

class Solution {
  public:
	string ReverseSentence(string str) {
		//先整体翻转
		reverse(str.begin(), str.end());
		int s = 0, e = 0;
		int i = 0;
		while (i < str.size()) {
			while (i < str.size() && str[i] == ' ') //空格跳过
				i++;
			e = s = i; //记录单词的第一个字符的位置
			//不是空格 找单词最后一个字符的位置
			while (i < str.size() && str[i] != ' ') {
				i++;
				e++;
			}
			//局部翻转
			reverse(str.begin()+s, str.begin()+e);
		}
		return str;
	}
};