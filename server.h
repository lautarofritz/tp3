#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <vector>
#include <cstdint>
#include <mutex>

class Server{
	private:
		int ganadores;
		int perdedores;
		std::vector <int> numeros;
		unsigned int indice;
		std::mutex m;

		std::string compararNumeros(std::string numeroCliente, std::string numero, int &vidas);

	public:
		Server(std::vector<int> v);
		void ejecutar(const char *port);
		int solicitarNumero();
		std::string procesar(char comando[], std::string numeroCliente, std::string numero, int &vidas);
		void estadisticas();
};

#endif
