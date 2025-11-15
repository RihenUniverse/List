#include "Unitest/TestRunner.h"
#include "Unitest/ConsoleReporter.h"
#include "Unitest/TestMacros.h"
#include "Unitest/TestCase.h"
#include "Unitest/Assertions.h"

#include "List/ListS.h"

#include <string>
#include <vector>

// ============================================================================
// FONCTIONS UTILITAires POUR LA GESTION SÉCURISÉE
// ============================================================================

/**
 * @brief Crée et valide un nœud de manière sécurisée
 */
NoeudS* CreerEtValiderNoeud(int valeur, const std::string& contexte = "") {
    NoeudS* noeud = CreerNoeudS(valeur);
    if (noeud == nullptr) {
        ASSERT_FAIL("Échec création nœud " + contexte);
        return nullptr;
    }
    return noeud;
}

/**
 * @brief Crée et valide une liste de manière sécurisée
 */
ListeSimple* CreerEtValiderListe(const std::string& contexte = "") {
    ListeSimple* liste = AllocateSimple();
    if (liste == nullptr) {
        ASSERT_FAIL("Échec création liste " + contexte);
        return nullptr;
    }
    return liste;
}

/**
 * @brief Nettoie une liste de manière sécurisée (gère les pointeurs null)
 */
void NettoyerListe(ListeSimple* liste) {
    if (liste != nullptr) {
        Nettoyer(liste);
    }
}

/**
 * @brief Détruit une liste de manière sécurisée (gère les pointeurs null)
 */
void DetruireListe(ListeSimple* liste) {
    if (liste != nullptr) {
        Detruire(liste);
    }
}

/**
 * @brief Initialise une liste de manière sécurisée
 */
bool InitialiserListe(ListeSimple* liste, const std::string& contexte = "") {
    if (liste == nullptr) {
        ASSERT_FAIL("Liste null dans " + contexte);
        return false;
    }
    Initialiser(liste);
    return true;
}

// ============================================================================
// TESTS DES FONCTIONS DE BASE
// ============================================================================

TEST_CASE(TestCreerNoeud) {
    NoeudS* noeud = CreerEtValiderNoeud(42, "TestCreerNoeud");
    
    if (noeud != nullptr) {
        ASSERT_EQUAL(42, noeud->donnee, "La donnée devrait être 42");
        ASSERT_NULL(noeud->suivant, "Le suivant devrait être NULL");
        free(noeud); // Nettoyage pour les nœuds créés individuellement
    }
}

TEST_CASE(TestCreerListe) {
    ListeSimple* liste = CreerEtValiderListe("TestCreerListe");
    
    if (liste != nullptr) {
        ASSERT_NULL(liste->tete, "La tête devrait être NULL");
        ASSERT_NULL(liste->queue, "La queue devrait être NULL");
        ASSERT_EQUAL(0, liste->taille, "La taille devrait être 0");
        ASSERT_FALSE(liste->estCirculaire, "La liste ne devrait pas être circulaire");
        
        // Test avec insertion
        InsererDebut(liste, 10);
        ASSERT_EQUAL(1, liste->taille, "La taille devrait être 1 après insertion");
        DetruireListe(liste); // Utiliser Detruire uniquement pour les listes allouées dynamiquement
    }
}

TEST_CASE(TestInitialiser) {
    ListeSimple liste; // Liste sur la pile
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestInitialiser")) {
        ASSERT_NULL(liste.tete, "La tête devrait être NULL");
        ASSERT_NULL(liste.queue, "La queue devrait être NULL");
        ASSERT_EQUAL(0, liste.taille, "La taille devrait être 0");
        ASSERT_FALSE(liste.estCirculaire, "La liste ne devrait pas être circulaire");
        
        // Test avec insertion
        InsererDebut(&liste, 10);
        ASSERT_EQUAL(1, liste.taille, "La taille devrait être 1 après insertion");
        
        // Pour les listes sur la pile, utiliser Nettoyer au lieu de Detruire
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestEstVide) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestEstVide")) {
        ASSERT_TRUE(EstVide(&liste), "La liste devrait être vide");
        InsererDebut(&liste, 1);
        ASSERT_FALSE(EstVide(&liste), "La liste ne devrait pas être vide après insertion");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestNettoyer) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestNettoyer")) {
        InsererDebut(&liste, 1);
        InsererDebut(&liste, 2);
        InsererDebut(&liste, 3);
        
        ASSERT_FALSE(EstVide(&liste), "La liste ne devrait pas être vide avant nettoyage");
        ASSERT_EQUAL(3, liste.taille, "La taille devrait être 3");
        
        NettoyerListe(&liste);
        
        ASSERT_TRUE(EstVide(&liste), "La liste devrait être vide après nettoyage");
        ASSERT_NULL(liste.tete, "La tête devrait être NULL");
        ASSERT_NULL(liste.queue, "La queue devrait être NULL");
        ASSERT_EQUAL(0, liste.taille, "La taille devrait être 0");
    }
}

