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
		enum Sign : short {
			POSITIVE,
			NEGATIVE
		};

		static Type inspect_type(const char*) noexcept;
		static std::string trim_zeroes_str(std::string) noexcept;
		static std::list<DIGIT> trim_zeroes(const std::list<DIGIT>&) noexcept;

		std::list<DIGIT> digits;
		Sign sign;

	public:
		Number() noexcept {  }
		Number(const std::list<DIGIT>, const Sign) noexcept;

		std::list<DIGIT> get_digits() const noexcept;
		Number::Sign get_sign() const noexcept;		
	};
}