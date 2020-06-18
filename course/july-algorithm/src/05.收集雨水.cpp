/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-18 13:39:59
 * @link    github.com/taseikyo
 */

int TrappingRainWater(int A[]，int n) {
	int secHight = 0; // 当前找到的第二大的数
	int left = 0;
	int right = n - 1;
	int trap = 0; //依次遍历每个方柱能装水的容量
	while (left < right) {
		if (A[left] < A[right]) {
			secHight = max(A[left]，secHight);
			trap += (secHight - A[left]);
			left++;
		} else {
			secHight = max(A[right]，secHight);
			trap += (secHight - A[right]);
			right--;
		}
		return trap;
	}
}