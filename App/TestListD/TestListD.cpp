#include "List/ListD.h"

#include "Unitest/TestRunner.h"
#include "Unitest/ConsoleReporter.h"
#include "Unitest/TestMacros.h"
#include "Unitest/TestCase.h"
#include "Unitest/Assertions.h"

#include <string>
#include <vector>

// ============================================================================
// TESTS DES FONCTIONS DE BASE
// ============================================================================

TEST_CASE(TestCreerNoeudDouble) {
    NoeudD* noeud = CreerNoeudD(42);
    ASSERT_NOT_NULL(noeud, "Le nœud devrait être créé");
    ASSERT_EQUAL(42, noeud->donnee, "La donnée devrait être 42");
    ASSERT_NULL(noeud->precedent, "Le précédent devrait être NULL");
    ASSERT_NULL(noeud->suivant, "Le suivant devrait être NULL");
    free(noeud); // Nettoyage
}

TEST_CASE(TestCreerListeDouble) {
    ListeDouble* liste = AllocateDouble();
    ASSERT_NOT_NULL(liste, "La liste devrait être créée");
    ASSERT_NULL(liste->tete, "La tête devrait être NULL");
    ASSERT_NULL(liste->queue, "La queue devrait être NULL");
    ASSERT_EQUAL(0, liste->taille, "La taille devrait être 0");
    ASSERT_FALSE(liste->estCirculaire, "La liste ne devrait pas être circulaire");
    Detruire(liste);
}

TEST_CASE(TestInitialiserDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    ASSERT_NULL(liste.tete, "La tête devrait être NULL");
    ASSERT_NULL(liste.queue, "La queue devrait être NULL");
    ASSERT_EQUAL(0, liste.taille, "La taille devrait être 0");
    ASSERT_FALSE(liste.estCirculaire, "La liste ne devrait pas être circulaire");
}

TEST_CASE(TestEstVideDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    ASSERT_TRUE(EstVide(&liste), "La liste devrait être vide");
    
    InsererDebut(&liste, 1);
    ASSERT_FALSE(EstVide(&liste), "La liste ne devrait pas être vide après insertion");
    
    Nettoyer(&liste);
}

TEST_CASE(TestNettoyerDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererDebut(&liste, 1);
    InsererDebut(&liste, 2);
    InsererDebut(&liste, 3);
    
    ASSERT_FALSE(EstVide(&liste), "La liste ne devrait pas être vide avant nettoyage");
    
    Nettoyer(&liste);
    
    ASSERT_TRUE(EstVide(&liste), "La liste devrait être vide après nettoyage");
    ASSERT_NULL(liste.tete, "La tête devrait être NULL");
    ASSERT_NULL(liste.queue, "La queue devrait être NULL");
    ASSERT_EQUAL(0, liste.taille, "La taille devrait être 0");
    
    Nettoyer(&liste);
}

// ============================================================================
// TESTS D'INSERTION
// ============================================================================

TEST_CASE(TestInsererDebutDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererDebut(&liste, 10);
    ASSERT_NOT_NULL(liste.tete, "La tête ne devrait pas être NULL");
    ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait contenir 10");
    ASSERT_EQUAL(1, liste.taille, "La taille devrait être 1");
    ASSERT_EQUAL(liste.tete, liste.queue, "Tête et queue devraient être identiques pour un seul élément");
    ASSERT_NULL(liste.tete->precedent, "Le précédent de la tête devrait être NULL");
    ASSERT_NULL(liste.tete->suivant, "Le suivant de la tête devrait être NULL");
    
    InsererDebut(&liste, 20);
    ASSERT_EQUAL(20, liste.tete->donnee, "La nouvelle tête devrait être 20");
    ASSERT_EQUAL(10, liste.queue->donnee, "La queue devrait rester 10");
    ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
    ASSERT_EQUAL(liste.tete, liste.queue->precedent, "La queue devrait pointer vers la tête comme précédent");
    
    Nettoyer(&liste);
}

TEST_CASE(TestInsererFinDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    ASSERT_NOT_NULL(liste.queue, "La queue ne devrait pas être NULL");
    ASSERT_EQUAL(10, liste.queue->donnee, "La queue devrait contenir 10");
    ASSERT_EQUAL(1, liste.taille, "La taille devrait être 1");
    
    InsererFin(&liste, 20);
    ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait rester 10");
    ASSERT_EQUAL(20, liste.queue->donnee, "La nouvelle queue devrait être 20");
    ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
    ASSERT_EQUAL(liste.queue, liste.tete->suivant, "La tête devrait pointer vers la queue comme suivant");
    ASSERT_EQUAL(liste.tete, liste.queue->precedent, "La queue devrait pointer vers la tête comme précédent");
    
    Nettoyer(&liste);
}

