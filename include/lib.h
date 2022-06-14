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
#define BACKLOG 10
#define BUFFER_SIZE 100
#define MAX_BUFFER 1024

//ERROR HANDLER
void errorHandler(const char *errorMsg);

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

#endif