import text_math;

#include <iostream>

using namespace text_math;

int main() {
	try {
		Integer<std::string> n("-1230"), m("-1230");
		std::cout << (n < m);
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}