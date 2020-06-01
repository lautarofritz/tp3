#include <string>
#include "common_miErrorFatal.h"

MiErrorFatal::MiErrorFatal(std::string mensaje) : mensaje(mensaje) {}

const char *MiErrorFatal::what() const noexcept{
	return this->mensaje.c_str();
}
