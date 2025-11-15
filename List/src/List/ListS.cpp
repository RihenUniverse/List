#include "ListS.h"
#include <iostream>
#include <string>

// ============================================================================
// FONCTIONS DE CRÉATION ET DESTRUCTION
// ============================================================================

ListeSimple* AllocateSimple()
{
    ListeSimple* nouvelleListe = (ListeSimple*)malloc(sizeof(ListeSimple));
    if (nouvelleListe != nullptr) {
        nouvelleListe->tete = nullptr;
        nouvelleListe->queue = nullptr;
    	nouvelleListe->taille = 0;
    	nouvelleListe->estCirculaire = false;
        nouvelleListe->estAllouee = true; // Marquer comme allouée
    }
    return nouvelleListe;
}

ListeSimple CreerSimple()
{
    ListeSimple nouvelleListe;
    nouvelleListe.tete = nullptr;
    nouvelleListe.queue = nullptr;
    nouvelleListe.taille = 0;
    nouvelleListe.estCirculaire = false;
    nouvelleListe.estAllouee = true; // Marquer comme allouée
    return nouvelleListe;
}

NoeudS* CreerNoeudS(int valeur) {
    NoeudS* nouveau = (NoeudS*)malloc(sizeof(NoeudS));
    if (nouveau == nullptr) {
        return nullptr;
    }
    nouveau->donnee = valeur;
    nouveau->suivant = nullptr;
    return nouveau;
}

void Initialiser(ListeSimple* liste) {
    if (liste == nullptr) {
        return;
    }
    
    // Si la liste contient déjà des données, on la nettoie d'abord
    if (!EstVide(liste)) {
        Nettoyer(liste);
    }
    
    liste->tete = nullptr;
    liste->queue = nullptr;
    liste->taille = 0;
    liste->estCirculaire = false;
    liste->estAllouee = false; // Par défaut, pas allouée dynamiquement
}

void Nettoyer(ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste)) {
        return;
    }
    
    NoeudS* courant = liste->tete;
    NoeudS* suivant = nullptr;
    
    while (courant != nullptr) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
        
        // Pour éviter les boucles infinies dans les listes circulaires
        if (courant == liste->tete) {
            break;
        }
    }
    
    liste->tete = nullptr;
    liste->queue = nullptr;
    liste->taille = 0;
    liste->estCirculaire = false;
}

void Detruire(ListeSimple* liste) {
    if (liste == nullptr) {
        return;
    }
    
    // Nettoyer tous les nœuds
    Nettoyer(liste);
    
    // Libérer la structure de la liste elle-même
    if (liste->estAllouee) {
        free(liste);
    }
}

// ============================================================================
// FONCTIONS D'INSERTION
// ============================================================================

void InsererDebut(ListeSimple* liste, int valeur) {
    if (liste == nullptr) {
        return;
    }
    
    NoeudS* nouveau = CreerNoeudS(valeur);
    if (nouveau == nullptr) {
        return;
    }
    
    if (EstVide(liste)) {
        liste->tete = nouveau;
        liste->queue = nouveau;
        if (liste->estCirculaire) {
            nouveau->suivant = nouveau;
        }
    } else {
        nouveau->suivant = liste->tete;
        liste->tete = nouveau;
        if (liste->estCirculaire) {
            liste->queue->suivant = nouveau;
        }
    }
    
    liste->taille++;
}

void InsererFin(ListeSimple* liste, int valeur) {
    if (liste == nullptr) {
        return;
    }
    
    NoeudS* nouveau = CreerNoeudS(valeur);
    if (nouveau == nullptr) {
        return;
    }
    
    if (EstVide(liste)) {
        liste->tete = nouveau;
        liste->queue = nouveau;
    } else {
        liste->queue->suivant = nouveau;
        liste->queue = nouveau;
    }
    
    if (liste->estCirculaire) {
        nouveau->suivant = liste->tete;
    }
    
    liste->taille++;
}

bool InsererApres(ListeSimple* liste, NoeudS* precedent, int valeur) {
    if (liste == nullptr || precedent == nullptr) {
        return false;
    }
    
    NoeudS* nouveau = CreerNoeudS(valeur);
    if (nouveau == nullptr) {
        return false;
    }
    
    nouveau->suivant = precedent->suivant;
    precedent->suivant = nouveau;
    
    if (precedent == liste->queue) {
        liste->queue = nouveau;
        if (liste->estCirculaire) {
            nouveau->suivant = liste->tete;
        }
    }
    
    liste->taille++;
    return true;
}

