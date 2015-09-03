#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#include <curses.h>

#include "ihm.h"

void curses_init(void)
{
    // Routine permettant d'initialiser curses
    initscr();

    // Désactiver le buffer au niveau du pilote TTY
    cbreak();

    // Supprime l'affichage automatique des caractères saisis
    noecho();

    // Permet la capture des touches spéciales telles que Backspace, Delete, F1, F2, ... et les touches directionnelles
    keypad(stdscr, TRUE);

    // Activer la gestion des couleurs
    if (has_colors() == TRUE)
    {
        start_color();
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
    }

}

void curses_stop(void)
{
    // Remet le terminal dans son état normal
    endwin();
}

void init_fenetre()
{
    fenetre = malloc(sizeof(FENETRE_PENDU));

    int sig_ok = signal(SIGWINCH, curses_fenetre_constantes);

    if (sig_ok == SIG_ERR)
    {
        clear();
        mvprintw(fenetre->fenetre_h0, fenetre->fenetre_l0, "Le gestionnaire de signal ne s'est pas initialisé.");
        mvprintw(fenetre->fenetre_h3, fenetre->fenetre_l0, "Le redimensionnement de la fenêtre ne sera pas pris en compte.");
        mvprintw(fenetre->fenetre_h5, fenetre->fenetre_l0, "Appuyez sur n'importe quelle touche pour continuer...");
        getch();
    }
}

void curses_fenetre_constantes(int signal)
{
    int h, l;
    getmaxyx(stdscr, h, l);

    fenetre->fenetre_hauteur = h - 1;
    fenetre->fenetre_largeur = l - 1;
    fenetre->fenetre_h0 = 0;
    fenetre->fenetre_h1 = 1;
    fenetre->fenetre_h2 = 2;
    fenetre->fenetre_h3 = 3;
    fenetre->fenetre_h4 = 4;
    fenetre->fenetre_h5 = 5;
    fenetre->fenetre_hauteur_2 = h - 2;
    fenetre->fenetre_hauteur_3 = h - 3;
    fenetre->fenetre_hauteur_4 = h - 4;
    fenetre->fenetre_hauteur_5 = h - 5;
    fenetre->fenetre_hauteur_6 = h - 6;
    fenetre->fenetre_hauteur_7 = h - 7;
    fenetre->fenetre_hauteur_8 = h - 8;
    fenetre->fenetre_hauteur_9 = h - 9;
    fenetre->fenetre_hauteur_10 = h - 10;
    fenetre->fenetre_hauteur_11 = h - 11;
    fenetre->fenetre_hauteur_12 = h - 12;
    fenetre->fenetre_l0 = 0;

    fenetre->pendu_l0 = (short) (l - 18) / 2;
    fenetre->pendu_l4 = fenetre->pendu_l0 + 4;
    fenetre->pendu_l6 = fenetre->pendu_l0 + 6;
    fenetre->pendu_l7 = fenetre->pendu_l0 + 7;
    fenetre->pendu_l10 = fenetre->pendu_l0 + 10;
    fenetre->pendu_l11 = fenetre->pendu_l0 + 11;
    fenetre->pendu_l12 = fenetre->pendu_l0 + 12;
    fenetre->pendu_l13 = fenetre->pendu_l0 + 13;
    fenetre->pendu_l14 = fenetre->pendu_l0 + 14;

    fenetre->menu_hauteur = 2;
    fenetre->menu_largeur = l;

    fenetre->invite_hauteur = (short)h / 4;
    fenetre->invite_largeur = (short) (l - 12) / 2;

    fenetre->menu_niveau_h = h - 1;
    fenetre->menu_niveau_l0 = (short) (l - 30) / 2;
    fenetre->menu_niveau_l1 = fenetre->menu_niveau_l0 + 9;
    fenetre->menu_niveau_l2 = fenetre->menu_niveau_l0 + 11;
    fenetre->menu_niveau_l3 = fenetre->menu_niveau_l0 + 20;
    fenetre->menu_niveau_l4 = fenetre->menu_niveau_l0 + 22;

    if (l >= 69)
    {
        fenetre->menu_h0 = h - 1;
        fenetre->menu_h1 = h - 1;
        fenetre->menu_h2 = h - 1;
        fenetre->menu_h3 = h - 1;
        fenetre->menu_h4 = h - 1;
        fenetre->menu_l0 = (short) (l - 69) / 2;
        fenetre->menu_l1 = fenetre->menu_l0 + 22;
        fenetre->menu_l2 = fenetre->menu_l0 + 24;
        fenetre->menu_l3 = fenetre->menu_l0 + 55;
        fenetre->menu_l4 = fenetre->menu_l0 + 57;
    }
    else
    {
        fenetre->menu_h0 = h - 2;
        fenetre->menu_h1 = h - 2;
        fenetre->menu_h2 = h - 1;
        fenetre->menu_h3 = h - 1;
        fenetre->menu_h4 = h - 1;
        fenetre->menu_l0 = (short) (l - 23) / 2;
        fenetre->menu_l1 = fenetre->menu_l0 + 22;
        fenetre->menu_l2 = (short) (l - 46) / 2;
        fenetre->menu_l3 = fenetre->menu_l2 + 21;
        fenetre->menu_l4 = fenetre->menu_l2 + 23;
    }

    fenetre->menu_niveau_largeur = (short) (l - 21) / 2;
    fenetre->menu_niveau_largeur_chiffre = fenetre->menu_niveau_largeur + 1;
    fenetre->menu_niveau_hauteur = (short)h / 4;
    fenetre->menu_niveau_hauteur_1 = fenetre->menu_niveau_hauteur + 1;
    fenetre->menu_niveau_hauteur_2 = fenetre->menu_niveau_hauteur + 2;
    fenetre->menu_niveau_hauteur_3 = fenetre->menu_niveau_hauteur + 3;

    fenetre->menu_demander_mot_largeur = (short) (l - 32) / 2;
    fenetre->menu_demander_mot_largeur_nombre = fenetre->menu_demander_mot_largeur + 4;
    fenetre->menu_demander_mot_largeur_lettres = fenetre->menu_demander_mot_largeur + 33;
    fenetre->menu_demander_mot_hauteur = (short)h / 4;
    fenetre->menu_demander_mot_hauteur_invite = fenetre->menu_demander_mot_hauteur  + 1;
    fenetre->menu_demander_mot_hauteur_lettres = fenetre->menu_demander_mot_hauteur  + 3;
    fenetre->menu_demander_mot_hauteur_message = fenetre->menu_demander_mot_hauteur  + 5;

    fenetre->chaine_masquee_hauteur = (short)h / 4 - 2,
    fenetre->chaine_masquee_largeur = (short) (l - 32) / 2;

    fenetre->tableau_score_largeur = (short)(l - 42) / 2;

    fenetre->erreurs_largeur = l - 12;
}

