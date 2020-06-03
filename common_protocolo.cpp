#include <netdb.h>
#include <limits.h>
#include <cstdint>
#include <vector>
#include <string>
#include <utility>
#include "common_protocolo.h"
#include "common_miErrorComando.h"
#include "common_miErrorFatal.h"

#define LONG_COMANDO 1

Protocolo::Protocolo(Socket socket) : socket(std::move(socket)) {}

void Protocolo::enviarComando(std::string comando){
	std::string procesado;
	procesado = procesarComando(comando);
	if(procesado == "h" || procesado == "s"){
		socket.enviar(procesado, LONG_COMANDO);
	} else {
		uint16_t numero;
		numero = std::stoi(procesado);
		numero = htons(numero);
		socket.enviar("n", LONG_COMANDO);
		socket.enviar_uint16(numero, sizeof(uint16_t));
	}
}

std::string Protocolo::procesarComando(std::string comando){
	int numero;
	if(comando == "AYUDA")
		return "h";
	if(comando == "RENDIRSE")
		return "s";

	if(comando[0] >= '0' && comando[0] <= '9' && comando.length() <= 5){
		numero = std::stoi(comando);
		if(numero > USHRT_MAX){
			throw MiErrorComando("Error: comando inválido. "
				"Escriba AYUDA para obtener ayuda\n");
		}

		return comando;
	}
	throw MiErrorComando("Error: comando inválido. "
		"Escriba AYUDA para obtener ayuda\n");
}

std::string Protocolo::recibirComando(){
	uint16_t nCliente;
	std::string comando;
	std::vector<char> buffer(LONG_COMANDO);
	if(this->socket.recibir(buffer, LONG_COMANDO) < LONG_COMANDO){
		comando = "Desconectar";
		return comando;
	}
	comando.assign(buffer.data(), LONG_COMANDO);
	if(comando == "n"){
		if(this->socket.recibir_uint16(nCliente, 2) < 2){
			comando = "Desconectar";
			return comando;
		}
		nCliente = ntohs(nCliente);
		comando = std::to_string(nCliente);
	}
	return comando;
}

void Protocolo::enviarRespuesta(std::string respuesta){
	uint32_t longRespuesta = respuesta.length();
	longRespuesta = htonl(longRespuesta);
	socket.enviar_uint32(longRespuesta, sizeof(uint32_t));
	socket.enviar(respuesta, respuesta.length());
}

std::string Protocolo::recibirRespuesta(){
	uint32_t longRespuesta;
	std::vector<char> buffer;
	socket.recibir_uint32(longRespuesta, sizeof(uint32_t));
	longRespuesta = ntohl(longRespuesta);
	buffer.resize(longRespuesta);
	socket.recibir(buffer, longRespuesta);
	std::string respuesta(buffer.data(), longRespuesta);
	return respuesta;
}