// ============================================================================
// TESTS D'INSERTION
// ============================================================================

TEST_CASE(TestInsererDebut) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestInsererDebut")) {
        InsererDebut(&liste, 10);
        ASSERT_NOT_NULL(liste.tete, "La tête ne devrait pas être NULL");
        ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait contenir 10");
        ASSERT_EQUAL(1, liste.taille, "La taille devrait être 1");
        ASSERT_EQUAL(liste.tete, liste.queue, "Tête et queue devraient être identiques pour un seul élément");
        
        InsererDebut(&liste, 20);
        ASSERT_EQUAL(20, liste.tete->donnee, "La nouvelle tête devrait être 20");
        ASSERT_EQUAL(10, liste.queue->donnee, "La queue devrait rester 10");
        ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestInsererFin) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestInsererFin")) {
        InsererFin(&liste, 10);
        ASSERT_NOT_NULL(liste.queue, "La queue ne devrait pas être NULL");
        ASSERT_EQUAL(10, liste.queue->donnee, "La queue devrait contenir 10");
        ASSERT_EQUAL(1, liste.taille, "La taille devrait être 1");
        
        InsererFin(&liste, 20);
        ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait rester 10");
        ASSERT_EQUAL(20, liste.queue->donnee, "La nouvelle queue devrait être 20");
        ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestInsererApres) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestInsererApres")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 30);
        
        NoeudS* noeud10 = liste.tete;
        ASSERT_NOT_NULL(noeud10, "Le nœud 10 devrait exister");
        
        if (noeud10 != nullptr) {
            ASSERT_TRUE(InsererApres(&liste, noeud10, 20), "Insertion après devrait réussir");
            
            ASSERT_EQUAL(3, liste.taille, "La taille devrait être 3");
            ASSERT_EQUAL(20, liste.tete->suivant->donnee, "Le deuxième élément devrait être 20");
            ASSERT_EQUAL(30, liste.tete->suivant->suivant->donnee, "Le troisième élément devrait être 30");
        }
        
        // Test insertion après queue
        ASSERT_TRUE(InsererApres(&liste, liste.queue, 40), "Insertion après queue devrait réussir");
        ASSERT_EQUAL(40, liste.queue->donnee, "La nouvelle queue devrait être 40");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestInsererAvant) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestInsererAvant")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 30);
        
        NoeudS* noeud30 = liste.queue;
        ASSERT_NOT_NULL(noeud30, "Le nœud 30 devrait exister");
        
        if (noeud30 != nullptr) {
            ASSERT_TRUE(InsererAvant(&liste, noeud30, 20), "Insertion avant devrait réussir");
            
            ASSERT_EQUAL(3, liste.taille, "La taille devrait être 3");
            ASSERT_EQUAL(20, liste.tete->suivant->donnee, "Le deuxième élément devrait être 20");
        }
        
        // Test insertion avant tête
        ASSERT_TRUE(InsererAvant(&liste, liste.tete, 5), "Insertion avant tête devrait réussir");
        ASSERT_EQUAL(5, liste.tete->donnee, "La nouvelle tête devrait être 5");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestInsererPosition) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestInsererPosition")) {
        // Insertion dans liste vide
        ASSERT_TRUE(InsererPosition(&liste, 0, 10), "Insertion position 0 devrait réussir");
        ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait être 10");
        
        // Insertion au début
        ASSERT_TRUE(InsererPosition(&liste, 0, 5), "Insertion au début devrait réussir");
        ASSERT_EQUAL(5, liste.tete->donnee, "La tête devrait être 5");
        
        // Insertion au milieu
        ASSERT_TRUE(InsererPosition(&liste, 1, 7), "Insertion au milieu devrait réussir");
        ASSERT_EQUAL(7, liste.tete->suivant->donnee, "Le deuxième élément devrait être 7");
        
        // Insertion à la fin
        ASSERT_TRUE(InsererPosition(&liste, 3, 15), "Insertion à la fin devrait réussir");
        ASSERT_EQUAL(15, liste.queue->donnee, "La queue devrait être 15");
        
        // Positions invalides
        ASSERT_FALSE(InsererPosition(&liste, 10, 100), "Position invalide devrait échouer");
        ASSERT_FALSE(InsererPosition(&liste, -1, 100), "Position négative devrait échouer");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestInsererTrie) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestInsererTrie")) {
        InsererTrie(&liste, 20);
        InsererTrie(&liste, 10);
        InsererTrie(&liste, 30);
        InsererTrie(&liste, 15);
        
        ASSERT_EQUAL(4, liste.taille, "La taille devrait être 4");
        ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait être 10");
        ASSERT_EQUAL(15, liste.tete->suivant->donnee, "Le deuxième élément devrait être 15");
        ASSERT_EQUAL(20, liste.tete->suivant->suivant->donnee, "Le troisième élément devrait être 20");
        ASSERT_EQUAL(30, liste.queue->donnee, "La queue devrait être 30");
        
        NettoyerListe(&liste);
    }
}

