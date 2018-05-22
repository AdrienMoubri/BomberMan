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

typedef struct      s_simple_env
{
    t_data_env      *data_env;
    int             socket_recv;
    int             socket_send;
    int             commande;
    pthread_mutex_t mutexRecv;
    pthread_mutex_t mutexSend;
}                   t_simple_env;
typedef struct info
{
    int     *i;
    int     socket;
    void    *info;
}   t_info;


void    myMemCpy(void *dest, void *src, size_t n);
void    send_commande(int s, pthread_mutex_t *mutex, int* commande);
void*   thread_send_commande (void* arg);
void    send_env(int s, pthread_mutex_t *mutex, t_data_env* env);
void*   thread_send_env (void* arg);
void    recv_env(int s, pthread_mutex_t *mutex, t_data_env *env);
void*   thread_recv_env (void* arg);
void    create_Server(int port, int* socket);
void    create_server(int port);
int     accept_client(int s);
void    wait (int ms);
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
char    *get_ip()
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


void	die(char *str)
{
    perror(str);
    exit(1);
}

void    wait (int ms)
{
    pthread_mutex_t fakeMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t mutexCond = PTHREAD_COND_INITIALIZER;
    struct timespec timeToWait;
    struct timeval now;
    gettimeofday(&now,NULL);
    timeToWait.tv_sec = now.tv_sec;
    timeToWait.tv_nsec = (now.tv_usec+1000UL*ms)*1000UL;
    pthread_mutex_lock(&fakeMutex);
    pthread_cond_timedwait(&(mutexCond), &fakeMutex, &timeToWait);
    pthread_mutex_unlock(&fakeMutex);
}

int     accept_client(int s)
{
    int     c;
    struct  sockaddr_in sin;
    int     size;

    size = sizeof(sin);
    if ((c = accept(s, (struct sockaddr *)&sin, &size)) < 0)
    {
        die("accept");
    }
    return (c);
}

int	    connect_to(char *hostname, int port)
{
    int			s;
    struct sockaddr_in	sin;

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(hostname);
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket");
    if (connect(s, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) < 0)
        die("connect");
    return (s);
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

void    connect_to_Server(char *ip, int port, int* socket)
{

    init();
    *socket = connect_to(ip, port);
}



void*   thread_send_env (void* arg) {
    t_simple_env *env = arg;
    printf("début thread send \n");
    while (1)
    {
        wait(500);
        send_env(env->socket_send, &(env->mutexSend), env->data_env);
    }
}

void    send_env(int s, pthread_mutex_t *mutex, t_data_env *env)
{
    int size = sizeof(t_data_env);
    unsigned char data [size];
    pthread_mutex_lock(mutex);
    myMemCpy(data, env, size);
    pthread_mutex_unlock(mutex);
    if (send(s, data, size, 0) < 0)
        die("send");
}

void*   thread_send_commande (void* arg) {
    t_simple_env *env = arg;
    printf("début thread send \n");
    while (1)
    {
        wait(500);
        send_commande(env->socket_send, &(env->mutexSend), &(env->commande));
    }
}

void    send_commande(int s, pthread_mutex_t *mutex, int *commande)
{
    int size = sizeof(int);
    unsigned char data [size];
    pthread_mutex_lock(mutex);
    myMemCpy(data, commande, size);
    pthread_mutex_unlock(mutex);
    if (send(s, data, size, 0) < 0)
        die("send");
}

void*   thread_recv_env (void* arg) {
    t_simple_env *env = arg;
    printf("début thread \n");
    while (1)
    {
        wait(500);
        recv_env(env->socket_recv, &(env->mutexRecv), env->data_env);
    }
}

void    recv_env(int s, pthread_mutex_t *mutex, t_data_env *env)
{
    int size = sizeof(t_data_env);
    unsigned char data[size];
    if ((recv(s, data, size, 0)) < 0)
        die("recv");
    pthread_mutex_lock(mutex);
    myMemCpy(env, data, size);
    pthread_mutex_unlock(mutex);
}

int     main(int argv, char **argc) {
    t_simple_env *env;
    env = malloc(sizeof(t_simple_env));
    env->data_env = malloc(sizeof(t_data_env));
    env->mutexRecv = PTHREAD_MUTEX_INITIALIZER;
    env->mutexSend = PTHREAD_MUTEX_INITIALIZER;
    env->socket_recv = 0;
    env->socket_send = 0;
    env->commande = 0;
    pthread_t t1;
    pthread_t t2;

    printf("ecoute de la socket 4249 :\n");
    connect_to_Server("192.168.56.1\0", 4249, &(env->socket_recv));
    printf("connexion socket 4249 : Réussi\n");
    printf("ecoute de la socket 4249 :\n");
    connect_to_Server("192.168.56.1\0", 4250, &(env->socket_send));
    printf("connexion socket 4250 : Réussi\n");
    recv_env(env->socket_recv, &(env->mutexRecv), env->data_env);
    pthread_create(&t1, NULL, thread_recv_env, (void *) env);
    pthread_create(&t2, NULL, thread_send_commande, (void *) env);

    while (1)
    {
        wait(500);
        pthread_mutex_lock(&(env->mutexRecv));
        for(int i = 0; i < MAXHERO; i++)
        {
            printf("Hero %d : alive : %d, ", i,  env->data_env->heroes[i].alive);
            printf("direction : %d, ", env->data_env->heroes[i].direction);
            printf("orientation : %d, ", env->data_env->heroes[i].orientation);
            printf("commande : %d \n", env->commande);
        }
        pthread_mutex_lock(&(env->mutexSend));
        env->commande = 5;
        pthread_mutex_unlock(&(env->mutexSend));
        pthread_mutex_unlock(&(env->mutexRecv));
        printf("end \n\n");
    }

    /*
    for(int i = 0; i < MAXHERO; i++)
    {
        env->data_env->heroes[i].alive = 100+v;
        env->data_env->heroes[i].direction = 100+v;
        env->data_env->heroes[i].orientation = 100+v;
        printf("hero %d alive : %d, direction : %d, orientation : %d \n", i, env->data_env->heroes[i].alive, env->data_env->heroes[i].direction, env->data_env->heroes[i].orientation);
    }
    printf("envoie des info sur la socket s \n");
    send_env(env->socket_send, &(env->mutexRecv), env->data_env);
    struct timespec timeToWait;
    struct timeval now;
    pthread_create (&t1, NULL, thread_send_env_to_player, (void*)env);
    while (1)
    {
        gettimeofday(&now,NULL);
        timeToWait.tv_sec = now.tv_sec;
        timeToWait.tv_nsec = (now.tv_usec+1000UL*500)*1000UL;
        pthread_mutex_lock(&fakeMutex);
        pthread_cond_timedwait(&(env->mutexCond), &fakeMutex, &timeToWait);
        pthread_mutex_unlock(&fakeMutex);
        v++;

        pthread_mutex_lock(&(env->mutexRecv));
        for(int i = 0; i < MAXHERO; i++)
        {
            env->data_env->heroes[i].alive = 100+v;
            env->data_env->heroes[i].direction = 100+v;
            env->data_env->heroes[i].orientation = 100+v;
            printf("hero %d alive : %d, direction : %d, orientation : %d \n", i, env->data_env->heroes[i].alive, env->data_env->heroes[i].direction, env->data_env->heroes[i].orientation);
        }
        printf("Done\n\n");

        pthread_mutex_unlock(&(env->mutexRecv));
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