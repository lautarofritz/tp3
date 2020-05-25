#ifndef THREAD_CLIENTE_H
#define THREAD_CLIENTE_H

#include <string>
#include <atomic>
//#include "server_aceptador.h"
#include "server.h"
//#include "common_socket.h"
#include "server_thread.h"

class Socket;
class ThreadAceptador;

class ThreadCliente : public Thread{
	private:
		Socket *socket;
		Server &server;
		std::atomic<bool> finalizo;
		ThreadAceptador &aceptador;

	public:
		ThreadCliente(Socket *socket, Server &server, ThreadAceptador &a);
		int operator()() override;
		std::string recibirYProcesar(std::string , int &vidas);
		void enviar(std::string respuesta);
		void terminar();
		bool termino();
		~ThreadCliente();
};

#endif
