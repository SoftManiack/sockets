#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 100

int main(void){
    int sock;
    struct sockaddr_in addr;
    char message[MAX];
    char buf[sizeof(message)];
    
    /*
        SOCK_STREAM - Передача потока данных с предварительной установкой соединения. Обеспечивается надёжный канал передачи данных, 
            при котором фрагменты отправленного блока не теряются, не переупорядочиваются и не дублируются. 
            Поскольку этот тип сокетов является самым распространённым, до конца раздела мы будем говорить только о нём. 
            Остальным типам будут посвящены отдельные разделы.
        SOCK_DGRAM - Передача данных в виде отдельных сообщений (датаграмм). Предварительная установка соединения не требуется. 
            Обмен данными происходит быстрее, но является ненадёжным: сообщения могут теряться в пути, дублироваться и переупорядочиваться. 
            Допускается передача сообщения нескольким получателям (multicasting) и широковещательная передача (broadcasting).
        SOCK_RAW - Этот тип присваивается низкоуровневым (т. н. "сырым") сокетам. Их отличие от обычных сокетов состоит в том,
            что с их помощью программа может взять на себя формирование некоторых заголовков, добавляемых к сообщению.
    */

    /* 
        При задании AF_UNIX для передачи данных используется файловая система ввода/вывода Unix. 
        AF_INET соответствует Internet-домену. Сокеты, размещённые в этом домене, могут использоваться для работы в любой IP-сети.
    */

    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    printf("%d", sock);

    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    printf("Enter text: ");

    fgets(message, MAX, stdin);

    send(sock, message, sizeof(message), 0);
    recv(sock, message, sizeof(message), 0);

    printf("buf: %s \n", buf);
    close(sock);

    return 0;
}