TEST_CASE(TestInsererAvantDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 30);
    
    NoeudD* noeud30 = liste.queue;
    ASSERT_TRUE(InsererAvant(&liste, noeud30, 20), "Insertion avant devrait réussir");
    
    ASSERT_EQUAL(3, liste.taille, "La taille devrait être 3");
    ASSERT_EQUAL(20, liste.tete->suivant->donnee, "Le deuxième élément devrait être 20");
    ASSERT_EQUAL(liste.tete, liste.tete->suivant->precedent, "Le précédent du nouveau nœud devrait être la tête");
    ASSERT_EQUAL(noeud30, liste.tete->suivant->suivant, "Le suivant du nouveau nœud devrait être le nœud 30");
    ASSERT_EQUAL(liste.tete->suivant, noeud30->precedent, "Le précédent du nœud 30 devrait être le nouveau nœud");
    
    Nettoyer(&liste);
}

TEST_CASE(TestInsererApresDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 30);
    
    NoeudD* noeud10 = liste.tete;
    ASSERT_TRUE(InsererApres(&liste, noeud10, 20), "Insertion après devrait réussir");
    
    ASSERT_EQUAL(3, liste.taille, "La taille devrait être 3");
    ASSERT_EQUAL(20, liste.tete->suivant->donnee, "Le deuxième élément devrait être 20");
    ASSERT_EQUAL(noeud10, liste.tete->suivant->precedent, "Le précédent du nouveau nœud devrait être le nœud 10");
    ASSERT_EQUAL(liste.queue, liste.tete->suivant->suivant, "Le suivant du nouveau nœud devrait être la queue");
    ASSERT_EQUAL(liste.tete->suivant, liste.queue->precedent, "Le précédent de la queue devrait être le nouveau nœud");
    
    Nettoyer(&liste);
}

TEST_CASE(TestInsererPositionDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
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
    
    // Vérification des liens
    ASSERT_EQUAL(liste.tete, liste.tete->suivant->precedent, "Lien précédent devrait être correct");
    ASSERT_EQUAL(liste.queue, liste.queue->precedent->suivant, "Lien suivant devrait être correct");
    
    Nettoyer(&liste);
}

TEST_CASE(TestInsererTrieDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererTrie(&liste, 20);
    InsererTrie(&liste, 10);
    InsererTrie(&liste, 30);
    InsererTrie(&liste, 15);
    
    ASSERT_EQUAL(4, liste.taille, "La taille devrait être 4");
    ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait être 10");
    ASSERT_EQUAL(15, liste.tete->suivant->donnee, "Le deuxième élément devrait être 15");
    ASSERT_EQUAL(20, liste.tete->suivant->suivant->donnee, "Le troisième élément devrait être 20");
    ASSERT_EQUAL(30, liste.queue->donnee, "La queue devrait être 30");
    
    // Vérification des liens
    NoeudD* courant = liste.tete;
    while (courant != nullptr) {
        if (courant->suivant != nullptr) {
            ASSERT_EQUAL(courant, courant->suivant->precedent, "Lien précédent devrait être cohérent");
        }
        if (courant->precedent != nullptr) {
            ASSERT_EQUAL(courant, courant->precedent->suivant, "Lien suivant devrait être cohérent");
        }
        courant = courant->suivant;
    }
    
    Nettoyer(&liste);
}

// ============================================================================
// TESTS DE SUPPRESSION
// ============================================================================

TEST_CASE(TestSupprimerDebutDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    // Suppression liste vide
    ASSERT_FALSE(SupprimerDebut(&liste), "Suppression liste vide devrait échouer");
    
    InsererDebut(&liste, 10);
    InsererDebut(&liste, 20);
    
    ASSERT_TRUE(SupprimerDebut(&liste), "Suppression début devrait réussir");
    ASSERT_EQUAL(10, liste.tete->donnee, "La nouvelle tête devrait être 10");
    ASSERT_EQUAL(1, liste.taille, "La taille devrait être 1");
    ASSERT_NULL(liste.tete->precedent, "Le précédent de la tête devrait être NULL");
    
    ASSERT_TRUE(SupprimerDebut(&liste), "Suppression dernier élément devrait réussir");
    ASSERT_TRUE(EstVide(&liste), "La liste devrait être vide");
    
    Nettoyer(&liste);
}

