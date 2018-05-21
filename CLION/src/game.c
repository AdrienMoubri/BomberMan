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
    env->socketInfo = 0;
    env->socketReponse= 0;
    //définition des port par défaut du server et du client
    int defaultportInfo = 4249;
    int defaultportResponse = 4250;
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
            if (env->socketInfo == 0) {
                create_Server(defaultportInfo, &(env->socketInfo));
                create_Server(defaultportResponse, &(env->socketReponse));
            }
            env->nb_heroes++;
            send_info_to_player(env->socketInfo, &(env->nb_heroes));
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
                            connect_to_Server(text,defaultportInfo,&(env->socketInfo));
                            SDL_Delay(10);
                            connect_to_Server(text,defaultportResponse,&(env->socketReponse));
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
    if (!env->server)
    {
        while(env->nb_heroes < 2)
            recv_info_from_server(env->socketInfo, &(env->nb_heroes));
        env->hero = env->nb_heroes -1;
    }
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
    if (case1->type == 2)
        case1->type = 1;
    return resultat;
}


/*
 * explose les cases autour de la case bombe
 */
void explose_bomb(t_bomb_elem *bomb_i_y,t_hero_list *heroes, t_case case_tab[WIDTH_MAP][HEIGHT_MAP])
{
    int debutX = bomb_i_y->bomb->positionCase->x - bomb_i_y->bomb->portee;
    int finX = bomb_i_y->bomb->positionCase->x + bomb_i_y->bomb->portee;

    int x = bomb_i_y->bomb->positionCase->x;
    int y = bomb_i_y->bomb->positionCase->y;

    int debutY = bomb_i_y->bomb->positionCase->y - bomb_i_y->bomb->portee;
    int finY = bomb_i_y->bomb->positionCase->y + bomb_i_y->bomb->portee;
    //on nétoie le coté
    for (int i = debutX; i < finX; i++)
    {
        exploseCase(&(case_tab[i][y]), heroes);
        if (i < x)
            case_tab[i][y].type = 5;
        else if(i == x)
            case_tab[i][y].type = 4;
        else if(i > x)
            case_tab[i][y].type = 6;
    }
    for (int i = debutY; i < finY; i++)
    {
        exploseCase(&(case_tab[x][i]), heroes);
        if (i < y)
            case_tab[x][i].type = 2;
        else if (i == y)
            case_tab[x][i].type = 4;
        else if (i > y)
            case_tab[x][i].type = 3;
    }
}

/*
 * envoie l'initialisation au client
 */

void                set_env_to_client(t_env *env)
{
    t_simple_env *env_simple = malloc(sizeof(t_simple_env));
    t_hero_elem *hero_elem = env->heroes->first;
    t_hero *hero;
    for (int i=0; i < WIDTH_MAP; i++)
        for (int y = 0; y < HEIGHT_MAP; y++)
            env_simple->map[i][y] = env->map->case_tab[i][y].type;
    for(int i = 0; i < env->heroes->nb_elem && hero_elem && i < MAXHERO; i++)
    {
        hero = hero_elem->hero;
        env_simple->heroes[i].alive = hero->play;
        env_simple->heroes[i].direction = hero->direction;
        env_simple->heroes[i].orientation = hero->orientation;
        env_simple->heroes[i].numHero = hero->numHero;
        env_simple->heroes[i].score = hero->score;
        env_simple->heroes[i].x = hero->positionCase->x;
        env_simple->heroes[i].y = hero->positionCase->y;
        t_bomb_elem * bomb_elem = hero->bombes->first;
        for (int y =0; y < hero->bombes->nb_elem && bomb_elem && y < MAXBOMBES; y++)
        {
            t_bomb *bomb = bomb_elem->bomb;
            env_simple->heroes[i].bombes[y].x = bomb->positionCase->x;
            env_simple->heroes[i].bombes[y].y = bomb->positionCase->y;
            env_simple->heroes[i].bombes[y].chrono = bomb->chrono;
        }
        hero_elem = hero_elem->next;
    }
    send_env_to_player(env->socketInfo,env->socketReponse, env_simple);
}

/*
 * le client recois les ino du server et les interprette
 */

