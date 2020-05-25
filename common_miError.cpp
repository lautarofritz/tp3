#include "common_miError.h"

MiError::MiError(std::string mensaje) : mensaje(mensaje) {}

const char *MiError::what() const noexcept{
	return this->mensaje.c_str();
}