// ============================================================================
// TESTS DE SUPPRESSION
// ============================================================================

TEST_CASE(TestSupprimerDebut) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestSupprimerDebut")) {
        // Suppression liste vide
        ASSERT_FALSE(SupprimerDebut(&liste), "Suppression liste vide devrait échouer");
        
        InsererDebut(&liste, 10);
        InsererDebut(&liste, 20);
        
        ASSERT_TRUE(SupprimerDebut(&liste), "Suppression début devrait réussir");
        ASSERT_EQUAL(10, liste.tete->donnee, "La nouvelle tête devrait être 10");
        ASSERT_EQUAL(1, liste.taille, "La taille devrait être 1");
        
        ASSERT_TRUE(SupprimerDebut(&liste), "Suppression dernier élément devrait réussir");
        ASSERT_TRUE(EstVide(&liste), "La liste devrait être vide");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestSupprimerFin) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestSupprimerFin")) {
        // Suppression liste vide
        ASSERT_FALSE(SupprimerFin(&liste), "Suppression liste vide devrait échouer");
        
        InsererDebut(&liste, 10);
        InsererDebut(&liste, 20);
        
        ASSERT_TRUE(SupprimerFin(&liste), "Suppression fin devrait réussir");
        ASSERT_EQUAL(20, liste.tete->donnee, "La tête devrait rester 20");
        ASSERT_EQUAL(20, liste.queue->donnee, "La queue devrait être 20");
        ASSERT_EQUAL(1, liste.taille, "La taille devrait être 1");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestSupprimerNoeud) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestSupprimerNoeud")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        NoeudS* noeud20 = liste.tete->suivant;
        ASSERT_NOT_NULL(noeud20, "Le nœud 20 devrait exister");
        
        if (noeud20 != nullptr) {
            ASSERT_TRUE(SupprimerNoeud(&liste, noeud20), "Suppression nœud milieu devrait réussir");
            
            ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
            ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait rester 10");
            ASSERT_EQUAL(30, liste.queue->donnee, "La queue devrait être 30");
            ASSERT_EQUAL(30, liste.tete->suivant->donnee, "Le suivant de la tête devrait être 30");
        }
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestSupprimerValeur) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestSupprimerValeur")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        // Suppression valeur existante
        ASSERT_TRUE(SupprimerValeur(&liste, 20), "Suppression valeur existante devrait réussir");
        ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
        ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait être 10");
        ASSERT_EQUAL(30, liste.queue->donnee, "La queue devrait être 30");
        
        // Suppression valeur inexistante
        ASSERT_FALSE(SupprimerValeur(&liste, 40), "Suppression valeur inexistante devrait échouer");
        
        // Suppression tête
        ASSERT_TRUE(SupprimerValeur(&liste, 10), "Suppression tête devrait réussir");
        ASSERT_EQUAL(30, liste.tete->donnee, "La nouvelle tête devrait être 30");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestSupprimerToutesOccurrences) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestSupprimerToutesOccurrences")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 10);
        InsererFin(&liste, 30);
        InsererFin(&liste, 10);
        
        int suppressions = SupprimerToutesOccurrences(&liste, 10);
        ASSERT_EQUAL(3, suppressions, "Devrait supprimer 3 occurrences");
        ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
        ASSERT_EQUAL(20, liste.tete->donnee, "La tête devrait être 20");
        ASSERT_EQUAL(30, liste.queue->donnee, "La queue devrait être 30");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestSupprimerPosition) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestSupprimerPosition")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        // Suppression position valide
        ASSERT_TRUE(SupprimerPosition(&liste, 1), "Suppression position 1 devrait réussir");
        ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
        ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait être 10");
        ASSERT_EQUAL(30, liste.queue->donnee, "La queue devrait être 30");
        
        // Suppression position invalide
        ASSERT_FALSE(SupprimerPosition(&liste, 5), "Suppression position invalide devrait échouer");
        
        NettoyerListe(&liste);
    }
}

