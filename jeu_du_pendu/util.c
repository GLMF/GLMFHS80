#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

#ifdef _WIN32
    #include <io.h>
#elif _WIN64
    #include <io.h>
#else
    #include <unistd.h>
#endif

#include "util.h"


/*******************
*                  *
*     Saisies      *
*                  *
*******************/


// Entiers

int saisir_entier(void)
{
    int entier;
    scanf("%d", &entier);
    return entier;
}


// Caractères

char saisir_caractere(void)
{
    char caractere;
    scanf("%c", &caractere);
    return caractere;
}


// Chaînes de caractères

char* saisir_chaine(void)
{
    // Saisie aléatoire (on considère que la longueux maximale d'un mot est de 32 caractères).
    char *saisie, *chaine;

    saisie = (char *) malloc(sizeof(char) * 32);
    scanf("%s", saisie);

    // On ne garde maintenant que la taille utile;
    chaine = (char *) malloc(sizeof(char) * (strlen(saisie) + 1));

    strcpy(chaine, saisie);

    return chaine;
}


/*******************
*                  *
*    Affichages    *
*                  *
*******************/


void afficher_chaine_masquee(const char * chaine, const char * trouves)
{
    int taille = strlen(chaine), i;
    for( i = 0 ; i < taille ; i++)
    {
        if (strchr(trouves, chaine[i]) == NULL)
        {
            printf("_");
        }
        else
        {
            printf("%c", chaine[i]);
        }
    }
    printf("\n");
}


/*******************
*     Travail      *
*       sur        *
*     chaines      *
*******************/


char caractere_dans_chaine(const char * chaine, const char caractere)
{
    if (strchr(chaine, caractere) == NULL)
    {
        return 0;
    }
    return 1;
}


char* chaine_vers_caracteres_uniques(const char * chaine)
{
    char *ensemble, *retour;

    // 26 lettres maxi dans l'alphabet.
    ensemble = (char *) malloc(sizeof(char) * 26);

    // On initialise l'ensemble à vide
    strcpy(ensemble, "");

    int taille = strlen(chaine), i;
    for (i = 0 ; i < taille ; i++)
    {
        if (strchr(ensemble, chaine[i]) == NULL)
        {
            // Le caractère de la chaîne n'est pas dans l'ensemble
            // Donc, on l'ajoute
            strncat(ensemble, &chaine[i], 1);
        }
    }

    // On ne garde maintenant que la taille utile;
    retour = (char *) malloc(sizeof(char) * (strlen(ensemble) + 1));

    strcpy(retour, ensemble);

    return retour;
}


/*******************
*                  *
*     Stockage     *
*                  *
*******************/


LISTE_MOT* lire_mots(const char *nom_fichier)
{
    // Préparation
    FILE *fp;
    char *content;
    char **mots;
    int resultat = 1, nombre_mots = 0;
    LISTE_MOT *liste_mots;

    content = (char *) malloc(sizeof(char) * 64);

    // ETAPE 1: mettre errno à 0 juste avant la fonction
    // Qui peut provoquer une erreur
    errno = 0;

    // Ouverture du fichier
    fp = fopen(nom_fichier, "r");

    if (fp == 0)
    {
        return NULL;
    }

    // Comptage du nombre de mots
    do {
        resultat = fscanf(fp, "%s", content);
        if (resultat != 1)
        {
            break;
        }
        nombre_mots ++;
    } while (1);

    // Fermeture du fichier
    fclose(fp );

    // Création d'un tableau
    mots = malloc(sizeof(*mots) * nombre_mots);

    // Vérifier la création
    if (mots == NULL)
    {
        return NULL; // TODO
    }

    nombre_mots = 0;

    // Seconde ouverture du fichier
    fp = fopen(nom_fichier, "r");

    // Remplissage du tableau de mots
    do {
        resultat = fscanf(fp, "%s", content);
        if (resultat != 1)
        {
            break;
        }
        // Création du mot dans le tableau
        mots[nombre_mots] = malloc(sizeof(char) * (strlen(content) + 1));
        strcpy(mots[nombre_mots], content);

        nombre_mots ++;
    } while (1);

    fclose(fp );

    // Renvoi de toutes les données
    liste_mots = malloc(sizeof(LISTE_MOT));
    liste_mots->mots = mots;
    liste_mots->nombre = nombre_mots;

    return liste_mots;
}