void                get_env(t_env *env)
{
    t_simple_env *env_simple = malloc(sizeof(t_simple_env));
    recv_env_from_server(env->socketInfo,env->socketReponse, env_simple);
    t_hero_elem *hero_elem = env->heroes->first;
    t_hero *hero;
    for (int i=0; i < WIDTH_MAP; i++)
        for (int y = 0; y < HEIGHT_MAP; y++)
            env_simple->map[i][y] = env->map->case_tab[i][y].type;
    for(int i = 0; i < env->heroes->nb_elem && hero_elem && i < MAXHERO; i++)
    {
        hero = hero_elem->hero;
        hero->play = env_simple->heroes[i].alive;
        hero->direction = env_simple->heroes[i].direction;
        hero->numHero = env_simple->heroes[i].numHero;
        hero->orientation = env_simple->heroes[i].orientation;
        hero->score = env_simple->heroes[i].score;
/*
        for (int j=0; j < WIDTH_MAP; j++)
            for (int y = 0; y < HEIGHT_MAP; y++)
                if (env_simple->heroes[i].x == env->map->case_tab[j][y].x && env_simple->heroes[i].y == env->map->case_tab[j][y].y)
                    hero->positionCase = &(env->map->case_tab[j][y]);*/

        hero->positionCase = &(env->map->case_tab[env_simple->heroes[i].x][env_simple->heroes[i].y]);
        hero->position.x = hero->positionCase->position.x;
        hero->position.y = hero->positionCase->position.y;
        t_bomb_elem *bomb_elem = hero->bombes->first ;
        for (int y =0; y < hero->bombes->nb_elem && bomb_elem && y < MAXBOMBES; y++)
        {
            t_bomb *bomb = bomb_elem->bomb;

            bomb->positionCase = &(env->map->case_tab[env_simple->heroes[i].bombes->x][env_simple->heroes[i].bombes->y]);

            /*
            for (int j=0; j < WIDTH_MAP; j++)
                for (int k = 0; k < HEIGHT_MAP; k++)
                    if (env_simple->heroes[i].bombes[j].x == env->map->case_tab[j][k].x && env_simple->heroes[i].bombes[j].x == env->map->case_tab[j][k].y)
                        bomb->positionCase = &(env->map->case_tab[j][k]);*/
            bomb->coord = bomb->positionCase->position;
            bomb->chrono = env_simple->heroes[i].bombes[y].chrono;
            bomb_elem = bomb_elem->next;
        }
        hero_elem = hero_elem->next;
    }
}

/*
 * envoie les actions du hero client au server
 */

void                set_hero_to_server(t_env *env)
{
    t_hero *hero;
    t_hero_elem * hero_elem = env->heroes->first->next;
    /*for (int i = 0; i < MAXHERO && hero_elem->hero->numHero != env->hero; i++)
    {
        hero_elem = hero_elem->next;
    }*/
    hero = hero_elem->hero;
    t_hero_simple *hero_simple = malloc(sizeof(t_hero_simple));
    //hero_simple->x = hero->positionCase->x;
    //hero_simple->y = hero->positionCase->y;
    hero_simple->numHero = hero->numHero;
    hero_simple->direction = hero->direction;
    hero_simple->orientation = hero->orientation;
    hero_simple->alive = hero->play;
    t_bomb_elem *bomb_elem= hero->bombes->first;
    for (int i =0; i < hero->bombes->nb_elem && i < MAXBOMBES; i++)
    {
        t_bomb *bomb = bomb_elem->bomb;
        hero_simple->bombes[i].x = bomb->positionCase->x;
        hero_simple->bombes[i].y = bomb->positionCase->y;
        hero_simple->bombes[i].chrono = bomb->chrono;
    }
    send_player_to_server(env->socketInfo,env->socketReponse, hero_simple);
}

/*
 * le server reçois les infos client
 */

void                get_hero_from_client(t_env* env)
{
    t_hero *hero;
    t_hero_elem * hero_elem = env->heroes->first->next;
    //for(int i = 0; i < env->heroes->nb_elem && hero_elem->hero->numHero == i; i++, hero_elem = hero_elem->next);
    hero = hero_elem->hero;
    t_hero_simple *hero_simple = malloc(sizeof(t_hero_simple));
    recv_player_from_player(env->socketInfo,env->socketReponse, hero_simple);
    //hero->positionCase  = &(env->map->case_tab[hero_simple->x][hero_simple->y]);
    //hero->position.x  =    hero->positionCase->position.x;
    //hero->position.y  =    hero->positionCase->position.y;
    hero->direction =hero_simple->direction ;
    hero->orientation =hero_simple->orientation ;
    hero->play =hero_simple->alive ;
    t_bomb_elem *bomb_elem = hero->bombes->first;
    for (int i = 0; i < hero->bombes->nb_elem && i < MAXBOMBES; i++) {
        t_bomb *bomb = bomb_elem->bomb;
        bomb->positionCase = &(env->map->case_tab[hero_simple->bombes[i].x][hero_simple->bombes[i].y]);
        bomb->chrono =hero_simple->bombes[i].chrono ;
    }
}


/*
 * lancement du serveret ouvertur des sockets
 */
void                launch_gameServer(t_env *env, SDL_Event *event) {
    int play = 1;
    init_game_resources(env);
    event->key.keysym.sym = 0;
    while (play) {
        SDL_PollEvent(event);
        SDL_Delay(100);
        set_env_to_client(env);
        draw_Game(env);
        t_hero_elem *hero_i = env->heroes->first;
        for (; hero_i; hero_i = hero_i->next) {
            if (hero_i->hero->direction == -1)
            {
                if (hero_i->hero->numHero == env->hero)
                {
                    hero_order(hero_i->hero, event);
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
                if ((SDL_GetTicks() - bomb_i_y->bomb->chrono) >= 2000) {
                    my_putstr("la bombe à explosé");
                    explose_bomb(bomb_i_y, env->heroes, env->map->case_tab);
                    del_bomb_from_list(bomb_i_y, hero_i->hero->bombes);
                }
            }
            //get_hero_from_client(env);
        }
    }
}


/*
 * lancement du jeu pour un client
 */
void                launch_gameClient(t_env *env, SDL_Event *event) {
    int play = 1;
    init_game_resources(env);
    event->key.keysym.sym = 0;
    while (play) {
        SDL_PollEvent(event);
        get_env(env);
        SDL_Delay(100);
        draw_Game(env);
        t_hero_elem *hero_i = env->heroes->first->next;
        hero_order(hero_i->hero, event);
        //set_hero_to_server(env);
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
