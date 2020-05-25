#include <iostream>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include "client.h"

#define NUMERO_MAX_2_BYTES 65536

Cliente::Cliente(const char *hostname, const char *port){
	this->socket.conectar(hostname, port);
}

void Cliente::ejecutar(){
	std::string comando, procesado;
	char *respuesta;
	while(true){
		std::cin >> comando;		//habra que usar getline?
		try{
			procesado = procesarComando(comando);
		} catch(const std::exception &e){
			//std::cout << e.what();			//termina el programa?
			//continue;
		}
		enviar(procesado);
		respuesta = recibir();

		if(strcmp(respuesta, "Perdiste") == 0 || strcmp(respuesta, "Ganaste") == 0){
			free(respuesta);
			break;
		} 
		free(respuesta);
	}
	//this->socket.cerrar();
	//cerrar socket
}

std::string Cliente::procesarComando(std::string comando){
	int numero;
	if(comando == "AYUDA")
		return "h";
	if(comando == "RENDIRSE")
		return "s";

	if(comando[0] >= '1' && comando[0] <= '9'){
		numero = std::stoi(comando);
		if(numero > NUMERO_MAX_2_BYTES){
			//throw MiError("Error: comando inválido. Escriba AYUDA para obtener ayuda");
		}

		return comando;
	}
	//throw MiError("Error: comando inválido. Escriba AYUDA para obtener ayuda");
	return "";
}

void Cliente::enviar(std::string procesado){
	uint16_t numero;
	if(procesado == "h" || procesado == "s"){
		socket.enviar(procesado, 1);
	} else {
		numero = std::stoi(procesado);
		numero = htons(numero);
		socket.enviar("n", 1);
		socket.enviar_uint16(numero, 2);
	}
}

char *Cliente::recibir(){
	uint32_t longRespuesta;
	char *respuesta;
	socket.recibir_uint32(longRespuesta, sizeof(uint32_t));
	longRespuesta = ntohl(longRespuesta);
	respuesta = (char*) malloc(longRespuesta + 1);
	socket.recibir(respuesta, longRespuesta);
	respuesta[longRespuesta] = '\0';
	std::cout << respuesta << std::endl;
	return respuesta;
}

Cliente::~Cliente(){
	this->socket.cerrar();
}