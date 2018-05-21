/*
** Bfm.h for bfm in /home/mathieu/Desktop/prog_c/Battle_For_Midgard
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Wed May 10 10:03:25 2017 MOUBRI Adrien
** Last update Sun May 14 21:56:34 2017 MOUBRI Adrien
*/

#ifndef			_BFM_H_
#define			_BFM_H_
#include <stdlib.h>
#include "lib/lib.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <pthread.h>

#define         WIDTH_CASE     16
#define         SPEED_HERO     4
#define         HEIGHT_CASE    16
#define         WIDTH_MAP     15
#define         HEIGHT_MAP     13
#define			WIDTH_WINDOW  1280
#define			HEIGHT_WINDOW 720
#define			WIDTH_HERO  20
#define			HEIGHT_HERO 33
#define         SIZE_IP 20
#define         MAXBOMBES 4
#define         MAXHERO 4

typedef struct		s_screen
{
    SDL_Rect		    positionMenu;
    SDL_Rect		    positionText;
    SDL_Rect		    positionTextHaut;
    SDL_Rect		    positionTextBas;
    SDL_Rect		    positionSelectorHaut;
    SDL_Rect		    positionSelectorBas;
    SDL_Rect		    positionSelector;
    SDL_Rect		    positionBackground;
    SDL_Surface		*text;
    SDL_Surface		*selector;
    TTF_Font		    *police;
    SDL_Color		    couleurNoire;
    SDL_Color		    couleurBomber;
    SDL_Surface		*ecran;
    SDL_Surface		*menu;
    SDL_Surface		*rect_text_haut;
    SDL_Surface		*rect_text_bas;
    SDL_Surface		*rect_menu;
    SDL_Surface		*rect_entree;
    SDL_Surface		*background;
    SDL_Surface		*bomb;
    SDL_Surface		*map;
}        t_screen;

typedef struct		s_hero_order
{
    unsigned int	key;
    void			(*order)();
}			t_hero_order;


typedef struct      s_hero_image
{
    int             numHero;
    int             orientation;
    SDL_Surface		*hero_img;
}                   t_hero_image;

typedef struct		    s_hero_img_elem
{
    t_hero_image		*hero;
    struct s_hero_img_elem	*next;
    struct s_hero_img_elem	*prev;
}			            t_hero_img_elem;

typedef struct		    s_hero_img_list
{
    t_hero_img_elem		*first;
    t_hero_img_elem		*last;
    int			        nb_elem;
}			            t_hero_img_list;

typedef struct      s_tile_image
{
    SDL_Surface		*tile_img;
}                   t_tile_image;

typedef struct      s_case
{
    int                x;
    int                y;
    SDL_Rect           position;
    t_tile_image       *image;
    int                type;
}                   t_case;

typedef struct 		s_bomb
{

    SDL_Surface		*Sprite;
    SDL_Rect		coord;
    int             portee;
    unsigned int    chrono;
    t_case          *positionCase;
}			        t_bomb;

typedef struct		s_bomb_elem
{
    t_bomb		    *bomb;
    struct s_bomb_elem	*next;
    struct s_bomb_elem	*prev;
}			        t_bomb_elem;

typedef struct		s_bomb_list
{
    t_bomb_elem		*first;
    t_bomb_elem		*last;
    int			    nb_elem;
}			        t_bomb_list;

typedef struct      s_bomb_image
{
    SDL_Surface		*bomb_img;
    SDL_Surface		*explo_center_img;
    SDL_Surface		*explo_right_img;
    SDL_Surface		*explo_left_img;
    SDL_Surface		*explo_top_img;
    SDL_Surface		*explo_bot_img;
}                   t_bomb_image;


typedef struct		s_hero
{
    t_hero_image      *image;
    int			      score;
    int               porteeBomb;
    SDL_Rect          position;
    t_case            *positionCase;
    int               direction;
    int               orientation;
    int               numHero;
    int               play;
    char*			  name;
    t_bomb_list		  *bombes;
}			        t_hero;

typedef struct		s_hero_elem
{
    t_hero		        *hero;
    struct s_hero_elem	*next;
    struct s_hero_elem	*prev;
}			        t_hero_elem;

typedef struct		s_hero_list
{
    t_hero_elem		*first;
    t_hero_elem		*last;
    int			    nb_elem;
}			        t_hero_list;

