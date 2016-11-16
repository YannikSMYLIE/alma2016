// largeint.h (Declaration of Class LargeInt)

#include <vector>
#include <string>
#include <iostream>


class LargeInt {
public:
	using inputtype = long long;

	LargeInt(inputtype);                           // constructor
	std::string decimal() const;                   // decimal representation
	bool operator<(const LargeInt &) const;        // comparison
	LargeInt operator+(const LargeInt &) const;    // addition
	const LargeInt & operator+=(const LargeInt &); // addition
	LargeInt operator*(const LargeInt &) const; // multiplikation
	const LargeInt & operator*=(const LargeInt &); // Multiplikation
	// Unsere beiden neuen Operationen
	bool operator==(const LargeInt &) const;
	bool operator!=(const LargeInt &) const;

	void print()
	{
		for (int i = _v.size() - 1; i >= 0; i--)
		{
			std::cout << _v[i];
		}
	}

private:
	std::vector<short> _v;  // store single digits, last digit in _v[0]
	static const std::string digits;

};
