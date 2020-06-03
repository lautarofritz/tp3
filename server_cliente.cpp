#include <string>
#include <utility>
#include "server_cliente.h"
#include "server_aceptador.h"
#include "common_protocolo.h"

#define VIDAS 10

ThreadCliente::ThreadCliente(Socket skt, Server &server, ThreadAceptador &a) :
	socket(std::move(skt)), server(server), finalizo(false), aceptador(a) {}

int ThreadCliente::operator()(){
	Protocolo protocolo(std::move(this->socket));
	int n = this->server.solicitarNumero();
	std::string nString = std::to_string(n);
	int vidas = VIDAS;
	std::string respuesta, comando;
	while(true){
		try{
			comando = protocolo.recibirComando();
			if(comando == "Desconectar"){
				break;
			}
			respuesta = server.procesar(comando, nString, vidas);
			protocolo.enviarRespuesta(respuesta);
		} catch(const std::exception &e){
			terminar();
			aceptador.notificar();
			return 1;
		}
	}
	terminar();
	aceptador.notificar();
	return 0;
}

void ThreadCliente::terminar(){
	this->finalizo = true;
}

bool ThreadCliente::termino(){
	return this->finalizo;
}
