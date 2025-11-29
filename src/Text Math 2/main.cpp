import text_math;

#include <iostream>

using namespace text_math;

int main() {
	try {
		Integer<std::string> n("-1"), m("-1");
		n.add(m);
		std::cout << n;
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}