bool InsererAvant(ListeSimple* liste, NoeudS* suivant, int valeur) {
    if (liste == nullptr || suivant == nullptr) {
        return false;
    }
    
    if (suivant == liste->tete) {
        InsererDebut(liste, valeur);
        return true;
    }
    
    NoeudS* precedent = TrouverPrecedent(liste, suivant);
    if (precedent != nullptr) {
        return InsererApres(liste, precedent, valeur);
    }
    
    return false;
}

bool InsererPosition(ListeSimple* liste, int position, int valeur) {
    if (liste == nullptr || position < 0 || position > liste->taille) {
        return false;
    }
    
    if (position == 0) {
        InsererDebut(liste, valeur);
        return true;
    }
    
    if (position == liste->taille) {
        InsererFin(liste, valeur);
        return true;
    }
    
    NoeudS* courant = liste->tete;
    for (int i = 0; i < position - 1; i++) {
        courant = courant->suivant;
    }
    
    return InsererApres(liste, courant, valeur);
}

void InsererTrie(ListeSimple* liste, int valeur) {
    if (liste == nullptr) {
        return;
    }
    
    if (EstVide(liste) || valeur <= liste->tete->donnee) {
        InsererDebut(liste, valeur);
        return;
    }
    
    if (valeur >= liste->queue->donnee) {
        InsererFin(liste, valeur);
        return;
    }
    
    NoeudS* courant = liste->tete;
    while (courant->suivant != nullptr && courant->suivant->donnee < valeur) {
        courant = courant->suivant;
    }
    
    InsererApres(liste, courant, valeur);
}

// ============================================================================
// FONCTIONS DE SUPPRESSION
// ============================================================================

bool SupprimerDebut(ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste)) {
        return false;
    }
    
    NoeudS* ancienneTete = liste->tete;
    
    if (liste->tete == liste->queue) {
        liste->tete = nullptr;
        liste->queue = nullptr;
    } else {
        liste->tete = liste->tete->suivant;
        if (liste->estCirculaire) {
            liste->queue->suivant = liste->tete;
        }
    }
    
    free(ancienneTete);
    liste->taille--;
    return true;
}

bool SupprimerFin(ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste)) {
        return false;
    }
    
    if (liste->tete == liste->queue) {
        return SupprimerDebut(liste);
    }
    
    NoeudS* avantDernier = TrouverPrecedent(liste, liste->queue);
    if (avantDernier != nullptr) {
        free(liste->queue);
        liste->queue = avantDernier;
        liste->queue->suivant = liste->estCirculaire ? liste->tete : nullptr;
        liste->taille--;
        return true;
    }
    
    return false;
}

bool SupprimerNoeud(ListeSimple* liste, NoeudS* cible) {
    if (liste == nullptr || cible == nullptr || EstVide(liste)) {
        return false;
    }
    
    if (cible == liste->tete) {
        return SupprimerDebut(liste);
    }
    
    NoeudS* precedent = TrouverPrecedent(liste, cible);
    if (precedent != nullptr) {
        precedent->suivant = cible->suivant;
        if (cible == liste->queue) {
            liste->queue = precedent;
            if (liste->estCirculaire) {
                liste->queue->suivant = liste->tete;
            }
        }
        free(cible);
        liste->taille--;
        return true;
    }
    
    return false;
}

bool SupprimerValeur(ListeSimple* liste, int valeur) {
    if (liste == nullptr) {
        return false;
    }
    
    NoeudS* cible = RechercherValeur(liste, valeur);
    if (cible != nullptr) {
        return SupprimerNoeud(liste, cible);
    }
    return false;
}

int SupprimerToutesOccurrences(ListeSimple* liste, int valeur) {
    if (liste == nullptr) {
        return 0;
    }
    
    int compteur = 0;
    NoeudS* courant = liste->tete;
    NoeudS* precedent = nullptr;
    
    while (courant != nullptr) {
        if (courant->donnee == valeur) {
            NoeudS* aSupprimer = courant;
            courant = courant->suivant;
            
            if (aSupprimer == liste->tete) {
                SupprimerDebut(liste);
            } else if (precedent != nullptr) {
                precedent->suivant = aSupprimer->suivant;
                if (aSupprimer == liste->queue) {
                    liste->queue = precedent;
                }
                free(aSupprimer);
                liste->taille--;
            }
            
            compteur++;
        } else {
            precedent = courant;
            courant = courant->suivant;
        }
        
        if (courant == liste->tete && liste->estCirculaire) {
            break;
        }
    }
    
    return compteur;
}

