#include "bfm.h"

void    myMemCpy(void *dest, void *src, size_t n);
void    send_env(int s, struct sockaddr *si_server, pthread_mutex_t *mutex, t_data_env* env);
void    recv_env(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, t_data_env *env);
void    recv_commande(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, int *env);
void    send_commande(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, int* commande);
void*   thread_send_commande (void* arg);
void*   thread_recv_commande (void* arg);
void*   thread_send_env (void* arg);
void*   thread_recv_env (void* arg);
int     create_server(int port, struct sockaddr_in *si_client);

void init(t_simple_env *env) {
#ifdef WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
    struct sockaddr_in si_recv = {0};
    struct sockaddr_in si_send = {0};
    for (int i=1; i < env->data_env->nb_hero; i++)
        env->usable_port[i] = 3000 + i*10;
    env->si_client_send = si_send;
    env->si_client_recv = si_recv;
    env->socket_recv = 0;
    env->socket_send = 0;
    env->commandeClient = 0;
    env->mutexSend = (pthread_mutex_t)  PTHREAD_MUTEX_INITIALIZER;
    env->mutexRecv = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    for (int i=0; i < env->data_env->nb_hero; i++)
    {
        struct sockaddr_in si_recv = {0};
        struct sockaddr_in si_send = {0};
        env->socketinfo[i].mutex_in = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
        env->socketinfo[i].si_client_out = si_recv;
        env->socketinfo[i].si_client_in = si_send;
        env->socketinfo[i].socket_out = 0;
        env->socketinfo[i].socket_in = 0;
    }
}

void end(int s) {
    close(s);
#ifdef WIN32
    WSACleanup();
#endif
}
char *get_ip() {
    char s[256] = {0}, **pp = NULL;
    char *ip;
    struct hostent *host = NULL;

    if(!gethostname(s, 256) && (host = gethostbyname(s)) != NULL)
        for(pp = host->h_addr_list ; *pp != NULL ; pp++)
            ip = inet_ntoa(*(struct in_addr *)*pp);
    close(-1);
    return ip;
}

void	die(char *str) {
    perror(str);
    exit(1);
}

int	    connect_to(char *hostname, int port, struct sockaddr_in	*sin) {
    int sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == 0)
        die("socket");
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = inet_addr(hostname);
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        die("connect");
    return (sock);
}

void    connect_to_Server(char *ip, int port, int* socket, struct sockaddr *sin) {
    *socket = connect_to(ip, port, (struct sockaddr_in *)sin);
}

int     create_server(int port, struct sockaddr_in *sin) {
    int sock= socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1)
        die("sock");
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr *) sin, sizeof(struct sockaddr)) == -1)
        die("bind");
    return (sock);
}

void    myMemCpy(void *dest, void *src, size_t n) {
    // cast src and dest addresses to (char *)
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    // Copy contents of src[] to dest[]
    for (int i=0; i<n; i++)
        cdest[i] = csrc[i];
}

void    create_Server(int port, int* socket, struct sockaddr_in *si_client) {
    *socket = create_server(port, si_client);
}

void*   thread_send_env (void* arg) {
    t_simple_env *env = arg;
    printf("debut thread send \n");
    while (1)
    {
        wait(250);
        for (int i =1; i < env->data_env->nb_hero; i++) {
            env->num_cli = i;
            send_env(env->socket_send, (struct sockaddr *) &(env->socketinfo[i].si_client_out), &(env->mutexSend),
                     env->data_env);
        }
    }
}

void    send_env(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, t_data_env *env) {
    int sizedata = sizeof(t_data_env);
    int sizesock = sizeof(struct sockaddr);
    unsigned char data [sizedata];

    pthread_mutex_lock(mutex);
    myMemCpy(data, env, sizedata);
    pthread_mutex_unlock(mutex);
    sendto(s, data, sizedata, 0, si_client, sizesock);
}

void*   thread_recv_env (void* arg) {
    t_simple_env *env = arg;
    printf("debut thread \n");
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(env->socket_recv, &readfds);
    while (1)
    {
        select(env->socket_recv+1, &readfds, NULL, NULL, NULL);
        if (FD_ISSET(env->socket_recv, &readfds))
            recv_env(env->socket_recv, (struct sockaddr *) &(env->si_client_recv), &(env->mutexRecv), env->data_env);
        else
            printf("Timed out.\n");
    }
}

