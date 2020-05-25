#ifndef THREAD_CLIENTE_H
#define THREAD_CLIENTE_H

#include <atomic>
#include <string>
#include "server.h"
#include "server_thread.h"

class Socket;
class ThreadAceptador;

class ThreadCliente : public Thread{
	private:
		Socket *socket;
		Server &server;
		std::atomic<bool> finalizo;
		ThreadAceptador &aceptador;

		//recibe el comando del cliente y se lo pasa al servidor
		//devuelve la respuesta de este si el cliente sigue conectado
		//o la cadena especial "Desconectar" en caso contrario
		//lanza una excepción si la recepción falla
		//(en realidad esta es lanzada en el socket, 
		//y se propaga por este método)
		std::string recibirYProcesar(std::string n, int &vidas);

		//envía la respuesta del servidor al cliente en dos partes:
		//primero la longitud, y luego la respuesta en sí
		//lanza una excepción si alguno de los envíos falla
		//(en realidad esta es lanzada en el socket, 
		//y se propaga por este método)
		void enviar(std::string respuesta);
		void terminar();

	public:
		ThreadCliente(Socket *socket, Server &server, ThreadAceptador &a);

		//hilo conductor de la comunicación con el cliente
		//primero recibe un comando, luego lo pasa al servidor
		//para que lo interprete y finalmente envía la respuesta
		//devuelve 0 si todo salió bien o 1 si atrapó una excepción
		int operator()() override;
		bool termino();
		~ThreadCliente();
};

#endif
