#include <list>

export module text_math:number;

using DIGIT = unsigned short;

namespace text_math {
	export class Number {
	public:
		enum Type : short {
			INTEGER,
			DECIMAL,
			INVALID
		};
		enum Sign : short {
			POSITIVE,
			NEGATIVE
		};

	protected:
		std::list<DIGIT> digits;
		Sign sign;

	public:
		Number(const std::list<DIGIT>, const Sign) noexcept;
	};
}