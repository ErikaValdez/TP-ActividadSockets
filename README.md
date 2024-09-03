# TP-ActividadSockets
DESARROLLO DE SOFTWARE EN SISTEMAS DISTRIBUIDOS

# Generador de Nombres de Usuario y Contraseñas

Este proyecto incluye un servidor que genera nombres de usuario y contraseñas según las solicitudes de los clientes. Incluye clientes desarrollados en C y C# .NET que interactúan con el servidor para obtener estos datos generados.

## Getting Started

Estas instrucciones te permitirán obtener una copia del proyecto en tu máquina local para desarrollo y pruebas.

### Prerequisites

- Compilador C (como GCC)
- Visual Studio (para el cliente en C# .NET)
- Winsock2 (para la funcionalidad de red en C)
- Codeblocks

### Installing

1. Clonar el repositorio:
   
   git clone https://github.com/tuusuario/proyecto.git](https://github.com/ErikaValdez/TP-ActividadSockets.git)
   
2. Compilar el Servidor
   
   gcc servidor.c -o servidor -lws2_32
   
3. Configurar Visual Studio para el cliente en C# .NET.

### Running the Tests
Actualmente, no se tienen pruebas automatizadas. Sin embargo, se puede probar manualmente el sistema iniciando el servidor y conectando los clientes para verificar su funcionalidad.
![Prueba C#](https://github.com/ErikaValdez/TP-ActividadSockets/blob/main/Screen%20de%20pruebas%20realizadas/Cliente%20C%23%20-%20NombreUsuario%20correcto.png)"Cliente-Servidor C)
![Prueba C](https://github.com/ErikaValdez/TP-ActividadSockets/blob/main/Screen%20de%20pruebas%20realizadas/Cliente-C-%20NombreUsuario%20correcto.png)"Cliente C#")



### Deployment
Para desplegar el servidor en un entorno en vivo, asegúrate de que el puerto 8080 esté disponible y que Winsock2 esté correctamente configurado en el sistema.

### Built With
C - Para el servidor y cliente.
.NET - Para el cliente en C#.
Winsock2 - Para la funcionalidad de red.

### Authors
Erika Valdez- Desarrollador Principal

### License
Este proyecto está licenciado bajo la Licencia MIT - ver el archivo LICENSE.md para más detalles.

