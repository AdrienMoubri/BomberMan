/*
** game.c for bfm.h in /home/mathieu/Desktop/prog_c/Battle_For_Midgard
** 
** Made by MOUBRI Adrien
** Login   <moubri_a@etna-alternance.net>
** 
** Started on  Wed May 10 10:23:51 2017 MOUBRI Adrien
** Last update Sun May 14 18:33:06 2017 MOUBRI Adrien
*/

#include "bfm.h"

/*
 * obtention des addresses des ressources pour SDL
 */
t_env			*init_game()
{
    t_env			*env;

    env = malloc(sizeof(t_env));
    if (env)
    {
        env->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
        env->heroes = malloc(sizeof (t_hero_list));
        env->screen = malloc(sizeof(t_screen));
        env->map = malloc(sizeof (t_map));
        env->simple_env = malloc(sizeof(t_simple_env));
        env->simple_env->data_env = malloc(sizeof(t_data_env));
    }
    return (env);
}

char *readStringSDL(char *s_dst, size_t n)
{
    return s_dst;
}
/*
 * lancement du menu et selection entre client ou server
 */
void                launch_menu(t_env *env, SDL_Event *event)
{
    int play = 0;
    while (!play)
    {
        draw_Menu(env);
        SDL_WaitEvent(event);
        while (event->type != SDL_KEYUP)
        {
            SDL_WaitEvent(event);
        }
        switch (event->key.keysym.sym)
        {
            case SDLK_RETURN:
                play = 1;
                env->hero = 0;
                break;

            default:
                change_select(env);
                break;
        }
    }
    char text[SIZE_IP];
    //initialise le tableau
    for (int i =0; i < SIZE_IP; i++)
    {
        text[i] = '\0';
    }
    size_t pos = 0;
    int unicode;
    SDL_EnableUNICODE(1);
    env->server = 0;
    env->nb_heroes = 1;
    while (play)
    {
        if (env->screen->positionSelector.y == env->screen->positionSelectorBas.y)
        {
            env->screen->rect_text_haut = TTF_RenderText_Blended(env->screen->police, "Entre une adresse IP ", env->screen->couleurBomber);
            env->screen->text = TTF_RenderText_Blended(env->screen->police, text, env->screen->couleurBomber);
        }
        else
        {
            env->screen->rect_text_haut = TTF_RenderText_Blended(env->screen->police, "Votre adresse IP ", env->screen->couleurBomber);
            env->screen->text = TTF_RenderText_Blended(env->screen->police, get_ip(), env->screen->couleurBomber);
            env->server = 1;
        }
        draw_Menu(env);
        //création du server
        if (env->server == 1)
        {
            init_connect_to_client(env->simple_env);
            env->nb_heroes++;
            SDL_WaitEvent(event);
            play = 0;
        }
        //TODO créer des méthode pour mieux visualiser les échanges
        else{
            SDL_WaitEvent(event);
            while (event->type != SDL_KEYDOWN)
            {
                SDL_WaitEvent(event);
            }
            switch (event->type)
            {
                case SDL_KEYDOWN:
                    switch (event->key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            init_connect_to_server(env->simple_env, text);
                            env->nb_heroes = 2;
                            env->hero = 1;
                            play = 0;
                            break;
                        default:
                            unicode = event->key.keysym.unicode;
                            if (unicode == 8 && pos > 0)
                            {
                                text[pos] = '\0';
                                pos--;
                            }
                            else
                            if (unicode >= 32 && unicode <= 127 && pos < 20)
                            {
                                text[pos] = (char)unicode;
                                pos++;
                            }
                            break;
                    }
                    break;
            }
        }
    }
    SDL_EnableUNICODE(0);
}

/*
 * explose une case
 * TODO ajouter l'image
 */

int exploseCase(t_case *case1, t_hero_list * hero_l)
{
    int resultat =0;
    t_hero_elem *hero_e = hero_l->first;
    for(int i = 0; i < hero_l->nb_elem; i++, hero_e = hero_e->next)
    {
        if (hero_e->hero->positionCase == case1){
            hero_e->hero->play = 0;
            resultat +=1;
        }
    }
    /*
    if (case1->type == 2)
        case1->type = 1;
    */
     return resultat;
}


/*
 * explose les cases autour de la case bombe
 */