bool SupprimerPosition(ListeSimple* liste, int position) {
    if (liste == nullptr || position < 0 || position >= liste->taille) {
        return false;
    }
    
    if (position == 0) {
        return SupprimerDebut(liste);
    }
    
    if (position == liste->taille - 1) {
        return SupprimerFin(liste);
    }
    
    NoeudS* cible = ObtenirNoeudPosition(liste, position);
    if (cible != nullptr) {
        return SupprimerNoeud(liste, cible);
    }
    
    return false;
}

// ============================================================================
// FONCTIONS DE RECHERCHE
// ============================================================================

NoeudS* RechercherValeur(const ListeSimple* liste, int valeur) {
    if (liste == nullptr || EstVide(liste)) {
        return nullptr;
    }
    
    NoeudS* courant = liste->tete;
    bool premierPassage = true;
    
    while (courant != nullptr && (premierPassage || courant != liste->tete)) {
        if (courant->donnee == valeur) {
            return courant;
        }
        courant = courant->suivant;
        premierPassage = false;
        
        if (!liste->estCirculaire && courant == nullptr) {
            break;
        }
    }
    
    return nullptr;
}

NoeudS** RechercherToutesOccurrences(const ListeSimple* liste, int valeur, int* count) {
    if (liste == nullptr || count == nullptr) {
        return nullptr;
    }
    
    *count = 0;
    
    // Premier passage : compter les occurrences
    NoeudS* courant = liste->tete;
    bool premierPassage = true;
    
    while (courant != nullptr && (premierPassage || courant != liste->tete)) {
        if (courant->donnee == valeur) {
            (*count)++;
        }
        courant = courant->suivant;
        premierPassage = false;
        
        if (!liste->estCirculaire && courant == nullptr) {
            break;
        }
    }
    
    if (*count == 0) {
        return nullptr;
    }
    
    // Deuxième passage : remplir le tableau
    NoeudS** resultats = (NoeudS**)malloc((*count + 1) * sizeof(NoeudS*));
    if (resultats == nullptr) {
        *count = 0;
        return nullptr;
    }
    
    int index = 0;
    courant = liste->tete;
    premierPassage = true;
    
    while (courant != nullptr && (premierPassage || courant != liste->tete)) {
        if (courant->donnee == valeur) {
            resultats[index++] = courant;
        }
        courant = courant->suivant;
        premierPassage = false;
        
        if (!liste->estCirculaire && courant == nullptr) {
            break;
        }
    }
    
    resultats[index] = nullptr;
    return resultats;
}

NoeudS* ObtenirNoeudPosition(const ListeSimple* liste, int position) {
    if (liste == nullptr || position < 0 || position >= liste->taille) {
        return nullptr;
    }
    
    NoeudS* courant = liste->tete;
    for (int i = 0; i < position && courant != nullptr; i++) {
        courant = courant->suivant;
    }
    
    return courant;
}

NoeudS* TrouverPrecedent(const ListeSimple* liste, const NoeudS* cible) {
    if (liste == nullptr || cible == nullptr || EstVide(liste) || cible == liste->tete) {
        return nullptr;
    }
    
    NoeudS* courant = liste->tete;
    NoeudS* precedent = nullptr;
    bool premierPassage = true;
    
    while (courant != nullptr && (premierPassage || courant != liste->tete)) {
        if (courant == cible) {
            return precedent;
        }
        precedent = courant;
        courant = courant->suivant;
        premierPassage = false;
        
        if (!liste->estCirculaire && courant == nullptr) {
            break;
        }
    }
    
    return nullptr;
}

// ============================================================================
// FONCTIONS D'INFORMATION
// ============================================================================

std::string ToString(const NoeudS* noeud) {
    if (noeud == nullptr) {
        return "NULL";
    }
    return "Noeud(" + std::to_string(noeud->donnee) + ")";
}

