/**
 * @date    2020-08-23 19:38:05
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class Trie {
  public:
	/** Initialize your data structure here. */
	Trie(): is_word(false) {
		for (int i = 0; i < 26; i++) {
			childern[i] = nullptr;
		}
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		auto p = this;
		for (auto ch : word) {
			if (!p->childern[ch - 'a']) {
				p->childern[ch - 'a'] = new Trie();
			}
			p = p->childern[ch - 'a'];
		}
		p->is_word = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		auto p = this;
		for (auto ch : word) {
			if (!p->childern[ch - 'a']) {
				return false;
			}
			p = p->childern[ch - 'a'];
		}
		return p->is_word;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		auto p = this;
		for (auto ch : prefix) {
			if (!p->childern[ch - 'a']) {
				return false;
			}
			p = p->childern[ch - 'a'];
		}
		return true;
	}
  private:
	bool is_word;
	Trie *childern[26];
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */