import text_math;

#include <iostream>

using namespace text_math;

int main() {
	try {
		Integer<short> n(100), m(5), rem(0);
		n.divide(m);
	
	}
	catch (std::exception err) {
		std::cout << err.what() << std::endl;
	}
	return 0;
}