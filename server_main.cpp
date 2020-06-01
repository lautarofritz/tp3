#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <vector>
#include "server.h"
#include "common_miErrorFatal.h"

//devuelve un vector con los números a ser pasados
//al servidor
//o lanza una excepción si el formato de los 
//números no es adecuado
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
	} catch (const std::exception &e){
		std::cerr << e.what();
		return 1;
	}

	Server server(v);
	server.ejecutar(port);
	server.estadisticas();

	return 0;
}

std::vector <int> procesarArchivo(std::string numeros){
	std::fstream archivo;
	std::string linea;
	int numero;
	std::vector <int> v;
	archivo.open(numeros, std::ios::in);
	if(!archivo){
		throw MiErrorFatal("No se pudo abrir el archivo.\n");
	}

	while(std::getline(archivo, linea)){
		if(linea[0] == linea[1] || linea[0] == linea[2] || linea[2] == linea[1]){
			archivo.close();
			throw MiErrorFatal("Error: formato de los números inválidos\n");
		}
    	numero = std::stoi(linea, nullptr);
    	if(numero < 100 || numero > 999){
    		archivo.close();
    		throw MiErrorFatal("Error: archivo con números fuera de rango\n");
    	}
    	v.push_back(numero);
    }
    archivo.close();
    return v;
}
