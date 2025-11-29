import text_math;

#include <iostream>

using namespace text_math;

int main() {
	try {
		Integer<std::string> n("1000");
		std::cout << n << std::endl;
		n.set_value<unsigned>(999);
		std::cout << n << std::endl;
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}