void explose_bomb(t_bomb_elem *bomb_i_y,t_hero_list *heroes, t_case case_tab[WIDTH_MAP][HEIGHT_MAP])
{
    int debutX;
    int finX;
    if (bomb_i_y->bomb->positionCase->x > bomb_i_y->bomb->portee)
         debutX = bomb_i_y->bomb->positionCase->x - bomb_i_y->bomb->portee;
    else
        debutX = 1;
    if ((bomb_i_y->bomb->positionCase->x + bomb_i_y->bomb->portee) < WIDTH_MAP - 1)
        finX = bomb_i_y->bomb->positionCase->x + bomb_i_y->bomb->portee;
    else
        finX = WIDTH_MAP - 2;

    int debutY;
    int finY;
    if (bomb_i_y->bomb->positionCase->y > bomb_i_y->bomb->portee)
        debutY = bomb_i_y->bomb->positionCase->y - bomb_i_y->bomb->portee;
    else
        debutY = 1;
    if ((bomb_i_y->bomb->positionCase->y + bomb_i_y->bomb->portee) < HEIGHT_MAP -1)
        finY = bomb_i_y->bomb->positionCase->y + bomb_i_y->bomb->portee;
    else
        finY = HEIGHT_MAP - 2;

    int x = bomb_i_y->bomb->positionCase->x;
    int y = bomb_i_y->bomb->positionCase->y;

    //on nétoie le coté
    for (int i = debutX; i <= finX; i++)
    {
        exploseCase(&(case_tab[i][y]), heroes);
        if (i == debutX)
            //end left
            case_tab[i][y].type = 3;
        else if (i == finX)
            //end right
            case_tab[i][y].type = 4;
        else
            // horizontal
            case_tab[i][y].type = 6;
    }
    for (int i = debutY; i <= finY; i++)
    {
        exploseCase(&(case_tab[x][i]), heroes);
        if (i == debutY)
            //end Up
            case_tab[x][i].type = 7;
        else if (i == finY)
            //end Down
            case_tab[x][i].type = 8;
        else if(i != y)
            //vertical
            case_tab[x][i].type = 9;
    }
    //middle
    case_tab[x][y].type = 5;
}

/*
 * envoie l'initialisation au client
 */

void                set_env_to_client(t_env *env)
{
    t_simple_env *env_simple = env->simple_env;
    t_hero_elem *hero_elem = env->heroes->first;
    t_hero *hero;
    for (int i = 0; i < WIDTH_MAP; i++)
        for (int y = 0; y < HEIGHT_MAP; y++)
            env_simple->data_env->map[i][y] = env->map->case_tab[i][y].type;
    for(int i = 0; i < env->heroes->nb_elem && hero_elem && i < MAXHERO; i++)
    {
        hero = hero_elem->hero;
        env_simple->data_env->heroes[i].alive = hero->play;
        env_simple->data_env->heroes[i].direction = hero->direction;
        env_simple->data_env->heroes[i].orientation = hero->orientation;
        env_simple->data_env->heroes[i].numHero = hero->numHero;
        env_simple->data_env->heroes[i].score = hero->score;
        env_simple->data_env->heroes[i].x = hero->positionCase->x;
        env_simple->data_env->heroes[i].y = hero->positionCase->y;
        t_bomb_elem * bomb_elem = hero->bombes->first;
        for (int y =0; y < hero->bombes->nb_elem && bomb_elem && y < MAXBOMBES; y++)
        {
            t_bomb *bomb = bomb_elem->bomb;
            env_simple->data_env->heroes[i].bombes[y].x = bomb->positionCase->x;
            env_simple->data_env->heroes[i].bombes[y].y = bomb->positionCase->y;
            env_simple->data_env->heroes[i].bombes[y].chrono = bomb->chrono;
        }
        hero_elem = hero_elem->next;
    }
}

/*
 * le client recois les ino du server et les interprette
 */