void rand_init(void)
{
    srand((unsigned) time(NULL));
}

void melanger_mots(LISTE_MOT * liste_mots)
{
    if (liste_mots == NULL)
    {
        return;
    }

    char **mots = liste_mots->mots;
    char *temp;
    int nombre = liste_mots->nombre,
        nombre_boucles = 2 * nombre + rand() % nombre,
        i,
        index1,
        index2;

    // Vérification du tableau de mots:
    for(i = 0; i < nombre_boucles ; i ++)
    {
        // Choisir un index dans le tableau
        index1 = rand() % nombre;
        // Choisir un autre index dans le tableau (forcément différent)
        do
        {
            index2 = rand() % nombre;
        } while (index1 == index2);

        // echanger les deux pointeurs du tableau
        //printf("echange entre %d et %d, soit %s et %s\n", index1, index2, mots[index1], mots[index2]);
        temp = mots[index1];
        mots[index1] = mots[index2];
        mots[index2] = temp;
    }

    return;
}


/*******************
*                  *
*    Arguments     *
*                  *
*******************/


LISTE_MOT* manage_arguments(int argc, char *argv[])
{
    LISTE_MOT *liste_mots = NULL;

    if ( argc > 2 )
    {
        // We print argv[0] assuming it is the program name
        printf( "usage: %s [filename]\n", argv[0] );
        exit(0);
    }

    if ( argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
        {
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
            char *erreur_message;
            erreur_message = malloc(sizeof(char) * 128);
            sprintf(erreur_message, "Une erreur s'est produite:\n> %s", argv[1]);
            perror(erreur_message);
            fprintf(stderr, "\nBasculement vers le mode deux joueurs.\n\n");
            return NULL;
        }
        melanger_mots(liste_mots);
        return liste_mots;
    }

    return NULL;
}


/*******************
*                  *
*      Scores      *
*                  *
*******************/


