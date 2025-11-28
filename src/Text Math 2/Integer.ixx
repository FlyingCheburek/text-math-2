export module text_math:integer;
import :number;
import <concepts>;
import <type_traits>;
import <stdexcept>;

namespace text_math {
	
	export template<typename T>
	class Integer : public Number {
	public:
		Integer(T value) {
			if constexpr (std::is_integral_v<T>) {
				if (value < 0) {
					this->sign = Number::NEGATIVE;
					value *= -1;
				}
				else if (value == 0) {
					this->sign = Number::POSITIVE;
					this->digits = std::list<DIGIT>({ 0 });
					return;
				}
				else {
					this->sign = Number::POSITIVE;
					while (value > 0) {
						this->digits.push_back(value % 10);
						value /= 10;
					}
				}
			}
			else if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>) {
				// TODO...
			}
			else throw std::invalid_argument("Error in text_math::Integer constructor: template parameter should be integral or string");
			
		}
	};
}