short ecran_accueil(FENETRE_PENDU *fenetre)
{
    char choix;

    clear();

    attron(A_BOLD);
    mvprintw(fenetre->invite_hauteur, fenetre->invite_largeur, "Jeu du Pendu");
    attroff(A_BOLD);

    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(fenetre->menu_h0, fenetre->menu_l0, "Jouer une partie (F1)");
    attroff(COLOR_PAIR(1));
    mvprintw(fenetre->menu_h1, fenetre->menu_l1, "|");
    attron(COLOR_PAIR(2));
    mvprintw(fenetre->menu_h2, fenetre->menu_l2, "Voir les meilleurs scores (F2)");
    attroff(COLOR_PAIR(2));
    mvprintw(fenetre->menu_h3, fenetre->menu_l3, "|");
    attron(COLOR_PAIR(3));
    mvprintw(fenetre->menu_h4, fenetre->menu_l4, "Quitter (F7)"); // 69
    attroff(A_BOLD | COLOR_PAIR(3));

    move(fenetre->fenetre_hauteur, fenetre->fenetre_largeur);

    refresh();

    while(1)
    {
        choix = getch();

        if (choix == KEY_F(1) || choix == '1')
        {
            return 1;
        }
        else if (choix == KEY_F(2) || choix == '2')
        {
            return 2;
        }
        else if (choix == KEY_F(7) || choix == '3')
        {
            return 3;
        }
	}
}



