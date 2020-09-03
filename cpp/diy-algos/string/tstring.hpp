/**
 * @date    2020-09-03 16:24:04
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @link 	github.com/taseikyo
 */

class tstring {
	friend std::ostream& operator<<(std::ostream &out,
	                                const tstring &str);
  public:
	size_t size() const;
	const char* c_str() const;
	// default constructor
	tstring(const char *str = nullptr);
	// copy constructor
	tstring(const tstring &str);
	// move constructor
	tstring(tstring &&str) noexcept;
	// assignment operator
	tstring& operator=(const tstring &str);
	// move assignment operator
	tstring& operator=(tstring &&str) noexcept;
	// [] operator
	char& operator[] (size_t idx);
	// destructor
	~tstring();
  private:
	char* tstr;
	size_t tsize;
};