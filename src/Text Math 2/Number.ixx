export module text_math:number;

import <regex>;
import <list>;
import <type_traits>;
import <tuple>;

using DIGIT = short;

namespace text_math {
	export class Number {
	protected:
		enum Type : short {
			INTEGER,
			DECIMAL,
			INVALID
		};

		static Type inspect_type(const char*) noexcept;
		static std::string trim_zeroes_str(std::string) noexcept;
		static std::list<DIGIT> trim_zeroes(const std::list<DIGIT>&) noexcept;
		static std::tuple<std::list<DIGIT>, std::list<DIGIT>> make_same_len(const std::list<DIGIT>&, const std::list<DIGIT>&, const bool&& compare_digit_value = false);

		template<typename T>
		static std::list<DIGIT> as_digit_list(T num) noexcept {
			std::list<DIGIT> ret;
			if constexpr (std::is_integral_v<T>) {
				while (num > 0) {
					ret.push_back(num % 10);
					num /= 10;
				}
			}
			else if constexpr (std::is_same_v<T, std::string>) {
				for (const char& d : trim_zeroes_str(num))
					ret.push_front(static_cast<DIGIT>(d - '0'));

				if (num.front() == '-')
					ret.pop_back();
			}
			return ret;
		}

	public:
		enum Sign : short {
			POSITIVE,
			NEGATIVE
		};

	protected:
		std::list<DIGIT> digits;
		Sign sign;

	public:
		Number() noexcept { }
		Number(const std::list<DIGIT>, const Sign) noexcept;

		virtual std::string as_string() const noexcept = 0;

		std::list<DIGIT> get_digits() const noexcept;
		Number::Sign get_sign() const noexcept;
	};
}