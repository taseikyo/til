/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 13:40:26
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=13&&tqId=11154&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 */

// 从左下角找，比这个值大的话向右，否则向上
class Solution {
  public:
	bool Find(int target, vector<vector<int>> array) {
		int rowCount = array.size();
		int colCount = array[0].size();
		int i, j;
		for (i = rowCount - 1, j = 0; i >= 0 && j < colCount;) {
			if (target == array[i][j])
				return true;
			else if (target < array[i][j]) {
				i--;
			} else {
				j++;
			}
		}
		return false;
	}
};
// 对每一行进行二分，但是编译不通过不知道为什么
class Solution1 {
  public:
	bool Find(int target, vector<vector<int> > array) {
		int row = array.size();
		for (int i = 0; i < row; ++i) {
			int low = 0, high = array[i].size();
			while (low <= high) {
				int mid = low + (high - low) / 2;
				if (target > array[i][mid])
					low = mid + 1;
				else if (target < array[i][mid])
					high = mid - 1;
				else
					return true;
			}
		}
		return false;
	}
};