void ajouter_score(TABLEAU_SCORE *tableau, int nouveau_score_valeur, char *nom_joueur)
{
    // !!!
    // Meilleur score = score plus petit
    // !!!


    SCORE *score_avant = NULL, *score_apres = NULL, *nouveau_score;
/*    char *nom_joueur;

    nom_joueur = malloc(sizeof(char) * 33);
    printf("Votre nom: ");
    scanf("%s", nom_joueur);
    printf("\n");
*/
    // Créer le nouvel objet score
    nouveau_score = malloc(sizeof(SCORE));
    nouveau_score->valeur = nouveau_score_valeur;
    nouveau_score->inferieur = NULL;
    nouveau_score->superieur = NULL;
    nouveau_score->nom_joueur = nom_joueur;

    // Cas particulier: on est le tout premier score
    if (tableau->nombre_scores == 0) // VALIDE
    {
        //printf("Nouveau score: %d %p %p\n", nouveau_score->valeur, nouveau_score->inferieur, nouveau_score->superieur);
        tableau->dernier = nouveau_score;
        tableau->premier = nouveau_score;
        tableau->nombre_scores = 1;

        return;
    }

    // Le score est-il le meilleur score ?
    if (nouveau_score_valeur < tableau->premier->valeur) // VALIDE
    {
        // On stocke l'ancien meilleur score
        score_apres = tableau->premier;
        // On met à jour le tableau pour y mettre le nouveau meilleur score
        tableau->premier = nouveau_score;
        // On chaîne le nouveau meilleur score avec l'ancien
        nouveau_score->inferieur = score_apres;
        // On chaine l'ancien avec le nouveau
        score_apres->superieur = nouveau_score;
        // Mettre à jour le nombre de scores
        tableau->nombre_scores ++;
        // Supprimer le onzième score
        if (tableau->nombre_scores >= 10) {
            // Garder une copie de l'ancien dernier
            SCORE *old_score = tableau->dernier;
            // Mettre à jour le nouveau dernier dans le tableau
            tableau->dernier = old_score->superieur;
            // Mettre à jour le dernier score : il n'a plus d'inférieur
            tableau->dernier->inferieur = NULL;
            // Libérer l'espace mémoire du score supprimé
            free(old_score);
            tableau->nombre_scores --;
        }
        return;
    }

    // Sinon, le tableau a un dernier élément.
    score_avant = tableau->dernier;

    if (nouveau_score_valeur >= score_avant->valeur)
    {
        if (tableau->nombre_scores < 10)
        {

            score_avant->inferieur = nouveau_score;
            nouveau_score->superieur = score_avant;
            tableau->dernier = nouveau_score;
        }
        //Sinon, le tableau est plein et l'on n'a pas fait mieux (on retourne sans rien faire)

        // Mettre à jour le nombre de scores
        tableau->nombre_scores ++;
        return;
    }

    while (nouveau_score_valeur < score_avant->valeur)
    {

        //printf("Nouveau : %d, courant = %d (%p > %p > %p)\n", nouveau_score_valeur, score_avant->valeur, score_avant->inferieur, score_avant, score_avant->superieur);

        // On prend le score juste au dessus.
        score_avant = score_avant->superieur;
        //if (y >1) break;
        //y++;
        // Jamais nul, parce que l'on a déjà traité le cas hish score !
    }
    // A ce stade, nous avons trouvé le premier score égal ou meilleur que le nouveau score
    // On va donc reprendre le score juste en dessous.
    score_apres = score_avant->inferieur;

    //printf("TROUVE AVANT : %d (%p > %p > %p)\n", score_avant->valeur, score_avant->inferieur, score_avant, score_avant->superieur);
    //printf("TROUVE APRES : %d (%p > %p > %p)\n", score_apres->valeur, score_apres->inferieur, score_apres, score_apres->superieur);

    // Aucun NULL dans les 4 lignes qui suivent (géré avant)
    nouveau_score->inferieur = score_apres;
    score_apres->superieur = nouveau_score;
    nouveau_score->superieur = score_avant;
    score_avant->inferieur = nouveau_score;

    tableau->nombre_scores ++;

    if (tableau->nombre_scores >= 10) {
        // Garder une copie de l'ancien dernier
        SCORE *old_score = tableau->dernier;
        // Mettre à jour le nouveau dernier dans le tableau
        tableau->dernier = old_score->superieur;
        // Mettre à jour le dernier score : il n'a plus d'inférieur
        tableau->dernier->inferieur = NULL;
        // Libérer l'espace mémoire du score supprimé
        free(old_score);
        tableau->nombre_scores --;
    }

    return;
}

void afficher_tableau_score(TABLEAU_SCORE *tableau)
{

    SCORE *score_courant = tableau->premier;

    if (score_courant == NULL)
    {
        printf("Pas encore de scores enregistrés.\n\n");
        return;
    }

    printf("+---------------------------------+-----+\n");
    printf("| Joueur                          |Score|\n");
    printf("+---------------------------------+-----+\n");

    //printf("TABLEAU: premier = %p \n", score_courant);
    do
    {
        //printf("SCORE:  |%d|  %p > %p > %p \n", score_courant->valeur, score_courant->superieur, score_courant, score_courant->inferieur);

        printf("|%32s | %4d|\n", score_courant->nom_joueur, score_courant->valeur);
        //printf("|%32s ||\n", score_courant->nom_joueur);
        //printf("| | %4d|\n",  score_courant->valeur);

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

    //printf("TABLEAU: dernier = %p \n", score_courant);
    //printf("TABLEAU: dernier = %p \n", tableau->dernier);

    printf("+---------------------------------+-----+\n\n");

}


/*******************
*                  *
* Base de données  *
*                  *
*******************/


void db_create(const char *db_filename)
{
    sqlite3 *db;
    char *message_erreur = 0;
    int rc;
    char *sql;

    rc = sqlite3_open(db_filename, &db);

    if( rc ){
        fprintf(stderr,
                "Ouverture de la base de données %s impossible: %s\n",
                db_filename,
                sqlite3_errmsg(db));
        exit(1);
    }

    sql = "CREATE TABLE SCORE("  \
          "NIVEAU INTEGER NOT NULL," \
          "NOM    TEXT    NOT NULL," \
          "SCORE  INTEGER NOT NULL);";

    rc = sqlite3_exec(db, sql, NULL, 0, &message_erreur);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors de la création de la base de donnée %s: %s\n",
                db_filename,
                message_erreur);
        sqlite3_free(message_erreur);
    }

    sqlite3_close(db);

    return;
}