short ecran_niveau(FENETRE_PENDU *fenetre)
{
    char choix;

    clear();

    attron(A_BOLD);
    mvprintw(fenetre->menu_niveau_hauteur, fenetre->menu_niveau_largeur, "Choisissez le niveau:");
    attroff(A_BOLD);

    mvprintw(fenetre->menu_niveau_hauteur_1, fenetre->menu_niveau_largeur, "[ ] Rapide     3 mots");
    mvprintw(fenetre->menu_niveau_hauteur_2, fenetre->menu_niveau_largeur, "[ ] Medium     5 mots");
    mvprintw(fenetre->menu_niveau_hauteur_3, fenetre->menu_niveau_largeur, "[ ] Endurant  10 mots");

    attron(A_BOLD | COLOR_PAIR(3));
    mvprintw(fenetre->menu_niveau_hauteur_1, fenetre->menu_niveau_largeur_chiffre, "1");
    mvprintw(fenetre->menu_niveau_hauteur_2, fenetre->menu_niveau_largeur_chiffre, "2");
    mvprintw(fenetre->menu_niveau_hauteur_3, fenetre->menu_niveau_largeur_chiffre, "3");
    attroff(A_BOLD | COLOR_PAIR(3));

    move(fenetre->fenetre_hauteur, fenetre->fenetre_largeur);

    refresh();

    while(1)
    {
        choix = getch();

        if (choix == '1')
        {
            return 3;
        }
        else if (choix == '2')
        {
            return 5;
        }
        else if (choix == '3')
        {
            return 10;
        }
	}
}

char * ecran_demander_mot(FENETRE_PENDU *fenetre)
{
    char saisie[32];
    char *mot, *a_trouver;
    int nb_a_trouver;

    clear();

    attron(A_BOLD);
    mvprintw(fenetre->menu_demander_mot_hauteur, fenetre->menu_demander_mot_largeur, "Veuillez saisir le mot à trouver");
    attroff(A_BOLD);

    mvprintw(fenetre->menu_demander_mot_hauteur_invite, fenetre->menu_demander_mot_largeur, "> ");

    refresh();

    echo();
    getstr(saisie);
    noecho();

    // Créer le mot, avec le strict espace mémoire nécessaire
    mot = malloc(sizeof(char) * (strlen(saisie) + 1));
    strcpy(mot, saisie);

    // Déterminer la liste des lettres à trouver
    a_trouver = chaine_vers_caracteres_uniques(mot);
    nb_a_trouver = strlen(a_trouver);

    attron(A_BOLD);
    mvprintw(fenetre->menu_demander_mot_hauteur_lettres, fenetre->menu_demander_mot_largeur, "Les    lettres à trouver sont :", nb_a_trouver, a_trouver);
    attron(COLOR_PAIR(3));
    mvprintw(fenetre->menu_demander_mot_hauteur_lettres, fenetre->menu_demander_mot_largeur_nombre , "%02d", nb_a_trouver);
    mvprintw(fenetre->menu_demander_mot_hauteur_lettres, fenetre->menu_demander_mot_largeur_lettres, "%s", a_trouver);
    attroff(A_BOLD | COLOR_PAIR(3));

    mvprintw(fenetre->menu_demander_mot_hauteur_message, fenetre->menu_demander_mot_largeur, "Appuyez sur une touche pour continuer");

    move(fenetre->fenetre_hauteur, fenetre->fenetre_largeur);

    // Pause

    refresh();
    getch();

    return mot;

}

void ecran_afficher_chaine_masquee(FENETRE_PENDU *fenetre, const char * chaine, const char * trouves)
{
    attron(A_BOLD | COLOR_PAIR(1));

    int taille = strlen(chaine), i;
    for( i = 0 ; i < taille ; i++)
    {
        if (strchr(trouves, chaine[i]) == NULL)
        {
            mvprintw(fenetre->chaine_masquee_hauteur,
                     fenetre->chaine_masquee_largeur + i,
                     "_");
        }
        else
        {
            mvprintw(fenetre->chaine_masquee_hauteur,
                     fenetre->chaine_masquee_largeur + i,
                     "%c",
                     chaine[i]);
        }
    }

    attroff(A_BOLD | COLOR_PAIR(1));
}

void ecran_afficher_chaine_reponse(FENETRE_PENDU *fenetre, const char * chaine, const char * trouves)
{

    int taille = strlen(chaine), i;
    for( i = 0 ; i < taille ; i++)
    {
        if (strchr(trouves, chaine[i]) == NULL)
        {
            attron(A_BOLD | COLOR_PAIR(3));
            mvprintw(fenetre->chaine_masquee_hauteur,
                     fenetre->chaine_masquee_largeur + i,
                     "%c",
                     chaine[i]);
            attroff(A_BOLD | COLOR_PAIR(3));
        }
        else
        {
            attron(A_BOLD | COLOR_PAIR(1));
            mvprintw(fenetre->chaine_masquee_hauteur,
                     fenetre->chaine_masquee_largeur + i,
                     "%c",
                     chaine[i]);
            attroff(A_BOLD | COLOR_PAIR(1));
        }
    }

}

