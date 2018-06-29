/*
** main.c for bomberman in /home/login_p/delivery/bomberman/main.c
**
** Made by MOUBRI adrien
** Login   <chassa_r@etna-alternance.net>
**
** Started on  jeu. oct. 05 10:43:31 2017 CHASSAIGNE Romain
** Last update jeu. oct. 05 10:43:31 2017 CHASSAIGNE Romain
*/


#define         MAXBOMBES       4
#define         MAXHERO         4
#define         WIDTH_MAP       15
#define         HEIGHT_MAP      13
#define         PORT_SERV_RECV  4343
#define         PORT_SERV_SEND  4444
#define         MAX_USERS       4

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#ifdef WIN32 /* si vous êtes sous Windows */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <afxres.h>

#pragma comment(lib, "ws2_32.lib")

#elif defined (linux) /* si vous êtes sous Linux */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#endif
typedef struct		s_bomb_simple
{
    int             x;
    int             y;
    int             chrono;
}			        t_bomb_simple;

typedef struct		s_hero_simple
{
    int             alive;
    int			    score;
    int             x;
    int             y;
    int             direction;
    int             orientation;
    t_bomb_simple	bombes[MAXBOMBES];
}			        t_hero_simple;
typedef struct      s_data_env
{
    t_hero_simple   heroes[MAXHERO];
    int             map[WIDTH_MAP][HEIGHT_MAP];
}                   t_data_env;

typedef struct      s_socketinfo
{
    int             socket_i;
    struct sockaddr_in si_client_i;
    pthread_mutex_t mutex_i;
}                   t_socketinfo;

typedef struct      s_simple_env
{
    t_data_env      *data_env;
    int             socket_recv;
    int             socket_send;
    int             num_cli;
    struct sockaddr_in si_client_recv;
    struct sockaddr_in si_client_send;
    int             commandeClient;
    int             commandes[MAX_USERS];
    int             usable_port[MAX_USERS];
    pthread_t       thread_recv;
    pthread_t       thread_send;
    pthread_mutex_t mutexSend;
    pthread_mutex_t mutexRecv;
    t_socketinfo    socketinfo[MAX_USERS];
}                   t_simple_env;

typedef struct      info
{
    int     *i;
    int     socket;
    void    *info;
}                   t_info;

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

static void init(t_simple_env *env) {
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
    for (int i=0; i < MAX_USERS; i++)
        env->usable_port[i] = 3000 + i*10;
    env->si_client_send = si_send;
    env->si_client_recv = si_recv;
    env->socket_recv = 0;
    env->socket_send = 0;
    env->commandeClient = 0;
    env->mutexSend = PTHREAD_MUTEX_INITIALIZER;
    env->mutexRecv = PTHREAD_MUTEX_INITIALIZER;
    for (int i=0; i < 4; i++)
    {
        env->socketinfo[i].mutex_i = PTHREAD_MUTEX_INITIALIZER;
        env->socketinfo[i].si_client_i = si_recv;
        env->socketinfo[i].socket_i = 0;
    }
}

static void end(int s) {
    close(s);
#ifdef WIN32
    WSACleanup();
#endif
}

char    *get_ip(){
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
    SOCKET sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == SOCKET_ERROR)
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

