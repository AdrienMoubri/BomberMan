/*
** order.c for bfm in /home/mathieu/Desktop/prog_c/Battle_For_Midgard
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Wed May 10 11:16:06 2017 MOUBRI Adrien
** Last update Sun May 14 14:43:50 2017 MOUBRI Adrien
*/

#include "bfm.h"
/*
 * tue le hero
 */
void				quit_battle(t_hero *hero)
{
  hero->play = 0;
}

/*
 * dépose une bombe
 * TODO rajouter les sprites
 */
void                create_bomb(t_hero *hero)
{
    t_bomb_elem *bomb_e = malloc(sizeof(t_bomb_elem));
    bomb_e->bomb = malloc(sizeof(t_bomb));
    bomb_e->bomb->positionCase = hero->positionCase;
    bomb_e->bomb->position = hero->positionCase->position;
    hero->positionCase->type = 10;
    bomb_e->bomb->chrono = SDL_GetTicks();
    bomb_e->bomb->portee = hero->porteeBomb;
    add_bomb_to_list(bomb_e, hero->bombes);
}

/*
 * l'action lancé par le perso
 */

void                drop_bomb(t_hero *hero)
{
    t_bomb_elem *bomb_i = hero->bombes->first;
    if (hero->bombes->nb_elem !=0)
    {
        for(int i = 0; i < hero->bombes->nb_elem; i++, bomb_i = bomb_i->next)
        {
            if (hero->positionCase != bomb_i->bomb->positionCase)
            {
                create_bomb(hero);
            }
        }
    }
    else
        create_bomb(hero);
}

/*
 * changement de direstion des hero
 */

void                down(t_hero *hero)
{
    hero->direction = 0;
    hero->orientation = 0;
}
void                left(t_hero *hero)
{
    hero->direction = 1;
    hero->orientation = 1;
}
void                right(t_hero *hero)
{
    hero->direction = 2;
    hero->orientation= 2;

}

void                up(t_hero *hero)
{
    hero->direction = 3;
    hero->orientation = 3;
}

/*
 * tableau de pointeur sur fonction des action des hero
 */

static const t_hero_order	g_order[] =
  {
    {SDLK_SPACE, drop_bomb},
    {SDLK_ESCAPE, quit_battle},
    {SDLK_a, left},
    {SDLK_w, up},
    {SDLK_d, right},
    {SDLK_s, down},
    {0, NULL}
  };

/*
 * détecte la touche lancé par le joueur
 */

void				hero_order(t_hero *hero, SDL_Event *event)
{
  int				i;
  i = 0;
  while (g_order[i].key)
    {
      if (event->key.keysym.sym == g_order[i].key)
	{
	  g_order[i].order(hero);
	  return ;
	}
      i += 1;
    }
}

/*
 * détecte la touche lancé par les joueurs a distances
 */

void				other_order(t_hero *hero, int commande)
{
    int				i;
    i = 0;
    while (g_order[i].key)
    {
        if (commande == g_order[i].key)
        {
            g_order[i].order(hero);
            return ;
        }
        i += 1;
    }
}