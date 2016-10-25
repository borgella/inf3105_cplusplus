/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Automne 2015/ TP3
 *  nom => BORGELLA JEAN MARY 
 */

#if !defined(_CARTE__H_)
#define _CARTE__H_
#include "coordonnee.h"
#include <cassert>
#include <istream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Carte{
  public:
  	     Carte();
  	       void ajouterSommet(string nom,Coordonnee coor);
  	       void ajouterArrete(string rue,vector<string>sommet, int etiquette);
	       void parcoursRechercheLargueur();
	       bool relationExiste(const string nomSommet,int max);
	       void ajouterLesRelations(list<string> listenomSommet);
	       double distanceEntre2Sommets(int indiceSomA,int indiceSomB);
	       void afficherlesVoisins(queue<int> listenomSommet);
	       int positionSommetCorrespondant(const string nomSommet,int max);
	       void decreaseKey(int sommet1,int sommet2);
  	       void primAlgo();
	       string trouverLaRue(const string nomSommet,int max);

  private: class Sommet{

		private:
   	    	  string nomSommet;
	    	 	  Coordonnee coor;
	     	 	  map<int,map<string,int> > relationVoisins; // int c est un sommet et map<rue,poids> renpresente A qui est la relation
	    	 	  map<int,double> relationDistance;
	     	  	mutable bool visite;
      		public:
	  	          Sommet(string nomSommet,Coordonnee coor){
			          this->nomSommet = nomSommet;
			          this->coor = coor;
			          this->visite = false;
	  	     }
		      Coordonnee getCoordonnee(){
			         return this->coor;
		      }
		     string getNom(){
			        return this->nomSommet;
		     }
		     bool operator < (Sommet& autre){
			        return this->coor < autre.coor;
		     }
		     private: friend class Carte;
	   };
   	  // variable d'instances de la classe Graphe
   	  // on associe un indice a chaque sommet pour eviter O(n) a chaque fois qu'on veut une info sur un sommet,exmpl: s'il est present etc...
   	  map<string,int> sommetIndice; // a un sommet est associe un indice ici S est represente par string
   	  map<int,string> aide; // a un indice est associe un sommet
   	  vector<Sommet> sommets;
      	  void ajouterArrete2(string sommetA,string sommetB,string rue, int etiquette);
	  int extractMaxUnSommet(string s);
	  int extractMaxSommetGraphe(list<int> liste);
	  int extractMaxSommetGraphe(string nom);
	  queue<Sommet> sommetsNonVisite;
  	  friend istream& operator >> (istream& is, Carte& carte);
};

#endif
