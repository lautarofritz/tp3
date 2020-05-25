#include "common_socket.h"
#include <string>

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

		//convierte el comando del cliente en uno apto para
		//ser entendido por el servidor
		//devuelve el comando en el formato correspondiente
		//si el comando del cliente es válido
		//o lanza una excepción en caso contrario
		std::string procesarComando(std::string comando);

		//le otorga el mensaje traducido al socket para su envío
		//lanza una excepción si el envío falla
		//(en realidad esta es lanzada en el socket, 
		//y se propaga por este método)
		void enviar(std::string procesado);

		//recibe el mensaje del servidor en dos partes:
		//primero la longitud y luego el mensaje en sí
		//lanza una excepción si alguna de las recepciones falla
		//(en realidad esta es lanzada en el socket, 
		//y se propaga por este método)
		//si la recepción fue exitosa, muestra por pantalla la
		//respuesta del servidor y luego la retorna
		char *recibir();
		~Cliente();
};
