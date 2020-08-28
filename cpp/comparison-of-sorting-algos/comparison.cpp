/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-27 23:59:22
 * @link    github.com/taseikyo
 */

#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <functional>
#include <iomanip>
#include <time.h>

using namespace std;

/**
 * selection_sort
 */
void selection_sort(vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		int idx = i;
		for (int j = i + 1; j < n; ++j) {
			if (nums[j] < nums[idx]) {
				idx = j;
			}
		}
		swap(nums[i], nums[idx]);
	}
}

/**
 * insertion_sort
 */
void insertion_sort(vector<int>& nums) {
	int n = nums.size();
	for (int i = 1; i < n; ++i) {
		int j = i - 1;
		for (; j >= 0; --j) {
			if (nums[j] <= nums[j + 1]) {
				break;
			}
			swap(nums[j], nums[j + 1]);
		}
	}
}


/**
 * merge_sort
 */
void merge(vector<int>& nums, int st, int mid, int ed) {
	vector<int> tmp(ed - st + 1, 0);
	int l = st, r = mid + 1, i = 0;
	while (l <= mid && r <= ed) {
		if (nums[l] < nums[r]) {
			tmp[i++] = nums[l++];
		} else {
			tmp[i++] = nums[r++];
		}
	}
	while (l <= mid) {
		tmp[i++] = nums[l++];
	}
	while (r <= ed) {
		tmp[i++] = nums[r++];
	}
	for (int i = 0; i < ed - st + 1; ++i) {
		nums[st + i] = tmp[i];
	}
}

void __merge_sort(vector<int>& nums, int st, int ed) {
	if (st >= ed) {
		return;
	}
	int mid = st + (ed - st) / 2;
	__merge_sort(nums, st, mid);
	__merge_sort(nums, mid + 1, ed);
	merge(nums, st, mid, ed);
}

void merge_sort(vector<int>& nums) {
	__merge_sort(nums, 0, nums.size() - 1);
}

/**
 * quick_sort
 */
void __quick_sort(vector<int>& nums, int l, int r) {
	if (l < r) {
		int i = l, j = r, x = nums[l];
		while (i < j) {
			while (i < j && nums[j] >= x) j--;
			if (i < j) nums[i++] = nums[j];
			while (i < j && nums[i] < x) i++;
			if (i < j) nums[j--] = nums[i];
		}
		nums[i] = x;
		__quick_sort(nums, l, i - 1);
		__quick_sort(nums, i + 1, r);
	}
}

void quick_sort(vector<int>& nums) {
	__quick_sort(nums, 0, nums.size() - 1);
}

/**
 * heap_sort
 */
void heapify(vector<int>& v, int st, int ed) {
	int dad = st;
	int son = dad * 2 + 1;
	while (son <= ed) {
		if (son + 1 <= ed && v[son] < v[son + 1]) son++;
		if (v[dad] > v[son]) return;
		else {
			swap(v[dad], v[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(vector<int>& v) {
	int n = v.size();
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(v, i, n - 1);
	for (int i = n - 1; i > 0; i--) {
		swap(v[0], v[i]);
		heapify(v, 0, i - 1);
	}
}

// [low, high]
vector<int> generate(int size, int low, int high) {
	vector<int> v(size, 0);
	srand(int(time(0)));
	for (int i = 0; i < size; ++i) {
		v[i] = rand() % (high - low + 1) + low;
	}
	return v;
}

int max_length(vector<string> nums) {
	int ans = 0;
	for (auto&x : nums) ans = max(ans, (int)x.size());
	return ans;
}

int main(int argc, char const *argv[]) {
	vector<string> sorting_methods{"quick", "heap", "merge", "select", "insert"};
	vector<function<void(vector<int>&)>> functions{quick_sort, heap_sort, merge_sort, selection_sort, insertion_sort};

	const int TEST_TIMES = 1 << 15;
	const int MAX_SIZE = 1000;
	auto nums = generate(MAX_SIZE, 0, INT_MAX);
	auto width = max_length(sorting_methods);
	double costs = 0;
	clock_t t1, t2;

	for (int i = 0; i < sorting_methods.size(); ++i) {
		cout << setw(width) << sorting_methods[i] << ": ";
		for (int j = 0; j < TEST_TIMES; ++j) {
			auto tmp = nums;
			t1 = clock();
			functions[i](tmp);
			t2 = clock();
			costs += t2 - t1;
		}
		// for (auto x : tmp) {
		// 	cout << x << " ";
		// }
		// cout << endl;
		cout << costs / CLOCKS_PER_SEC << endl;
	}

	return 0;
}