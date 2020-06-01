#include <string>
#include "common_miErrorComando.h"

MiErrorComando::MiErrorComando(std::string mensaje) : mensaje(mensaje) {}

const char *MiErrorComando::what() const noexcept{
	return this->mensaje.c_str();
}
