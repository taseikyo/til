/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-06-29 21:19:32
 * @link    github.com/taseikyo
 */
// https://leetcode-cn.com/problems/lfu-cache/solution/lfuhuan-cun-by-leetcode-solution/

// 缓存的节点信息
struct Node {
    int key, val, freq;
    Node(int k, int v, int f): key(k), val(v), freq(f){}
};
class LFUCache {
    int minfreq, size;
    unordered_map<int, list<Node>::iterator> key_table;
    unordered_map<int, list<Node>> freq_table;
public:
    LFUCache(int capacity): minfreq(0), size(capacity) {}
    
    int get(int key) {
        if (size == 0 || key_table.find(key) == key_table.end()) return -1;
        auto node = key_table[key];
        int val = node -> val, freq = node -> freq;
        freq_table[freq].erase(node);
        // 如果当前链表为空，我们需要在哈希表中删除，且更新minFreq
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (minfreq == freq) minfreq += 1;
        }
        // 插入到 freq + 1 中
        freq_table[freq + 1].push_front(Node(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
        return val;
    }
    
    void put(int key, int value) {
        if (size == 0) return;
        if (key_table.find(key) == key_table.end()) {
            // 缓存已满，需要进行删除操作
            if (key_table.size() == size) {
                // 通过 minFreq 拿到 freq_table[minFreq] 链表的末尾节点
                key_table.erase(freq_table[minfreq].back().key);
                freq_table[minfreq].pop_back();
                if (freq_table[minfreq].size() == 0) {
                    freq_table.erase(minfreq);
                }
            } 
            freq_table[1].push_front(Node(key, value, 1));
            key_table[key] = freq_table[1].begin();
            minfreq = 1;
        } else {
            // 与 get 操作基本一致，除了需要更新缓存的值
            auto node =key_table[key];
            int freq = node -> freq;
            freq_table[freq].erase(node);
            if (freq_table[freq].size() == 0) {
                freq_table.erase(freq);
                if (minfreq == freq) minfreq += 1;
            }
            freq_table[freq + 1].push_front(Node(key, value, freq + 1));
            key_table[key] = freq_table[freq + 1].begin();
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */