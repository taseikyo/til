/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-17 12:40:37
 * @link    github.com/taseikyo
 */

// A&&B，表示如果A成立则执行B，否则如果A不成立，不用执行B
class Solution {
public:
    int Sum_Solution(int n) {
        bool x = n > 1 && (n += Sum_Solution(n-1)); // bool x只是为了不报错
        return n;
    }
};