TEST_CASE(TestSupprimerFinDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    // Suppression liste vide
    ASSERT_FALSE(SupprimerFin(&liste), "Suppression liste vide devrait échouer");
    
    InsererDebut(&liste, 10);
    InsererDebut(&liste, 20);
    
    ASSERT_TRUE(SupprimerFin(&liste), "Suppression fin devrait réussir");
    ASSERT_EQUAL(20, liste.tete->donnee, "La tête devrait rester 20");
    ASSERT_EQUAL(20, liste.queue->donnee, "La queue devrait être 20");
    ASSERT_EQUAL(1, liste.taille, "La taille devrait être 1");
    ASSERT_NULL(liste.queue->suivant, "Le suivant de la queue devrait être NULL");
    
    Nettoyer(&liste);
}

TEST_CASE(TestSupprimerNoeudDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    NoeudD* noeud20 = liste.tete->suivant;
    ASSERT_TRUE(SupprimerNoeud(&liste, noeud20), "Suppression nœud milieu devrait réussir");
    
    ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
    ASSERT_EQUAL(30, liste.tete->suivant->donnee, "Le suivant de la tête devrait être 30");
    ASSERT_EQUAL(liste.tete, liste.tete->suivant->precedent, "Le précédent du nœud 30 devrait être la tête");
    
    Nettoyer(&liste);
}

TEST_CASE(TestSupprimerValeurDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
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
    
    Nettoyer(&liste);
}

TEST_CASE(TestSupprimerToutesOccurrencesDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
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
    
    // Vérification des liens
    ASSERT_EQUAL(liste.queue, liste.tete->suivant, "La tête devrait pointer vers la queue");
    ASSERT_EQUAL(liste.tete, liste.queue->precedent, "La queue devrait pointer vers la tête");
    
    Nettoyer(&liste);
}

TEST_CASE(TestSupprimerPositionDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    // Suppression position valide
    ASSERT_TRUE(SupprimerPosition(&liste, 1), "Suppression position 1 devrait réussir");
    ASSERT_EQUAL(2, liste.taille, "La taille devrait être 2");
    ASSERT_EQUAL(10, liste.tete->donnee, "La tête devrait être 10");
    ASSERT_EQUAL(30, liste.queue->donnee, "La queue devrait être 30");
    
    // Vérification des liens
    ASSERT_EQUAL(liste.queue, liste.tete->suivant, "La tête devrait pointer vers la queue");
    ASSERT_EQUAL(liste.tete, liste.queue->precedent, "La queue devrait pointer vers la tête");
    
    // Suppression position invalide
    ASSERT_FALSE(SupprimerPosition(&liste, 5), "Suppression position invalide devrait échouer");
    
    Nettoyer(&liste);
}

// ============================================================================
// TESTS DE RECHERCHE
// ============================================================================

TEST_CASE(TestRechercherValeurDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    NoeudD* resultat = RechercherValeur(&liste, 20);
    ASSERT_NOT_NULL(resultat, "Devrait trouver la valeur 20");
    ASSERT_EQUAL(20, resultat->donnee, "Le nœud trouvé devrait contenir 20");
    
    resultat = RechercherValeur(&liste, 40);
    ASSERT_NULL(resultat, "Ne devrait pas trouver la valeur 40");
    
    Nettoyer(&liste);
}

TEST_CASE(TestRechercherToutesOccurrencesDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 10);
    InsererFin(&liste, 30);
    InsererFin(&liste, 10);
    
    int count = 0;
    NoeudD** resultats = RechercherToutesOccurrences(&liste, 10, &count);
    
    ASSERT_EQUAL(3, count, "Devrait trouver 3 occurrences");
    ASSERT_NOT_NULL(resultats, "Le tableau de résultats ne devrait pas être NULL");
    
    for (int i = 0; i < count; i++) {
        ASSERT_NOT_NULL(resultats[i], "Chaque résultat devrait être non NULL");
        ASSERT_EQUAL(10, resultats[i]->donnee, "Chaque résultat devrait contenir 10");
    }
    
    ASSERT_NULL(resultats[count], "Le tableau devrait se terminer par NULL");
    
    free(resultats);
    Nettoyer(&liste);
}

TEST_CASE(TestObtenirNoeudPositionDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    NoeudD* noeud = ObtenirNoeudPosition(&liste, 0);
    ASSERT_NOT_NULL(noeud, "Devrait obtenir le nœud à position 0");
    ASSERT_EQUAL(10, noeud->donnee, "Le nœud devrait contenir 10");
    
    noeud = ObtenirNoeudPosition(&liste, 1);
    ASSERT_EQUAL(20, noeud->donnee, "Le nœud devrait contenir 20");
    
    noeud = ObtenirNoeudPosition(&liste, 2);
    ASSERT_EQUAL(30, noeud->donnee, "Le nœud devrait contenir 30");
    
    noeud = ObtenirNoeudPosition(&liste, 5);
    ASSERT_NULL(noeud, "Position invalide devrait retourner NULL");
    
    Nettoyer(&liste);
}

TEST_CASE(TestObtenirNoeudPositionInverseDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    NoeudD* noeud = ObtenirNoeudPositionInverse(&liste, 0);
    ASSERT_NOT_NULL(noeud, "Devrait obtenir le nœud à position inverse 0");
    ASSERT_EQUAL(30, noeud->donnee, "Le nœud devrait contenir 30 (dernier)");
    
    noeud = ObtenirNoeudPositionInverse(&liste, 1);
    ASSERT_EQUAL(20, noeud->donnee, "Le nœud devrait contenir 20 (avant-dernier)");
    
    noeud = ObtenirNoeudPositionInverse(&liste, 2);
    ASSERT_EQUAL(10, noeud->donnee, "Le nœud devrait contenir 10 (premier depuis la fin)");
    
    noeud = ObtenirNoeudPositionInverse(&liste, 5);
    ASSERT_NULL(noeud, "Position inverse invalide devrait retourner NULL");
    
    Nettoyer(&liste);
}

// ============================================================================
// TESTS DE TRANSFORMATION
// ============================================================================

TEST_CASE(TestRendreCirculaireDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    RendreCirculaire(&liste);
    ASSERT_TRUE(liste.estCirculaire, "La liste devrait être marquée comme circulaire");
    ASSERT_EQUAL(liste.tete, liste.queue->suivant, "La queue devrait pointer vers la tête");
    ASSERT_EQUAL(liste.queue, liste.tete->precedent, "La tête devrait pointer vers la queue comme précédent");
    
    RendreLineaire(&liste);
    ASSERT_FALSE(liste.estCirculaire, "La liste ne devrait plus être circulaire");
    ASSERT_NULL(liste.queue->suivant, "La queue devrait pointer vers NULL");
    ASSERT_NULL(liste.tete->precedent, "La tête devrait avoir précédent NULL");
    
    Nettoyer(&liste);
}

TEST_CASE(TestInverserDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    Inverser(&liste);
    
    ASSERT_EQUAL(30, liste.tete->donnee, "La nouvelle tête devrait être 30");
    ASSERT_EQUAL(20, liste.tete->suivant->donnee, "Le deuxième élément devrait être 20");
    ASSERT_EQUAL(10, liste.queue->donnee, "La nouvelle queue devrait être 10");
    ASSERT_EQUAL(3, liste.taille, "La taille devrait rester 3");
    
    // Vérification des liens inversés
    ASSERT_NULL(liste.tete->precedent, "Le précédent de la tête devrait être NULL");
    ASSERT_NULL(liste.queue->suivant, "Le suivant de la queue devrait être NULL");
    ASSERT_EQUAL(liste.tete, liste.tete->suivant->precedent, "Le précédent du deuxième devrait être la tête");
    ASSERT_EQUAL(liste.queue, liste.queue->precedent->suivant, "Le suivant de l'avant-dernier devrait être la queue");
    
    Nettoyer(&liste);
}

TEST_CASE(TestTrierDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 30);
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 5);
    
    Trier(&liste);
    
    ASSERT_EQUAL(5, liste.tete->donnee, "La tête devrait être 5");
    ASSERT_EQUAL(10, liste.tete->suivant->donnee, "Le deuxième élément devrait être 10");
    ASSERT_EQUAL(20, liste.tete->suivant->suivant->donnee, "Le troisième élément devrait être 20");
    ASSERT_EQUAL(30, liste.queue->donnee, "La queue devrait être 30");
    
    // Vérification de la cohérence des liens
    NoeudD* courant = liste.tete;
    while (courant->suivant != nullptr) {
        ASSERT_EQUAL(courant, courant->suivant->precedent, "Le lien précédent devrait être cohérent");
        courant = courant->suivant;
    }
    
    Nettoyer(&liste);
}

