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
typedef struct      s_simple_env
{
    t_hero_simple   heroes[MAXHERO];
    int             map[WIDTH_MAP][HEIGHT_MAP];
}                   t_simple_env;
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
void myMemCpy(void *dest, void *src, size_t n);
void    send_player_to_server(int s, t_hero_simple* player);
void    send_env_to_player(int s, t_simple_env* env);
void    recv_player_from_player(int s, t_hero_simple* player);
void    recv_env_from_server(int s, t_simple_env* env);
int     create_server(int port);
int     listenServeurInfo(char*, int,t_simple_env* );
int     sendServeurInfo(int port, t_simple_env*);

int     listenPlayerInfo(int, t_hero_simple*);
int     sendPlayerInfo(char* ,int port, t_hero_simple*);
int     accept_client(int s);
void	die(char *str)
{
    perror(str);
    exit(1);
}
int sendServeurPort(int port, int portPlayable, int* socket);

typedef struct info
{
    int     *i;
    int     socket;
    void    *info;
}   t_info;


int     accept_client(int s);

void send_port_to_player(int s, int port)
{
    int size = sizeof(int);
    unsigned char data [size];
    myMemCpy(data, &port, size);
    if (send(s, data, size, 0) < 0)
        die("send");
}
int sendServeurPort(int port, int portPlayable, int* socket)
{
    init();
    *socket = accept_client(create_server(port));
    send_port_to_player(*socket, portPlayable);
    end(*socket);
}


/*
 * trust me im a  an ingeneer
 */


int	connect_to(char *hostname, int port)
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

int create_server(int port)
{
    int s;
    struct sockaddr_in sin;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
        die("bind");
    if (listen(s, 42) < 0)
        die("listen");
    return (s);
}

void myMemCpy(void *dest, void *src, size_t n)
{
    // cast src and dest addresses to (char *)
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    // Copy contents of src[] to dest[]
    for (int i=0; i<n; i++)
        cdest[i] = csrc[i];
}

void send_info_to_player(int s, int *info)
{
    int size = sizeof(int);
    unsigned char data [size];
    myMemCpy(data, info, size);
    if (send(s, data, size, 0) < 0)
        die("send");
}

void recv_info_from_server(int s,int* info)
{
    int size = sizeof(int);
    unsigned char data [size];
    if ((recv(s, data, size, 0)) < 0)
        die("recv");
    myMemCpy(info, data, size);
}


void connect_to_Server(char *ip, int port, int* socket)
{

    init();
    *socket = connect_to(ip, port);
}
void create_Server(int port, int* socket)
{
    init();
    *socket = accept_client(create_server(port));
}


void* thread_send_env_to_player (void* arg) {

    t_info *inf = arg;
    int size = sizeof(t_simple_env);
    unsigned char data [size];
    myMemCpy(data, inf->info, size);
    while (*(inf->i))
    {
        if (send(inf->socket, data, size, 0) < 0)
            die("send");
    }
    pthread_exit(NULL);
}

void* thread_res_env_to_player (void* arg) {
    t_info *inf = arg;
    int res =0;
    int size = sizeof(int);
    unsigned char data [size];
    if (recv(inf->socket, data, size, 0) < 0)
        die("recv");
    myMemCpy(&(res), data, size);
    if (res == 1) {
        *(inf->i) = 0;
    }
    pthread_exit(NULL); /* Fin du thread */
}

void send_env_to_player(int s, t_simple_env* env)
{
    pthread_t t1;
    pthread_t t2;
    int i =1;
    t_info *inf = malloc(sizeof(t_info));
    inf->socket = s;
    inf->info = env;
    inf->i = &i;
    pthread_create (&t1, NULL, thread_send_env_to_player, (void*)inf);
}

void recv_env_from_server(int s, t_simple_env* env)
{
    int i=1;
    int size = sizeof(t_simple_env);
    unsigned char data[size];
    if ((recv(s, data, size, 0)) < 0)
        die("recv");
    myMemCpy(env, data, size);
    size = sizeof(int);
}

void* thread_send_player_to_server (void* arg) {

    t_info *inf = arg;
    int size = sizeof(t_hero_simple);
    unsigned char data [size];
    myMemCpy(data, inf->info, size);
    while (*(inf->i))
    {
        if (send(inf->socket, data, size, 0) < 0)
            die("send");
    }
    pthread_exit(NULL);
}

void* thread_res_player_to_server (void* arg) {
    t_info *inf = arg;
    int res =0;
    int size = sizeof(int);
    unsigned char data [size];
    if (recv(inf->socket, data, size, 0) < 0)
        die("recv");
    myMemCpy(&(res), data, size);
    if (res == 1) {
        *(inf->i) = 0;
    }
    pthread_exit(NULL); /* Fin du thread */
}

void send_player_to_server(int s, t_hero_simple* player)
{
    pthread_t t1;
    pthread_t t2;
    t_info *inf = malloc(sizeof(t_info));
    inf->socket  =s;
    inf->info  =player;
    int i =1;
    inf->i = &i;
    pthread_create (&t1, NULL, thread_send_player_to_server, (void*)inf);
}

void recv_player_from_player(int s, t_hero_simple* player)
{
    int size = sizeof(t_hero_simple);
    unsigned char data [size];
    if ((recv(s, data, size, 0)) < 0)
        die("recv");
    myMemCpy(player, data, size);
}

int accept_client(int s)
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
int main(int argv, char **argc) {

    int s =0;
    int y =0;
    create_Server(4249, &s);
    create_Server(4250, &y);
    printf("socket : %d", s);
    /*
    connect_to_Server("192.168.1.7", 4249,&s);
    connect_to_Server("192.168.1.7", 4250,&y);
    */
    t_simple_env *env;
    env = malloc(sizeof(t_simple_env));
    t_hero_simple *hero = &(env->heroes[0]);

    for(int i = 0; i < MAXHERO; i++)
    {
        env->heroes[i].alive = 1;
        env->heroes[i].direction = 10;
        env->heroes[i].orientation = 100;
    }
    send_env_to_player(4246, env);

    /*
    for(int i = 0; i < 4; i++)
    {
        hero->bombes[i].x = 1;
        hero->bombes[i].y = 1;
        hero->bombes[i].chrono = 1;
        hero->direction = 10;
        hero->orientation = 100;
    }
    sendPlayerInfo("10.234.1.81", 4247, &(env->heroes[0]));
    */
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