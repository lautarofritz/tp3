#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <vector>
#include "server.h"
#include "common_miError.h"

std::vector <int> procesarArchivo(std::string numeros);

int main(int argc, char *argv[]){
	if(argc != 3){
		std::cerr << "Error: argumentos invalidos.";
		return 1;
	}

	const char *port = argv[1];
	std::string numeros = argv[2];
	std::vector <int> v;

	try{
		v = procesarArchivo(numeros);
		Server server(v);
		server.ejecutar(port);
		server.estadisticas();
	} catch (const std::exception &e){
		std::cerr << e.what();
		return 1;
	}
}

std::vector <int> procesarArchivo(std::string numeros){
	std::fstream archivo;
	std::string linea;
	int numero;
	std::vector <int> v;
	archivo.open(numeros, std::ios::in);
	if(!archivo){
		throw MiError("No se pudo abrir el archivo.\n");
	}

	while(std::getline(archivo, linea)){
		if(linea[0] == linea[1] || linea[0] == linea[2] || linea[2] == linea[1]){
			archivo.close();
			throw MiError("Error: formato de los números inválidos");
		}
    	numero = std::stoi(linea, nullptr);
    	if(numero < 100 || numero > 999){
    		archivo.close();
    		throw MiError("Error: archivo con números fuera de rango");
    	}
    	v.push_back(numero);
    }
    archivo.close();
    return v;
}