#ifndef CHALLENGES_H
#define CHALLENGES_H

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define ERROR_CODE -1
#define VALID 0
#define MY_ADDR "0.0.0.0"
#define MY_PORT 8080
#define STDERR 2

#define CHALLENGE_HEADER "----- DESAFIO ----------"
#define EXTRA_QUESTION_HEADER "----- PREGUNTA PARA INVESTIGAR --------------"
#define CONGRATS "Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto"
#define MAX_LEVELS 12
#define GENERIC_CHALLENGE NULL

typedef struct Challenge {
    char * hint;
    char * ans;
    char * question;
    void (*func)(void);
} Challenge;

//FUNCIONES DE CHALLENGES
void Challenge4();
void Challenge7();
void Challenge8();
void Challenge10();
void Challenge11();
void Challenge12();

static Challenge challenges[] = {
    {
        "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\nDeberán estar atentos a los easter eggs.\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra \'entendido\\n\'\n\n\n",
        "entendido\n",
        "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?\n\n",
        GENERIC_CHALLENGE
    },
    {
        "The Wire S1E5\n5295 888 6288\n\n\n",
        "itba\n",
        "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n\n",
        GENERIC_CHALLENGE
    },
    {
        "https://ibb.co/tc0Hb6w\n\n\n",
        "M4GFKZ289aku\n",
        "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?\n\n",
        GENERIC_CHALLENGE
    },
    {
        "EBADF... \n\n\n",
        "fk3wfLCm3QvS\n",
        "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?\n\n",
        Challenge4
    },
    {
        "respuesta = strings: INSERTAR NUMERO DE LINEA \n\n\n", /*FIX: CUANDO NOSOTROS HACEMOS UN STRINGS EN QUE LINEA APARECE*/
        "too_easy\n",
        "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n\n",
        GENERIC_CHALLENGE
    },
    {
        "INSERTAR SECCIONES DEL DISSASEMBLY ? INSERTAR SECCIONES DEL DISSASEMBLY\n\n\n", /*FIX: CUANDO NOSOTROS HACEMOS UN -D VER LAS SECCIONES QUE APARECEN*/ 
        ".RUN_ME\n",
        "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?\n\n",
        GENERIC_CHALLENGE
    },
    {
        "Filter error\n\n\n",
        "K5n2UFfpFMUN\n",
        "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n\n",
        Challenge7
    },
    {
        "¿?\n\n\n",
        "BUmyYq5XxXGt\n",
        "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n\n",
        Challenge8
    },
    {
        "Latexme\n\nSi\n \\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\nentonces\ny = \n\n\n",
        "u^v\n",
        "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n\n",
        GENERIC_CHALLENGE
    },
    {
        "quine\n\n\n",
        "chin_chu_lan_cha\n",
        "¿Cuáles son las características del protocolo SCTP?\n\n",
        Challenge10
    },
    {
        "b gdbme y encontrá el valor mágico\n\n\n",
        "gdb_rules\n",
        "¿Qué es un RFC?\n\n",
        Challenge11
    },
    {
        "Me conoces\n\n\n",
        "normal\n",
        "¿Fue divertido?\n\n",
        Challenge12
    }

};

static char *answers[] = {
    "entendido\n",
    "itba\n",
    "M4GFKZ289aku\n",
    "fk3wfLCm3QvS\n",
    "too_easy\n",
    ".RUN_ME\n",
    "K5n2UFfpFMUN\n",
    "BUmyYq5XxXGt\n",
    "u^v\n",
    "chin_chu_lan_cha\n",
    "gdb_rules\n",
    "normal\n",
    NULL
};

#endif