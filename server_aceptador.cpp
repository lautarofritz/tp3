#include <exception>
#include <iostream>
#include <utility>
#include "server_aceptador.h"
#include "server_cliente.h"

ThreadAceptador::ThreadAceptador(const char *port, Server &server) :
	port(port), server(server), cerrado(false){}

int ThreadAceptador::operator()(){
	try{
		this->socket.bindListen(nullptr, port);
	} catch (const std::exception &e){
		std::cerr << e.what();
		cerrar();
		return 1;
	}

	while(true){
		Socket peer;
		try{
			peer = this->socket.aceptar();
		} catch(const std::exception &e){
			if(!this->cerrado){
				std::cerr << e.what();
				liberarClientes();
				cerrar();
				return 1;
			}
			break;
		}
		ThreadCliente* cliente = new ThreadCliente(std::move(peer), server, *this);
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

	liberarClientes();
	return 0;
}

void ThreadAceptador::liberarClientes(){
	for(unsigned int i = 0; i < clientes.size(); i++){
		std::unique_lock<std::mutex> lock(m);
		while(!clientes[i]->termino()){
			cv.wait(lock);
		}
		clientes[i]->unir();
		delete clientes[i];
	}
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