// ============================================================================
// TESTS DE RECHERCHE
// ============================================================================

TEST_CASE(TestRechercherValeur) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestRechercherValeur")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        NoeudS* resultat = RechercherValeur(&liste, 20);
        ASSERT_NOT_NULL(resultat, "Devrait trouver la valeur 20");
        ASSERT_EQUAL(20, resultat->donnee, "Le nœud trouvé devrait contenir 20");
        
        resultat = RechercherValeur(&liste, 40);
        ASSERT_NULL(resultat, "Ne devrait pas trouver la valeur 40");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestRechercherToutesOccurrences) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestRechercherToutesOccurrences")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 10);
        InsererFin(&liste, 30);
        InsererFin(&liste, 10);
        
        int count = 0;
        NoeudS** resultats = RechercherToutesOccurrences(&liste, 10, &count);
        
        ASSERT_EQUAL(3, count, "Devrait trouver 3 occurrences");
        
        if (resultats != nullptr) {
            for (int i = 0; i < count; i++) {
                ASSERT_NOT_NULL(resultats[i], "Chaque résultat devrait être non NULL");
                ASSERT_EQUAL(10, resultats[i]->donnee, "Chaque résultat devrait contenir 10");
            }
            
            ASSERT_NULL(resultats[count], "Le tableau devrait se terminer par NULL");
            free(resultats);
        }
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestObtenirNoeudPosition) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestObtenirNoeudPosition")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        NoeudS* noeud = ObtenirNoeudPosition(&liste, 0);
        ASSERT_NOT_NULL(noeud, "Devrait obtenir le nœud à position 0");
        ASSERT_EQUAL(10, noeud->donnee, "Le nœud devrait contenir 10");
        
        noeud = ObtenirNoeudPosition(&liste, 1);
        ASSERT_EQUAL(20, noeud->donnee, "Le nœud devrait contenir 20");
        
        noeud = ObtenirNoeudPosition(&liste, 2);
        ASSERT_EQUAL(30, noeud->donnee, "Le nœud devrait contenir 30");
        
        noeud = ObtenirNoeudPosition(&liste, 5);
        ASSERT_NULL(noeud, "Position invalide devrait retourner NULL");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestTrouverPrecedent) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestTrouverPrecedent")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        NoeudS* precedent = TrouverPrecedent(&liste, liste.tete->suivant);
        ASSERT_NOT_NULL(precedent, "Devrait trouver le précédent");
        ASSERT_EQUAL(10, precedent->donnee, "Le précédent devrait contenir 10");
        
        precedent = TrouverPrecedent(&liste, liste.tete);
        ASSERT_NULL(precedent, "Le précédent de la tête devrait être NULL");
        
        NettoyerListe(&liste);
    }
}

// ============================================================================
// TESTS DE TRANSFORMATION
// ============================================================================

