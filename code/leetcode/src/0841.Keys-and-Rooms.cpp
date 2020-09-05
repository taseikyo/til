/**
 * @date    2020-08-31 20:27:57
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Solution {
  public:
	bool canVisitAllRooms(vector<vector<int>>& rooms) {
		vector<bool> ok(rooms.size(), false);
		queue<int> next;
		int count = 1;

		next.push(0);
		ok[0] = true;
		while (!next.empty()) {
			int r = next.front();
			next.pop();
			for (int key : rooms[r]) {
				if (!ok[key]) {
					next.push(key);
					count++;
				}
				ok[key] = true;
			}
		}
		return count == rooms.size();
	}
};