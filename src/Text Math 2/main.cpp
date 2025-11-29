import text_math;

#include <iostream>

using namespace text_math;

int main() {
	try {
		Integer<std::string> n("100"), m("-19912");
		n.add(m); // test
		std::cout << n;
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}