void db_set(const char *db_filename, int niveau, TABLEAU_SCORE *tableau)
{
    sqlite3 *db;
    int rc;
    SCORE *score_courant = tableau->premier;
    static char *base_sql = "INSERT INTO SCORE (NIVEAU, NOM, SCORE) VALUES (?, ?, ?);";
    static char *delete_sql = "DELETE FROM SCORE where niveau=?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_open(db_filename, &db);

    if( rc ){
        fprintf(stderr,
                "Ouverture de la base de données %s impossible: %s\n",
                db_filename,
                sqlite3_errmsg(db));
        exit(1);
    }

    // Préparation de la requête.
    rc = sqlite3_prepare(db, delete_sql, -1, &stmt, 0);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors de la préparation de la requête SQL %s pour la base de donnéee %s:\n",
                delete_sql,
                db_filename);
        exit(1);
    }

    // Bind des paramètres
    rc = sqlite3_bind_int(stmt, 1, niveau);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors du bind de %d à la requête %s pour la base de donnéee %s:\n",
                niveau,
                delete_sql,
                db_filename);
        exit(1);
    }

    // Exécution de la requête
    while (1)
    {
        rc = sqlite3_step(stmt);
        if( rc == SQLITE_DONE )
        {
            break;
        }
        else
        {
            fprintf(stderr,
                "Problème lors de la suppression des données de requête %s pour la base de donnéee %s:\n",
                delete_sql,
                db_filename);
            exit(1);
        }
    }

    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
    sqlite3_finalize(stmt);

    //
    // Seconde partie : inserts
    //

    if (score_courant == NULL)
    {
        return;
    }

    // Préparation de la requête.
    rc = sqlite3_prepare(db, base_sql, -1, &stmt, 0);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors de la préparation de la requête SQL %s pour la base de donnéee %s:\n",
                base_sql,
                db_filename);
        exit(1);
    }
    do
    {
        // Bind du paramètre 'niveau'
        rc = sqlite3_bind_int(stmt, 1, niveau);
        if( rc != SQLITE_OK ){
            fprintf(stderr,
                    "Problème lors du bind du niveau %d à la requête %s pour la base de donnéee %s:\n",
                    niveau,
                    base_sql,
                    db_filename);
            exit(1);
        }

        // Bind du paramètre 'nom'
        rc = sqlite3_bind_text(stmt, 2, score_courant->nom_joueur, strlen(score_courant->nom_joueur), SQLITE_STATIC);
        if( rc != SQLITE_OK ){
            fprintf(stderr,
                    "Problème lors du bind du nom du joueur %s à la requête %s pour la base de donnéee %s:\n",
                    score_courant->nom_joueur,
                    base_sql,
                    db_filename);
            exit(1);
        }

        // Bind du paramètre 'score'
        rc = sqlite3_bind_int(stmt, 3, score_courant->valeur);
        if( rc != SQLITE_OK ){
            fprintf(stderr,
                    "Problème lors du bind du score %d à la requête %s pour la base de donnéee %s:\n",
                    score_courant->valeur,
                    base_sql,
                    db_filename);
            exit(1);
        }

        // Exécution de la requête
        while (1)
        {
            rc = sqlite3_step(stmt);
            if( rc == SQLITE_DONE )
            {
                break;
            }
            else
            {
                fprintf(stderr,
                    "Problème lors de l'ajout des données de requête %s pour la base de donnéee %s:\n",
                    base_sql,
                    db_filename);
                exit(1);
            }
        }

        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);

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

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return;
}

