void errorHandler(const char *errorMsg) {
    perror(errorMsg);
    exit(EXIT_FAILURE);
};