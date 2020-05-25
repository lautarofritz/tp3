#ifndef MI_ERROR_H
#define MI_ERROR_H

#include <exception>
#include <string>

class MiError : public std::exception{
	private:
		std::string mensaje;

	public:
		explicit MiError(std::string mensaje);
		virtual const char* what() const noexcept override;
};

#endif
