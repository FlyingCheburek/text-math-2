export module text_math:number;

import <regex>;
import <list>;

using DIGIT = unsigned short;

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

		template<std::integral T>
		static std::list<DIGIT> as_digit_list(T num) noexcept {
			std::list<DIGIT> ret;
			while (num > 0) {
				ret.push_back(num % 10);
				num /= 10;
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
		Number() noexcept {  }
		Number(const std::list<DIGIT>, const Sign) noexcept;

		virtual std::string as_string() const noexcept = 0;

		std::list<DIGIT> get_digits() const noexcept;
		Number::Sign get_sign() const noexcept;
	};
}