// ============================================================================
// TESTS DE FONCTIONNALITÉS AVANCÉES
// ============================================================================

TEST_CASE(TestCopierDouble) {
    ListeDouble originale;
    Initialiser(&originale);
    
    InsererFin(&originale, 10);
    InsererFin(&originale, 20);
    InsererFin(&originale, 30);
    
    ListeDouble* copie = Copier(&originale);
    
    ASSERT_EQUAL(originale.taille, copie->taille, "La copie devrait avoir la même taille");
    ASSERT_EQUAL(10, copie->tete->donnee, "La tête de la copie devrait être 10");
    ASSERT_EQUAL(20, copie->tete->suivant->donnee, "Le deuxième élément de la copie devrait être 20");
    ASSERT_EQUAL(30, copie->queue->donnee, "La queue de la copie devrait être 30");
    
    // Vérifier que c'est une vraie copie (pas la même mémoire)
    ASSERT_NOT_EQUAL(originale.tete, copie->tete, "Les têtes ne devraient pas pointer vers la même mémoire");
    
    // Vérifier la cohérence des liens dans la copie
    ASSERT_EQUAL(copie->tete, copie->tete->suivant->precedent, "Lien précédent devrait être cohérent dans la copie");
    
    Nettoyer(&originale);
    Detruire(copie);
}

TEST_CASE(TestConcatenerDouble) {
    ListeDouble liste1, liste2;
    Initialiser(&liste1);
    Initialiser(&liste2);
    
    InsererFin(&liste1, 10);
    InsererFin(&liste1, 20);
    
    InsererFin(&liste2, 30);
    InsererFin(&liste2, 40);
    
    Concatener(&liste1, &liste2);
    
    ASSERT_EQUAL(4, liste1.taille, "La liste concaténée devrait avoir 4 éléments");
    ASSERT_EQUAL(10, liste1.tete->donnee, "La tête devrait rester 10");
    ASSERT_EQUAL(40, liste1.queue->donnee, "La queue devrait être 40");
    
    // Vérification des liens entre les deux listes
    ASSERT_EQUAL(30, liste1.tete->suivant->suivant->donnee, "Le troisième élément devrait être 30");
    ASSERT_EQUAL(liste1.tete->suivant, liste1.tete->suivant->suivant->precedent, "Lien précédent devrait être correct entre les listes");
    
    Nettoyer(&liste1);
    Nettoyer(&liste2);
}

TEST_CASE(TestDiviserDouble) {
    ListeDouble liste, liste2;
    Initialiser(&liste);
    Initialiser(&liste2);
    
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
    
    // Vérification des liens
    ASSERT_NULL(liste.queue->suivant, "La queue de la première liste devrait pointer vers NULL");
    ASSERT_NULL(liste2.tete->precedent, "La tête de la deuxième liste devrait avoir précédent NULL");
    
    Nettoyer(&liste);
    Nettoyer(&liste2);
}

TEST_CASE(TestEchangerNoeudsDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    InsererFin(&liste, 40);
    
    NoeudD* noeud20 = liste.tete->suivant;
    NoeudD* noeud40 = liste.queue;
    
    ASSERT_TRUE(EchangerNoeuds(&liste, noeud20, noeud40), "Échange devrait réussir");
    
    ASSERT_EQUAL(40, liste.tete->suivant->donnee, "Le deuxième élément devrait être 40 après échange");
    ASSERT_EQUAL(20, liste.queue->donnee, "Le dernier élément devrait être 20 après échange");
    
    // Vérification des liens
    ASSERT_EQUAL(liste.tete, liste.tete->suivant->precedent, "Lien précédent du nœud 40 devrait être correct");
    ASSERT_EQUAL(liste.queue->precedent, liste.tete->suivant->suivant, "Lien suivant du nœud 40 devrait être correct");
    
    Nettoyer(&liste);
}

