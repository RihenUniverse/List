#ifndef LISTE_DOUBLE_H
#define LISTE_DOUBLE_H

#include <string>

/**
 * @brief Structure représentant un nœud de liste doublement chaînée
 */
typedef struct NoeudD {
    int donnee;             /**< Donnée stockée dans le nœud */
    struct NoeudD* precedent; /**< Pointeur vers le nœud précédent */
    struct NoeudD* suivant;   /**< Pointeur vers le nœud suivant */
} NoeudD;

/**
 * @brief Structure représentant une liste doublement chaînée
 */
typedef struct {
    NoeudD* tete;          /**< Pointeur vers le premier nœud de la liste */
    NoeudD* queue;         /**< Pointeur vers le dernier nœud de la liste */
    int taille;            /**< Nombre d'éléments dans la liste */
    bool estCirculaire;    /**< Indique si la liste est circulaire */
} ListeDouble;

// ============================================================================
// FONCTIONS DE CRÉATION ET DESTRUCTION
// ============================================================================

/**
 * @brief Crée une nouvelle liste double vide
 * @return Pointeur vers la liste créée
 */
ListeDouble* AllocateDouble();

/**
 * @brief Crée une nouvelle liste double vide
 * @return Liste dans le tast créée
 */
ListeDouble CreerDouble();

/**
 * @brief Crée un nouveau nœud double avec la valeur spécifiée
 * @param valeur La valeur à stocker dans le nœud
 * @return Pointeur vers le nœud créé
 */
NoeudD* CreerNoeudD(int valeur);

/**
 * @brief Initialise une liste double existante (vide ses données si nécessaire)
 * @param liste Pointeur vers la liste à initialiser
 */
void Initialiser(ListeDouble* liste);

/**
 * @brief Vide tous les éléments de la liste mais conserve la structure
 * @param liste Pointeur vers la liste à vider
 */
void Nettoyer(ListeDouble* liste);

/**
 * @brief Libère toute la mémoire occupée par la liste double (nœuds + structure)
 * @param liste Pointeur vers la liste à détruire
 */
void Detruire(ListeDouble* liste);

// ============================================================================
// FONCTIONS D'INSERTION
// ============================================================================

/**
 * @brief Insère un élément au début de la liste double
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à insérer
 */
void InsererDebut(ListeDouble* liste, int valeur);

/**
 * @brief Insère un élément à la fin de la liste double
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à insérer
 */
void InsererFin(ListeDouble* liste, int valeur);

/**
 * @brief Insère un élément avant un nœud donné
 * @param liste Pointeur vers la liste
 * @param suivant Pointeur vers le nœud avant lequel insérer
 * @param valeur Valeur à insérer
 * @return true si l'insertion a réussi, false sinon
 */
bool InsererAvant(ListeDouble* liste, NoeudD* suivant, int valeur);

/**
 * @brief Insère un élément après un nœud donné
 * @param liste Pointeur vers la liste
 * @param precedent Pointeur vers le nœud après lequel insérer
 * @param valeur Valeur à insérer
 * @return true si l'insertion a réussi, false sinon
 */
bool InsererApres(ListeDouble* liste, NoeudD* precedent, int valeur);

/**
 * @brief Insère un élément à une position spécifique
 * @param liste Pointeur vers la liste
 * @param position Position où insérer (0-based)
 * @param valeur Valeur à insérer
 * @return true si l'insertion a réussi, false si position invalide
 */
bool InsererPosition(ListeDouble* liste, int position, int valeur);

/**
 * @brief Insère un élément dans une liste double triée (maintenant l'ordre)
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à insérer
 */
void InsererTrie(ListeDouble* liste, int valeur);

// ============================================================================
// FONCTIONS DE SUPPRESSION
// ============================================================================

/**
 * @brief Supprime le premier élément de la liste double
 * @param liste Pointeur vers la liste
 * @return true si la suppression a réussi, false si liste vide
 */
bool SupprimerDebut(ListeDouble* liste);

/**
 * @brief Supprime le dernier élément de la liste double
 * @param liste Pointeur vers la liste
 * @return true si la suppression a réussi, false si liste vide
 */
bool SupprimerFin(ListeDouble* liste);

/**
 * @brief Supprime un nœud spécifique de la liste double
 * @param liste Pointeur vers la liste
 * @param cible Pointeur vers le nœud à supprimer
 * @return true si la suppression a réussi, false si nœud non trouvé
 */
bool SupprimerNoeud(ListeDouble* liste, NoeudD* cible);

/**
 * @brief Supprime la première occurrence d'une valeur
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à supprimer
 * @return true si la suppression a réussi, false si valeur non trouvée
 */
bool SupprimerValeur(ListeDouble* liste, int valeur);

/**
 * @brief Supprime toutes les occurrences d'une valeur
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à supprimer
 * @return Nombre d'éléments supprimés
 */
int SupprimerToutesOccurrences(ListeDouble* liste, int valeur);

/**
 * @brief Supprime l'élément à une position spécifique
 * @param liste Pointeur vers la liste
 * @param position Position à supprimer (0-based)
 * @return true si la suppression a réussi, false si position invalide
 */
bool SupprimerPosition(ListeDouble* liste, int position);

// ============================================================================
// FONCTIONS DE RECHERCHE
// ============================================================================

/**
 * @brief Recherche la première occurrence d'une valeur
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à rechercher
 * @return Pointeur vers le nœud trouvé, ou NULL si non trouvé
 */
NoeudD* RechercherValeur(const ListeDouble* liste, int valeur);

