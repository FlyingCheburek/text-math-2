export module text_math:integer;
import :number;
import <stdexcept>;
import <ostream>;
import <iostream>;

namespace text_math {
	
	export template<typename T>
	class Integer final : public Number {
	private:
		Integer() noexcept { }

		template<typename M>
		void set_value(M value, const Number::Sign sign) {
			this->set_value(value);
			this->sign = sign;
		}

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

		void sum(const Integer value) noexcept {
			if (this->sign != value.get_sign()) {
				this->sign = this->sign == Number::POSITIVE ? Number::NEGATIVE : Number::POSITIVE;
				this->subtract(value);
				this->sign = this->sign == Number::POSITIVE && this->digits.back() != 0 ? Number::NEGATIVE : Number::POSITIVE;
			}
			else {
				auto [a, b] = Number::make_same_len(this->digits, value.get_digits());
				std::list<DIGIT> result;
				if (this->sign == Number::POSITIVE && value.get_sign() == Number::POSITIVE || this->sign == Number::NEGATIVE && value.get_sign() == Number::NEGATIVE) {
					for (auto it_a = a.begin(), it_b = b.begin(); it_a != a.end(); ++it_a, ++it_b) {
						result.push_back((*it_a + *it_b) % 10);
						if (std::next(it_b) != b.end())
							*std::next(it_b) += (*it_a + *it_b) / 10;
						else {
							if ((*it_a + *it_b) > 9)
								result.push_back((*it_a + *it_b) / 10);
						}
					}
					this->digits = result;
				}
			}
		}
		inline Integer operator+(const Integer& other) const noexcept {
			Integer result(*this);
			result.sum(other);
			return result;
		}
		inline Integer& operator++() noexcept { // prefix (++x)
			if constexpr (std::is_integral_v<T>)
				this->sum(Integer<T>(1));
			else
				this->sum(Integer<T>("1"));
			return *this;
		}
		inline Integer operator++(int) noexcept { // post-fix (x++)
			Integer result(*this);
			++*this;
			return result;
		}
		inline Integer operator+=(const Integer& other) noexcept {
			*this = *this + other;
			return *this;
		}
		

		void subtract(const Integer value) noexcept {
			if (this->sign != value.get_sign()) {
				this->sign = this->sign == Number::POSITIVE ? Number::NEGATIVE : Number::POSITIVE;
				this->sum(value);
				this->sign = this->sign == Number::POSITIVE ? Number::NEGATIVE : Number::POSITIVE;
			}
			else {
				auto [a, b] = Number::make_same_len(this->digits, value.get_digits(), true);
				std::list<DIGIT> result;
				for (auto it_a = a.begin(), it_b = b.begin(); it_a != a.end(); ++it_a, ++it_b) {
					DIGIT d = *it_a - *it_b;
					if (d < 0) {
						d += 10;
						*std::next(it_a) -= 1;
					}
					result.push_back(d);
				}
				while (result.size() > 1 && result.back() == 0)
					result.pop_back();

				this->sign = this->is_equal_or_greater_than(value) ? Number::POSITIVE : Number::NEGATIVE;
				this->digits = result;
			}
		}
		inline Integer operator-(const Integer& other) const noexcept {
			Integer result(*this);
			result.subtract(other);
			return result;
		}
		inline Integer& operator--() noexcept { // prefix (--x)
			if constexpr (std::is_integral_v<T>)
				this->subtract(Integer<T>(1));
			else
				this->subtract(Integer<T>("1"));
			return *this;
		}
		inline Integer operator--(int) noexcept { // post-fix (x--)
			Integer result(*this);
			--*this;
			return result;
		}
		inline Integer operator-=(const Integer& other) noexcept {
			Integer result(*this);
			*this = *this - other;
			return *this;
		}

		void multiply(const Integer value) noexcept {
			if (value.get_digits() == std::list<DIGIT>({ 0 }) || this->digits == std::list<DIGIT>({ 0 }))
				this->digits = std::list<DIGIT>({ 0 });
			
			else {
				auto [a, b] = Number::make_same_len(this->digits, value.get_digits());
				size_t count = 0;
				Integer result;
				for (auto it_b = b.cbegin(); it_b != b.cend(); ++it_b) {
					if (*it_b == 0 && std::next(it_b) == b.cend())
						break;

					DIGIT extra = 0, curr = 0;
					std::string prod = "";
					for (auto it_a = a.cbegin(); it_a != a.cend(); ++it_a) {
						curr = (*it_a * *it_b) + extra;
						prod = std::to_string(std::next(it_a) == a.cend() ? curr : curr % 10) + prod;
						extra = curr / 10;
					}
					for (size_t i = 0; i < count; i++)
						prod.push_back('0');
					if (count == 0)
						result.set_value<std::string>(prod);
					else {
						if constexpr (std::is_integral_v<T>) {
							Integer temp;
							temp.set_value<std::string>(prod);
							result.sum(temp);
						}
						else
							result.sum(Integer(prod));
						
					}
					count++;
				}
				this->sign = this->sign != value.get_sign() ? Number::NEGATIVE : Number::POSITIVE;
				this->digits = result.get_digits();
			}
		}
		inline Integer operator*(const Integer& other) const noexcept {
			Integer result(*this);
			result.multiply(other);
			return result;
		}
		inline Integer operator*=(const Integer& other) noexcept {
			Integer result(*this);
			result.multiply(other);
			*this = result;
			return *this;
		}

		void divide(const Integer value, Integer* remainder = nullptr) {
			if (value.get_digits() == std::list<DIGIT>({ 0 }))
				throw std::invalid_argument("Error in text_math::Integer::divide: division by 0.");

			if (this->is_less_than(Integer::abs(value))) {
				this->digits = std::list<DIGIT>({ 0 });
				this->sign = Number::POSITIVE;
				if (remainder)
					*remainder = value;
			}	
			else {
				// TODO...
			}
		}

		inline bool is_equal(const Integer value) const noexcept {
			return value.get_sign() == this->sign && this->digits == value.get_digits();
		}
		inline bool operator==(const Integer value) const noexcept {
			return is_equal(value);
		}
		inline bool is_not_equal(const Integer value) const noexcept {
			return value.get_sign() != this->sign || this->digits != value.get_digits();
		}
		inline bool operator!=(const Integer value) const noexcept {
			return is_not_equal(value);
		}

		bool is_greater_than(const Integer value) const noexcept {
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
		inline bool operator>(const Integer value) const noexcept {
			return is_greater_than(value);
		}
		inline bool is_equal_or_greater_than(const Integer value) const noexcept {
			return is_equal(value) || is_greater_than(value);
		}
		inline bool operator>=(const Integer value) const noexcept {
			return is_equal(value) || is_greater_than(value);
		}

		inline bool is_less_than(const Integer value) const noexcept {
			return is_equal(value) xor !is_greater_than(value);
		}
		inline bool operator<(const Integer value) const noexcept {
			return is_equal(value) xor !is_greater_than(value);
		}
		inline bool is_equal_or_less_than(const Integer value) const noexcept {
			return is_equal(value) || is_less_than(value);
		}
		inline bool operator<= (const Integer value) const noexcept {
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

		static Integer abs(const Integer value) noexcept {
			Integer result;
			result.set_value<std::string>(value.as_string(), Number::POSITIVE);
			return result;
		}

		friend static std::ostream& operator<<(std::ostream& os, const Integer& obj) noexcept {
			os << obj.as_string();
			return os;
		}
	};
}
