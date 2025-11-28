import text_math;

#include <iostream>

using namespace text_math;

int main() {
	try {
		Integer<float> n(0.0);
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}