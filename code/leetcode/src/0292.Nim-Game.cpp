/**
 * @date    2020-08-21 17:26:32
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 面对4的整数倍的人永远无法翻身，你拿N根对手就会拿4-N根，保证每回合共减4根，你永远对面4倍数，直到4
// 相反，如果最开始不是4倍数，你可以拿掉刚好剩下4倍数根，让他永远对面4倍数。
class Solution {
  public:
	bool canWinNim(int n) {
		return n % 4 != 0;
	}
};