TEST_CASE(TestRendreCirculaire) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestRendreCirculaire")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        RendreCirculaire(&liste);
        ASSERT_TRUE(liste.estCirculaire, "La liste devrait être marquée comme circulaire");
        ASSERT_EQUAL(liste.tete, liste.queue->suivant, "La queue devrait pointer vers la tête");
        
        RendreLineaire(&liste);
        ASSERT_FALSE(liste.estCirculaire, "La liste ne devrait plus être circulaire");
        ASSERT_NULL(liste.queue->suivant, "La queue devrait pointer vers NULL");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestInverser) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestInverser")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        Inverser(&liste);
        
        ASSERT_EQUAL(30, liste.tete->donnee, "La nouvelle tête devrait être 30");
        ASSERT_EQUAL(20, liste.tete->suivant->donnee, "Le deuxième élément devrait être 20");
        ASSERT_EQUAL(10, liste.queue->donnee, "La nouvelle queue devrait être 10");
        ASSERT_EQUAL(3, liste.taille, "La taille devrait rester 3");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestTrier) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestTrier")) {
        InsererFin(&liste, 30);
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 5);
        
        Trier(&liste);
        
        ASSERT_EQUAL(5, liste.tete->donnee, "La tête devrait être 5");
        ASSERT_EQUAL(10, liste.tete->suivant->donnee, "Le deuxième élément devrait être 10");
        ASSERT_EQUAL(20, liste.tete->suivant->suivant->donnee, "Le troisième élément devrait être 20");
        ASSERT_EQUAL(30, liste.queue->donnee, "La queue devrait être 30");
        
        NettoyerListe(&liste);
    }
}

// ============================================================================
// TESTS DE FONCTIONNALITÉS AVANCÉES
// ============================================================================

TEST_CASE(TestCopier) {
    ListeSimple originale;
    originale.queue = nullptr;
    originale.tete = nullptr;
    
    if (InitialiserListe(&originale, "TestCopier originale")) {
        InsererFin(&originale, 10);
        InsererFin(&originale, 20);
        InsererFin(&originale, 30);
        
        ListeSimple* copie = Copier(&originale);
        
        if (copie != nullptr) {
            ASSERT_EQUAL(originale.taille, copie->taille, "La copie devrait avoir la même taille");
            ASSERT_EQUAL(10, copie->tete->donnee, "La tête de la copie devrait être 10");
            ASSERT_EQUAL(20, copie->tete->suivant->donnee, "Le deuxième élément de la copie devrait être 20");
            ASSERT_EQUAL(30, copie->queue->donnee, "La queue de la copie devrait être 30");
            
            // Vérifier que c'est une vraie copie (pas la même mémoire)
            ASSERT_NOT_EQUAL(originale.tete, copie->tete, "Les têtes ne devraient pas pointer vers la même mémoire");
            
            DetruireListe(copie);
        }
        
        NettoyerListe(&originale);
    }
}

TEST_CASE(TestConcatener) {
    ListeSimple liste1, liste2;
    liste1.queue = nullptr;
    liste1.tete = nullptr;
    liste2.queue = nullptr;
    liste2.tete = nullptr;
    
    if (InitialiserListe(&liste1, "TestConcatener liste1") && 
        InitialiserListe(&liste2, "TestConcatener liste2")) {
        
        InsererFin(&liste1, 10);
        InsererFin(&liste1, 20);
        
        InsererFin(&liste2, 30);
        InsererFin(&liste2, 40);
        
        Concatener(&liste1, &liste2);
        
        ASSERT_EQUAL(4, liste1.taille, "La liste concaténée devrait avoir 4 éléments");
        ASSERT_EQUAL(10, liste1.tete->donnee, "La tête devrait rester 10");
        ASSERT_EQUAL(40, liste1.queue->donnee, "La queue devrait être 40");
        ASSERT_EQUAL(20, liste1.tete->suivant->donnee, "Le deuxième élément devrait être 20");
        ASSERT_EQUAL(30, liste1.tete->suivant->suivant->donnee, "Le troisième élément devrait être 30");
        
        NettoyerListe(&liste1);
        NettoyerListe(&liste2);
    }
}

TEST_CASE(TestDiviser) {
    ListeSimple liste, liste2;
    liste.queue = nullptr;
    liste.tete = nullptr;
    liste2.queue = nullptr;
    liste2.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestDiviser liste") && 
        InitialiserListe(&liste2, "TestDiviser liste2")) {
        
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        InsererFin(&liste, 40);
        
        Diviser(&liste, 2, &liste2);
        
        ASSERT_EQUAL(2, liste.taille, "La première liste devrait avoir 2 éléments");
        ASSERT_EQUAL(2, liste2.taille, "La deuxième liste devrait avoir 2 éléments");
        ASSERT_EQUAL(10, liste.tete->donnee, "La tête de la première liste devrait être 10");
        ASSERT_EQUAL(20, liste.queue->donnee, "La queue de la première liste devrait être 20");
        ASSERT_EQUAL(30, liste2.tete->donnee, "La tête de la deuxième liste devrait être 30");
        ASSERT_EQUAL(40, liste2.queue->donnee, "La queue de la deuxième liste devrait être 40");
        
        NettoyerListe(&liste);
        NettoyerListe(&liste2);
    }
}