void    recv_env(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, t_data_env *env) {
    int sizedata = sizeof(t_data_env);
    int sizesock = sizeof(struct sockaddr);
    unsigned char data[sizedata];
    if (recvfrom(s, data, sizedata, 0, si_client, &sizesock) >= 0)
    {
        pthread_mutex_lock(mutex);
        myMemCpy(env, data, sizedata);
        pthread_mutex_unlock(mutex);
    }
}

void*   thread_send_commande (void* arg) {
    t_simple_env *env = arg;
    while (1)
    {
        wait (250);
        send_commande(env->socket_send, (struct sockaddr *) &env->si_client_send, &(env->mutexSend), &(env->commandeClient));
    }
}

void    send_commande(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, int *commande) {
    int sizedata = sizeof(int);
    int sizesocket = sizeof(struct sockaddr);
    unsigned char data [sizedata];

    pthread_mutex_lock(mutex);
    myMemCpy(data, commande, sizedata);
    pthread_mutex_unlock(mutex);
    sendto(s, data, sizedata, 0, si_client, sizesocket);
}

void*   thread_recv_commande (void* arg) {
    t_simple_env *env = arg;
    int num = env->num_cli;
    printf("debut thread recv\n");
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(env->socketinfo[num].socket_in, &readfds);
    while (1)
    {

        select(env->socketinfo[num].socket_in+1, &readfds, NULL, NULL, NULL);
        if (FD_ISSET(env->socketinfo[num].socket_in, &readfds))
        {
            recv_commande(env->socketinfo[num].socket_in,(struct sockaddr *) &(env->socketinfo[num].si_client_in), &(env->socketinfo[num].mutex_in), &(env->commandes[num]));
            printf("received : %d for client number : %d \n", env->commandes[num], num);
        }
        else{
            printf("Timed out.\n");
        }
    }
}

void    recv_commande(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, int *commande) {
    int sizedata = sizeof(int);
    int sizesock = sizeof(struct sockaddr);
    unsigned char data[sizedata];
    if (recvfrom(s, data, sizedata, 0, si_client, &sizesock) >= 0)
    {
        pthread_mutex_lock(mutex);
        myMemCpy(commande, data, sizedata);
        pthread_mutex_unlock(mutex);
    }
}

void    init_connect_to_client(t_simple_env *env) {
    init(env);
    fd_set readfds;
    char buffer[1024];
    int size_si = sizeof(env->si_client_send);
    int hero_num = 0;
    int fin = 0;
    int clef = CLEF;
    int size = sizeof(int);
    unsigned char data [size];
    unsigned char clefChar [size];
    myMemCpy(clefChar, &(clef), size);
    create_Server(PORT_SERV_SEND, &(env->socket_send), &(env->si_client_send));
    for(int nb_cli = 1; nb_cli < env->data_env->nb_hero; nb_cli++)
    {
        myMemCpy(data, &(env->usable_port[nb_cli]), size);
        printf("waiting on 4343 :\n");
        while (!fin) {
            int nb_octet = recvfrom(env->socket_send, buffer, sizeof buffer - 1, 0,
                                    (struct sockaddr *) &(env->socketinfo[nb_cli].si_client_out),
                                    &size_si);
            if (nb_octet > 0) {
                fin = 1;
                sendto(env->socket_send, clefChar, size, 0,(struct sockaddr *) &(env->socketinfo[nb_cli].si_client_out), size_si);
                sendto(env->socket_send, data, size, 0,(struct sockaddr *) &(env->socketinfo[nb_cli].si_client_out), size_si);
            }
        }
        fin = 0;
        printf("create server :\n");
        create_Server(env->usable_port[nb_cli], &(env->socketinfo[nb_cli].socket_in), &(env->socketinfo[nb_cli].si_client_in));
        printf("wait receving :\n");
        FD_ZERO(&readfds);
        FD_SET(env->socketinfo[nb_cli].socket_in, &readfds);
        select(env->socketinfo[nb_cli].socket_in + 1, &readfds, NULL, NULL, NULL);
        if (FD_ISSET(env->socketinfo[nb_cli].socket_in, &readfds)) {
            int nb_octet = recvfrom(env->socketinfo[nb_cli].socket_in, data, size, 0,
                                    (struct sockaddr *) &(env->socketinfo[nb_cli].si_client_in), &size_si);
            if (nb_octet < 0) {
                die("send_send()");
            } else{
                printf("Received\n");
            }
        }
    }
    printf("start send nb_heroes\n");
    for(int i = 1; i < env->data_env->nb_hero; i++)
    {
        hero_num = i;
        printf("send Final\n");
        myMemCpy(data, &(env->data_env->nb_hero), size);
        sendto(env->socket_send, data, size, 0,(struct sockaddr *) &(env->socketinfo[i].si_client_out), size_si);
        wait(200);
        myMemCpy(data, &(hero_num), size);
        printf("send num_hero\n");
        sendto(env->socket_send, data, size, 0,(struct sockaddr *) &(env->socketinfo[i].si_client_out), size_si);
    }
}

