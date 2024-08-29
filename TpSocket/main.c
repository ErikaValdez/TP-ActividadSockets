#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <time.h>

#pragma comment(lib, "Ws2_32.lib")

#define PUERTO 8080
#define TAMANIO_BUFFER 1024

char obtener_vocal_aleatoria() {
    char vocales[] = "aeiou";
    return vocales[rand() % 5];
}

char obtener_consonante_aleatoria() {
    char consonantes[] = "bcdfghjklmnpqrstvwxyz";
    return consonantes[rand() % 21];
}

void generar_nombre_usuario(int longitud, char *nombre_usuario) {
    if (longitud < 5 || longitud > 15) {
        strcpy(nombre_usuario, "Error: Longitud de usuario inválida.");
        return;
    }

    int empezar_con_vocal = rand() % 2;
    for (int i = 0; i < longitud; i++) {
        if (empezar_con_vocal) {
            nombre_usuario[i] = (i % 2 == 0) ? obtener_vocal_aleatoria() : obtener_consonante_aleatoria();
        } else {
            nombre_usuario[i] = (i % 2 == 0) ? obtener_consonante_aleatoria() : obtener_vocal_aleatoria();
        }
    }
    nombre_usuario[longitud] = '\0';
}

void generar_contrasena(int longitud, char *contrasena) {
    if (longitud < 8 || longitud > 50) {
        strcpy(contrasena, "Error: Longitud de contraseña inválida.");
        return;
    }

    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < longitud; i++) {
        contrasena[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    contrasena[longitud] = '\0';
}

int main() {
    WSADATA wsa;
    SOCKET servidor_fd, nuevo_socket;
    struct sockaddr_in direccion;
    int tam_direccion = sizeof(direccion);
    char buffer[TAMANIO_BUFFER] = {0};

    srand(time(0));

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error: Fallo en la inicialización de Winsock. Código de error: %d\n", WSAGetLastError());
        return 1;
    }

    // Crear el socket del servidor
    if ((servidor_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Fallo en la creación del socket. Código de error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PUERTO);

    // Vincular el socket con el puerto
    if (bind(servidor_fd, (struct sockaddr *)&direccion, sizeof(direccion)) == SOCKET_ERROR) {
        printf("Falló la vinculación. Codigo de error: %d\n", WSAGetLastError());
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    // Escuchar conexiones entrantes
    if (listen(servidor_fd, 3) == SOCKET_ERROR) {
        printf("Falló la escucha. Codigo de error: %d\n", WSAGetLastError());
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    printf("Servidor escuchando en el puerto %d...\n", PUERTO);

    while (1) {
        if ((nuevo_socket = accept(servidor_fd, (struct sockaddr *)&direccion, &tam_direccion)) == INVALID_SOCKET) {
            printf("Falló la aceptacion. Codigo de error: %d\n", WSAGetLastError());
            continue;
        }

        recv(nuevo_socket, buffer, TAMANIO_BUFFER, 0);

        printf("Buffer recibido: %s\n", buffer); // Para ver el mensaje completo recibido

        int opcion = buffer[0] - '0';
        int longitud = atoi(buffer + 1);

        printf("Opcion recibida: %d\n", opcion);
        printf("Longitud recibida: %d\n", longitud);

        char respuesta[TAMANIO_BUFFER] = {0};

        if (opcion == 1) { // Generador de nombres de usuario
            generar_nombre_usuario(longitud, respuesta);
        } else if (opcion == 2) { // Generador de contraseñas
            generar_contrasena(longitud, respuesta);
        } else {
            strcpy(respuesta, "Error: Opción inválida.");
        }

        send(nuevo_socket, respuesta, strlen(respuesta), 0);
        closesocket(nuevo_socket);
    }

    closesocket(servidor_fd);
    WSACleanup();
    return 0;
}
