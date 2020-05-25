#ifndef SERVER_ACEPTADOR_H
#define SERVER_ACEPTADOR_H

#include <condition_variable>
#include <mutex>
#include <vector>
#include "common_socket.h"
#include "server.h"
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

		void liberarClientes();

	public:
		ThreadAceptador(const char *port, Server &server);

		//hilo conductor de la ejecución del programa
		//lanza los hilos con los que se comunican los clientes
		//luego, los elimina a medida que los clientes
		//se vayan desconectando
		//devuelve 0 si todo sale bien o 1 si atrapa una excepción
		int operator()() override;

		//notifica al hilo aceptador que un cliente se desconectó
		//sólo en el caso que ya se haya cerrado el servidor
		//o sea, que se haya recibido la 'q' por entrada estándar
		void notificar();
		void unir();
		void cerrar();
};

#endif
