#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <cstdint>
#include <string>
#include <vector>

//creado para poder cumplir con la restricción 
//de 80 caracteres por línea
typedef struct addrinfo list;

class Socket{
	private:
		int fd;

		list *getAddrList(const char *hostname, const char *port, int flag);
		void setFd(int fd);

	public:
		//inicializa el socket con un file descriptor "simbólico" 
		//con valor -1
		Socket();

		//constructor y operador de asignación por movimiento
		Socket(Socket&& other);
		Socket& operator=(Socket&& other);

		//trata de atar al socket para que pueda escuchar conexiones
		//si lo logra, asigna el file descriptor al del socket,
		//reemplazando al anterior
		//si puede atarlo, lo deja escuchando conexiones entrantes
		//si alguna de las dos operaciones falla, lanza una excepción
		void bindListen(const char *hostname, const char *port);

		//trata de conectar al socket al servidor
		//si lo logra, asigna el file descriptor al del socket,
		//reemplazando al anterior
		//si no lo logra, lanza una excepción
		void conectar(const char *hostname, const char *port);

		//trata de aceptar la conexión entrante
		//si lo logra, asigna el file descriptor al peer socket usado
		//para la comunicación y lo devuelve por movimiento
		//si falla la función "accept" lanza una excepción
		Socket aceptar();

		//envía el mensaje recibido a través de la red
		//lanza una excepción en caso de que haya un
		//error en el envío
		void enviar(std::string mensaje, int longitud);

		//recibe el mensaje enviado a través de la red
		//en el buffer provisto
		//devuelve la cantidad de bytes leídos si la recepción fue exitosa
		//o si la otra parte se desconectó
		//lanza una excepción si hubo un fallo en la recepción
		int recibir(std::vector<char> &buf, int longitud);

		//envía el número de 2 bytes recibido a través de la red
		//lanza una excepción en caso de que haya un
		//error en el envío
		void enviar_uint16(uint16_t n, int longitud);

		//envía el número de 4 bytes recibido a través de la red
		//lanza una excepción en caso de que haya un
		//error en el envío
		void enviar_uint32(uint32_t n, int longitud);

		//recibe el número de 2 bytes enviado a través de la red
		//devuelve la cantidad de bytes leídos si la recepción fue exitosa
		//o si la otra parte se desconectó
		//lanza una excepción si hubo un fallo en la recepción
		int recibir_uint16(uint16_t &n, int longitud);

		//recibe el número de 4 bytes enviado a través de la red
		//devuelve la cantidad de bytes leídos si la recepción fue exitosa
		//o si la otra parte se desconectó
		//lanza una excepción si hubo un fallo en la recepción
		int recibir_uint32(uint32_t &n, int longitud);
		void cerrar();
		~Socket();
};

#endif
