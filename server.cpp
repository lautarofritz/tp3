#include <iostream>
#include <cstring>
#include "server.h"
#include "server_aceptador.h"

Server::Server(std::vector<int> v) : 
	ganadores(0), perdedores(0), numeros(v), indice(0) {}

void Server::ejecutar(const char *port){
	ThreadAceptador *aceptador = new ThreadAceptador(port, *this);
	aceptador->empezar();
	char c;
	while(true){
		c = std::cin.get();
		if(c == 'q')
			break;
	}
	aceptador->cerrar();
	aceptador->unir();
	delete aceptador;
}

int Server::solicitarNumero(){
	std::lock_guard<std::mutex> lock(m);
	int numero = numeros[indice];
	if(indice == numeros.size() - 1){
		indice = 0;
	} else {
		indice++;
	}

	return numero;
}

std::string Server::procesar(char comando[], std::string numeroCliente, std::string numero, int &vidas){
	std::lock_guard<std::mutex> lock(m);
	if(strcmp(comando, "h") == 0){
		return "Comandos válidos:​ \n\t​AYUDA: despliega la lista de comandos"
		" válidos​ \n\t​RENDIRSE: pierde el juego automáticamente​ \n\t​"
		"XXX: Número de 3 cifras a ser enviado al servidor para adivinar"
		" el número secreto";
	}

	if(strcmp(comando, "s") == 0){
		perdedores++;
		return "Perdiste";
	}

	std::string respuesta = compararNumeros(numeroCliente, numero, vidas);
	if(vidas == 0){
		perdedores++;
		return "Perdiste";
	}

	return respuesta;
}

std::string Server::compararNumeros(std::string numeroCliente, std::string numero, int &vidas){
	if(numeroCliente.length() != 3 || 
		numeroCliente[0] == numeroCliente[1] || 
		numeroCliente[1] == numeroCliente[2] || 
		numeroCliente[0] == numeroCliente[2]){
		vidas--;
		return "Número inválido. Debe ser de 3 cifras no repetidas";
	}

	int cantBien = 0, cantRegular = 0;
	std::string respuesta;

	if(numeroCliente == numero){
		ganadores++;
		return "Ganaste";
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(numero[i] == numeroCliente[j]){
				if(i == j){
					cantBien++;
				} else{
					cantRegular++;
				}
			}
		}
	}

	if(cantBien > 0 && cantRegular > 0){
		std::string aux = std::to_string(cantBien);
		respuesta = aux + " bien, ";
		aux = std::to_string(cantRegular);
		respuesta += aux + " regular";
	} else if(cantBien > 0 && cantRegular == 0){
		std::string aux = std::to_string(cantBien);
		respuesta = aux + " bien";
	} else if(cantBien == 0 && cantRegular > 0){
		std::string aux = std::to_string(cantRegular);
		respuesta = aux + " regular";
	} else if(cantBien == 0 && cantRegular == 0){
		respuesta = "3 mal";
	}
	vidas--;

	return respuesta;
}

void Server::estadisticas(){
	std::cout << "Estadísticas:\n\t"
	"Ganadores:  " << ganadores << 
	"\n\tPerdedores: " << perdedores << "\n";
}