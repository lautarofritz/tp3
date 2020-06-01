#ifndef THREAD_CLIENTE_H
#define THREAD_CLIENTE_H

#include <atomic>
#include "server.h"
#include "server_thread.h"
#include "common_socket.h"

class ThreadAceptador;

class ThreadCliente : public Thread{
	private:
		Socket socket;
		Server &server;
		std::atomic<bool> finalizo;
		ThreadAceptador &aceptador;

		void terminar();

	public:
		ThreadCliente(Socket socket, Server &server, ThreadAceptador &a);

		//hilo conductor de la comunicación con el cliente
		//primero recibe un comando, luego lo pasa al servidor
		//para que lo interprete y finalmente envía la respuesta
		//devuelve 0 si todo salió bien o 1 si atrapó una excepción
		int operator()() override;
		bool termino();
};

#endif