void    start_server(t_simple_env *env) {

    printf("start SERVER\n");
    pthread_create(&(env->thread_send), NULL, thread_send_env, (void *) env);
    for (int i = 1; i < env->data_env->nb_hero; i++){
        printf("start Recv Commande \n");
        env->num_cli = i;
        pthread_create(&(env->socketinfo[i].thread_recv), NULL, thread_recv_commande, (void *) env);
        wait(25);
    }
}

void    init_connect_to_server(t_simple_env *env, char ip[]) {
    init(env);
    int size_si = sizeof(env->si_client_send);
    int nb_octet=0;
    fd_set readfds;
    printf("ecoute de la socket 4343 :\n");
    connect_to_Server(ip, PORT_SERV_SEND, &(env->socket_recv), (struct sockaddr *) &(env->si_client_recv));
    sendto(env->socket_recv, "salut", strlen("salut"), 0,(struct sockaddr *) &(env->si_client_recv), size_si);
    int port = 0;
    int clef=0;
    int size = sizeof(int);
    unsigned char data [size];
    FD_ZERO(&readfds);
    FD_SET(env->socket_recv, &readfds);
    int test = 1;
    while (test){
        select(env->socket_recv+1, &readfds, NULL, NULL, NULL);
        if (FD_ISSET(env->socket_recv, &readfds)) {
            recvfrom(env->socket_recv, data, size, 0,
                     (struct sockaddr *) &(env->si_client_recv),
                     &size_si);
            myMemCpy(&clef, data, size);
            if (clef == CLEF)
            {
                select(env->socket_recv+1, &readfds, NULL, NULL, NULL);
                if (FD_ISSET(env->socket_recv, &readfds)) {
                    recvfrom(env->socket_recv, data, size, 0,
                             (struct sockaddr *) &(env->si_client_recv),
                             &size_si);
                    myMemCpy(&port, data, size);
                    test=0;
                }
            }
        }
    }
    printf("port :: %d", port);
    printf("ecoute de la socket 4444 :\n");
    connect_to_Server(ip, port, &(env->socket_send), (struct sockaddr *) &(env->si_client_send));
    wait(1000);
    sendto(env->socket_send, data, size, 0,(struct sockaddr *) &(env->si_client_send), size_si);
    if (nb_octet < 0) {
        die("send_send()");
    }
    FD_ZERO(&readfds);
    FD_SET(env->socket_recv, &readfds);
    select(env->socket_recv+1, &readfds, NULL, NULL, NULL);
    if (FD_ISSET(env->socket_recv, &readfds)) {
        recvfrom(env->socket_recv, data, size, 0,
                 (struct sockaddr *) &(env->si_client_recv),
                 &size_si);
        myMemCpy(&(env->data_env->nb_hero), data, size);
    }
    wait(20);
    FD_ZERO(&readfds);
    FD_SET(env->socket_recv, &readfds);
    select(env->socket_recv+1, &readfds, NULL, NULL, NULL);
    if (FD_ISSET(env->socket_recv, &readfds)) {
        recvfrom(env->socket_recv, data, size, 0,
                 (struct sockaddr *) &(env->si_client_recv),
                 &size_si);
        myMemCpy(&(env->data_env->num_hero), data, size);
    }
}

void start_client(t_simple_env *env)
{
    pthread_create(&(env->thread_recv), NULL, thread_recv_env, (void *) env);
    pthread_create(&(env->thread_send), NULL, thread_send_commande, (void *) env);
    wait(200);
}


