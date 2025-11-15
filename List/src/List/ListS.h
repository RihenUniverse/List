#ifndef LISTE_SIMPLE_H
#define LISTE_SIMPLE_H

#include <string>

/**
 * @brief Structure représentant un nœud de liste simplement chaînée
 */
typedef struct NoeudS {
    int donnee;           /**< Donnée stockée dans le nœud */
    struct NoeudS* suivant; /**< Pointeur vers le nœud suivant */
} NoeudS;

/**
 * @brief Structure représentant une liste simplement chaînée
 */
typedef struct {
    NoeudS* tete;         /**< Pointeur vers le premier nœud de la liste */
    NoeudS* queue;        /**< Pointeur vers le dernier nœud de la liste */
    int taille;           /**< Nombre d'éléments dans la liste */
    bool estCirculaire;   /**< Indique si la liste est circulaire */
    bool estAllouee;      // Nouveau flag pour suivre l'allocation
} ListeSimple;

// ============================================================================
// FONCTIONS DE CRÉATION ET DESTRUCTION
// ============================================================================

/**
 * @brief Crée une nouvelle liste vide
 * @return Pointeur vers la liste créée
 */
ListeSimple* AllocateSimple();

/**
 * @brief Crée une nouvelle liste vide
 * @return Liste dans le tast créée
 */
ListeSimple CreerSimple();

/**
 * @brief Crée un nouveau nœud avec la valeur spécifiée
 * @param valeur La valeur à stocker dans le nœud
 * @return Pointeur vers le nœud créé
 */
NoeudS* CreerNoeudS(int valeur);

/**
 * @brief Initialise une liste existante (vide ses données si nécessaire)
 * @param liste Pointeur vers la liste à initialiser
 */
void Initialiser(ListeSimple* liste);

/**
 * @brief Vide tous les éléments de la liste mais conserve la structure
 * @param liste Pointeur vers la liste à vider
 */
void Nettoyer(ListeSimple* liste);

/**
 * @brief Libère toute la mémoire occupée par la liste (nœuds + structure)
 * @param liste Pointeur vers la liste à détruire
 */
void Detruire(ListeSimple* liste);

// ============================================================================
// FONCTIONS D'INSERTION
// ============================================================================

/**
 * @brief Insère un élément au début de la liste
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à insérer
 */
void InsererDebut(ListeSimple* liste, int valeur);

/**
 * @brief Insère un élément à la fin de la liste
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à insérer
 */
void InsererFin(ListeSimple* liste, int valeur);

/**
 * @brief Insère un élément après un nœud donné
 * @param liste Pointeur vers la liste
 * @param precedent Pointeur vers le nœud après lequel insérer
 * @param valeur Valeur à insérer
 * @return true si l'insertion a réussi, false sinon
 */
bool InsererApres(ListeSimple* liste, NoeudS* precedent, int valeur);

/**
 * @brief Insère un élément avant un nœud donné
 * @param liste Pointeur vers la liste
 * @param suivant Pointeur vers le nœud avant lequel insérer
 * @param valeur Valeur à insérer
 * @return true si l'insertion a réussi, false sinon
 */
bool InsererAvant(ListeSimple* liste, NoeudS* suivant, int valeur);

/**
 * @brief Insère un élément à une position spécifique
 * @param liste Pointeur vers la liste
 * @param position Position où insérer (0-based)
 * @param valeur Valeur à insérer
 * @return true si l'insertion a réussi, false si position invalide
 */
bool InsererPosition(ListeSimple* liste, int position, int valeur);

/**
 * @brief Insère un élément dans une liste triée (maintenant l'ordre)
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à insérer
 */
void InsererTrie(ListeSimple* liste, int valeur);

// ============================================================================
// FONCTIONS DE SUPPRESSION
// ============================================================================

/**
 * @brief Supprime le premier élément de la liste
 * @param liste Pointeur vers la liste
 * @return true si la suppression a réussi, false si liste vide
 */
bool SupprimerDebut(ListeSimple* liste);

/**
 * @brief Supprime le dernier élément de la liste
 * @param liste Pointeur vers la liste
 * @return true si la suppression a réussi, false si liste vide
 */
bool SupprimerFin(ListeSimple* liste);

/**
 * @brief Supprime un nœud spécifique de la liste
 * @param liste Pointeur vers la liste
 * @param cible Pointeur vers le nœud à supprimer
 * @return true si la suppression a réussi, false si nœud non trouvé
 */
bool SupprimerNoeud(ListeSimple* liste, NoeudS* cible);

/**
 * @brief Supprime la première occurrence d'une valeur
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à supprimer
 * @return true si la suppression a réussi, false si valeur non trouvée
 */
bool SupprimerValeur(ListeSimple* liste, int valeur);

/**
 * @brief Supprime toutes les occurrences d'une valeur
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à supprimer
 * @return Nombre d'éléments supprimés
 */
int SupprimerToutesOccurrences(ListeSimple* liste, int valeur);

/**
 * @brief Supprime l'élément à une position spécifique
 * @param liste Pointeur vers la liste
 * @param position Position à supprimer (0-based)
 * @return true si la suppression a réussi, false si position invalide
 */
bool SupprimerPosition(ListeSimple* liste, int position);

