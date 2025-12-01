export module text_math:integer;
import :number;
import <stdexcept>;
import <ostream>;

namespace text_math {
	
	export template<typename T>
	class Integer : public Number {
	public:
		template<typename M>
		void set_value(M value) {
			if constexpr (std::is_integral_v<M>) {
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
				}
				this->digits = Number::as_digit_list<M>(value);
			}
			else if constexpr (std::is_same_v<M, std::string>) {
				if (Number::inspect_type(value.c_str()) == Number::INTEGER) {
					this->sign = value.front() == '-' ? Number::NEGATIVE : Number::POSITIVE;
					this->digits = Number::as_digit_list<std::string>(value);
				}
				else throw std::invalid_argument("Error in text_math::Integer::set_value: invalid integer formatting provided.");
			}
			else if constexpr (std::is_same_v<M, std::list<DIGIT>>) {
				this->digits = value;
			}
			else throw std::invalid_argument("Error in text_math::Integer::set_value: template parameter should be integral or std::string.");
		}

		void add(const Integer value) noexcept {
			auto [a, b] = Number::make_same_len(this->digits, value.get_digits());
			std::list<DIGIT> result;
			if (this->sign == Number::POSITIVE && value.get_sign() == Number::POSITIVE || this->sign == Number::NEGATIVE && value.get_sign() == Number::NEGATIVE) {
				for (auto it_a = a.begin(), it_b = b.begin(); it_a != a.end(); ++it_a, ++it_b) {
					result.push_back( (*it_a + *it_b) % 10 );
					if (std::next(it_b) != b.end()) 
						*std::next(it_b) += (*it_a + *it_b) / 10;
					else {
						if ((*it_a + *it_b) > 9)
							result.push_back((*it_a + *it_b) / 10);
					}
				}
				this->digits = result;
			}
			// ...
		}
		// TODO: operator+

		inline bool is_equal(const Integer value) noexcept {
			return value.get_sign() == this->sign && this->digits == value.get_digits();
		}
		inline bool operator==(const Integer value) noexcept {
			return is_equal(value);
		}
		inline bool is_not_equal(const Integer value) noexcept {
			return value.get_sign() != this->sign || this->digits != value.get_digits();
		}
		inline bool operator!=(const Integer value) noexcept {
			return is_not_equal(value);
		}

		bool is_greater_than(const Integer value) noexcept {
			std::list<DIGIT> _value = value.get_digits();
			if (value.get_sign() == Number::NEGATIVE && this->sign == Number::POSITIVE)
				return true;
			else if (value.get_sign() == Number::POSITIVE && this->sign == Number::NEGATIVE)
				return false;
			else if (_value.size() != this->digits.size())
				return value.get_sign() == Number::POSITIVE ? this->digits.size() > _value.size() : this->digits.size() < _value.size();
			else {
				for (auto it_a = this->digits.crbegin(), it_b = _value.crbegin(); it_a != this->digits.rend(); ++it_a, ++it_b) {
					if (*it_a > *it_b)
						return this->sign == Number::POSITIVE;
					else if (*it_a < *it_b)
						return this->sign == Number::NEGATIVE;
				}
			}
			return false;
		}
		inline bool operator>(const Integer value) noexcept {
			return is_greater_than(value);
		}
		inline bool is_equal_or_greater_than(const Integer value) noexcept {
			return is_equal(value) || is_greater_than(value);
		}
		inline bool operator>=(const Integer value) noexcept {
			return is_equal(value) || is_greater_than(value);
		}

		inline bool is_less_than(const Integer value) noexcept {
			return is_equal(value) xor !is_greater_than(value);
		}
		inline bool operator<(const Integer value) noexcept {
			return is_equal(value) xor !is_greater_than(value);
		}
		inline bool is_equal_or_less_than(const Integer value) noexcept {
			return is_equal(value) || is_less_than(value);
		}
		inline bool operator<= (const Integer value) noexcept {
			return is_equal(value) || is_less_than(value);
		}

		Integer(T value) {
			try {
				set_value<T>(value);
			}
			catch (std::exception err) {
				throw std::invalid_argument("Exception caught at text_math::Integer constructor: '" + std::string(err.what()) + "'");
			}
		}

		std::string as_string() const noexcept override {
			std::string str = this->sign == Number::NEGATIVE ? "-" : "";
			for (auto it = this->digits.rbegin(); it != digits.rend(); ++it)
				str.push_back(static_cast<char>(*it + '0'));
			return str;
		}

		friend static std::ostream& operator<<(std::ostream& os, const Integer& obj) noexcept {
			os << obj.as_string();
			return os;
		}
	};
}
