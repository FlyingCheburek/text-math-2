module text_math:number;

using namespace text_math;

Number::Type Number::inspect_type(const char* value) noexcept{
	if (std::regex_match(value, std::regex("^-?\\d+$")))
		return INTEGER;

	if (std::regex_match(value, std::regex("^-?\\d*\\.\\d+$")))
		return DECIMAL;

	return INVALID;
}

std::string Number::trim_zeroes_str(std::string value) noexcept {
	bool negative = value.front() == '-';
	if (negative)
		value.erase(0, 1);

	size_t trim_idx = value.find_first_not_of('0');

	if (trim_idx == std::string::npos)
		return "0";
	else if (trim_idx != value.length() - 1)
		value = value.substr(trim_idx);

	if (negative) value = "-" + value;

	return value;
}

std::list<DIGIT> Number::trim_zeroes(const std::list<DIGIT>& value) noexcept {
	bool trimming = true;
	std::list<DIGIT> trimmed;
	for (const DIGIT& d : value) {
		if (d > 0) {
			if (trimming)
				trimming = false;
			trimmed.push_back(d);
		}
		else if (!trimming)
			trimmed.push_back(d);
	}
	if (trimmed.empty()) 
		trimmed.push_back(0);

	return trimmed;
}

std::tuple<std::list<DIGIT>, std::list<DIGIT>> text_math::Number::make_same_len(const std::list<DIGIT>& a, const std::list<DIGIT>& b) {
	auto [big, small] = std::make_tuple( (a.size() > b.size() ? a : b), (a.size() < b.size() ? a : b));

	for (size_t siz = big.size() - small.size() + 1; siz > 1; siz--)
		small.push_back(0);

	return std::make_tuple(big, small);
}

Number::Number(const std::list<DIGIT> value, const Sign sign = Number::POSITIVE) noexcept {
	this->digits = value;
	this->sign = sign;
}

std::list<DIGIT> Number::get_digits() const noexcept {
	return digits;
}

Number::Sign Number::get_sign() const noexcept {
	return sign;
}
