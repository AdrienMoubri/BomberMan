/*
** init_sdl.c for my_ftl in /home/mathieu/Desktop/prog_c/MY_FTL/moubri_a/sdl
**
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
**
** Started on  Sat Apr 15 10:19:29 2017 MOUBRI Adrien
** Last update Sun May 14 19:01:28 2017 MOUBRI Adrien
*/

#include "bfm.h"

/*
 * initialise les images du menu  pour SDL
 */

void	init_screen(t_env *env)
{
  env->screen = malloc (sizeof (t_screen));
  if (env->screen)
    {
      SDL_Init(SDL_INIT_VIDEO);
      TTF_Init();
      env->screen->police = TTF_OpenFont("bm.ttf", 25);
      env->screen->ecran = NULL;
      env->screen->menu = NULL;
      env->screen->couleurBomber.r = 0xF7;
      env->screen->couleurBomber.g = 0xA4;
      env->screen->couleurBomber.b = 0x26;
      env->screen->couleurNoire.r = 0;
      env->screen->couleurNoire.g = 0;
      env->screen->couleurNoire.b = 0;
      env->screen->icon = IMG_Load("my_bfm_img/Bomberman_icon.png");
      SDL_WM_SetCaption("Super BomberMan 2", NULL);
      SDL_WM_SetIcon(env->screen->icon, NULL);
      env->screen->ecran = SDL_SetVideoMode(WIDTH_WINDOW, HEIGHT_WINDOW, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
      env->screen->menu = IMG_Load("my_bfm_img/menu.jpg");
      env->screen->map = IMG_Load("my_bfm_img/map.png");
      env->screen->selector = IMG_Load("my_bfm_img/selector2.png");
      env->screen->positionMenu.x = 0;
      env->screen->positionMenu.y = 0;
      env->screen->positionBackground.x = 0;
      env->screen->positionBackground.y = 0;
      env->screen->positionText.x = 300;
      env->screen->positionText.y = 400;
      env->screen->positionTextHaut.x = 330;
      env->screen->positionTextHaut.y = 520;
      env->screen->positionTextBas.x = 330;
      env->screen->positionTextBas.y = 660;
      env->screen->positionSelectorBas.x = 300;
      env->screen->positionSelectorBas.y = 660;
      env->screen->positionSelectorHaut.x = 300;
      env->screen->positionSelectorHaut.y = 520;
      env->screen->positionSelector = env->screen->positionSelectorHaut;
    }
}

/*
 * initialise les sprite du hero en fonction de son numéro
 */

t_hero_img_elem    *load_hero_img(t_hero_img_list *list_img, int num, char* file)
{
    for(int i = 0; i< 4; i++)
    {
        char str[50] = {"my_bfm_img/"};
        my_strcat(str, file);
        my_putstr(str);
        switch (i)
        {
            case 0:
                my_strcat(str, strdup("_front.png"));
                break;
            case 1:
                my_strcat(str, strdup("_left.png"));
                break;
            case 2:
                my_strcat(str, strdup("_right.png"));
                break;
            case 3:
                my_strcat(str, strdup("_back.png"));
                break;
            default:
                break;
        }
        t_hero_image *h1 = malloc(sizeof(t_hero_image));
        t_hero_img_elem *h1_e = malloc(sizeof(t_hero_img_elem));
        h1->numHero = num;
        h1->orientation = i;
        h1->hero_img = IMG_Load(str);
        h1_e->hero = h1;
        add_hero_img_to_list(h1_e, list_img);
    }
}

/*
 * initialise la map
 */
int             init_map(t_env *env)
{
    for(int i = 0; i < WIDTH_MAP; i++)
    {
        for(int y = 0; y < HEIGHT_MAP; y++)
        {
            env->map->case_tab[i][y].x = i;
            env->map->case_tab[i][y].y = y;
            env->map->case_tab[i][y].position.x = i * WIDTH_CASE;
            env->map->case_tab[i][y].position.y = y * HEIGHT_CASE;
            env->map->case_tab[i][y].position.w = WIDTH_CASE;
            env->map->case_tab[i][y].position.h = HEIGHT_CASE;
            if (i == 0 || y == 0 || y == HEIGHT_MAP - 1 || i == WIDTH_MAP - 1 )
                env->map->case_tab[i][y].type = 1;
            else
                env->map->case_tab[i][y].type = 0;
            if (i % 2 ==0 && y % 2 ==0)
            {
                env->map->case_tab[i][y].type = 1;
            }
        }
    }
}
/*
 * lance l'initialisation des 4 héros
 */
void    init_hero_ressources(t_env *env)
{
    create_hero_img_list(env);
    load_hero_img(env->heroes_img,0 , strdup("Black/black"));
    load_hero_img(env->heroes_img,1 , strdup("Green/green"));
    load_hero_img(env->heroes_img,2 , strdup("Red/Red"));
    load_hero_img(env->heroes_img,3 , strdup("White/white"));
}

/*
 * initialise les ressources des bombes
 */

t_bomb_image    init_bomb_ressources(t_env *env)
{   env->bomb_image = malloc(sizeof(t_bomb_image));
    env->bomb_image->bomb_img = IMG_Load("my_bfm_img/bomb_explosions/bomb.png");
    env->bomb_image->explo_center_img = IMG_Load("my_bfm_img/bomb_explosions/explo_center.png");
    env->bomb_image->explo_right_img = IMG_Load("my_bfm_img/bomb_explosions/explo_end_right.png");
    env->bomb_image->explo_left_img = IMG_Load("my_bfm_img/bomb_explosions/explo_end_left.png");
    env->bomb_image->explo_top_img = IMG_Load("my_bfm_img/bomb_explosions/explo_end_top.png");
    env->bomb_image->explo_bot_img = IMG_Load("my_bfm_img/bomb_explosions/explo_end_bottom.png");
    env->bomb_image->explo_horizontal_img = IMG_Load("my_bfm_img/bomb_explosions/explo_extend_hor.png");
    env->bomb_image->explo_vertical_img = IMG_Load("my_bfm_img/bomb_explosions/explo_extend_vert.png");

}

/*
 * initialise toutes les ressources demandé par la boucle de jeu
 */

void	init_game_resources(t_env *env) {
    init_hero_ressources(env);
    init_bomb_ressources(env);
    init_map(env);

    env->sizeCase.w = WIDTH_CASE;
    env->sizeCase.h = WIDTH_CASE;
    create_hero_list(env);

    for(int i = 0; i < env->simple_env->data_env->nb_hero; i++)
    {
        t_hero *h1 = malloc(sizeof(t_hero));
        h1->numHero = i;
        h1->play = 1;
        h1->direction = -1;
        h1->orientation = 0;
        h1->score = 0;
        h1->image = find_hero_img(0,0,env->heroes_img)->hero;
        h1->positionCase = &(env->map->case_tab[h1->numHero*2 +1][h1->numHero*2 +1]);
        h1->position.x = h1->positionCase->position.x;
        h1->position.y = h1->positionCase->position.y;
        h1->porteeBomb = 4;
        //a modifier
        env->simple_env->data_env->heroes[h1->numHero].orientation = h1->orientation;
        env->simple_env->data_env->heroes[h1->numHero].direction = h1->direction;
        env->simple_env->data_env->heroes[h1->numHero].x = h1->position.x;
        env->simple_env->data_env->heroes[h1->numHero].y = h1->position.y;
        env->simple_env->data_env->heroes[h1->numHero].alive = 1;
        //utiliser un générateur
        create_bomb_list(h1);
        t_hero_elem *h1_e = malloc(sizeof(t_hero_elem));
        h1_e->hero = h1;
        add_hero_to_list(h1_e, env->heroes);
    }
    env->sizeHero.w = WIDTH_HERO;
    env->sizeHero.h = HEIGHT_HERO;
    env->sizeHero.x = 0;
    env->sizeHero.y = 0;
}
/*
 * libère toutes la place mémoire utilisé
 */

void	free_sdl(t_env *env)
{
  TTF_CloseFont(env->screen->police);
  SDL_FreeSurface(env->screen->menu);
  //SDL_FreeSurface(env->screen->hero);
  SDL_FreeSurface(env->screen->selector);
  SDL_FreeSurface(env->screen->ecran);
  TTF_Quit();
  SDL_Quit();
}
