#include <string>
#include <cstdint>

typedef struct addrinfo list;

class Socket{
	private:
		int fd;

		list *getAddrList(const char *hostname, const char *port, const int flag);
		void setFd(int fd);

	public:
		Socket();
		//dejo el nombre en inglés porque no conozco la traducción exacta
		int bindListen(const char *hostname, const char *port);
		int conectar(const char *hostname, const char *port);
		Socket* aceptar();
		int enviar(std::string mensaje, int longitud);
		int recibir(char buf[], int longitud);
		int enviar_uint16(uint16_t n, int longitud);
		int enviar_uint32(uint32_t n, int longitud);
		int recibir_uint16(uint16_t &n, int longitud);
		int recibir_uint32(uint32_t &n, int longitud);
		void cerrar();
		~Socket();
};