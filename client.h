#ifndef CLIENTE_H
#define CLIENTE_H

#include "common_socket.h"

class Cliente{
	private:
		Socket socket;

	public:
		//intenta conectar al cliente al servidor
		//si no lo logra, lanza una excepción
		//(en realidad esta es lanzada en el socket, 
		//y se propaga por este método)
		Cliente(const char *hostname, const char *port);

		//hilo conductor de la comunicación con el servidor
		//si atrapa una excepción resultante de un comando erróneo,
		//permite al cliente el ingreso de un nuevo comando
		//si atrapa una excepción resultante de una falla en
		//el envío o la recepción, cierra el socket y retorna
		void ejecutar();
		~Cliente();
};

#endif