void    wait (int ms) {
    pthread_mutex_t fakeMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t fakeCond = PTHREAD_COND_INITIALIZER;
    struct timespec timeToWait;
    struct timeval now;
    gettimeofday(&now,NULL);
    timeToWait.tv_sec = now.tv_sec;
    timeToWait.tv_nsec = (now.tv_usec+1000UL*ms)*1000UL;
    pthread_mutex_lock(&fakeMutex);
    pthread_cond_timedwait(&fakeCond, &fakeMutex, &timeToWait);
    pthread_mutex_unlock(&fakeMutex);
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
    printf("début thread send \n");
    while (1)
    {
        wait (250);
            send_env(env->socket_send, (struct sockaddr *) &env->si_client_send, &(env->mutexSend), env->data_env);
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
    printf("début thread recv\n");
    struct timeval tv;
    fd_set readfds;
    struct timespec timeToWait;
    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(env->socketinfo[env->num_cli].socket_i, &readfds);
        timeToWait.tv_sec = 5;
        timeToWait.tv_nsec = 0;
        select(env->socket_recv+1, &readfds, NULL, NULL, &tv);
        if (FD_ISSET(env->socketinfo[env->num_cli].socket_i, &readfds))
            recv_commande(env->socketinfo[env->num_cli].socket_i,(struct sockaddr *) &(env->socketinfo[env->num_cli].si_client_i), &(env->socketinfo[env->num_cli].mutex_i), &(env->commandes[env->num_cli]));
        else
            printf("Timed out.\n");
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
    // init

    char buffer[1024];
    int size_si = sizeof(env->si_client_send);
    printf("creation du server :\n");
    create_Server(PORT_SERV_SEND, &(env->socket_send), &(env->si_client_send));
    int fin = 0;
    int nb_cli = 0;
    int size = sizeof(int);
    unsigned char data [size];
    while(nb_cli < MAX_USERS)
    {
        myMemCpy(data, &(env->usable_port[nb_cli]), size);
        printf("waiting on 4343 :\n");
        while (!fin) {
            int nb_octet = recvfrom(env->socket_send, buffer, sizeof buffer - 1, 0,
                                    (struct sockaddr *) &(env->si_client_send),
                                    &size_si);
            if (nb_octet > 0) {
                fin = 1;
                wait (1000);
                sendto(env->socket_send, data, size, 0,(struct sockaddr *) &(env->si_client_send), size_si);
            }
        }
        fin = 0;
        create_Server(env->usable_port[nb_cli], &(env->socketinfo[nb_cli].socket_i), &(env->socketinfo[nb_cli].si_client_i));
        nb_cli++;
    }
    nb_cli = 0;
    while(nb_cli < MAX_USERS)
    {
        wait (25);
        int nb_octet = sendto(env->socketinfo[nb_cli].socket_i, data, size, 0,(struct sockaddr *) &(env->socketinfo[nb_cli].si_client_i), size_si);
            if (nb_octet < 0) {
                die("send_send()");
            }
        else
            nb_cli++;
    }
}

void    start_server(t_simple_env *env) {
    pthread_create(&(env->thread_send), NULL, thread_send_env, (void *) env);
    for (int i = 0; i < MAX_USERS; i++){
        env->num_cli = i;
        pthread_create(&(env->thread_recv), NULL, thread_recv_commande, (void *) env);
    }

}

void    server(t_simple_env *env) {
    // initialisation
    init(env);

    //connection
    init_connect_to_client(env);

    //lancement
    printf("envoie des info sur la socket s \n");
    start_server(env);
    //lecture
    for (int i = 0; i < MAXHERO; i++) {
        env->data_env->heroes[i].alive = 100;
        env->data_env->heroes[i].direction = 100;
        env->data_env->heroes[i].orientation = 100;
        printf("hero %d alive : %d, direction : %d, orientation : %d \n", i, env->data_env->heroes[i].alive,
               env->data_env->heroes[i].direction, env->data_env->heroes[i].orientation);
    }
    t_hero_simple *hero;
    while (1) {
        wait(500);
        pthread_mutex_lock(&(env->mutexSend));
        for (int i = 0; i < MAXHERO; i++) {
            pthread_mutex_lock(&(env->socketinfo[i].mutex_i));
            env->data_env->heroes[i].alive++;
            env->data_env->heroes[i].direction += env->commandes[i];
            env->data_env->heroes[i].orientation++;
            printf("hero %d alive : %d, direction : %d, orientation : %d \n", i, env->data_env->heroes[i].alive,
                   env->data_env->heroes[i].direction, env->data_env->heroes[i].orientation);
              hero = &(env->data_env->heroes[i]);
            for (int i = 0; i < 4; i++) {
                hero->bombes[i].x = 1;
                hero->bombes[i].y = 1;
                hero->bombes[i].chrono = 1;
                printf("x %d y : %d, chrono : %d \n", hero->bombes[i].x ,  hero->bombes[i].y ,
                       hero->bombes[i].chrono);
            }
            pthread_mutex_unlock(&(env->socketinfo[i].mutex_i));
        }
        pthread_mutex_unlock(&(env->mutexRecv));
        printf("Done\n\n");
    }
}

void    init_connect_to_server(t_simple_env *env, char ip[]) {
    struct timeval tv;
    struct timespec timeToWait;
    int size_si = sizeof(env->si_client_send);
    int nb_octet=0;
    fd_set readfds;
    printf("ecoute de la socket 4343 :\n");
    connect_to_Server(ip, PORT_SERV_SEND, &(env->socket_recv), (struct sockaddr *) &(env->si_client_recv));
    sendto(env->socket_recv, "salut", strlen("salut"), 0,(struct sockaddr *) &(env->si_client_recv), size_si);
    int port = 0;
    int size = sizeof(int);
    unsigned char data [size];
    FD_ZERO(&readfds);
    FD_SET(env->socket_recv, &readfds);
    timeToWait.tv_sec = 150;
    timeToWait.tv_nsec = 0;
    select(env->socket_recv+1, &readfds, NULL, NULL, &tv);
    if (FD_ISSET(env->socket_recv, &readfds))
        recvfrom(env->socket_recv, data, size, 0,
                 (struct sockaddr *) &(env->si_client_recv),
                 &size_si);
    myMemCpy(&port, data, size);
    printf("port :: %d", port);
    printf("ecoute de la socket 4444 :\n");
    connect_to_Server(ip, port, &(env->socket_send), (struct sockaddr *) &(env->si_client_send));
    FD_ZERO(&readfds);
    FD_SET(env->socket_recv, &readfds);
    timeToWait.tv_sec = 150;
    timeToWait.tv_nsec = 0;
    select(env->socket_recv+1, &readfds, NULL, NULL, &tv);
    if (FD_ISSET(env->socket_recv, &readfds))
    {
        nb_octet = recvfrom(env->socket_send, data, size, 0,(struct sockaddr *) &(env->si_client_send), &size_si);
        if ( nb_octet < 0)
        {
            die("send_send()");
        }
    }
}

void    start_client(t_simple_env *env) {
    pthread_create(&(env->thread_recv), NULL, thread_recv_env, (void *) env);
    pthread_create(&(env->thread_send), NULL, thread_send_commande, (void *) env);
}

void    client(t_simple_env *env) {
    //init
    init(env);
    // connection
    init_connect_to_server(env, "127.0.0.1\0");

    // lancement
    start_client(env);

    // lecture
    t_hero_simple *hero;
    for(int i = 0; i < MAXHERO; i++)
    {
        env->data_env->heroes[i].alive = 100;
        env->data_env->heroes[i].direction = 100;
        env->data_env->heroes[i].orientation = 100;
        printf("hero %d alive : %d, direction : %d, orientation : %d \n", i, env->data_env->heroes[i].alive, env->data_env->heroes[i].direction, env->data_env->heroes[i].orientation);
    }
    while (1)
    {
        wait(500);
        pthread_mutex_lock(&(env->mutexRecv));
        for(int i = 0; i < MAXHERO; i++)
        {
            printf("Hero %d : alive : %d, ", i,  env->data_env->heroes[i].alive);
            printf("direction : %d, ", env->data_env->heroes[i].direction);
            printf("orientation : %d, ", env->data_env->heroes[i].orientation);
            printf("commande : %d \n", env->commandeClient);
            hero = &(env->data_env->heroes[i]);
            for (int i = 0; i < 4; i++) {
                printf("x %d y : %d, chrono : %d \n", hero->bombes[i].x ,  hero->bombes[i].y ,
                       hero->bombes[i].chrono);
            }
        }
        pthread_mutex_lock(&(env->mutexSend));
        env->commandeClient = 8;
        pthread_mutex_unlock(&(env->mutexSend));
        pthread_mutex_unlock(&(env->mutexRecv));
        printf("end \n\n");
    }
}

int     main(int argv, char **argc) {

    t_simple_env *env;
    env = malloc(sizeof(t_simple_env));
    env->data_env = malloc(sizeof(t_data_env));
    server(env);
    //client(env);
}
