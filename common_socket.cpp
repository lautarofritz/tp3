#define _POSIX_C_SOURCE 201112L
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include "common_miError.h"
#include "common_socket.h"

Socket::Socket() : fd(-1) {}

void Socket::conectar(const char* hostname, const char* port){
    struct addrinfo *resultados = getAddrList(hostname, port, 0);
    struct addrinfo *ptr;
    int fd;
    for (ptr = resultados; ptr != NULL; ptr = ptr -> ai_next) {
        fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (fd == -1)
            continue;
        if (connect(fd, ptr -> ai_addr, ptr -> ai_addrlen) != -1)
            break;
        close(fd);
    }

    if (ptr == NULL)
        throw MiError("No se pudo conectar a la red\n");

    setFd(fd);
    freeaddrinfo(resultados);
}

void Socket::bindListen(const char *hostname, const char *port){
    list *resultados = getAddrList(hostname, port, AI_PASSIVE);
    list *ptr;
    int fd;
    for (ptr = resultados; ptr != NULL; ptr = ptr -> ai_next){
        fd = socket(ptr -> ai_family, ptr -> ai_socktype, ptr -> ai_protocol);
        if (fd == -1)
            continue;

        if (bind(fd, ptr -> ai_addr, ptr -> ai_addrlen) == 0)
            break;
        close(fd);
    }

    if (ptr == NULL){
      throw MiError("No se pudo dejar atado al socket\n");
    }

    setFd(fd);
    freeaddrinfo(resultados);
    if (listen(this -> fd, 10) == -1){
      throw MiError("No se pudo dejar escuchando al socket\n");
    }
}

Socket* Socket::aceptar(){
    int accept_fd = accept(this->fd, NULL, NULL);
    if(accept_fd == -1){
      throw MiError("Error al intentar aceptar una conexión\n");
    }
    Socket* peer = new Socket();
    peer->setFd(accept_fd);
    return peer;
}

list *Socket::getAddrList(const char *hostname, const char *port, int flag){
	list hints, *resultados;

    std::memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = flag;
    
    getaddrinfo(hostname, port, &hints, &resultados);
    
    return resultados;
}

void Socket::enviar(std::string msj, int longitud){
    int total = 0, enviado = 0;
    while (total < longitud){
       enviado = send(this->fd, &msj[total], longitud - total, MSG_NOSIGNAL);
       if (enviado == -1)
           throw MiError("Error en el envío del mensaje\n");
       total += enviado;
    }
}

void Socket::enviar_uint16(uint16_t n, int longitud){
    int total = 0, enviado = 0;
    while (total < longitud){
       enviado = send(this->fd, &n, longitud - total, MSG_NOSIGNAL);
       if (enviado == -1)
           throw MiError("Error en el envío del número de 2 bytes\n");
       total += enviado;
    }
}

void Socket::enviar_uint32(uint32_t n, int longitud){
    int total = 0, enviado = 0;
    while (total < longitud){
       enviado = send(this->fd, &n, longitud - total, MSG_NOSIGNAL);
       if (enviado == -1)
           throw MiError("Error en el envío del número de 4 bytes\n");
       total += enviado;
    }
}

int Socket::recibir(char buf[], int longitud){
    int total_rec = 0, recibido = 0;
    while (total_rec < longitud){
       recibido = recv(this->fd, &buf[total_rec], longitud - total_rec, 0);
       if (recibido == -1)
           throw MiError("Error en el la recepción del mensaje\n");
       if (recibido == 0)
           return 0;
       total_rec += recibido;
    }
    return total_rec;
}


int Socket::recibir_uint16(uint16_t &n, int longitud){
    int total_rec = 0, recibido = 0;
    while (total_rec < longitud){
       recibido = recv(this->fd, &n, longitud - total_rec, 0);
       if (recibido == -1)
           throw MiError("Error en el la recepción del número de 2 bytes\n");
       if (recibido == 0)
           return 0;
       total_rec += recibido;
    }
    return total_rec;
}

int Socket::recibir_uint32(uint32_t &n, int longitud){
    int total_rec = 0, recibido = 0;
    while (total_rec < longitud){
       recibido = recv(this->fd, &n, longitud - total_rec, 0);
       if (recibido == -1)
           throw MiError("Error en el la recepción del número de 4 bytes\n");
       if (recibido == 0)
           return 0;
       total_rec += recibido;
    }
    return total_rec;
}

void Socket::setFd(int fd){
    this->fd = fd;
}

void Socket::cerrar(){
    if (this->fd != -1){
        shutdown(this->fd, SHUT_RDWR);
        close(this->fd);
    }
}

Socket::~Socket(){
	cerrar();
}