void ecran_afficher_pendu(FENETRE_PENDU *fenetre, short echecs)
{
    switch (echecs)
    {
        case 12:
        case 11:
        {
            mvprintw(fenetre->fenetre_hauteur_6, fenetre->pendu_l13, "\\");
            mvprintw(fenetre->fenetre_hauteur_5, fenetre->pendu_l14, "b");
        }
        case 10:
        {
            mvprintw(fenetre->fenetre_hauteur_6, fenetre->pendu_l11, "/");
            mvprintw(fenetre->fenetre_hauteur_5, fenetre->pendu_l10, "d");
        }
        case 9:
        {
            mvprintw(fenetre->fenetre_hauteur_8, fenetre->pendu_l13, "\\");
            mvprintw(fenetre->fenetre_hauteur_7, fenetre->pendu_l14, "'");
        }
        case 8:
        {
            mvprintw(fenetre->fenetre_hauteur_8, fenetre->pendu_l11, "/");
            mvprintw(fenetre->fenetre_hauteur_7, fenetre->pendu_l10, "'");
        }
        case 7:
        {
            mvprintw(fenetre->fenetre_hauteur_8, fenetre->pendu_l12, "|");
            mvprintw(fenetre->fenetre_hauteur_7, fenetre->pendu_l12, "|");
        }
        case 6:
        {
            mvprintw(fenetre->fenetre_hauteur_9, fenetre->pendu_l12, "O");
        }
        case 5:
        {
            mvprintw(fenetre->fenetre_hauteur_11, fenetre->pendu_l12, "|");
            mvprintw(fenetre->fenetre_hauteur_10, fenetre->pendu_l12, "|");
        }
        case 4:
        {
            mvprintw(fenetre->fenetre_hauteur_11, fenetre->pendu_l7, "/");
            mvprintw(fenetre->fenetre_hauteur_10, fenetre->pendu_l6, "/");
        }
        case 3:
        {
            mvprintw(fenetre->fenetre_hauteur_12, fenetre->pendu_l4, "==========");
        }
        case 2:
        {
            mvprintw(fenetre->fenetre_hauteur_5, fenetre->pendu_l4, "||");
            mvprintw(fenetre->fenetre_hauteur_6, fenetre->pendu_l4, "||");
            mvprintw(fenetre->fenetre_hauteur_7, fenetre->pendu_l4, "||");
            mvprintw(fenetre->fenetre_hauteur_8, fenetre->pendu_l4, "||");
            mvprintw(fenetre->fenetre_hauteur_9, fenetre->pendu_l4, "||");
            mvprintw(fenetre->fenetre_hauteur_10, fenetre->pendu_l4, "||");
            mvprintw(fenetre->fenetre_hauteur_11, fenetre->pendu_l4, "||");
        }
        case 1:
        {
            mvprintw(fenetre->fenetre_hauteur_4, fenetre->pendu_l0, "==================");
            mvprintw(fenetre->fenetre_hauteur_3, fenetre->pendu_l0, "XX              XX");
            mvprintw(fenetre->fenetre_hauteur_2, fenetre->pendu_l0, "XX              XX");
        }

    }

    if (echecs == 12)
    {
            mvprintw(fenetre->fenetre_hauteur_4, fenetre->pendu_l0, "==========     ===");
            mvprintw(fenetre->fenetre_hauteur_3, fenetre->pendu_l0, "XX         \\     XX");
            mvprintw(fenetre->fenetre_hauteur_2, fenetre->pendu_l0, "XX          \\    XX");
            mvprintw(fenetre->fenetre_hauteur_6, fenetre->pendu_l11, "| |"); // 12
            mvprintw(fenetre->fenetre_hauteur_5, fenetre->pendu_l10, " d b "); // 12
    }

}

