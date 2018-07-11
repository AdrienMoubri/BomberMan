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
        env->play = 1;
        env->server = 0;
        env->client = 0;
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
    env->screen->text = TTF_RenderText_Blended(env->screen->police, "Press enter to start a game ", env->screen->couleurBomber);
    env->screen->rect_text_haut = TTF_RenderText_Blended(env->screen->police, "Here to play as Server ", env->screen->couleurBomber);
    env->screen->rect_text_bas = TTF_RenderText_Blended(env->screen->police, "Here to play as Client ", env->screen->couleurBomber);
    while (!play)
    {
        draw_Menu(env);
        SDL_WaitEvent(event);
        while (event->type != SDL_KEYUP && event->type != SDL_QUIT)
        {
            SDL_WaitEvent(event);
        }
        switch (event->key.keysym.sym)
        {
            case SDLK_RETURN:
                play = 1;
                env->hero = 0;
                break;
            case SDLK_ESCAPE:
                play = 2;
                env->play = 0;
            default:
                change_select(env);
                break;
        }
        if (event->type == SDL_QUIT )
        {
            play = 2;
            env->play = 0;
        }
    }
    char text[SIZE_IP];
    char nbPlayer;
    //initialise le tableau
    for (int i =0; i < SIZE_IP; i++)
    {
        text[i] = '\0';
    }
    size_t pos = 0;
    int unicode;
    SDL_EnableUNICODE(1);
    while (play==1)
    {
        if (env->screen->positionSelector.y == env->screen->positionSelectorBas.y)
        {
            env->screen->rect_text_haut = TTF_RenderText_Blended(env->screen->police, "Please enter your IP adress", env->screen->couleurBomber);
            env->screen->text = TTF_RenderText_Blended(env->screen->police, text, env->screen->couleurBomber);
        }
        else
        {
            env->screen->rect_text_haut = TTF_RenderText_Blended(env->screen->police, "Choose Number of player between 2 and 4 ", env->screen->couleurBomber);
            env->screen->text = TTF_RenderText_Blended(env->screen->police, text, env->screen->couleurBomber);
            env->server = 1;
        }
        draw_Menu(env);
        //création du server
        if (env->server == 1)
        {



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
                            env->simple_env->data_env->nb_hero = nbPlayer - '0';
                            env->screen->rect_text_haut = TTF_RenderText_Blended(env->screen->police, "Your IP  adress is : ", env->screen->couleurBomber);
                            env->screen->rect_text_bas = TTF_RenderText_Blended(env->screen->police, "You are waiting for players", env->screen->couleurBomber);
                            env->screen->text = TTF_RenderText_Blended(env->screen->police, get_ip(), env->screen->couleurBomber);
                            draw_Menu(env);
                            init_connect_to_client(env->simple_env);
                            SDL_WaitEvent(event);
                            play = 0;
                            break;
                        default:
                            unicode = event->key.keysym.unicode;
                            if (unicode == 8 && pos > 0)
                            {
                                nbPlayer = '\0';
                                pos--;
                            }
                            else
                            if (unicode >= 32 && unicode <= 127 && pos < 20)
                            {
                                nbPlayer = (char)unicode;
                                text [0]= nbPlayer;
                                pos++;
                            }
                            break;
                    }
                    break;
            }
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
                            env->simple_env->data_env->nb_hero=0;
                            init_connect_to_server(env->simple_env, text);
                            env->client=1;
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
        case1->type = 0;
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
    int debutY;
    int finY;
    int x;
    int y;

    if (bomb_i_y->bomb->positionCase->x > bomb_i_y->bomb->portee)
         debutX = bomb_i_y->bomb->positionCase->x - bomb_i_y->bomb->portee;
    else
        debutX = 1;
    if ((bomb_i_y->bomb->positionCase->x + bomb_i_y->bomb->portee) < WIDTH_MAP - 1)
        finX = bomb_i_y->bomb->positionCase->x + bomb_i_y->bomb->portee;
    else
        finX = WIDTH_MAP - 2;


    if (bomb_i_y->bomb->positionCase->y > bomb_i_y->bomb->portee)
        debutY = bomb_i_y->bomb->positionCase->y - bomb_i_y->bomb->portee;
    else
        debutY = 1;
    if ((bomb_i_y->bomb->positionCase->y + bomb_i_y->bomb->portee) < HEIGHT_MAP -1)
        finY = bomb_i_y->bomb->positionCase->y + bomb_i_y->bomb->portee;
    else
        finY = HEIGHT_MAP - 2;

    x = bomb_i_y->bomb->positionCase->x;
    y = bomb_i_y->bomb->positionCase->y;

    //on nétoie le coté

    for (int xi = x; xi >= debutX; xi--)
    {
        exploseCase(&(case_tab[xi][y]), heroes);
        if (case_tab[xi-1][y].type == 1 || xi == debutX)
        {
            //end left 3
            //on touche un mur
            case_tab[xi][y].type = 3;
            debutX = xi;
        }
        else
            // horizontal 6
            case_tab[xi][y].type = 6;
    }

    for (int xi = x; xi <= finX; xi++)
    {
        exploseCase(&(case_tab[xi][y]), heroes);
        if (case_tab[xi+1][y].type == 1 || xi == finX)
        {
            //end right 4
            //on touche un mur
            case_tab[xi][y].type = 4;
            finX = xi;
        }else
            // horizontal
            case_tab[xi][y].type = 6;
    }

    for (int yi = y; yi >= debutY; yi--)
    {
        exploseCase(&(case_tab[x][yi]), heroes);
        if (case_tab[x][yi-1].type == 1 || yi == debutY)
        {
            //end left 3
            //on touche un mur
            case_tab[x][yi].type = 7;
            debutY = yi;
        }
        else
            case_tab[x][yi].type = 9;
    }

    for (int yi = y; yi <= finY; yi++)
    {
        exploseCase(&(case_tab[x][yi]), heroes);
        if (case_tab[x][yi+1].type == 1 || yi == finY)
        {
            //end left 3
            //on touche un mur
            case_tab[x][yi].type = 8;
            finY = yi;
        }
        else
            case_tab[x][yi].type = 9;
    }
    //middle 5
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
 * le client reçois les info du server et les interprette
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
 * lancement du server et ouverture des sockets
 */