TEST_CASE(TestRotationDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    InsererFin(&liste, 40);
    
    RotationGauche(&liste, 1);
    ASSERT_EQUAL(20, liste.tete->donnee, "Après rotation gauche, tête devrait être 20");
    ASSERT_EQUAL(10, liste.queue->donnee, "Après rotation gauche, queue devrait être 10");
    
    RotationDroite(&liste, 1);
    ASSERT_EQUAL(10, liste.tete->donnee, "Après rotation droite, tête devrait être 10");
    ASSERT_EQUAL(40, liste.queue->donnee, "Après rotation droite, queue devrait être 40");
    
    Nettoyer(&liste);
}

TEST_CASE(TestSupprimerDoublonsTriesDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
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
    
    Nettoyer(&liste);
}

TEST_CASE(TestSupprimerDoublonsNonTriesDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 10);
    InsererFin(&liste, 30);
    InsererFin(&liste, 20);
    InsererFin(&liste, 10);
    
    SupprimerDoublonsNonTries(&liste);
    
    ASSERT_EQUAL(3, liste.taille, "Devrait avoir 3 éléments après suppression des doublons");
    
    Nettoyer(&liste);
}

TEST_CASE(TestFusionnerListesTrieesDouble) {
    ListeDouble liste1, liste2;
    Initialiser(&liste1);
    Initialiser(&liste2);
    
    InsererFin(&liste1, 10);
    InsererFin(&liste1, 30);
    InsererFin(&liste1, 50);
    
    InsererFin(&liste2, 20);
    InsererFin(&liste2, 40);
    InsererFin(&liste2, 60);
    
    ListeDouble* fusion = FusionnerListesTriees(&liste1, &liste2);
    
    ASSERT_EQUAL(6, fusion->taille, "La fusion devrait avoir 6 éléments");
    
    NoeudD* courant = fusion->tete;
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
    
    Nettoyer(&liste1);
    Nettoyer(&liste2);
    Detruire(fusion);
}

TEST_CASE(TestTrouverMilieuDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    // Liste impaire
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    NoeudD* milieu = TrouverMilieu(&liste);
    ASSERT_NOT_NULL(milieu, "Devrait trouver le milieu");
    ASSERT_EQUAL(20, milieu->donnee, "Le milieu devrait être 20");
    
    Nettoyer(&liste);
    
    // Liste paire
    Initialiser(&liste);
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    InsererFin(&liste, 40);
    
    milieu = TrouverMilieu(&liste);
    ASSERT_NOT_NULL(milieu, "Devrait trouver le milieu");
    ASSERT_EQUAL(30, milieu->donnee, "Le milieu devrait être 30 (deuxième milieu)");
    
    Nettoyer(&liste);
}

TEST_CASE(TestEstPalindromeDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    // Test liste vide
    ASSERT_TRUE(EstPalindrome(&liste), "Liste vide devrait être un palindrome");
    
    // Test un élément
    InsererFin(&liste, 10);
    ASSERT_TRUE(EstPalindrome(&liste), "Liste à un élément devrait être un palindrome");
    
    // Test palindrome pair
    Initialiser(&liste);
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 20);
    InsererFin(&liste, 10);
    ASSERT_TRUE(EstPalindrome(&liste), "Liste palindrome devrait retourner true");
    
    Nettoyer(&liste);
    
    // Test non-palindrome
    Initialiser(&liste);
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    ASSERT_FALSE(EstPalindrome(&liste), "Liste non-palindrome devrait retourner false");
    
    Nettoyer(&liste);
}

// ============================================================================
// TESTS DE ROBUSTESSE
// ============================================================================

TEST_CASE(TestContientCycleDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    // Liste linéaire ne devrait pas avoir de cycle
    ASSERT_FALSE(ContientCycle(&liste), "Liste linéaire ne devrait pas avoir de cycle");
    
    // Liste circulaire devrait détecter un cycle
    RendreCirculaire(&liste);
    ASSERT_TRUE(ContientCycle(&liste), "Liste circulaire devrait détecter un cycle");
    
    Nettoyer(&liste);
}

TEST_CASE(TestToStringDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    // Test liste vide
    std::string resultatVide = ToString(&liste);
    ASSERT_TRUE(resultatVide.find("ListeDouble[]") != std::string::npos, "ToString liste vide incorrect");
    
    // Test avec éléments
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    
    std::string resultat = ToString(&liste);
    ASSERT_TRUE(resultat.find("10") != std::string::npos, "ToString devrait contenir 10");
    ASSERT_TRUE(resultat.find("20") != std::string::npos, "ToString devrait contenir 20");
    ASSERT_TRUE(resultat.find("<->") != std::string::npos, "ToString devrait contenir des doubles flèches");
    
    Nettoyer(&liste);
}