std::string ToString(const ListeSimple* liste) {
    if (liste == nullptr) {
        return "Liste[NULL]";
    }
    
    if (EstVide(liste)) {
        return "Liste[]";
    }
    
    std::string resultat = "Liste[";
    NoeudS* courant = liste->tete;
    bool premierPassage = true;
    
    while (courant != nullptr && (premierPassage || courant != liste->tete)) {
        resultat += ToString(courant);
        courant = courant->suivant;
        premierPassage = false;
        
        if (courant != nullptr && (courant != liste->tete || !liste->estCirculaire)) {
            resultat += " -> ";
        }
        
        if (!liste->estCirculaire && courant == nullptr) {
            break;
        }
    }
    
    resultat += "]";
    if (liste->estCirculaire) {
        resultat += " (circulaire)";
    }
    
    return resultat;
}

int CompterElements(const ListeSimple* liste) {
    if (liste == nullptr) {
        return 0;
    }
    return liste->taille;
}

bool EstVide(const ListeSimple* liste) {
    return liste == nullptr || liste->tete == nullptr || liste->taille == 0;
}

bool ContientCycle(const ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste)) {
        return false;
    }
    
    if (liste->estCirculaire) {
        return true;
    }
    
    if (liste->tete->suivant == nullptr) {
        return false;
    }
    
    NoeudS* lent = liste->tete;
    NoeudS* rapide = liste->tete;
    
    while (rapide != nullptr && rapide->suivant != nullptr) {
        lent = lent->suivant;
        rapide = rapide->suivant->suivant;
        
        if (lent == rapide) {
            return true;
        }
    }
    
    return false;
}

// ============================================================================
// FONCTIONS DE CONVERSION ET TRANSFORMATION
// ============================================================================

void RendreCirculaire(ListeSimple* liste) {
    if (liste == nullptr || liste->estCirculaire || EstVide(liste)) {
        return;
    }
    
    liste->queue->suivant = liste->tete;
    liste->estCirculaire = true;
}

void RendreLineaire(ListeSimple* liste) {
    if (liste == nullptr || !liste->estCirculaire) {
        return;
    }
    
    liste->queue->suivant = nullptr;
    liste->estCirculaire = false;
}

void Inverser(ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste) || liste->tete == liste->queue) {
        return;
    }
    
    NoeudS* prev = nullptr;
    NoeudS* curr = liste->tete;
    NoeudS* next = nullptr;
    NoeudS* ancienneTete = liste->tete;
    
    while (curr != nullptr) {
        next = curr->suivant;
        curr->suivant = prev;
        prev = curr;
        curr = next;
        
        if (curr == ancienneTete && liste->estCirculaire) {
            break;
        }
    }
    
    liste->tete = prev;
    
    // Mettre à jour la queue
    if (!liste->estCirculaire) {
        liste->queue = ancienneTete;
    } else {
        liste->queue = ancienneTete;
        liste->queue->suivant = liste->tete;
    }
}

void Trier(ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste) || liste->tete == liste->queue) {
        return;
    }
    
    // Tri par insertion
    NoeudS* courant = liste->tete->suivant;
    NoeudS* precedentCourant = liste->tete;
    
    while (courant != nullptr && (courant != liste->tete || !liste->estCirculaire)) {
        int valeurCourante = courant->donnee;
        NoeudS* temp = liste->tete;
        NoeudS* precedentTemp = nullptr;
        
        while (temp != courant && temp->donnee <= valeurCourante) {
            precedentTemp = temp;
            temp = temp->suivant;
        }
        
        if (temp != courant) {
            // Retirer le nœud courant
            precedentCourant->suivant = courant->suivant;
            if (courant == liste->queue) {
                liste->queue = precedentCourant;
            }
            
            // Insérer avant temp
            if (precedentTemp == nullptr) {
                // Insérer au début
                courant->suivant = liste->tete;
                liste->tete = courant;
            } else {
                precedentTemp->suivant = courant;
                courant->suivant = temp;
            }
            
            // Mettre à jour les pointeurs circulaires si nécessaire
            if (liste->estCirculaire) {
                liste->queue->suivant = liste->tete;
            }
        } else {
            precedentCourant = courant;
        }
        
        courant = precedentCourant->suivant;
        
        if (courant == liste->tete && liste->estCirculaire) {
            break;
        }
    }
}

