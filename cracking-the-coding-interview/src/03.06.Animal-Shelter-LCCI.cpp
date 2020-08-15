/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2020-08-15 20:27:41
 * @link    github.com/taseikyo
 */

class AnimalShelf {
  public:
    AnimalShelf() {}

    void enqueue(vector<int> animal) {
        if (animal[1] == 0) {
            cat.push(animal);
        } else {
            dog.push(animal);
        }
    }

    vector<int> dequeueAny() {
        if (dog.empty() && cat.empty()) {
            return {-1, -1};
        }
        if (dog.empty()) {
            return dequeueCat();
        }
        if (cat.empty()) {
            return dequeueDog();
        }
        vector<int> ans1 = cat.front();
        vector<int> ans2 = dog.front();
        if (ans1[0] < ans2[0]) {
            cat.pop();
            return ans1;
        } else {
            dog.pop();
            return ans2;
        }
    }

    vector<int> dequeueDog() {
        if (dog.empty()) {
            return {-1, -1};
        }
        vector<int> ans = dog.front();
        dog.pop();
        return ans;
    }

    vector<int> dequeueCat() {
        if (cat.empty()) {
            return {-1, -1};
        }
        vector<int> ans = cat.front();
        cat.pop();
        return ans;
    }
  private:
    queue<vector<int>> cat, dog;
};

/**
 * Your AnimalShelf object will be instantiated and called as such:
 * AnimalShelf* obj = new AnimalShelf();
 * obj->enqueue(animal);
 * vector<int> param_2 = obj->dequeueAny();
 * vector<int> param_3 = obj->dequeueDog();
 * vector<int> param_4 = obj->dequeueCat();
 */