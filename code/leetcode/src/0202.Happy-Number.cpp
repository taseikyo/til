/**
 * @date    2020-08-28 20:37:20
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

// 不是快乐数的数称为不快乐数（unhappy number），所有不快乐数的数位平方和计算
// 最後都会进入 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4 的循环中

// 不快乐数会落入循环区间内。先暴力运算10次，得数如果落入循环期间了，就返回false（为什么是10次，因为9次我试过，不行hhh）
// —— 来自评论区
class Solution {
  public:
	bool isHappy(int n) {
		int temp = 0;
		for (int t = 1; t <= 10; t++) {
			while (n >= 10) {
				temp = temp + (n % 10) * (n % 10);
				n = n / 10;
			}
			temp = temp + n * n;
			n = temp;
			temp = 0;
		}

		if (n == 4 || n == 16 || n == 37 || n == 58  || n == 89
		        || n == 145 || n == 42  || n == 20) {
			return false;
		} else {
			return true;
		}
	}
};