int ecran_jeu(FENETRE_PENDU *fenetre, char *mot)
{
    char *a_trouver;
    char essayes[26] = {};
    char essai;
    int echecs = 0, nb_a_trouver, nb_trouves = 0;
    time_t temps_debut, temps_fin;

    a_trouver = chaine_vers_caracteres_uniques(mot);
    nb_a_trouver = strlen(a_trouver);

    clear();

    // Démarer le chronomètre
    time(&temps_debut);

    while(echecs < 12)
    {

        mvprintw(0, 0, "A vous de jouer !");
        mvprintw(0, fenetre->erreurs_largeur, "Erreurs: %02d", echecs);

        // Afficher le mot tel qu'on le connaît
        ecran_afficher_chaine_masquee(fenetre, mot, essayes);

        // Demander un nouveau caractère (pas encore essayé)
        essai = 0;

        attron(A_BOLD);
        mvprintw(fenetre->menu_demander_mot_hauteur, fenetre->menu_demander_mot_largeur, "Tapez une lettre (dejà essayees %s): ", essayes);
        attroff(A_BOLD);

        mvprintw(fenetre->menu_demander_mot_hauteur_invite, fenetre->menu_demander_mot_largeur, "> ");

        refresh();

        echo();

        while (essai < 97 || essai > 122) {

            do
            {
                  essai = getch();
            }
            while (essai < 65);

            if (caractere_dans_chaine(essayes, essai))
            {
                essai = 0;
                mvprintw(fenetre->menu_demander_mot_hauteur_lettres, fenetre->menu_demander_mot_largeur, "Ce caractère a déjà été essayé");
            }
        }

        noecho();

        clear();

        // Le caractère est valide, on l'ajoute aux essais
        essayes[strlen(essayes)] = essai;

        // Valider le caractère ou non
        if (caractere_dans_chaine(mot, essai))
        {
            mvprintw(fenetre->menu_demander_mot_hauteur_lettres, fenetre->menu_demander_mot_largeur, "Nouveau caractère trouvé !");
            nb_trouves ++;
            if (nb_trouves >= nb_a_trouver)
            {
                break;
            }
        }
        else {
            echecs ++; // On incrémente que les erreurs.
            mvprintw(fenetre->menu_demander_mot_hauteur_lettres, fenetre->menu_demander_mot_largeur, "%c n'est pas dans le mot mystère !", essai);
        }

        ecran_afficher_pendu(fenetre, echecs);

    }

    // Arrêter le chronomètre
    time(&temps_fin);

    // Afficher le temps passé
    mvprintw(fenetre->menu_demander_mot_hauteur, fenetre->menu_demander_mot_largeur, "Vous avez mis %.2f secondes", difftime(temps_fin, temps_debut));

    ecran_afficher_chaine_reponse(fenetre, mot, essayes);

    // Gérer le fait que le joueur ait gagné ou pas
    if (echecs == 12)
    {
        // On est allé au bout de la boucle d'itération: on a donc perdu !
        mvprintw(fenetre->menu_demander_mot_hauteur_invite, fenetre->menu_demander_mot_largeur, "Vous n'avez pas trouvé le mot: Malus de 5 minutes !");
        // Ajout d'un malus
        temps_fin += 300;
    }
    else
    {
        temps_fin += echecs;
        mvprintw(fenetre->menu_demander_mot_hauteur_invite, fenetre->menu_demander_mot_largeur, "Le mot est trouvé !");
    }

    mvprintw(fenetre->menu_demander_mot_hauteur_lettres, fenetre->menu_demander_mot_largeur, "Appuyez sur une touche pour continuer.");

    getch();

    return difftime(temps_fin, temps_debut);
}


char * ecran_resultat(FENETRE_PENDU *fenetre, int score)
{
    char saisie[32];
    char *nom_joueur;

    clear();

    attron(A_BOLD);
    mvprintw(fenetre->menu_demander_mot_hauteur, fenetre->menu_demander_mot_largeur, "Votre score total est %d", score);
    attroff(A_BOLD);

    mvprintw(fenetre->menu_demander_mot_hauteur_invite, fenetre->menu_demander_mot_largeur, "> ");

    refresh();

    echo();
    getstr(saisie);
    noecho();

    // Créer le mot, avec le strict espace mémoire nécessaire
    nom_joueur = malloc(sizeof(char) * (strlen(saisie) + 1));
    strcpy(nom_joueur, saisie);

    return nom_joueur;

}