/**
 * @brief Recherche toutes les occurrences d'une valeur
 * @param liste Pointeur vers la liste
 * @param valeur Valeur à rechercher
 * @param count Pointeur pour stocker le nombre d'occurrences trouvées
 * @return Tableau de pointeurs vers les nœuds trouvés (terminé par NULL)
 */
NoeudD** RechercherToutesOccurrences(const ListeDouble* liste, int valeur, int* count);

/**
 * @brief Récupère le nœud à une position spécifique (depuis le début)
 * @param liste Pointeur vers la liste
 * @param position Position souhaitée (0-based)
 * @return Pointeur vers le nœud, ou NULL si position invalide
 */
NoeudD* ObtenirNoeudPosition(const ListeDouble* liste, int position);

/**
 * @brief Récupère le nœud à une position spécifique (depuis la fin)
 * @param liste Pointeur vers la liste
 * @param position Position depuis la fin (0-based, 0 = dernier)
 * @return Pointeur vers le nœud, ou NULL si position invalide
 */
NoeudD* ObtenirNoeudPositionInverse(const ListeDouble* liste, int position);

// ============================================================================
// FONCTIONS D'INFORMATION
// ============================================================================

/**
 * @brief Convertit un nœud double en représentation string
 * @param noeud Pointeur vers le nœud à convertir
 * @return Représentation string du nœud
 */
std::string ToString(const NoeudD* noeud);

/**
 * @brief Convertit une liste double en représentation string
 * @param liste Pointeur vers la liste à convertir
 * @return Représentation string de la liste
 */
std::string ToString(const ListeDouble* liste);

/**
 * @brief Compte le nombre d'éléments dans la liste double
 * @param liste Pointeur vers la liste
 * @return Nombre d'éléments
 */
int CompterElements(const ListeDouble* liste);

/**
 * @brief Vérifie si la liste double est vide
 * @param liste Pointeur vers la liste
 * @return true si la liste est vide, false sinon
 */
bool EstVide(const ListeDouble* liste);

/**
 * @brief Vérifie si la liste contient un cycle (pour listes non circulaires)
 * @param liste Pointeur vers la liste
 * @return true si un cycle est détecté, false sinon
 */
bool ContientCycle(const ListeDouble* liste);

// ============================================================================
// FONCTIONS DE CONVERSION ET TRANSFORMATION
// ============================================================================

/**
 * @brief Convertit la liste double en liste circulaire
 * @param liste Pointeur vers la liste
 */
void RendreCirculaire(ListeDouble* liste);

/**
 * @brief Convertit la liste circulaire double en liste linéaire
 * @param liste Pointeur vers la liste
 */
void RendreLineaire(ListeDouble* liste);

/**
 * @brief Inverse l'ordre des éléments dans la liste double
 * @param liste Pointeur vers la liste
 */
void Inverser(ListeDouble* liste);

/**
 * @brief Trie la liste double en ordre croissant
 * @param liste Pointeur vers la liste
 */
void Trier(ListeDouble* liste);

/**
 * @brief Copie une liste double dans une nouvelle liste
 * @param liste Pointeur vers la liste source
 * @return Nouvelle liste copiée
 */
ListeDouble* Copier(const ListeDouble* liste);

/**
 * @brief Concatène deux listes doubles (ajoute liste2 à la fin de liste1)
 * @param liste1 Première liste
 * @param liste2 Deuxième liste à ajouter
 */
void Concatener(ListeDouble* liste1, const ListeDouble* liste2);

/**
 * @brief Divise la liste double en deux listes à une position spécifique
 * @param liste Liste à diviser
 * @param position Position de division
 * @param liste2 Nouvelle liste contenant les éléments après la position
 */
void Diviser(ListeDouble* liste, int position, ListeDouble* liste2);

// ============================================================================
// FONCTIONS UTILITAIRES AVANCÉES
// ============================================================================

/**
 * @brief Supprime les doublons dans une liste double triée
 * @param liste Pointeur vers la liste
 */
void SupprimerDoublonsTries(ListeDouble* liste);

/**
 * @brief Supprime les doublons dans une liste double non triée
 * @param liste Pointeur vers la liste
 */
void SupprimerDoublonsNonTries(ListeDouble* liste);

/**
 * @brief Fusionne deux listes doubles triées en une seule liste triée
 * @param liste1 Première liste triée
 * @param liste2 Deuxième liste triée
 * @return Nouvelle liste fusionnée et triée
 */
ListeDouble* FusionnerListesTriees(const ListeDouble* liste1, const ListeDouble* liste2);

/**
 * @brief Trouve le milieu de la liste double
 * @param liste Pointeur vers la liste
 * @return Pointeur vers le nœud du milieu
 */
NoeudD* TrouverMilieu(const ListeDouble* liste);

/**
 * @brief Vérifie si la liste double est un palindrome
 * @param liste Pointeur vers la liste
 * @return true si la liste est un palindrome, false sinon
 */
bool EstPalindrome(const ListeDouble* liste);

/**
 * @brief Échange deux nœuds dans la liste double
 * @param liste Pointeur vers la liste
 * @param noeud1 Premier nœud à échanger
 * @param noeud2 Deuxième nœud à échanger
 * @return true si l'échange a réussi, false sinon
 */
bool EchangerNoeuds(ListeDouble* liste, NoeudD* noeud1, NoeudD* noeud2);

/**
 * @brief Fait une rotation de la liste double vers la gauche
 * @param liste Pointeur vers la liste
 * @param k Nombre de positions à rotationner
 */
void RotationGauche(ListeDouble* liste, int k);

/**
 * @brief Fait une rotation de la liste double vers la droite
 * @param liste Pointeur vers la liste
 * @param k Nombre de positions à rotationner
 */
void RotationDroite(ListeDouble* liste, int k);

#endif