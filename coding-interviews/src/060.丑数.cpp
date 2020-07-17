/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 12:33:16
 * @link    github.com/taseikyo
 */

/*

https://www.nowcoder.com/questionTerminal/6aa9e04fc3794f68acf8778237ba065b?answerType=1&f=discussion

丑数能够分解成 2^x3^y5^z
所以只需要把得到的丑数不断地乘以2、3、5之后并放入他们应该放置的位置即可，
而此题的难点就在于如何有序的放在合适的位置。
1乘以 （2、3、5）=2、3、5；2乘以（2、3、5）=4、6、10；
3乘以（2、3、5）=6,9,15；5乘以（2、3、5）=10、15、25；
从这里我们可以看到如果不加策略地添加丑数是会有重复并且无序，
而在2x，3y，5z中，如果x=y=z那么最小丑数一定是乘以2的，
但关键是有可能存在x>y>z的情况，所以我们要维持三个指针
来记录当前乘以2、乘以3、乘以5的最小值，然后当其被选为新的最小值后，
要把相应的指针+1；因为这个指针会逐渐遍历整个数组，因此最终数组中的
每一个值都会被乘以2、乘以3、乘以5，也就是实现了我们最开始的想法，
只不过不是同时成乘以2、3、5，而是在需要的时候乘以2、3、5.
*/
class Solution {
  public:
	int GetUglyNumber_Solution(int index) {
		if (index <= 0) {
			return 0;
		}
		//初始化三个指向三个潜在成为最小丑数的位置
		int p2 = 0, p3 = 0, p5 = 0;
		vector<int> v(index);
		v[0] = 1;
		for (int i = 1; i < index; i++) {
			v[i] = min(v[p2] * 2, min(v[p3] * 3, v[p5] * 5));
			if (v[i] == v[p2] * 2)
				p2++; //为了防止重复需要三个if都能够走到
			if (v[i] == v[p3] * 3)
				p3++; //为了防止重复需要三个if都能够走到
			if (v[i] == v[p5] * 5)
				p5++; //为了防止重复需要三个if都能够走到
		}
		return v[index - 1];
	}
};