/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-04 15:51:38
 * @link    github.com/taseikyo
 */

/**
 * https://www.nowcoder.com/practice/8fecd3f8ba334add803bf2a06af1b993?tpId=13&&tqId=11185&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
 * 输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。
 */

// 如果有两个字符串a,b，
// 如果a + b < b + a, 显然我们希望a排在b的前面
// 因为a排在前面可以使结果更小
class Solution {
public:
    string PrintMinNumber(vector<int> nums) {
        vector<string> str;
        for (int val : nums) str.push_back(to_string(val));
        sort(str.begin(), str.end(), [](string a, string b) {
            return a + b < b + a;
        });
        string ret = "";
        for (string s : str) ret += s;
        return ret;
    }
};