#include <iostream>
#include <string>
#include "client.h"
#include "common_protocolo.h"
#include "common_miErrorComando.h"
#include "common_miErrorFatal.h"

Cliente::Cliente(const char *hostname, const char *port){
	this->socket.conectar(hostname, port);
}

void Cliente::ejecutar(){
	Protocolo protocolo(std::move(this->socket));
	std::string comando, respuesta;
	while(true){
		std::cin >> comando;
		try{
			protocolo.enviarComando(comando);
			respuesta = protocolo.recibirRespuesta();
		} catch(const MiErrorComando &e){
			std::cout << e.what();
			continue;
		} catch(const MiErrorFatal &e){
			std::cout << e.what();
			break;
		}

		std::cout << respuesta << std::endl;
		if(respuesta == "Ganaste" || respuesta == "Perdiste")
			break;
	}
}

Cliente::~Cliente() {}
