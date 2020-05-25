#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include "common_socket.h"
#include "server.h"
#include "server_cliente.h"
#include <mutex>
#include <vector>
#include <condition_variable>
#include "server_thread.h"

class ThreadCliente;

class ThreadAceptador : public Thread{
	private:
		Socket socket;
		const char *port;
		Server &server;
		std::vector<ThreadCliente*> clientes;
		bool cerrado;
		std::mutex m;
		std::condition_variable cv;

	public:
		ThreadAceptador(const char *port, Server &server);
		int operator()() override;
		void unir();
		void cerrar();
		void notificar();
};

#endif
