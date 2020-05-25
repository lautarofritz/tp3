#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <vector>
#include <cstdint>
#include <mutex>
#include <string>

typedef std::string str;

class Server{
	private:
		int ganadores;
		int perdedores;
		std::vector <int> numeros;
		unsigned int indice;
		std::mutex m;

		str compararNumeros(str numeroCliente, str numero, int &vidas);

	public:
		explicit Server(std::vector<int> v);
		void ejecutar(const char *port);
		int solicitarNumero();
		str procesar(char cmd[], str nroCliente, str nro, int &vidas);
		void estadisticas();
};

#endif