TABLEAU_SCORE* db_get(const char *db_filename, int niveau)
{
    sqlite3 *db;
    int rc;
    static char *base_sql = "SELECT NOM, SCORE FROM SCORE WHERE NIVEAU = ? ORDER BY SCORE ASC LIMIT 10;";
    sqlite3_stmt *stmt;
    TABLEAU_SCORE *tableau_score;

    tableau_score = malloc(sizeof(TABLEAU_SCORE));
    tableau_score->premier = NULL;
    tableau_score->dernier = NULL;
    tableau_score->nombre_scores = 0;

    rc = sqlite3_open(db_filename, &db);

    if( rc ){
        fprintf(stderr,
                "Ouverture de la base de données %s impossible: %s\n",
                db_filename,
                sqlite3_errmsg(db));
        exit(1);
    }

    // Préparation de la requête.
    rc = sqlite3_prepare(db, base_sql, -1, &stmt, 0);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors de la préparation de la requête SQL %s pour la base de donnéee %s:\n",
                base_sql,
                db_filename);
        exit(1);
    }

    // Bind des paramètres
    rc = sqlite3_bind_int(stmt, 1, niveau);
    if( rc != SQLITE_OK ){
        fprintf(stderr,
                "Problème lors du bind de %d à la requête %s pour la base de donnéee %s:\n",
                niveau,
                base_sql,
                db_filename);
        exit(1);
    }

    // Exécution de la requête
    while (1)
    {
        rc = sqlite3_step(stmt);
        if( rc == SQLITE_DONE )
        {
            break;
        }
        else if( rc == SQLITE_ROW )
        {
            const char *nom;
            int valeur;

            nom  = (const char *)sqlite3_column_text (stmt, 0);
            valeur = sqlite3_column_int(stmt, 1);

            // Création du score
            SCORE *score;

            score = malloc(sizeof(SCORE));
            score->nom_joueur = malloc(sizeof(char) * (strlen(nom) + 1));
            strcpy(score->nom_joueur, nom);
            score->valeur = valeur;
            tableau_score->nombre_scores ++;

            if (tableau_score->premier == NULL)
            {
                score->inferieur = NULL;
                score->superieur = NULL;
                tableau_score->premier = score;
                tableau_score->dernier = score;
            }
            else
            {
                tableau_score->dernier->inferieur = score;
                score->superieur = tableau_score->dernier;
                tableau_score->dernier = score;
            }


        }
        else
        {
            fprintf(stderr,
                "Problème lors de la lecture des données de requête %s pour la base de donnéee %s:\n",
                base_sql,
                db_filename);
            exit(1);
        }
    }

    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);

    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return tableau_score;
}


/*******************
*     Système      *
*        de        *
*     fichiers     *
*******************/


void db_creer_si_existepas(const char *db_filename)
{
    if (access(db_filename, F_OK) == -1)
    {
        printf("Création d'une base de données vierge.\n");
        db_create(db_filename);
    }
}


/*******************
*                  *
*     Logique      *
*                  *
*******************/


short menu()
{
    int choix;

    printf("Voulez-vous:\n");
    printf("[1] Jouer une partie\n");
    printf("[2] Visualisez les meilleurs scores\n");
    printf("[3] Quitter le programme\n\n");

    do
    {
        printf("Votre choix: ");

        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
            case 2:
            case 3:
            {
                return choix;
            }
            default:
            {
                printf("Nous n'avons pas compris la réponse, merci de la saisir à nouveau.\n");
                break;
            }

        }
    }
    while (1);
}


