using System;
using System.Net.Sockets;
using System.Text;

string servidor = "127.0.0.1"; // Dirección IP del servidor
int puerto = 8080; // Puerto del servidor

try
{
    using (TcpClient cliente = new TcpClient(servidor, puerto))
    using (NetworkStream flujoDeRed = cliente.GetStream())
    {
        Console.WriteLine("Conectado al servidor.");

        // Opción: 1 para nombre de usuario, 2 para contraseña
        Console.Write("Ingrese la opción (1 para nombre de usuario, 2 para contraseña): ");
        string opcion = Console.ReadLine();

        // Longitud del nombre de usuario o contraseña
        Console.Write("Ingrese la longitud deseada: ");
        string longitud = Console.ReadLine();

        // Enviar opción y longitud al servidor
        string mensaje = opcion + longitud;
        byte[] datosParaEnviar = Encoding.ASCII.GetBytes(mensaje);
        flujoDeRed.Write(datosParaEnviar, 0, datosParaEnviar.Length);

        // Leer respuesta del servidor
        byte[] datosParaLeer = new byte[1024];
        int bytesLeidos = flujoDeRed.Read(datosParaLeer, 0, datosParaLeer.Length);
        string respuesta = Encoding.ASCII.GetString(datosParaLeer, 0, bytesLeidos);

        Console.WriteLine("Respuesta del servidor: " + respuesta);
    }
}
catch (SocketException e)
{
    Console.WriteLine("Error de conexión: " + e.Message);
}
