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

void init(t_simple_env *env)
{
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
    env->si_client_send = si_send;
    env->si_client_recv = si_recv;
    env->socket_recv = 0;
    env->socket_send = 0;
    env->commande = 0;
    env->mutexSend = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    env->mutexRecv = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
}

void end(int s)
{
    close(s);
#ifdef WIN32
    WSACleanup();
#endif
}
char *get_ip()
{
    char s[256] = {0}, **pp = NULL;
    char *ip;
    struct hostent *host = NULL;

    if(!gethostname(s, 256) && (host = gethostbyname(s)) != NULL)
        for(pp = host->h_addr_list ; *pp != NULL ; pp++)
            ip = inet_ntoa(*(struct in_addr *)*pp);
    close(-1);
    return ip;
}
int     create_server(int port, struct sockaddr_in *si_client);

void	die(char *str)
{
    perror(str);
    exit(1);
}

int     sendServeurPort(int port, int portPlayable, int* socket);


void    send_port_to_player(int s, int port)
{
    int size = sizeof(int);
    unsigned char data [size];
    myMemCpy(data, &port, size);
    if (send(s, data, size, 0) < 0)
        die("send");
}
/*
int     sendServeurPort(int port, int portPlayable, int* socket)
{
    init();
    *socket = accept_client(create_server(port));
    send_port_to_player(*socket, portPlayable);
    end(*socket);
}*/


/*
 * trust me im a  an ingeneer
 */

int	    connect_to(char *hostname, int port, struct sockaddr_in	*sin)
{
    int sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1)
        die("socket");
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = inet_addr(hostname);
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        die("connect");
    return (sock);
}
void    connect_to_Server(char *ip, int port, int* socket, struct sockaddr *sin)
{
    *socket = connect_to(ip, port, (struct sockaddr_in *)sin);
}

void    wait (int ms)
{
    pthread_mutex_t fakeMutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t fakeCond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    struct timespec timeToWait;
    struct timeval now;
    gettimeofday(&now,NULL);
    timeToWait.tv_sec = now.tv_sec;
    timeToWait.tv_nsec = (now.tv_usec+1000UL*ms)*1000UL;
    pthread_mutex_lock(&fakeMutex);
    pthread_cond_timedwait(&fakeCond, &fakeMutex, &timeToWait);
    pthread_mutex_unlock(&fakeMutex);
}

int     create_server(int port, struct sockaddr_in *sin)
{
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

void    myMemCpy(void *dest, void *src, size_t n)
{
    // cast src and dest addresses to (char *)
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    // Copy contents of src[] to dest[]
    for (int i=0; i<n; i++)
        cdest[i] = csrc[i];
}
void    create_Server(int port, int* socket, struct sockaddr_in *si_client)
{
    *socket = create_server(port, si_client);
}

void*   thread_send_env (void* arg) {
    t_simple_env *env = arg;
    printf("début thread send \n");
    while (1)
    {
        wait (250);
        send_env(env->socket_send, (struct sockaddr *) &env->si_client_send, &(env->mutexSend), env->data_env);
    }
}

void    send_env(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, t_data_env *env)
{
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
    printf("début thread \n");
    struct timeval tv;
    fd_set readfds;
    struct timespec timeToWait;
    int retval;
    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(env->socket_recv, &readfds);
        timeToWait.tv_sec = 5;
        timeToWait.tv_nsec = 50;
        retval = select(env->socket_recv+1, &readfds, NULL, NULL, &tv);
        if (retval == -1)
            printf("ERROR SELECT.\n");
        else if (env->socket_recv, &readfds)
            recv_env(env->socket_recv, (struct sockaddr *) &(env->si_client_recv), &(env->mutexRecv), env->data_env);
        else
            printf("Timed out.\n");
    }
}

void    recv_env(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, t_data_env *env)
{
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
        send_commande(env->socket_send, (struct sockaddr *) &env->si_client_send, &(env->mutexSend), &(env->commande));
    }
}

void    send_commande(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, int *commande)
{
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
    printf("début thread recv\n");
    struct timeval tv;
    fd_set readfds;
    struct timespec timeToWait;
    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(env->socket_recv, &readfds);
        timeToWait.tv_sec = 5;
        timeToWait.tv_nsec = 0;
        select(env->socket_recv+1, &readfds, NULL, NULL, &tv);
        if (FD_ISSET(env->socket_recv, &readfds))
            recv_commande(env->socket_recv,(struct sockaddr *) &(env->si_client_recv), &(env->mutexRecv), &(env->commande));
        else
            printf("Timed out.\n");
    }
}

void    recv_commande(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, int *commande)
{
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

void init_connect_to_client(t_simple_env *env)
{
    char buffer[1024];
    int size_si = sizeof(env->si_client_send);
    printf("creation du server :\n");
    create_Server(PORT_SERV_SEND, &(env->socket_send), &(env->si_client_send));
    int fin = 0;

    printf("waiting on 4343 :\n");
    while (!fin) {
        int nb_octet = recvfrom(env->socket_send, buffer, sizeof buffer - 1, 0,
                                (struct sockaddr *) &(env->si_client_send),
                                &size_si);
        if (nb_octet > 0) {
            fin = 1;
        }
    }
    create_Server(PORT_SERV_RECV, &(env->socket_recv), &(env->si_client_recv));
    fin = 0;
    printf("waiting on 4444 :\n");
    while (!fin) {
        int nb_octet = recvfrom(env->socket_recv, buffer, sizeof buffer - 1, 0,
                                (struct sockaddr *) &(env->si_client_recv),
                                &size_si);
        if (nb_octet > 0) {
            fin = 1;
        }
    }
}



void start_server(t_simple_env *env)
{
    pthread_create(&(env->thread_send), NULL, thread_send_env, (void *) env);
    pthread_create(&(env->thread_recv), NULL, thread_recv_commande, (void *) env);
}

void init_connect_to_server(t_simple_env *env, char ip[])
{
    int size_si = sizeof(env->si_client_send);
    printf("ecoute de la socket 4343 :\n");
    connect_to_Server(ip, PORT_SERV_SEND, &(env->socket_recv), (struct sockaddr *) &(env->si_client_recv));
    int nb_octet = sendto(env->socket_recv, "salut", strlen("salut"), 0,(struct sockaddr *) &(env->si_client_recv), size_si);
    if ( nb_octet < 0)
    {
        die("send_recv()");
    }
    printf("ecoute de la socket 4444 :\n");
    connect_to_Server(ip, PORT_SERV_RECV, &(env->socket_send), (struct sockaddr *) &(env->si_client_send));
    nb_octet = sendto(env->socket_send, "salut2", strlen("salut2"), 0,(struct sockaddr *) &(env->si_client_send), size_si);
    if ( nb_octet < 0)
    {
        die("send_send()");
    }
}

void start_client(t_simple_env *env)
{
    pthread_create(&(env->thread_recv), NULL, thread_recv_env, (void *) env);
    pthread_create(&(env->thread_send), NULL, thread_send_commande, (void *) env);
}