void                launch_gameServer(t_env *env, SDL_Event *event) {
    init_game_resources(env);
    start_server(env->simple_env);
    while (env->heroes->first->hero->play && event->type != SDL_QUIT) {
        SDL_PollEvent(event);
        SDL_Delay(100);
        pthread_mutex_lock(&(env->simple_env->mutexSend));
        set_env_to_client(env);
        pthread_mutex_unlock(&(env->simple_env->mutexSend));
        draw_Game(env);
        for (t_hero_elem *hero_i = env->heroes->first; hero_i; hero_i = hero_i->next) {
            if (hero_i->hero->direction == -1)
            {
                if (hero_i->hero->numHero == env->hero)
                {
                    hero_order(hero_i->hero, event);
                }
                else
                {
                    pthread_mutex_lock(&(env->simple_env->mutexRecv));
                    other_order(hero_i->hero, env->simple_env->commandes[hero_i->hero->numHero]);
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
    init_game_resources(env);
    start_client(env->simple_env);
    event->key.keysym.sym = 0;
    t_hero_elem *my_hero = env->heroes->first;
    while (my_hero != NULL && my_hero->hero->numHero != env->simple_env->data_env->num_hero)
        my_hero = my_hero->next;
    if (my_hero != NULL)
    {
        while (my_hero->hero->play && env->simple_env->commandeClient != SDLK_ESCAPE && event->type != SDL_QUIT ) {
            SDL_PollEvent(event);
            pthread_mutex_lock(&(env->simple_env->mutexRecv));
            get_env(env);
            pthread_mutex_unlock(&(env->simple_env->mutexRecv));
            SDL_Delay(100);
            if (env->heroes != NULL && env->heroes->first != NULL)
            {
                draw_Game(env);
                pthread_mutex_lock(&(env->simple_env->mutexSend));
                env->simple_env->commandeClient = event->key.keysym.sym;
                pthread_mutex_unlock(&(env->simple_env->mutexSend));
            }
            event->key.keysym.sym = 0;
        }
    }
    env->simple_env->commandeClient = 0;
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
