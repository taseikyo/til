/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-10 13:18:58
 * @link    github.com/taseikyo
 */

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        int num;
        for(const string& token: tokens) {
            if(token == "+") {
                num = stk.top();
                stk.pop();
                stk.top() += num;
            } else if(token == "-"){
                num = stk.top();
                stk.pop();
                stk.top() -= num;
            } else if(token == "*") {
                num = stk.top();
                stk.pop();
                stk.top() *= num;
            } else if(token == "/") {
                num = stk.top();
                stk.pop();
                stk.top() /= num;
            } else {
                num = stoi(token);
                stk.push(num);
            }            
        }
        
        return stk.top();
    }
};