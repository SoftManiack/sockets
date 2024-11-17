#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define MAX 100

int main(void){
    char message[MAX];
    printf("Enter text: ");

    fgets(message, MAX, stdin);
    printf("Message: %s\n", message);

    return 0;
}