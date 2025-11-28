module text_math;

using namespace text_math;

Number::Number(const std::list<DIGIT> value, const Sign sign = Number::POSITIVE) noexcept {
	this->digits = value;
	this->sign = sign;
}