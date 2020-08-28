/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-07 19:50:51
 * @link    github.com/taseikyo
 */

/**
 *https://www.nowcoder.com/practice/d77d11405cc7470d82554cb392585106?tpId=13&&tqId=11174&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）
 */

// https://www.nowcoder.com/questionTerminal/d77d11405cc7470d82554cb392585106?answerType=1&f=discussion
// 这个题挺难的，题解说加一个辅助栈用来模拟入栈
class Solution {
  public:
	bool IsPopOrder(vector<int> pushV, vector<int> popV) {
		stack<int> st;
		int i = 0, j = 0;
		while (i < pushV.size()) {
			if (pushV[i] != popV[j]) {
				st.push(pushV[i++]);
			} else {
				++i, ++j;
				while (!st.empty() && st.top() == popV[j]) {
					st.pop();
					++j;
				}
			}
		} // end outer while

		return st.empty();
	}
};