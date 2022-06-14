#include <lib.h>

__attribute__((section(".RUN_ME")))

//https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
//https://www.geeksforgeeks.org/socket-programming-cc/

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
        "respuesta = strings: 73 \n\n\n", /*FIX: CUANDO NOSOTROS HACEMOS UN STRINGS EN QUE LINEA APARECE*/
        "too_easy\n",
        "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n\n",
        GENERIC_CHALLENGE
    },
    {
        ".got.plt .data ? .bss .comment \n\n\n", /*FIX: CUANDO NOSOTROS HACEMOS UN -D VER LAS SECCIONES QUE APARECEN*/ 
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

static void buildSocket(int * serverFd, int * optValue, int * clientFd, struct sockaddr_in * address, socklen_t addressLength) {

    if ((*serverFd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR_CODE) {

        errorHandler("Error creating socket");
    }
    
    if(setsockopt(*serverFd, SOL_SOCKET, SO_REUSEADDR, optValue, sizeof(*optValue)) == ERROR_CODE) {
        errorHandler("Error setting socket opt");
    }
    
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(MY_PORT);

    if(bind(*serverFd, (struct sockaddr *) address, addressLength) == ERROR_CODE) {
        errorHandler("Error binding socket");
    }

    if(listen(*serverFd,BACKLOG) == ERROR_CODE) {
        errorHandler("Error listening socket");
    }

    if((*clientFd = accept(*serverFd, (struct sockaddr *) address, &addressLength)) == ERROR_CODE) {
        errorHandler("Error accepting socket");
    }

    return;
}

static void startGame(int socketFd) {
    unsigned int currentLevel = 0;
    
    size_t bufferSize = BUFFER_SIZE;
    char * buffer = malloc(sizeof(char) * bufferSize);
    if(buffer == NULL) {
        errorHandler("Error allocating memory");
    }

    FILE * socketFile;
    if( (socketFile = fdopen(socketFd, "r")) == NULL) {
        errorHandler("Error opening socket file");
    }

    while(currentLevel < MAX_LEVELS) {
        printf("\033[1;1H\033[2J");

        printf("%s\n", CHALLENGE_HEADER);
        printf("%s\n", challenges[currentLevel].hint);
        if(challenges[currentLevel].func != GENERIC_CHALLENGE) {
            challenges[currentLevel].func();
        }
        printf("%s\n", EXTRA_QUESTION_HEADER);
        printf("%s\n", challenges[currentLevel].question);

        if(getline(&buffer,&bufferSize,socketFile) == ERROR_CODE) {
            errorHandler("Error reading stream");
            return;
        }

        if(strcmp(challenges[currentLevel].ans, buffer) == 0) {
            currentLevel += 1;
        }
        else {
            printf("Respuesta incorrecta! Intenta de nuevo\n");
            sleep(2);
            currentLevel += 0;
        }
    }

    printf("\033[1;1H\033[2J");
    printf("%s\n\n", CONGRATS);
    fclose(socketFile);
    free(buffer);
}

int main () {

    struct sockaddr_in serverAddress;
    socklen_t addressLength = sizeof(serverAddress);
    int serverSocketFd, clientSocketFd;
    int optValue = 1;
    
    buildSocket(&serverSocketFd, &optValue, &clientSocketFd, &serverAddress, addressLength);

    startGame(clientSocketFd);

    if(close(serverSocketFd) == ERROR_CODE) {
        errorHandler("Error closing socket");
    }

    return 0;
}
