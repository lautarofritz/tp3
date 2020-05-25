#include "common_socket.h"
#include <string>

class Cliente{
	private:
		Socket socket;

	public:
		Cliente(const char *hostname, const char *port);
		void ejecutar();
		std::string procesarComando(std::string comando);
		void enviar(std::string procesado);
		char *recibir();
		~Cliente();
};