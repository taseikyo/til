/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 13:08:56
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/623a5ac0ea5b4e5f95552655361ae0a8?tpId=13&&tqId=11203&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。
 */

// 不需要额外的数组或者hash table来保存，题目里写了数组里数字的范围保证在0 ~ n-1 之间
// 所以可以利用现有数组设置标志，当一个数字被访问过后，可以设置对应位上的数 + n
// 之后再遇到相同的数时，会发现对应位上的数已经大于等于n了，那么直接返回这个数即可
class Solution {
  public:
	// Parameters:
	//        numbers:     an array of integers
	//        length:      the length of array numbers
	//        duplication: (Output) the duplicated number in the array number
	// Return value:       true if the input is valid, and there are some duplications in the array number
	//                     otherwise false
	bool duplicate(int numbers[], int length, int* duplication) {
		for (int i = 0; i < length; ++i) {
			int index = numbers[i];
			if (index >= length) {
				index -= length;
			}
			if (numbers[index] >= length) {
				*duplication = index;
				return true;
			}
			numbers[index] += length;
		}
		return false;
	}
};
// 从评论区扣的答案，不然自己想大概是用哈希来做
// 这里简单解答一下，由于数组每个数是 0-n-1
// 所以可以把每个数当作下标，由于存在重复，必然有一个位置被多次索引
// 第一次对索引位置的数+length，第二次索引发现该值如果大于length，那么此位置的数就是重复的数