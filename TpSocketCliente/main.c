#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define PUERTO 8080
#define TAMANIO_BUFFER 1024

int main() {
    WSADATA wsa;
    SOCKET socket_cliente;
    struct sockaddr_in direccion_servidor;
    char buffer[TAMANIO_BUFFER] = {0};
    char mensaje[TAMANIO_BUFFER] = {0};

    // Inicializar Winsock
    printf("Inicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error: Fallo en la inicialización de Winsock. Código de error: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Winsock inicializado correctamente.\n");

    // Crear el socket del cliente
    printf("Creando el socket del cliente...\n");
    if ((socket_cliente = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Error: Fallo en la creación del socket. Codigo de error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket del cliente creado correctamente.\n");

    direccion_servidor.sin_family = AF_INET;
    direccion_servidor.sin_port = htons(PUERTO);

    // Convertir la dirección IP a formato binario
    printf("Convirtiendo la direccion IP...\n");
    if (inet_pton(AF_INET, "127.0.0.1", &direccion_servidor.sin_addr) <= 0) {
        printf("Error: Direccion invalida\n");
        closesocket(socket_cliente);
        WSACleanup();
        return 1;
    }
    printf("Direccion IP convertida correctamente.\n");

    // Conectar al servidor
    printf("Conectando al servidor...\n");
    if (connect(socket_cliente, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) {
        printf("Error: Conexion fallida. Codigo de error: %d\n", WSAGetLastError());
        closesocket(socket_cliente);
        WSACleanup();
        return 1;
    }
    printf("Conexion al servidor exitosa.\n");

    int opcion, longitud;

    printf("Menu principal:\n");
    printf("1. Generar nombre de usuario\n");
    printf("2. Generar contraseña\n");
    printf("Elige una opcion: ");
    scanf("%d", &opcion);

    printf("Introduce la longitud: ");
    scanf("%d", &longitud);

    snprintf(mensaje, sizeof(mensaje), "%d%d", opcion, longitud);

    // Enviar la solicitud al servidor
    printf("Enviando solicitud al servidor...\n");
    if (send(socket_cliente, mensaje, strlen(mensaje), 0) < 0) {
        printf("Error al enviar la solicitud.\n");
        closesocket(socket_cliente);
        WSACleanup();
        return 1;
    }
    printf("Solicitud enviada correctamente.\n");

    // Recibir la respuesta del servidor
    printf("Esperando respuesta del servidor...\n");
    int bytes_recibidos = recv(socket_cliente, buffer, TAMANIO_BUFFER, 0);
    if (bytes_recibidos > 0) {
        buffer[bytes_recibidos] = '\0';  //La cadena debe estar terminada
        printf("Respuesta del servidor: %s\n", buffer);
    } else {
        printf("Error al recibir la respuesta o no se recibió nada.\n");
    }

    closesocket(socket_cliente);
    WSACleanup();
    return 0;
}