// ============================================================================
// FONCTIONS DE RECHERCHE
// ============================================================================

/**
 * @brief Recherche la première occurrence d'une valeur
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à rechercher
 * @return Pointeur vers le nœud trouvé, ou NULL si non trouvé
 */
NoeudS* RechercherValeur(const ListeSimple* liste, int valeur);

/**
 * @brief Recherche toutes les occurrences d'une valeur
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à rechercher
 * @param count Pointeur pour stocker le nombre d'occurrences trouvées
 * @return Tableau de pointeurs vers les nœuds trouvés (terminé par NULL)
 */
NoeudS** RechercherToutesOccurrences(const ListeSimple* liste, int valeur, int* count);

/**
 * @brief Récupère le nœud à une position spécifique
 * @param liste Pointeur vers la liste
 * @param position Position souhaitée (0-based)
 * @return Pointeur vers le nœud, ou NULL si position invalide
 */
NoeudS* ObtenirNoeudPosition(const ListeSimple* liste, int position);

/**
 * @brief Trouve le nœud précédent un nœud donné
 * @param liste Pointeur vers la liste
 * @param cible Pointeur vers le nœud cible
 * @return Pointeur vers le nœud précédent, ou NULL si non trouvé
 */
NoeudS* TrouverPrecedent(const ListeSimple* liste, const NoeudS* cible);

// ============================================================================
// FONCTIONS D'INFORMATION
// ============================================================================

/**
 * @brief Convertit un nœud en représentation string
 * @param noeud Pointeur vers le nœud à convertir
 * @return Représentation string du nœud
 */
std::string ToString(const NoeudS* noeud);

/**
 * @brief Convertit une liste en représentation string
 * @param liste Pointeur vers la liste à convertir
 * @return Représentation string de la liste
 */
std::string ToString(const ListeSimple* liste);

/**
 * @brief Compte le nombre d'éléments dans la liste
 * @param liste Pointeur vers la liste
 * @return Nombre d'éléments
 */
int CompterElements(const ListeSimple* liste);

/**
 * @brief Vérifie si la liste est vide
 * @param liste Pointeur vers la liste
 * @return true si la liste est vide, false sinon
 */
bool EstVide(const ListeSimple* liste);

/**
 * @brief Vérifie si la liste contient un cycle (pour listes non circulaires)
 * @param liste Pointeur vers la liste
 * @return true si un cycle est détecté, false sinon
 */
bool ContientCycle(const ListeSimple* liste);

// ============================================================================
// FONCTIONS DE CONVERSION ET TRANSFORMATION
// ============================================================================

/**
 * @brief Convertit la liste en liste circulaire
 * @param liste Pointeur vers la liste
 */
void RendreCirculaire(ListeSimple* liste);

/**
 * @brief Convertit la liste circulaire en liste linéaire
 * @param liste Pointeur vers la liste
 */
void RendreLineaire(ListeSimple* liste);

/**
 * @brief Inverse l'ordre des éléments dans la liste
 * @param liste Pointeur vers la liste
 */
void Inverser(ListeSimple* liste);

/**
 * @brief Trie la liste en ordre croissant (algorithme au choix)
 * @param liste Pointeur vers la liste
 */
void Trier(ListeSimple* liste);

/**
 * @brief Copie une liste dans une nouvelle liste
 * @param liste Pointeur vers la liste source
 * @return Nouvelle liste copiée
 */
ListeSimple* Copier(const ListeSimple* liste);

/**
 * @brief Concatène deux listes (ajoute liste2 à la fin de liste1)
 * @param liste1 Première liste
 * @param liste2 Deuxième liste à ajouter
 */
void Concatener(ListeSimple* liste1, const ListeSimple* liste2);

/**
 * @brief Divise la liste en deux listes à une position spécifique
 * @param liste Liste à diviser
 * @param position Position de division
 * @param liste2 Nouvelle liste contenant les éléments après la position
 */
void Diviser(ListeSimple* liste, int position, ListeSimple* liste2);

// ============================================================================
// FONCTIONS UTILITAIRES AVANCÉES
// ============================================================================

/**
 * @brief Supprime les doublons dans une liste triée
 * @param liste Pointeur vers la liste
 */
void SupprimerDoublonsTries(ListeSimple* liste);

/**
 * @brief Supprime les doublons dans une liste non triée
 * @param liste Pointeur vers la liste
 */
void SupprimerDoublonsNonTries(ListeSimple* liste);

/**
 * @brief Fusionne deux listes triées en une seule liste triée
 * @param liste1 Première liste triée
 * @param liste2 Deuxième liste triée
 * @return Nouvelle liste fusionnée et triée
 */
ListeSimple* FusionnerListesTriees(const ListeSimple* liste1, const ListeSimple* liste2);

/**
 * @brief Trouve le milieu de la liste (algorithme du lièvre et de la tortue)
 * @param liste Pointeur vers la liste
 * @return Pointeur vers le nœud du milieu
 */
NoeudS* TrouverMilieu(const ListeSimple* liste);

/**
 * @brief Vérifie si la liste est un palindrome
 * @param liste Pointeur vers la liste
 * @return true si la liste est un palindrome, false sinon
 */
bool EstPalindrome(const ListeSimple* liste);

#endif