void ecran_scores(FENETRE_PENDU *fenetre, TABLEAU_SCORE *tableau1, TABLEAU_SCORE *tableau2, TABLEAU_SCORE *tableau3)
{

    char choix = '1';
    int i;
    TABLEAU_SCORE *tableau = tableau1;
    SCORE *score_courant;

    while (1)
    {

        clear();

        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(fenetre->menu_niveau_h, fenetre->menu_niveau_l0, "NIVEAU 1");
        attroff(COLOR_PAIR(1));
        mvprintw(fenetre->menu_niveau_h, fenetre->menu_niveau_l1, "|");
        attron(COLOR_PAIR(2));
        mvprintw(fenetre->menu_niveau_h, fenetre->menu_niveau_l2, "NIVEAU 2");
        attroff(COLOR_PAIR(2));
        mvprintw(fenetre->menu_niveau_h, fenetre->menu_niveau_l3, "|");
        attron(COLOR_PAIR(3));
        mvprintw(fenetre->menu_niveau_h, fenetre->menu_niveau_l4, "NIVEAU 3");
        attroff(A_BOLD | COLOR_PAIR(3));

        score_courant = tableau->premier;
        i = 3;

        switch(choix)
        {
            case '1':
            {
                attron(COLOR_PAIR(1));
                break;
            }
            case '2':
            {
                attron(COLOR_PAIR(2));
                break;
            }
            case '3':
            {
                attron(COLOR_PAIR(3));
                break;
            }
        }

        if (score_courant == NULL)
        {
            mvprintw(1, fenetre->tableau_score_largeur, "Pas encore de scores enregistrés.");
        }
        else
        {
            mvprintw(fenetre->fenetre_h0, fenetre->tableau_score_largeur, "+---------------------------------+-----+");
            mvprintw(fenetre->fenetre_h1, fenetre->tableau_score_largeur, "| Joueur                          |Score|");
            mvprintw(fenetre->fenetre_h2, fenetre->tableau_score_largeur, "+---------------------------------+-----+");

            do
            {
                mvprintw(i, fenetre->tableau_score_largeur, "|%32s | %4d|\n", score_courant->nom_joueur, score_courant->valeur);
                i++;

                if (score_courant->inferieur != NULL)
                {
                    score_courant = score_courant->inferieur;
                }
                else
                {
                    break;
                }
            }
            while (1);

            mvprintw(i, fenetre->tableau_score_largeur, "+---------------------------------+-----+");
        }

        mvprintw(fenetre->fenetre_hauteur_5, fenetre->fenetre_l0, "Appuyez sur [1], [2] ou [3] pour changer de niveau.");
        mvprintw(fenetre->fenetre_hauteur_4, fenetre->fenetre_l0, "Appuyez sur une touche pour revenir au menu principal.");

        switch(choix)
        {
            case '1':
            {
                attroff(COLOR_PAIR(1));
                break;
            }
            case '2':
            {
                attroff(COLOR_PAIR(2));
                break;
            }
            case '3':
            {
                attroff(COLOR_PAIR(3));
                break;
            }
        }

        move(fenetre->fenetre_hauteur, fenetre->fenetre_largeur);

        refresh();

        choix = getch();

        if (choix == '1')
        {
            tableau = tableau1;
        }
        else if (choix == '2')
        {
            tableau = tableau2;
        }
        else if ( choix == '3')
        {
            tableau = tableau3;
        }
        else
        {
            return;
        }

    }

}

LISTE_MOT* curses_manage_arguments(FENETRE_PENDU *fenetre, int argc, char *argv[])
{
    LISTE_MOT *liste_mots = NULL;

    if ( argc > 2 )
    {
        // We print argv[0] assuming it is the program name
        curses_stop();
        printf( "usage: %s [filename]\n", argv[0] );
        exit(0);
    }

    if ( argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        {
            curses_stop();
            printf( "usage: %s [filename]\n\n", argv[0] );
            printf( "Pour jouer seul face à l'ordinateur:    %s fichier_dictionnaire.txt\n", argv[0] );
            printf( "Pour jouer à deux, l'un contre l'autre: %s\n", argv[0] );
            printf( "\nS. Chazallet pour Linux Magazine\n" );
            exit(0);
        }
        // We assume argv[1] is a filename to open
        liste_mots = lire_mots(argv[1]);

        if (errno != 0)
        {
            const char *erreur_label = strerror(errno);
            mvprintw(fenetre->fenetre_h0, fenetre->fenetre_l0, "Une erreur s'est produite dans le chargement du fichier %s: %s", argv[1], erreur_label);
            mvprintw(fenetre->fenetre_h3, fenetre->fenetre_l0, "Basculement vers le mode deux joueurs.");
            mvprintw(fenetre->fenetre_h5, fenetre->fenetre_l0, "Appuyez sur n'importe quelle touche pour continuer...");
            getch();
            return NULL;
        }
        melanger_mots(liste_mots);
        return liste_mots;
    }

    return NULL;
}