TEST_CASE(TestSupprimerDoublonsTries) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestSupprimerDoublonsTries")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        InsererFin(&liste, 30);
        InsererFin(&liste, 30);
        
        SupprimerDoublonsTries(&liste);
        
        ASSERT_EQUAL(3, liste.taille, "Devrait avoir 3 éléments après suppression des doublons");
        ASSERT_EQUAL(10, liste.tete->donnee, "Premier élément devrait être 10");
        ASSERT_EQUAL(20, liste.tete->suivant->donnee, "Deuxième élément devrait être 20");
        ASSERT_EQUAL(30, liste.queue->donnee, "Troisième élément devrait être 30");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestSupprimerDoublonsNonTries) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestSupprimerDoublonsNonTries")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 10);
        InsererFin(&liste, 30);
        InsererFin(&liste, 20);
        InsererFin(&liste, 10);
        
        SupprimerDoublonsNonTries(&liste);
        
        ASSERT_EQUAL(3, liste.taille, "Devrait avoir 3 éléments après suppression des doublons");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestFusionnerListesTriees) {
    ListeSimple liste1, liste2;
    liste1.queue = nullptr;
    liste1.tete = nullptr;
    liste2.queue = nullptr;
    liste2.tete = nullptr;
    
    if (InitialiserListe(&liste1, "TestFusionnerListesTriees liste1") && 
        InitialiserListe(&liste2, "TestFusionnerListesTriees liste2")) {
        
        InsererFin(&liste1, 10);
        InsererFin(&liste1, 30);
        InsererFin(&liste1, 50);
        
        InsererFin(&liste2, 20);
        InsererFin(&liste2, 40);
        InsererFin(&liste2, 60);
        
        ListeSimple* fusion = FusionnerListesTriees(&liste1, &liste2);
        
        if (fusion != nullptr) {
            ASSERT_EQUAL(6, fusion->taille, "La fusion devrait avoir 6 éléments");
            
            NoeudS* courant = fusion->tete;
            ASSERT_EQUAL(10, courant->donnee, "Premier élément devrait être 10");
            courant = courant->suivant;
            ASSERT_EQUAL(20, courant->donnee, "Deuxième élément devrait être 20");
            courant = courant->suivant;
            ASSERT_EQUAL(30, courant->donnee, "Troisième élément devrait être 30");
            courant = courant->suivant;
            ASSERT_EQUAL(40, courant->donnee, "Quatrième élément devrait être 40");
            courant = courant->suivant;
            ASSERT_EQUAL(50, courant->donnee, "Cinquième élément devrait être 50");
            courant = courant->suivant;
            ASSERT_EQUAL(60, courant->donnee, "Sixième élément devrait être 60");
            
            DetruireListe(fusion);
        }
        
        NettoyerListe(&liste1);
        NettoyerListe(&liste2);
    }
}

TEST_CASE(TestTrouverMilieu) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestTrouverMilieu")) {
        // Liste impaire
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        NoeudS* milieu = TrouverMilieu(&liste);
        ASSERT_NOT_NULL(milieu, "Devrait trouver le milieu");
        ASSERT_EQUAL(20, milieu->donnee, "Le milieu devrait être 20");
        
        NettoyerListe(&liste);
        
        // Liste paire
        InitialiserListe(&liste, "TestTrouverMilieu paire");
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        InsererFin(&liste, 40);
        
        milieu = TrouverMilieu(&liste);
        ASSERT_NOT_NULL(milieu, "Devrait trouver le milieu");
        ASSERT_EQUAL(30, milieu->donnee, "Le milieu devrait être 30 (deuxième milieu)");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestEstPalindrome) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestEstPalindrome")) {
        // Test liste vide
        ASSERT_TRUE(EstPalindrome(&liste), "Liste vide devrait être un palindrome");
        
        // Test un élément
        InsererFin(&liste, 10);
        ASSERT_TRUE(EstPalindrome(&liste), "Liste à un élément devrait être un palindrome");
        
        NettoyerListe(&liste);
        
        // Test palindrome pair
        InitialiserListe(&liste, "TestEstPalindrome pair");
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 20);
        InsererFin(&liste, 10);
        ASSERT_TRUE(EstPalindrome(&liste), "Liste palindrome devrait retourner true");
        
        NettoyerListe(&liste);
        
        // Test non-palindrome
        InitialiserListe(&liste, "TestEstPalindrome non-palindrome");
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        ASSERT_FALSE(EstPalindrome(&liste), "Liste non-palindrome devrait retourner false");
        
        NettoyerListe(&liste);
    }
}

