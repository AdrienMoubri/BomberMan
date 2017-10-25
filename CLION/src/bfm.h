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
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#define			NBCREA 5
#define			MAGIC_BOX_PRICE 30
#define			MUSHROOM_PRICE 9
#define			START_PRICE 320
#define			WIDTH_WINDOW 500
#define			HEIGHT_WINDOW 500

typedef struct		s_screen
{
  SDL_Rect		positionMenu;
  SDL_Rect		positionCreature;
  SDL_Rect		positionHero;
  SDL_Rect		positionText;
  SDL_Rect		positionCadre;
  SDL_Rect		positionBackground;
  SDL_Surface		*text;
  SDL_Surface		*cadre;
  TTF_Font		*police;
  SDL_Color		couleurNoire;
  SDL_Surface		*ecran;
  SDL_Surface		*menu;
  SDL_Surface		*background;
  SDL_Surface		*town;
  SDL_Surface		*battle;
  SDL_Surface		*hero;
  SDL_Surface		*creature;
}			t_screen;

typedef struct 		s_creature
{
  char			*name;
  int			lvl;
  int			pv;
  int			pv_max;
  int			pm;
  int			pm_max;
}			t_creature;

typedef struct		s_digimon
{
  t_creature		*digimon;
  struct s_digimon	*next;
  struct s_digimon	*prev;
}			t_digimon;

typedef struct		s_team
{
  t_digimon		*first;
  t_digimon		*last;
  int			nb_elem;
  t_digimon		*selected;
}			t_team;

typedef struct		s_hero
{
  int			magic_ball;
  int			rupees;
  int			shroom;
  char*			name;
  t_team		*team;
}			t_hero;


typedef struct		s_env
{
  t_hero		*hero;
  t_creature		*creature;
  t_screen		*screen;
  int			fight;
  int			play;
}			t_env;

typedef struct		s_hero_order
{
  unsigned int		key;
  void			(*order)();
}			t_hero_order;

typedef struct		s_load_img
{
  char			*key;
  char			*front;
  char			*back;
}			t_load_img;

int			my_strcmp(char *str1, char *str2);
int			my_rand();
void			my_putstr_color(const char *color,const char *str);
void			my_put_nbr(int i);
int			my_getnbr(char *str);
int			my_is_odd(int i);
void			my_putstr(char *str);
char			*my_strdup(char *str);
char			*my_strcat(char *str1, char *str2);
char			*read_line();
char			*my_strupcase(char *str);
int			add_team_to_hero(t_hero *hero);
void			add_digimon_to_team(t_digimon *node, t_hero *hero);
void			hero_order(t_env *env, SDL_Event *event);
void			play(t_env *env, SDL_Event *event);
t_creature		*get_creature();
t_env			*init_game(char *str);
void			order_out_battle(t_env *env, SDL_Event *event);
void			slash(t_env *env);
void			fire(t_env *env);
void			gamble(t_env *env);
void			rest(t_env *env);
void			creature_slash(t_env *env);
void			creature_fire(t_env * env);
void			creature_gamble(t_env *env);
void			creature_rest(t_env *env);
void			mob_random(t_env *env);
void			del_digimon_from_team(t_digimon *node, t_hero *hero);
void			chance_catch(t_env *env);
void			merchant(t_env *env, SDL_Event *event);
void			eat_shroom(t_env *env);
void			rand_rupees(t_env *env);
void			init_screen(t_env *env);
void			free_sdl(t_env *env);
void			display_screen(t_env *env);
void			select_img(t_env *env);
void			set_text(char *str, t_env *env);
#endif			/* !_BFM_H_ */
