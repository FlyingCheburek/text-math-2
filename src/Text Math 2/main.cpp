import text_math;

#include <iostream>

using namespace text_math;

int main() {
	try {
		Integer<std::string> n("1"), m("66");
		n -= m;
		m -= n;
		std::cout << m;
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}