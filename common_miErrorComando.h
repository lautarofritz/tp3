#ifndef MI_ERROR_COMANDO_H
#define MI_ERROR_COMANDO_H

#include <exception>
#include <string>

class MiErrorComando : public std::exception{
	private:
		std::string mensaje;

	public:
		explicit MiErrorComando(std::string mensaje);
		virtual const char* what() const noexcept override;
};

#endif