ListeSimple* Copier(const ListeSimple* liste) {
    if (liste == nullptr) {
        return nullptr;
    }
    
    ListeSimple* nouvelleListe = AllocateSimple();
    if (nouvelleListe == nullptr) {
        return nullptr;
    }
    
    if (EstVide(liste)) {
        return nouvelleListe;
    }
    
    NoeudS* courant = liste->tete;
    bool premierPassage = true;
    
    while (courant != nullptr && (premierPassage || courant != liste->tete)) {
        InsererFin(nouvelleListe, courant->donnee);
        courant = courant->suivant;
        premierPassage = false;
        
        if (!liste->estCirculaire && courant == nullptr) {
            break;
        }
    }
    
    if (liste->estCirculaire) {
        RendreCirculaire(nouvelleListe);
    }
    
    return nouvelleListe;
}

void Concatener(ListeSimple* liste1, const ListeSimple* liste2) {
    if (liste1 == nullptr || liste2 == nullptr || EstVide(liste2)) {
        return;
    }
    
    if (EstVide(liste1)) {
        ListeSimple* copie = Copier(liste2);
        if (copie != nullptr) {
            *liste1 = *copie;
            free(copie);
        }
        return;
    }
    
    // Sauvegarder l'état circulaire original
    bool etaitCirculaire = liste1->estCirculaire;
    if (etaitCirculaire) {
        RendreLineaire(liste1);
    }
    
    // Copier liste2
    ListeSimple* copieListe2 = Copier(liste2);
    if (copieListe2 == nullptr) {
        return;
    }
    
    if (copieListe2->estCirculaire) {
        RendreLineaire(copieListe2);
    }
    
    // Concaténer
    liste1->queue->suivant = copieListe2->tete;
    liste1->queue = copieListe2->queue;
    liste1->taille += copieListe2->taille;
    
    // Restaurer l'état circulaire si nécessaire
    if (etaitCirculaire) {
        RendreCirculaire(liste1);
    }
    
    // Libérer la copie temporaire
    free(copieListe2);
}

void Diviser(ListeSimple* liste, int position, ListeSimple* liste2) {
    if (liste == nullptr || liste2 == nullptr || position < 1 || position >= liste->taille - 1) {
        return;
    }
    
    Initialiser(liste2);
    
    NoeudS* noeudDivision = ObtenirNoeudPosition(liste, position);
    if (noeudDivision == nullptr) {
        return;
    }
    
    // Configurer liste2
    liste2->tete = noeudDivision;
    liste2->queue = liste->queue;
    liste2->taille = liste->taille - position;
    liste2->estCirculaire = liste->estCirculaire;
    
    // Mettre à jour liste1
    NoeudS* nouvelleQueue = ObtenirNoeudPosition(liste, position - 1);
    if (nouvelleQueue != nullptr) {
        liste->queue = nouvelleQueue;
        if (liste->estCirculaire) {
            liste->queue->suivant = liste->tete;
        } else {
            liste->queue->suivant = nullptr;
        }
        liste->taille = position;
    }
    
    // Si la liste était circulaire, rendre liste2 linéaire
    if (liste2->estCirculaire) {
        RendreLineaire(liste2);
    }
}

// ============================================================================
// FONCTIONS UTILITAIRES AVANCÉES
// ============================================================================

void SupprimerDoublonsTries(ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste) || liste->tete == liste->queue) {
        return;
    }
    
    NoeudS* courant = liste->tete;
    
    while (courant != nullptr && courant->suivant != nullptr) {
        if (courant->donnee == courant->suivant->donnee) {
            NoeudS* doublon = courant->suivant;
            courant->suivant = doublon->suivant;
            if (doublon == liste->queue) {
                liste->queue = courant;
            }
            free(doublon);
            liste->taille--;
        } else {
            courant = courant->suivant;
        }
        
        if (courant == liste->tete && liste->estCirculaire) {
            break;
        }
    }
}

void SupprimerDoublonsNonTries(ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste) || liste->tete == liste->queue) {
        return;
    }
    
    NoeudS* courant = liste->tete;
    
    while (courant != nullptr) {
        NoeudS* runner = courant;
        while (runner->suivant != nullptr) {
            if (runner->suivant->donnee == courant->donnee) {
                NoeudS* doublon = runner->suivant;
                runner->suivant = doublon->suivant;
                if (doublon == liste->queue) {
                    liste->queue = runner;
                }
                free(doublon);
                liste->taille--;
            } else {
                runner = runner->suivant;
            }
            
            if (runner->suivant == liste->tete && liste->estCirculaire) {
                break;
            }
        }
        
        courant = courant->suivant;
        if (courant == liste->tete && liste->estCirculaire) {
            break;
        }
    }
}