// ============================================================================
// TESTS DE ROBUSTESSE
// ============================================================================

TEST_CASE(TestContientCycle) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestContientCycle")) {
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        // Liste linéaire ne devrait pas avoir de cycle
        ASSERT_FALSE(ContientCycle(&liste), "Liste linéaire ne devrait pas avoir de cycle");
        
        // Liste circulaire devrait détecter un cycle
        RendreCirculaire(&liste);
        ASSERT_TRUE(ContientCycle(&liste), "Liste circulaire devrait détecter un cycle");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestToString) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestToString")) {
        // Test liste vide
        std::string resultatVide = ToString(&liste);
        Print(resultatVide);
        ASSERT_TRUE(resultatVide.find("Liste[]") != std::string::npos, "ToString liste vide incorrect");
        
        // Test avec éléments
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        
        std::string resultat = ToString(&liste);
        ASSERT_TRUE(resultat.find("10") != std::string::npos, "ToString devrait contenir 10");
        ASSERT_TRUE(resultat.find("20") != std::string::npos, "ToString devrait contenir 20");
        ASSERT_TRUE(resultat.find("->") != std::string::npos, "ToString devrait contenir des flèches");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestCompterElements) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestCompterElements")) {
        ASSERT_EQUAL(0, CompterElements(&liste), "Liste vide devrait avoir 0 éléments");
        
        InsererFin(&liste, 10);
        InsererFin(&liste, 20);
        InsererFin(&liste, 30);
        
        ASSERT_EQUAL(3, CompterElements(&liste), "Liste avec 3 éléments devrait retourner 3");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestIntegrationComplet) {
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    
    if (InitialiserListe(&liste, "TestIntegrationComplet")) {
        // Scénario d'utilisation complet
        InsererDebut(&liste, 5);
        InsererFin(&liste, 15);
        InsererPosition(&liste, 1, 10);
        
        ASSERT_EQUAL(3, liste.taille, "Taille devrait être 3 après insertions");
        ASSERT_EQUAL(5, liste.tete->donnee, "Tête incorrecte");
        ASSERT_EQUAL(15, liste.queue->donnee, "Queue incorrecte");
        
        // Recherche et suppression
        NoeudS* noeud10 = RechercherValeur(&liste, 10);
        ASSERT_NOT_NULL(noeud10, "Devrait trouver la valeur 10");
        
        SupprimerValeur(&liste, 10);
        ASSERT_EQUAL(2, liste.taille, "Taille devrait être 2 après suppression");
        
        // Transformation
        Inverser(&liste);
        ASSERT_EQUAL(15, liste.tete->donnee, "Tête après inversion incorrecte");
        ASSERT_EQUAL(5, liste.queue->donnee, "Queue après inversion incorrecte");
        
        // Test avec liste circulaire
        RendreCirculaire(&liste);
        ASSERT_TRUE(liste.estCirculaire, "La liste devrait être circulaire");
        
        NettoyerListe(&liste);
    }
}

TEST_CASE(TestGestionMemoire) {
    // Test de création/destruction multiple - utiliser Detruire uniquement pour les listes allouées
    for (int i = 0; i < 10; i++) {
        ListeSimple* liste = CreerEtValiderListe("TestGestionMemoire iteration " + std::to_string(i));
        
        if (liste != nullptr) {
            for (int j = 0; j < 5; j++) {
                InsererFin(liste, j);
            }
            
            ASSERT_EQUAL(5, liste->taille, "La liste devrait avoir 5 éléments");
            
            DetruireListe(liste);
        }
    }
    
    // Test avec liste sur la pile - utiliser Nettoyer
    ListeSimple liste;
    liste.queue = nullptr;
    liste.tete = nullptr;
    if (InitialiserListe(&liste, "TestGestionMemoire pile")) {
        for (int j = 0; j < 5; j++) {
            InsererFin(&liste, j);
        }
        
        ASSERT_EQUAL(5, liste.taille, "La liste devrait avoir 5 éléments");
        
        NettoyerListe(&liste);
    }
}