typedef struct      s_map
{
    //t_case_list     *case_list;
    t_case          case_tab[WIDTH_MAP][HEIGHT_MAP];
}                   t_map;

typedef struct      s_connection
{
    int             socket_info;
    int             socket_reponse;
}                   t_connection;

typedef struct		s_bomb_simple
{
    int             x;
    int             y;
    unsigned int    chrono;
}			        t_bomb_simple;

typedef struct		s_hero_simple
{
    int             alive;
    int			    score;
    int             x;
    int             y;
    int             direction;
    int             numHero;
    int             orientation;
    t_bomb_simple	bombes[MAXBOMBES];
}			        t_hero_simple;
typedef struct      s_simple_env
{
    t_hero_simple   heroes[MAXHERO];
    int             map[WIDTH_MAP][HEIGHT_MAP];
}                   t_simple_env;

typedef struct		s_env
{
    t_hero_list		*heroes;
    t_screen		    *screen;
    int               hero;
    pthread_mutex_t   mutex;
    int               nb_heroes;
    int               server;
    int               socketInfo;
    int               socketReponse;
    t_map             *map;
    SDL_Rect          sizeHero;
    t_hero_img_list   *heroes_img;
    t_bomb_image      *bomb_image;
    t_simple_env      simple_env;
    t_connection      *connection_client;
    t_connection      *connection_server[MAXHERO];
}			        t_env;



int		            create_hero_list(t_env *env);
void		        del_elem(t_hero_list *hero_l, t_hero_elem *hero_e);
void		        add_hero_to_list(t_hero_elem *hero_e, t_hero_list *hero_l);
void		        del_hero_from_list(t_hero_elem *node, t_hero_list *hero);

void                recv_info_from_server(int s,int* info);
void                send_info_to_player(int s, int *info);
int                 create_hero_img_list(t_env *env);
void		        add_hero_img_to_list(t_hero_img_elem *hero_e, t_hero_img_list *hero_l);
t_hero_img_elem     *find_hero_img(int num, int dir, t_hero_img_list *list);
int		            create_case_list(t_map *env);
/*
void		        del_case_elem(t_case_list *case_l, t_case_elem *case_e);
void		        add_case_to_list(t_case_elem *hero_e, t_case_list *hero_l);
void		        del_case_from_list(t_case_elem *node, t_case_list *hero);
 */
int		            create_bomb_list(t_hero *env);
void		        add_bomb_to_list(t_bomb_elem *hero_e, t_bomb_list *hero_l);
t_env			    *init_game();
void			    init_game_resources(t_env *env);
void		        del_bomb_from_list(t_bomb_elem *node, t_bomb_list *hero);


void                connect_to_Server(char *ip, int port, int* socket);
void				hero_order(t_hero *hero, SDL_Event *event);
int                 collisionObject(SDL_Rect, SDL_Rect);
int                 collisionCase(t_hero *hero, t_case map[WIDTH_MAP][HEIGHT_MAP]);
int                 finishedMovement(t_hero *hero);
void                launch_menu(t_env *env, SDL_Event *event);
void                launch_gameServer(t_env *env, SDL_Event *event);
void                launch_gameClient(t_env *env, SDL_Event *event);
char*               get_ip();
int                 listenPlayerInfo(int, t_hero_simple*);
void                send_env_to_player(int s,int s2, t_simple_env* env);

void                recv_env_from_server(int s,int s2,t_simple_env* env);
void                send_player_to_server(int s,int s2, t_hero_simple* player);
void                recv_player_from_player(int s,int s2, t_hero_simple* player);
void                connect_to_Server(char *ip, int port, int* socket);
void                create_Server(int port, int* socket);
//void			    del_digimon_from_team(t_digimon *node, t_hero *hero);
//void			    chance_catch(t_env *env);
//void			    merchant(t_env *env, SDL_Event *event);
//void			    eat_shroom(t_env *env);
//void			    rand_rupees(t_env *env);
void                move_hero(t_hero* hero);
void			    init_screen(t_env *env);
void			    free_sdl(t_env *env);
void			    change_select(t_env *env);
void			    display_screen(t_env *env);
//void			    select_img(t_env *env);
void                draw_Menu(t_env *env);
void                draw_Game(t_env *env);
void			    set_text(char *str, t_env *env);
#endif			    /* !_BFM_H_ */