ListeSimple* FusionnerListesTriees(const ListeSimple* liste1, const ListeSimple* liste2) {
    if (liste1 == nullptr && liste2 == nullptr) {
        return nullptr;
    }
    
    ListeSimple* resultat = AllocateSimple();
    if (resultat == nullptr) {
        return nullptr;
    }
    
    if (liste1 == nullptr || EstVide(liste1)) {
        ListeSimple* copie = Copier(liste2);
        if (copie != nullptr) {
            *resultat = *copie;
            free(copie);
        }
        return resultat;
    }
    
    if (liste2 == nullptr || EstVide(liste2)) {
        ListeSimple* copie = Copier(liste1);
        if (copie != nullptr) {
            *resultat = *copie;
            free(copie);
        }
        return resultat;
    }
    
    NoeudS* ptr1 = liste1->tete;
    NoeudS* ptr2 = liste2->tete;
    bool premierPassage1 = true;
    bool premierPassage2 = true;
    
    while ((ptr1 != nullptr && (premierPassage1 || ptr1 != liste1->tete)) || 
           (ptr2 != nullptr && (premierPassage2 || ptr2 != liste2->tete))) {
        
        if (ptr1 != nullptr && (premierPassage1 || ptr1 != liste1->tete) && 
            (ptr2 == nullptr || ptr1->donnee <= ptr2->donnee)) {
            InsererFin(resultat, ptr1->donnee);
            ptr1 = ptr1->suivant;
            premierPassage1 = false;
            
            if (!liste1->estCirculaire && ptr1 == nullptr) {
                premierPassage1 = true;
            }
        } else if (ptr2 != nullptr && (premierPassage2 || ptr2 != liste2->tete)) {
            InsererFin(resultat, ptr2->donnee);
            ptr2 = ptr2->suivant;
            premierPassage2 = false;
            
            if (!liste2->estCirculaire && ptr2 == nullptr) {
                premierPassage2 = true;
            }
        }
    }
    
    return resultat;
}

NoeudS* TrouverMilieu(const ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste)) {
        return nullptr;
    }
    
    NoeudS* lent = liste->tete;
    NoeudS* rapide = liste->tete;
    bool premierPassage = true;
    
    while (rapide != nullptr && rapide->suivant != nullptr && 
           (premierPassage || rapide != liste->tete)) {
        lent = lent->suivant;
        rapide = rapide->suivant->suivant;
        premierPassage = false;
        
        if (rapide == liste->tete && liste->estCirculaire) {
            break;
        }
    }
    
    return lent;
}

bool EstPalindrome(const ListeSimple* liste) {
    if (liste == nullptr || EstVide(liste) || liste->tete == liste->queue) {
        return true;
    }
    
    // Trouver le milieu
    NoeudS* milieu = TrouverMilieu(liste);
    if (milieu == nullptr) {
        return false;
    }
    
    // Inverser la seconde moitié
    NoeudS* secondeMoitie = milieu->suivant;
    NoeudS* prev = nullptr;
    NoeudS* curr = secondeMoitie;
    NoeudS* next = nullptr;
    
    while (curr != nullptr && curr != liste->tete) {
        next = curr->suivant;
        curr->suivant = prev;
        prev = curr;
        curr = next;
    }
    
    NoeudS* teteSecondeMoitieInversee = prev;
    
    // Comparer les deux moitiés
    NoeudS* ptr1 = liste->tete;
    NoeudS* ptr2 = teteSecondeMoitieInversee;
    bool estPalindrome = true;
    
    while (ptr2 != nullptr && ptr2 != liste->tete) {
        if (ptr1->donnee != ptr2->donnee) {
            estPalindrome = false;
            break;
        }
        ptr1 = ptr1->suivant;
        ptr2 = ptr2->suivant;
    }
    
    // Ré-inverser la seconde moitié (restaurer la liste originale)
    curr = teteSecondeMoitieInversee;
    prev = nullptr;
    while (curr != nullptr && curr != liste->tete) {
        next = curr->suivant;
        curr->suivant = prev;
        prev = curr;
        curr = next;
    }
    milieu->suivant = prev;
    
    return estPalindrome;
}