short choisir_niveau()
{
    int choix;

    printf("Choisissez le niveau:\n");
    printf("[1] Rapide      3 mots\n");
    printf("[2] Medium      5 mots\n");
    printf("[3] Endurant   10 mots\n\n");

    do
    {
        printf("Votre choix: ");

        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
            {
                return 3;
            }
            case 2:
            {
                return 5;
            }
            case 3:
            {
                return 10;
            }
            default:
            {
                printf("Nous n'avons pas compris la réponse, merci de la saisir à nouveau.\n");
                break;
            }

        }
    }
    while (1);
}

char* demander_mot(void)
{
    char *mot, *a_trouver;
    int nb_a_trouver;

    // Déterminer le mot à trouver
    printf("Veuillez saisir le mot à trouver: ");
    mot = saisir_chaine();

    // Déterminer la liste des lettres à trouver
    a_trouver = chaine_vers_caracteres_uniques(mot);
    nb_a_trouver = strlen(a_trouver);

    printf("\nLe mot est : %s (%d)\n", mot, (int)strlen(mot));
    printf("Les lettres à trouver sont : %s (%d)\n", a_trouver, nb_a_trouver);

    // Faire en sorte que le second joueur ne voit pas la saisie.
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    return mot;
}

int jeu(const char *mot)
{
    char *a_trouver;
    char essayes[26] = {};
    char essai;
    int echecs = 0, nb_a_trouver, nb_trouves = 0;
    time_t temps_debut, temps_fin;

    // Déterminer la liste des lettres à trouver
    a_trouver = chaine_vers_caracteres_uniques(mot);
    nb_a_trouver = strlen(a_trouver);

    printf("A vous de jouer !\n\n");
    // Démarer le chronomètre
    time(&temps_debut);

    while(echecs < 12)
    {
        // Afficher le mot tel qu'on le connaît
        afficher_chaine_masquee(mot, essayes);

        // Demander un nouveau caractère (pas encore essayé)
        essai = 0;
        while (essai < 97 || essai > 122) {
            printf("\nTapez une lettre (dejà essayees %s): ", essayes);
            do
            {
                essai = saisir_caractere();
            }
            while (essai < 65);
            if (caractere_dans_chaine(essayes, essai))
            {
                essai = 0;
                printf("Ce caractère a déjà été essayé");
            }
        }

        // Le caractère est valide, on l'ajoute aux essais
        essayes[strlen(essayes)] = essai;

        // Valider le caractère ou non
        if (caractere_dans_chaine(mot, essai))
        {
            printf("Nouveau caractère trouvé !\n");
            nb_trouves ++;
            if (nb_trouves >= nb_a_trouver)
            {
                break;
            }
        }
        else {
            echecs ++; // On incrémente que les erreurs.
            printf("Ce caractère n'est pas contenu dans le mot mystère ! Erreur n°%d\n", echecs);
        }
    }

    // Arrêter le chronomètre
    time(&temps_fin);

    // Afficher le mot
    printf("\n\nLe mot était: %s\n", mot);

    // Afficher le temps passé
    printf("\n\nVous avez mis %.2f secondes\n", difftime(temps_fin, temps_debut));

    // Gérer le fait que le joueur ait gagné ou pas
    if (echecs == 12)
    {
        // On est allé au bout de la boucle d'itération: on a donc perdu !
        printf("Vous n'avez pas trouvé le mot: Malus de 5 minutes !");
        // Ajout d'un malus
        temps_fin += 300;
    }
    else
    {
        temps_fin += echecs;
        printf("Le mot est trouvé !");
    }

    printf("\n\n\n");

    return difftime(temps_fin, temps_debut);
}

void scores(TABLEAU_SCORE *tableau_scores_1, TABLEAU_SCORE *tableau_scores_2, TABLEAU_SCORE *tableau_scores_3)
{
    printf("Scores pour le niveau 1:\n");
    afficher_tableau_score(tableau_scores_1);
    printf("Scores pour le niveau 2:\n");
    afficher_tableau_score(tableau_scores_2);
    printf("Scores pour le niveau 3:\n");
    afficher_tableau_score(tableau_scores_3);

    return;
}
