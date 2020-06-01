#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <mutex>
#include <string>

//creado para poder cumplir con la restricción 
//de 80 caracteres por línea
typedef std::string str;

class Server{
	private:
		int ganadores;
		int perdedores;
		std::vector <int> numeros;
		unsigned int indice;
		std::mutex m;

		//devuelve la respuesta a ser enviada al cliente
		//y resta las vidas de forma correspondiente
		//en base al número que haya ingresado
		str compararNumeros(str numeroCliente, str numero, int &vidas);

	public:
		explicit Server(std::vector<int> v);

		//lanza el hilo aceptador y luego espera a la 'q'
		//para salir
		void ejecutar(const char *port);
		int solicitarNumero();

		//devuelve la respuesta a ser enviada al cliente
		//si el comando no es "AYUDA" o "RENDIRSE", llama a la 
		//función compararNumeros
		str procesar(str comando, str nro, int &vidas);
		void estadisticas();
};

#endif