TEST_CASE(TestCompterElementsDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    ASSERT_EQUAL(0, CompterElements(&liste), "Liste vide devrait avoir 0 éléments");
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    ASSERT_EQUAL(3, CompterElements(&liste), "Liste avec 3 éléments devrait retourner 3");
    
    Nettoyer(&liste);
}

TEST_CASE(TestParcoursBidirectionnel) {
    ListeDouble liste;
    Initialiser(&liste);
    
    InsererFin(&liste, 10);
    InsererFin(&liste, 20);
    InsererFin(&liste, 30);
    
    // Parcours avant
    NoeudD* courant = liste.tete;
    int valeursAvant[3];
    int i = 0;
    while (courant != nullptr) {
        valeursAvant[i++] = courant->donnee;
        courant = courant->suivant;
    }
    ASSERT_EQUAL(10, valeursAvant[0], "Parcours avant - premier élément");
    ASSERT_EQUAL(20, valeursAvant[1], "Parcours avant - deuxième élément");
    ASSERT_EQUAL(30, valeursAvant[2], "Parcours avant - troisième élément");
    
    // Parcours arrière
    courant = liste.queue;
    int valeursArriere[3];
    i = 0;
    while (courant != nullptr) {
        valeursArriere[i++] = courant->donnee;
        courant = courant->precedent;
    }
    ASSERT_EQUAL(30, valeursArriere[0], "Parcours arrière - premier élément");
    ASSERT_EQUAL(20, valeursArriere[1], "Parcours arrière - deuxième élément");
    ASSERT_EQUAL(10, valeursArriere[2], "Parcours arrière - troisième élément");
    
    Nettoyer(&liste);
}

TEST_CASE(TestIntegrationCompletDouble) {
    ListeDouble liste;
    Initialiser(&liste);
    
    // Scénario d'utilisation complet
    InsererDebut(&liste, 5);
    InsererFin(&liste, 15);
    InsererPosition(&liste, 1, 10);
    
    ASSERT_EQUAL(3, liste.taille, "Taille devrait être 3 après insertions");
    ASSERT_EQUAL(5, liste.tete->donnee, "Tête incorrecte");
    ASSERT_EQUAL(15, liste.queue->donnee, "Queue incorrecte");
    
    // Vérification des liens
    ASSERT_EQUAL(10, liste.tete->suivant->donnee, "Deuxième élément incorrect");
    ASSERT_EQUAL(liste.tete, liste.tete->suivant->precedent, "Lien précédent incorrect");
    ASSERT_EQUAL(liste.queue, liste.tete->suivant->suivant, "Lien suivant incorrect");
    
    // Recherche et suppression
    NoeudD* noeud10 = RechercherValeur(&liste, 10);
    ASSERT_NOT_NULL(noeud10, "Devrait trouver la valeur 10");
    
    SupprimerValeur(&liste, 10);
    ASSERT_EQUAL(2, liste.taille, "Taille devrait être 2 après suppression");
    
    // Transformation
    Inverser(&liste);
    ASSERT_EQUAL(15, liste.tete->donnee, "Tête après inversion incorrecte");
    ASSERT_EQUAL(5, liste.queue->donnee, "Queue après inversion incorrecte");
    
    // Vérification des liens après inversion
    ASSERT_NULL(liste.tete->precedent, "Précédent de la tête après inversion devrait être NULL");
    ASSERT_NULL(liste.queue->suivant, "Suivant de la queue après inversion devrait être NULL");
    ASSERT_EQUAL(liste.tete, liste.queue->precedent, "Lien précédent de la queue après inversion incorrect");
    
    // Test avec liste circulaire
    RendreCirculaire(&liste);
    ASSERT_TRUE(liste.estCirculaire, "La liste devrait être circulaire");
    
    Nettoyer(&liste);
}

TEST_CASE(TestGestionMemoireDouble) {
    // Test de création/destruction multiple
    for (int i = 0; i < 10; i++) {
        ListeDouble* liste = AllocateDouble();
        ASSERT_NOT_NULL(liste, "La liste devrait être créée");
        
        for (int j = 0; j < 5; j++) {
            InsererFin(liste, j);
        }
        
        ASSERT_EQUAL(5, liste->taille, "La liste devrait avoir 5 éléments");
        
        Detruire(liste);
    }
}