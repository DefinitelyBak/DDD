#pragma once


class OutOfStock : public std::exception {
public:
	OutOfStock(const std::string& message) : msg_(message) {}

	virtual const char* what() const noexcept override
	{
		return msg_.c_str();
	}

private:
	std::string msg_;
};