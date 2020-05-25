#include <iostream>
#include "client.h"

int main(int argc, char* argv[]){
	if(argc != 3){
		std::cout << "Error: argumentos invalidos.";
		return 0;
	}

	const char* hostname = argv[1];
	const char* port = argv[2];

	try{
		Cliente cliente(hostname, port);
		cliente.ejecutar();
	} catch (const std::exception &e){
		std::cout << e.what();
		return 0;
	}

	return 0;
}
