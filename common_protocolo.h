#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <string>
#include "common_socket.h"

class Protocolo{
	private:
		Socket socket;

		//convierte el comando del cliente en uno apto para
		//ser entendido por el servidor
		//devuelve el comando en el formato correspondiente
		//si el comando del cliente es válido
		//o lanza una excepción en caso contrario
		std::string procesarComando(std::string comando);

	public:
		explicit Protocolo(Socket socket);

		//le otorga el mensaje traducido al socket para su envío
		//lanza una excepción si el envío falla
		//(en realidad esta es lanzada en el socket, 
		//y se propaga por este método)
		void enviarComando(std::string comando);

		//recibe el comando del cliente en un std::vector<char>
		//y lo devuelve como string, para facilitar procesos
		//si el cliente se desconectó, 
		//devuelve la cadena especial "Desconectar"
		//lanza una excepción si la recepción falla
		//(en realidad esta es lanzada en el socket, 
		//y se propaga por este método)
		std::string recibirComando();

		//envía la respuesta del servidor al cliente en dos partes:
		//primero la longitud, y luego la respuesta en sí
		//lanza una excepción si alguno de los envíos falla
		//(en realidad esta es lanzada en el socket, 
		//y se propaga por este método)
		void enviarRespuesta(std::string respuesta);

		//recibe el mensaje del servidor en dos partes:
		//primero la longitud y luego el mensaje en sí
		//la recibe en un std::vector<char>
		//y la devuelve como string, para facilitar procesos
		//lanza una excepción si alguna de las recepciones falla
		//(en realidad esta es lanzada en el socket, 
		//y se propaga por este método)
		std::string recibirRespuesta();
};

#endif
