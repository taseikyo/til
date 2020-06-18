/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-18 13:33:01
 * @link    github.com/taseikyo
 */

int LargestRectangleArea(vector<int>&height) {
	// 确保原数组height的最后一位能够得到计算
	height.push_back(0);
	stack<int>s;
	int answer = 0;
	int temp;
	for (int i = 0; i < (int)height.size();) {
		if (s.empty() || height[i] > height[s.top()]) {
			s.push(i);
			i++;
		} else {
			temp = s.top();
			s.pop();
			answer = max(answer, height[temp] * (s.empty() ? i;
			                                     i - s.top() - 1));
		}
	}
	return answer;
}