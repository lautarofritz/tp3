#include <iostream>
#include <cstdint>
#include <arpa/inet.h>
#include <cstring>
//#include "common_socket.h"
#include "server_cliente.h"
#include "server_aceptador.h"

#define VIDAS 10

ThreadCliente::ThreadCliente(Socket *skt, Server &server, ThreadAceptador &a) :
	server(server), finalizo(false), aceptador(a){
		this->socket = skt;
	}

int ThreadCliente::operator()(){
	int n = this->server.solicitarNumero();
	std::string nString = std::to_string(n);
	int vidas = VIDAS;
	std::string respuesta;
	while(true){
		respuesta = recibirYProcesar(nString, vidas);
		if(respuesta == "Desconectar"){
			break;
		}
		enviar(respuesta);
	}
	terminar();
	aceptador.notificar();
	return 0;
}

std::string ThreadCliente::recibirYProcesar(std::string n, int &vidas){
	char comando[2];
	uint16_t nCliente;
	std::string nClienteString;
	if(this->socket->recibir(comando, 1) == 0){
		return "Desconectar";
	}
	comando[1] = '\0';
	if(strcmp(comando, "n") == 0){
		this->socket->recibir_uint16(nCliente, 2);
		nCliente = ntohs(nCliente);
		nClienteString = std::to_string(nCliente);
	}
	std::string respuesta = server.procesar(comando, nClienteString, n, vidas);
	return respuesta;
}

void ThreadCliente::enviar(std::string respuesta){
	uint32_t longRespuesta = respuesta.length();
	longRespuesta = htonl(longRespuesta);
	socket->enviar_uint32(longRespuesta, sizeof(uint32_t));
	socket->enviar(respuesta, respuesta.length());
}

void ThreadCliente::terminar(){
	this->finalizo = true;
	this->socket->cerrar();
}

bool ThreadCliente::termino(){
	return this->finalizo;
}

ThreadCliente::~ThreadCliente(){
	delete this->socket;
}
