/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 21:01:05
 * @link    github.com/taseikyo
 */

// 看 0146.lru-cache.png 这张图可以更好的理解实现
// 
// 本题使用 哈希表+双向链表 来实现
// 
// 1. HashMap 保存每个节点的地址，可以基本保证在 O(1) 时间内查找节点
// 2. 双向链表能后在 O(1) 时间内添加和删除节点，单链表则不行

class LRUCache {
  public:
	struct CacheNode {
		int key;
		int value;
		CacheNode(int k, int v) : key(k), value(v) {}
	};
	list<CacheNode> cacheList; // doubly linked list
	unordered_map<int, list<CacheNode>::iterator> cacheMap;
	int size;
	LRUCache(int capacity): size(capacity) {}

	int get(int key) {
		if (cacheMap.find(key) == cacheMap.end()) return -1;

		// 把当前访问的节点移到链表头部，并且更新map中该节点的地址
		cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
		cacheMap[key] = cacheList.begin();
		return cacheMap[key]->value;
	}

	void put(int key, int value) {
		if (cacheMap.find(key) == cacheMap.end()) {
			//删除链表尾部节点（最少访问的节点）
			if (cacheList.size() == size) {
				cacheMap.erase(cacheList.back().key);
				cacheList.pop_back();
			}
			// 插入新节点到链表头部, 并且在map中增加该节点
			cacheList.push_front(CacheNode(key, value));
			cacheMap[key] = cacheList.begin();
		} else {
			//更新节点的值，把当前访问的节点移到链表头部,并且更新map中该节点的地址
			cacheMap[key]->value = value;
			cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
			cacheMap[key] = cacheList.begin();
		}
	}
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */