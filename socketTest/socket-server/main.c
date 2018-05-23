/*
** main.c for bomberman in /home/login_p/delivery/bomberman/main.c
**
** Made by MOUBRI adrien
** Login   <chassa_r@etna-alternance.net>
**
** Started on  jeu. oct. 05 10:43:31 2017 CHASSAIGNE Romain
** Last update jeu. oct. 05 10:43:31 2017 CHASSAIGNE Romain
*/


#define         MAXBOMBES 4
#define         MAXHERO 4
#define         WIDTH_MAP     15
#define         HEIGHT_MAP     13
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#ifdef WIN32 /* si vous êtes sous Windows */

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

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
/*
typedef struct      s_player
{
    int             socket_recv;
    int             socket_send;
    int             commande;
};*/

typedef struct      s_simple_env
{
    t_data_env      *data_env;
    SOCKET          socket_recv;
    SOCKET          socket_send;
    struct sockaddr_in si_client_recv;
    struct sockaddr_in si_client_send;
    int             commande;
    pthread_mutex_t mutexSend;
    pthread_mutex_t mutexRecv;
}                   t_simple_env;

typedef struct info
{
    int     *i;
    int     socket;
    void    *info;
}   t_info;

static void init(void)
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
}

static void end(int s)
{
    close(s);
#ifdef WIN32
    WSACleanup();
#endif
}
char *get_ip()
{
    init();
    char s[256] = {0}, **pp = NULL;
    char *ip;
    struct hostent *host = NULL;

    if(!gethostname(s, 256) && (host = gethostbyname(s)) != NULL)
        for(pp = host->h_addr_list ; *pp != NULL ; pp++)
            ip = inet_ntoa(*(struct in_addr *)*pp);
    close(-1);
    return ip;
}
void    myMemCpy(void *dest, void *src, size_t n);
void    send_env(int s, struct sockaddr *si_server, pthread_mutex_t *mutex, t_data_env* env);
void    recv_env(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, t_data_env *env);
void    recv_commande(int s, struct sockaddr *si_client, pthread_mutex_t *mutex, int *env);
void*   thread_recv_commande (void* arg);
void*   thread_send_env (void* arg);
void*   thread_recv_env (void* arg);
SOCKET     create_server(int port, struct sockaddr_in *si_client);

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

void    wait (int ms)
{
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

SOCKET     create_server(int port, struct sockaddr_in *sin)
{
    SOCKET sock= socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET)
        die("sock");
    sin->sin_family = AF_INET;
    sin->sin_port = htons(port);
    sin->sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (struct sockaddr *) sin, sizeof(struct sockaddr)) == SOCKET_ERROR)
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
    init();
    *socket = create_server(port, si_client);
}

void*   thread_send_env (void* arg) {
    t_simple_env *env = arg;
    printf("début thread send \n");
    /*struct timeval tv;
    fd_set writefds;
    struct timespec timeToWait;
    struct timeval now;
    FD_ZERO(&writefds);
    FD_SET(env->socket_send, &writefds);*/
    while (1)
    {
        //wait (250);
        /*gettimeofday(&now,NULL);
        timeToWait.tv_sec = now.tv_sec;
        timeToWait.tv_nsec = (now.tv_usec+1000UL*500)*1000UL;
        select(env->socket_send+1, &writefds, NULL, NULL, &tv);
        if (FD_ISSET(env->socket_send, &writefds))*/
            send_env(env->socket_send, (struct sockaddr *) &env->si_client_send, &(env->mutexSend), env->data_env);
        /*else
            printf("Timed out send.\n");*/
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
    struct timeval now;
    FD_ZERO(&readfds);
    FD_SET(env->socket_recv, &readfds);
    while (1)
    {
        gettimeofday(&now,NULL);
        timeToWait.tv_sec = now.tv_sec;
        timeToWait.tv_nsec = (now.tv_usec+1000UL*500)*1000UL;


        /* ignorer writefds et exceptfds: */
        select(env->socket_recv+1, &readfds, NULL, NULL, &tv);

        if (FD_ISSET(env->socket_recv, &readfds))
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

void*   thread_recv_commande (void* arg) {
    t_simple_env *env = arg;
    printf("début thread recv\n");
    struct timeval tv;
    fd_set readfds;
    struct timespec timeToWait;
    struct timeval now;
    FD_ZERO(&readfds);
    FD_SET(env->socket_recv, &readfds);
    while (1)
    {
        gettimeofday(&now,NULL);
        timeToWait.tv_sec = now.tv_sec;
        timeToWait.tv_nsec = (now.tv_usec+1000UL*500)*1000UL;


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

int     main(int argv, char **argc) {
    pthread_t t1;
    pthread_t t2;
    init();
    t_simple_env *env;
    char buffer[1024];
    env = malloc(sizeof(t_simple_env));
    env->data_env = malloc(sizeof(t_data_env));
    struct sockaddr_in si_recv = { 0 };
    struct sockaddr_in si_send = { 0 };
    env->si_client_send = si_send;
    env->si_client_recv = si_recv;
    int size_si = sizeof(env->si_client_send);
    env->socket_recv = 0;
    env->socket_send = 0;
    env->commande = 0;
    env->mutexSend = PTHREAD_MUTEX_INITIALIZER;
    env->mutexRecv = PTHREAD_MUTEX_INITIALIZER;
    printf("creation du server :\n");
    create_Server(4343, &(env->socket_send), &(env->si_client_send));
    int fin = 0;

    printf("waiting on 4343 :\n");
    while (!fin) {
        int nb_octet = recvfrom(env->socket_send, buffer, sizeof buffer - 1, 0, (struct sockaddr *) &(env->si_client_send),
                 &size_si);
        if (nb_octet > 0)
        {
            fin = 1;
        }
    }
    create_Server(4444, &(env->socket_recv), &(env->si_client_recv));
    fin = 0;
    printf("waiting on 4444 :\n");
    while (!fin) {
        int nb_octet = recvfrom(env->socket_recv, buffer, sizeof buffer - 1, 0, (struct sockaddr *) &(env->si_client_recv),
                                &size_si);
        if (nb_octet > 0)
        {
            fin = 1;
        }
    }
    for(int i = 0; i < MAXHERO; i++)
    {
        env->data_env->heroes[i].alive = 100;
        env->data_env->heroes[i].direction = 100;
        env->data_env->heroes[i].orientation = 100;
        printf("hero %d alive : %d, direction : %d, orientation : %d \n", i, env->data_env->heroes[i].alive, env->data_env->heroes[i].direction, env->data_env->heroes[i].orientation);
    }
    printf("envoie des info sur la socket s \n");
    //send_env(env->socket_send, (struct sockaddr *) &si_client, &(env->mutexSend), env->data_env);
    pthread_create(&t1, NULL, thread_send_env, (void *) env);
    pthread_create(&t2, NULL, thread_recv_commande, (void *) env);
    while (1)
    {
        wait(500);
        pthread_mutex_lock(&(env->mutexSend));
        pthread_mutex_lock(&(env->mutexRecv));
        for(int i = 0; i < MAXHERO; i++)
        {
            env->data_env->heroes[i].alive++;
            env->data_env->heroes[i].direction += env->commande;
            env->data_env->heroes[i].orientation++;
            printf("hero %d alive : %d, direction : %d, orientation : %d \n", i, env->data_env->heroes[i].alive, env->data_env->heroes[i].direction, env->data_env->heroes[i].orientation);
        }
        pthread_mutex_unlock(&(env->mutexSend));
        pthread_mutex_unlock(&(env->mutexRecv));
        printf("Done\n\n");
    }

/*
    for(int i = 0; i < 4; i++)
    {
        hero->bombes[i].x = 1;
        hero->bombes[i].y = 1;
        hero->bombes[i].chrono = 1;
        hero->direction = 10;
        hero->orientation = 100;
    }
    send_env(4246, env);

    /*
    listenServeurInfo("10.234.1.81", 4246,env);

    //écrit le resultat on devrait le retourner
    for(int i = 0; i < MAXHERO; i++)
    {
        printf("%d\n", env->heroes[i].alive);
        printf("%d\n", env->heroes[i].direction);
        printf("%d\n", env->heroes[i].orientation);
    }
    */
    /*
    listenPlayerInfo(4247, &(env->heroes[0]));
    printf("Etape : %d\n", 0);
    printf("bombe x : %d\n", hero->bombes[0].x);
    printf("bombe x : %d\n", hero->bombes[0].y);
    printf("bombe chrono : %d\n", hero->bombes[0].chrono);
    printf("Orientation : %d\n", hero->orientation);
    printf("Direction  : %d\n", hero->direction);
    return (0);
     */
}