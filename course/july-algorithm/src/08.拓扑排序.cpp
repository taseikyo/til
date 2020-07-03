/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-07-02 23:11:43
 * @link    github.com/taseikyo
 */

// 结点数为 n, 用邻接矩阵 gragh[n][n] 存储边权,
// 用indegree[n]存储每个结点的入度
void topologic(int* toposort) {
	int cnt = 0; //当前拓扑排序列表中有多少结点
	queue<int>q;//保存入度为0的结点:还可以用栈甚至随机取
	int i;
	for (i = 0; i < n; i++)
		if (indegree[i] == 0)
			q.push(i);
	int cur; //当前入度为0的结点
	while (!q.empty())
		cur = q.front();
	q.pop();
	toposort[cnt++] = cur;
	for (i = 0; i < n; i++) {
		if (gragh[cur][i] != 0) {
			indegree[i]--;
			if (indegree[i] == 0)
				q.push(i);
		}
	}
}