void                get_env(t_env *env)
{
    t_hero_elem *hero_elem = env->heroes->first;
    t_hero *hero;
    for (int i=0; i < WIDTH_MAP; i++)
        for (int y = 0; y < HEIGHT_MAP; y++)
             env->map->case_tab[i][y].type = env->simple_env->data_env->map[i][y];
    for(int i = 0; i < env->heroes->nb_elem && hero_elem && i < MAXHERO; i++)
    {
        hero = hero_elem->hero;
        hero->play = env->simple_env->data_env->heroes[i].alive;
        hero->direction = env->simple_env->data_env->heroes[i].direction;
        hero->numHero = env->simple_env->data_env->heroes[i].numHero;
        hero->orientation = env->simple_env->data_env->heroes[i].orientation;
        hero->score = env->simple_env->data_env->heroes[i].score;
        for (int j=0; j < WIDTH_MAP; j++)
            for (int y = 0; y < HEIGHT_MAP; y++)
                    env->map->case_tab[j][y].type = env->simple_env->data_env->map[j][y];

        hero->positionCase = &(env->map->case_tab[env->simple_env->data_env->heroes[i].x][env->simple_env->data_env->heroes[i].y]);
        hero->position.x = hero->positionCase->position.x;
        hero->position.y = hero->positionCase->position.y;
        t_bomb_elem *bomb_elem = hero->bombes->first ;
        for (int y =0; y < hero->bombes->nb_elem && bomb_elem && y < MAXBOMBES; y++)
        {
            t_bomb *bomb = bomb_elem->bomb;
            bomb->positionCase = &(env->map->case_tab[env->simple_env->data_env->heroes[i].bombes->x][env->simple_env->data_env->heroes[i].bombes->y]);
            bomb->chrono = env->simple_env->data_env->heroes[i].bombes[y].chrono;
            bomb_elem = bomb_elem->next;
        }
        hero_elem = hero_elem->next;
    }
}


/*
 * lancement du serveret ouvertur des sockets
 */
void                launch_gameServer(t_env *env, SDL_Event *event) {
    env->heroes->first->hero->play = 1;
    init_game_resources(env);
    event->key.keysym.sym = 0;
    start_server(env->simple_env);
    while (env->heroes->first->hero->play) {
        SDL_PollEvent(event);
        SDL_Delay(100);

        pthread_mutex_lock(&(env->simple_env->mutexSend));
        set_env_to_client(env);
        pthread_mutex_unlock(&(env->simple_env->mutexSend));
        draw_Game(env);
        t_hero_elem *hero_i = env->heroes->first;
        for (; hero_i; hero_i = hero_i->next) {
            if (hero_i->hero->direction == -1)
            {
                if (hero_i->hero->numHero == env->hero)
                {
                    hero_order(hero_i->hero, event);
                }
                else
                {
                    pthread_mutex_lock(&(env->simple_env->mutexRecv));
                    other_order(hero_i->hero, env->simple_env->commande);
                    pthread_mutex_unlock(&(env->simple_env->mutexRecv));
                }
                collisionCase(hero_i->hero, env->map->case_tab);
            }
            if (finishedMovement(hero_i->hero)) {
                hero_i->hero->direction = -1;
            }
            else
                move_hero(hero_i->hero);
            t_bomb_elem *bomb_i_y = hero_i->hero->bombes->first;
            for (int y = 0; y < hero_i->hero->bombes->nb_elem; y++, bomb_i_y = bomb_i_y->next) {
                if ((SDL_GetTicks() - bomb_i_y->bomb->chrono) >= 2000 && (SDL_GetTicks() - bomb_i_y->bomb->chrono) < 3000) {
                    explose_bomb(bomb_i_y, env->heroes, env->map->case_tab);
                }
                else if ((SDL_GetTicks() - bomb_i_y->bomb->chrono) >= 3000)
                {
                    del_bomb(bomb_i_y, hero_i->hero->bombes, env->map);
                }
            }
            event->key.keysym.sym = 0;
        }
    }
}


/*
 * lancement du jeu pour un client
 */
void                launch_gameClient(t_env *env, SDL_Event *event) {
    int play = 1;
    init_game_resources(env);
    start_client(env->simple_env);
    event->key.keysym.sym = 0;
    while (env->heroes->first->next->hero->play) {
        SDL_PollEvent(event);

        pthread_mutex_lock(&(env->simple_env->mutexRecv));
        get_env(env);
        pthread_mutex_unlock(&(env->simple_env->mutexRecv));
        SDL_Delay(100);
        if (env->heroes != NULL && env->heroes->first != NULL)
        {
            draw_Game(env);
            pthread_mutex_lock(&(env->simple_env->mutexSend));
            env->simple_env->commande = event->key.keysym.sym;
            pthread_mutex_unlock(&(env->simple_env->mutexSend));
        }
    }
}

/*
 * fait bouger le curseur dans le menu
 */
void change_select(t_env *env) {
    if (env->screen->positionSelector.y == env->screen->positionSelectorBas.y)
        env->screen->positionSelector = env->screen->positionSelectorHaut;
    else
        env->screen->positionSelector = env->screen->positionSelectorBas;
}
