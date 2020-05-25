#include "server_aceptador.h"
#include <exception>
#include <iostream>

ThreadAceptador::ThreadAceptador(const char *port, Server &server) :
	port(port), server(server), cerrado(false){}

int ThreadAceptador::operator()(){
	try{
		this->socket.bindListen(nullptr, port);
		while(true){
			Socket *peer = this->socket.aceptar();
			if(this->cerrado)
				break;
			ThreadCliente* cliente = new ThreadCliente(peer, server, *this);
			cliente->empezar();
			clientes.push_back(cliente);
			for(unsigned int i = 0; i < clientes.size(); i++){
				if(clientes[i]->termino()){
					clientes[i]->unir();
					delete clientes[i];
					clientes.erase(clientes.begin() + i);
				}
			}
		}
		for(unsigned int i = 0; i < clientes.size(); i++){
			std::unique_lock<std::mutex> lock(m);
			while(!clientes[i]->termino()){
				cv.wait(lock);
			}
			clientes[i]->unir();
			delete clientes[i];
		}
	} catch (const std::exception &e){
		std::cerr << e.what();
		return 1;
	}

	return 0;
}

void ThreadAceptador::notificar(){
	std::unique_lock<std::mutex> lock(m);

	if(this->cerrado)
		cv.notify_all();
}

void ThreadAceptador::unir(){
	Thread::unir();
}

void ThreadAceptador::cerrar(){
	this->cerrado = true;
	this->socket.cerrar();
}