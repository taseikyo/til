/**
 * @date    2020-09-04 09:26:45
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

/**
 * 编译的时候遇到一些问题，开始时将声明与实现分开，结果编译各种报错
 * 合到一起就 OK 了，绝了
 */

template <typename T>
class tshared_ptr {
  public:
	tshared_ptr(T *p = nullptr): count(new int(1)), tptr(p) {}

	tshared_ptr(const tshared_ptr<T>& obj):
		count(&(++ * obj.count)), tptr(obj.tptr) {}

	tshared_ptr<T>& operator=(const tshared_ptr<T>& obj) {
		if (&obj != this) {
			if (--(*count) == 0) {
				delete tptr;
				delete count;
				count = nullptr;
				tptr = nullptr;
			}
			++*obj.count;
			tptr = obj.tptr;
			count = obj.count;
		}
		return *this;
	}

	int use_count() {
		return *count;
	}

	T* operator->() {
		return tptr;
	}

	T& operator*() {
		return *tptr;
	}

	~tshared_ptr() {
		if (--*count == 0) {
			delete tptr;
			delete count;
			count = nullptr;
			tptr = nullptr;
		}
	}
  private:
	int *count;
	T* tptr;
};