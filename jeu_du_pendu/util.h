#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

/*******************
*                  *
*     Saisies      *
*                  *
*******************/


// Entiers

int saisir_entier(void);


// Caractères

char saisir_caractere(void);


// Chaînes de caractères

char * saisir_chaine(void);


/*******************
*                  *
*    Affichages    *
*                  *
*******************/


void afficher_chaine_masquee(const char * chaine, const char * trouves);


/*******************
*     Travail      *
*       sur        *
*     chaines      *
*******************/


char caractere_dans_chaine(const char * chaine, const char caractere);


char * chaine_vers_caracteres_uniques(const char * chaine);


/*******************
*                  *
*     Stockage     *
*                  *
*******************/


typedef struct _liste_mot
{
    char **mots;
    int nombre;
} LISTE_MOT;


LISTE_MOT * lire_mots(const char *nom_fichier);

void rand_init(void);

void melanger_mots(LISTE_MOT * liste_mots);


/*******************
*                  *
*    Arguments     *
*                  *
*******************/


LISTE_MOT *manage_arguments(int argc, char *argv[]);


/*******************
*                  *
*      Scores      *
*                  *
*******************/


typedef struct _score
{
    int valeur;
    char *nom_joueur;
    struct _score *superieur;
    struct _score *inferieur;
} SCORE;

typedef struct _tableau_score
{
    short nombre_scores;
    SCORE *premier;
    SCORE *dernier;
} TABLEAU_SCORE;

void ajouter_score(TABLEAU_SCORE *tableau, int nouveau_score_valeur, char *nom_joueur);

void afficher_tableau_score(TABLEAU_SCORE *tableau);


/*******************
*                  *
* Base de données  *
*                  *
*******************/


void db_create(const char *db_filename);

void db_set(const char *db_filename, int niveau, TABLEAU_SCORE *tableau);

TABLEAU_SCORE* db_get(const char *db_filename, int niveau);


/*******************
*     Système      *
*        de        *
*     fichiers     *
*******************/


void db_creer_si_existepas(const char *db_filename);


/*******************
*                  *
*     Logique      *
*                  *
*******************/


short menu();

short choisir_niveau();

char * demander_mot(void);

int jeu(const char *mot);

void scores(TABLEAU_SCORE *tableau_scores_1, TABLEAU_SCORE *tableau_scores_2, TABLEAU_SCORE *tableau_scores_3);

#endif // UTIL_H_INCLUDED
