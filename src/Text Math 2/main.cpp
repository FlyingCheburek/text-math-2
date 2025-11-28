import text_math;

#include <iostream>

using namespace text_math;

int main() {
	try {
		Integer<int> n(-9999);
		std::cout << n.as_string();
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}