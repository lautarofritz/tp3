#ifndef MI_ERROR_FATAL_H
#define MI_ERROR_FATAL_H

#include <exception>
#include <string>

class MiErrorFatal : public std::exception{
	private:
		std::string mensaje;

	public:
		explicit MiErrorFatal(std::string mensaje);
		virtual const char* what() const noexcept override;
};

#endif
