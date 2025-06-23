✅ ¿QUÉ HACE ESTE PROGRAMA?
Este programa permite gestionar reclamos de vecinos desde la consola de Windows. Se pueden:

Agregar reclamos (nombre, dirección, tipo, fecha).

Cambiar el estado del reclamo (pendiente, en proceso, resuelto).

Buscar reclamos por nombre, tipo o estado.

Mostrar todos los reclamos ordenados por fecha.

Guardar y leer los reclamos desde un archivo .txt.



🚀 INSTRUCCIONES PASO A PASO PARA USARLO



🟡 PASO 1 – Crear la carpeta y copiar el archivo


Abrí el Explorador de Archivos de Windows.

Entrá al Disco Local C (C:).

Creá una carpeta llamada exactamente: TP_Reclamos

Copiá y pegá dentro de esa carpeta el archivo con el código:
Tp_gestion_reclamos_vecinales_G8.c


🟡 PASO 2 – Compilar el programa desde CMD o PowerShell


Abrí CMD o PowerShell:

Presioná Win + R, escribí cmd y enter.

O hacé clic derecho en la carpeta TP_Reclamos y seleccioná “Abrir en PowerShell aquí”.

Escribí este comando para entrar a la carpeta (si no lo hiciste desde ahí):   cd C:\TP_Reclamos

Escribí este comando para compilar el código:   gcc Tp_gestion_reclamos_vecinales_G8.c -o reclamos.exe

Si no aparece ningún error, ahora ejecutá el programa con:   .\reclamos.exe


Ya podés empezar a cargar y gestionar reclamos desde la consola.


👥 INTEGRANTES DEL GRUPO

Lautaro Fernández 

Roles:

Agregar reclamos (agregarReclamo)
Mostrar reclamos (mostrarReclamos)
Buscar reclamos (buscarReclamo)
Cambiar estado de un reclamo (cambiarEstado)
Funciones auxiliares de entrada/salida: aMinusculas, liberarLista


Bautista Zorrilla

Roles:

Cargar y guardar en archivo (cargarDesdeArchivo, guardarEnArchivo)
Ordenar por fecha (ordenarPorFecha)
Estructuras y definición de main()
Diseño y manejo de estructuras (Reclamo, Nodo) y constantes
Estructura general del menú (menuPrincipal)