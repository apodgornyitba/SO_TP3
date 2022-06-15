# Sistemas Operativos - TP3: Sockets
## Autores
    ● 60299 - Juan Pablo Arias
    ● 60570 - Andrés Podgorny
    ● 61278 - Sol Victoria Anselmo
    
## Entorno de desarrollo y ejecución
Es un requisito clonar este repositorio
          
## Instrucciones de Compilación
Ubicado dentro del directorio donde se descargaron los archivos, ejecutar el siguiente comando en una terminal:

    $ make all
    
Esto generará todos los archivos ejecutables necesarios.
## Instrucciones de Ejecución
Para iniciar el servidor, ejecute:

    $ ./ourServer
 
Para iniciar el cliente, ejecute:

    $ ./client
    
Como alernativa, si se desea saltear o acceder directamente a un challenge especifico, ejecute el comando anterior con un unico argumento (numero entero entre 1 y 12)
 de la siguiente manera:

    $ ./client <NUMERO>


## Instrucciones de Limpieza
Ubicado dentro del directorio donde se descargaron los archivos, para borrar todos los archivos ejecutables generados, ejecutar el comando:
    
    $ make clean
    
## Problemas
Encontramos un error en el challenge 10 durante la ejecucion del server con el cliente que no supimos resolver. Cuando se le pasa un archivo quine.c valido, el server
devuelve que se encontro diferencias aunque no haya ninguna.  Observando el codigo no logramos encontrar el error, creemos que se produce en la linea 36 del archivo
"challenges.c" (donde se realiza un int valid = system("./quine | diff - quine.c")). Este system devuelve un 256, que significaria que el proceso creado retorno
con un exit(1).

