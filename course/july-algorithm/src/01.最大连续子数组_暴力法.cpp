/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-11 13:49:10
 * @link    github.com/taseikyo
 */

int MaxSubArray(int* A, int n) {
	int maxSum = a[0];
	int currSum;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			currSum = 0;
			for (int k = i; k <= j; k++) {
				currSum += A[k];
			}
			if (currSum > maxSum)
				maxSum = currSum;
		}
	}
	return maxSum;
}