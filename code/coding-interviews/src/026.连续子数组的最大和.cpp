/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 12:32:04
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/459bd355da1549fa8a49e350bf3df484?tpId=13&&tqId=11183&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。给一个数组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)
 */

// 记 S[i] 为以 A[i] 结尾的数组中和最大的子数组
// 则：S[i+1] = max(S[i]+A[i+1]，A[i+1])
class Solution {
  public:
	int FindGreatestSumOfSubArray(vector<int> array) {
		if (array.empty()) {
			return 0;
		}
		int sum = -1;
		int result = -1;
		for (auto x : array) {
			if (sum > 0) {
				sum += x;
			} else {
				sum = x;
			}
			if (sum > result) {
				result = sum;
			}
		}
		return result;
	}
};