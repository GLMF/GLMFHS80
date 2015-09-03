#include <curses.h>

#include "util.h"

#ifndef IHM_H_INCLUDED
#define IHM_H_INCLUDED

typedef struct _fenetre_pendu
{
    short fenetre_hauteur,
          fenetre_largeur,
          fenetre_h0,
          fenetre_h1,
          fenetre_h2,
          fenetre_h3,
          fenetre_h4,
          fenetre_h5,
          fenetre_hauteur_2,
          fenetre_hauteur_3,
          fenetre_hauteur_4,
          fenetre_hauteur_5,
          fenetre_hauteur_6,
          fenetre_hauteur_7,
          fenetre_hauteur_8,
          fenetre_hauteur_9,
          fenetre_hauteur_10,
          fenetre_hauteur_11,
          fenetre_hauteur_12,
          fenetre_l0,
          pendu_l0,
          pendu_l4,
          pendu_l6,
          pendu_l7,
          pendu_l10,
          pendu_l11,
          pendu_l12,
          pendu_l13,
          pendu_l14,
          invite_hauteur,
          invite_largeur,
          menu_hauteur,
          menu_largeur,
          menu_niveau_h,
          menu_niveau_l0,
          menu_niveau_l1,
          menu_niveau_l2,
          menu_niveau_l3,
          menu_niveau_l4,
          menu_h0, menu_l0,
          menu_h1, menu_l1,
          menu_h2, menu_l2,
          menu_h3, menu_l3,
          menu_h4, menu_l4,
          menu_niveau_largeur,
          menu_niveau_largeur_chiffre,
          menu_niveau_hauteur,
          menu_niveau_hauteur_1,
          menu_niveau_hauteur_2,
          menu_niveau_hauteur_3,
          menu_demander_mot_largeur,
          menu_demander_mot_largeur_nombre,
          menu_demander_mot_largeur_lettres,
          menu_demander_mot_hauteur,
          menu_demander_mot_hauteur_invite,
          menu_demander_mot_hauteur_lettres,
          menu_demander_mot_hauteur_message,
          chaine_masquee_hauteur,
          chaine_masquee_largeur,
          tableau_score_largeur,
          erreurs_largeur;

} FENETRE_PENDU;


FENETRE_PENDU * fenetre;


void curses_init(void);

void curses_stop(void);

void init_fenetre(void);

void curses_fenetre_constantes(int signal);

short ecran_accueil(FENETRE_PENDU *fenetre);

short ecran_niveau(FENETRE_PENDU *fenetre);

char * ecran_demander_mot(FENETRE_PENDU *fenetre);

void ecran_afficher_chaine_masquee(FENETRE_PENDU *fenetre, const char * chaine, const char * trouves);

void ecran_afficher_chaine_reponse(FENETRE_PENDU *fenetre, const char * chaine, const char * trouves);

void ecran_afficher_pendu(FENETRE_PENDU *fenetre, short echecs);

int ecran_jeu(FENETRE_PENDU *fenetre, char *mot);

char * ecran_resultat(FENETRE_PENDU *fenetre, int score);

void ecran_scores(FENETRE_PENDU *fenetre, TABLEAU_SCORE *tableau1, TABLEAU_SCORE *tableau2, TABLEAU_SCORE *tableau3);

LISTE_MOT* curses_manage_arguments(FENETRE_PENDU *fenetre, int argc, char *argv[]);

#endif // IHM_H_INCLUDED
