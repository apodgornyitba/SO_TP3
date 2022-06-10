#include <challenges.h>

#define BACKLOG 10
#define BUFFER_SIZE 100

//https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
//https://www.geeksforgeeks.org/socket-programming-cc/

void errorHandler(const char *errorMsg) {
    perror(errorMsg);
    exit(EXIT_FAILURE);
}

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
