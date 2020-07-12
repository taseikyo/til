/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-12 15:36:34
 * @link    github.com/taseikyo
 */

class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        unsigned short dict[101] = {0};
        unsigned short ret = 0;
        for (auto i: nums) {
        	ret += dict[i];
        	++dict[i];
        }
        return ret;
    }
};