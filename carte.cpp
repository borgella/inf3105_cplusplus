/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  Automne 2015 / TP3
 *  nom => BORGELLA JEAN MARY
 */

#include <cstdio>
#include <stdlib.h>
#include <ctype.h>
#include <limits>
#include <math.h>
#include <queue>
#include <sstream>
#include "carte.h"

Carte::Carte(){}

void Carte::ajouterSommet(string nom,Coordonnee coor){
    map<string,int>::iterator it = sommetIndice.find(nom);
    assert(!(it != sommetIndice.end()));
    int indice = sommetIndice.size();
    sommetIndice[nom] = indice;
    sommets.push_back(Sommet(nom,coor));
    // code pour aide
    aide[indice] = nom;
    sommetsNonVisite.push(Sommet(nom,coor));
}

void Carte::ajouterArrete(string rue,vector<string>listeSommet, int etiquette){
	int i = 0;
	while(i < listeSommet.size()){
		string nomSommetA = listeSommet[i];
		for(int j = i+1; j < listeSommet.size();j++){
			ajouterArrete2(nomSommetA,listeSommet[j],rue,etiquette);
		}
		i++;
	}
}

void Carte::ajouterArrete2(string nomSommetA,string nomSommetB,string rue, int etiquette){
	int iA = sommetIndice[nomSommetA];
	int iB = sommetIndice[nomSommetB];
	double distance = distanceEntre2Sommets(iA, iB);
	sommets[iA].relationVoisins[iB][rue] = etiquette;
	sommets[iB].relationVoisins[iA][rue] = etiquette;	
	sommets[iA].relationDistance[iB] = distance;
	sommets[iB].relationDistance[iA] = distance;
}

double Carte::distanceEntre2Sommets(int indiceSomA,int indiceSomB){
	Sommet somA = sommets.at(indiceSomA);
	Sommet somB = sommets.at(indiceSomB);
	Coordonnee coorA = somA.getCoordonnee();
	Coordonnee coorB = somB.getCoordonnee();
	return coorA.distance(coorB);
}

istream& operator >> (istream& is, Carte& carte){
	while(is){
	   string nomSommet;
	   is >> nomSommet;
	   if(nomSommet == "---") break;
	        Coordonnee coor;
	        is >> coor;
	        carte.ajouterSommet(nomSommet, coor);
	}
       string nomRue;
       char deuxpoints;
       is >> nomRue >> deuxpoints;
	while (is) {
	     string nomSommet;	
	     vector<string> listenomSommet;
	     while (is) {
	           is >> nomSommet;
	           if (nomSommet == ";") break;		    
	           if(isalpha(nomSommet[0]))listenomSommet.push_back(nomSommet);
	           else if(isdigit(nomSommet[0]))carte.ajouterArrete(nomRue, listenomSommet,stoi(nomSommet));
	    }	
	    is >> nomRue >> deuxpoints;	
	}
    return is;
}
// pour l'instant ca a l'air de fonctionner on verra apres la pause
void Carte::primAlgo(){
	int cost = 0;
	queue<Sommet>nonVisite = sommetsNonVisite;
	set<Sommet>chemin;
	queue<int> edgesAvailable;
	list<int> liste;
	
	while(!nonVisite.empty()){
		Sommet& sommet = nonVisite.front();
		liste.push_back(sommetIndice[sommet.getNom()]);
		int indiceSommet1 = sommetIndice[sommet.getNom()];
		nonVisite.pop();
		int max = extractMaxSommetGraphe(liste);
	       if(relationExiste(sommet.getNom(),max)){
			int max2 = extractMaxUnSommet(sommet.getNom());
			int pos = positionSommetCorrespondant(sommet.getNom(),max2);
			cost+= max2;
	       	cout<<aide[indiceSommet1]<<" "<< aide[pos]<<"\n"<<trouverLaRue(sommet.getNom(),max)<<"\n"<<max2<< endl; 
			decreaseKey(indiceSommet1,pos);

	       }else{
			int max2 = extractMaxUnSommet(sommet.getNom());
		       int pos = positionSommetCorrespondant(sommet.getNom(),max2);
			cost+= max2;
	       	cout<<aide[indiceSommet1]<<" "<< aide[pos]<<"\n"<<trouverLaRue(sommet.getNom(),max)<<"\n"<<max2<< endl; 
			decreaseKey(indiceSommet1,pos);
	       }
	}
	cout<<"---"<<"\n"<<cost<<endl;
}

int Carte::extractMaxSommetGraphe(string nom){
	int indice = sommetIndice[nom];
	int sommetMaximum, min = 0;
	sommetMaximum = extractMaxUnSommet(sommets[indice].getNom());
	for(int i = 0 ; i < sommets.size(); i++){
		if(i != indice){
		     min = extractMaxUnSommet(sommets[i].getNom());  
		     if( sommetMaximum < min )
			  	sommetMaximum = min;
	     }
	}
	return sommetMaximum;
}

//cette fonction retourne le sommet maximum pour chaque sommet de la liste. NB les sommets sont des indices.
int Carte::extractMaxSommetGraphe(list<int> liste){
	list<int>::const_iterator iter = liste.begin(); // iter represente l indice d un sommet dans le grand tableau de sommets
	int sommetMaximum, min = 0;
	while(iter != liste.end()){
		sommetMaximum = extractMaxUnSommet(sommets[*iter].getNom());
		for(int i = 0 ; i < sommets.size(); i++){
			if(i != *iter){
			     min = extractMaxUnSommet(sommets[i].getNom());  
			     if( sommetMaximum < min )
				  	sommetMaximum = min;
		     }
		}
	  ++iter;
	}
	return sommetMaximum;
}

// cette fonction retourne le poids le plus fort de la graphe en fonction d'un sommet
int Carte::extractMaxUnSommet(string nomSommet){
	int retour,etiquette = -1;
	int indice = sommetIndice[nomSommet];
	double distance = 0.0;
	const Sommet& sommet = sommets.at(indice);// tres important
       for(map<int,map<string,int> >::const_iterator iter(sommet.relationVoisins.begin()); iter!=sommet.relationVoisins.end(); ++iter){
	 	map<string,int>::const_iterator rueEtiquette = iter->second.begin();
		if(rueEtiquette->second > etiquette){	
			etiquette = rueEtiquette->second;
			retour = etiquette;
			distance = sommets[indice].relationDistance[iter->first];
		}else if(rueEtiquette->second == etiquette && sommets[indice].relationDistance[iter->first] < distance)
			retour = etiquette;	
	}
       return retour;
}

int Carte::positionSommetCorrespondant(const string nomSommet,int max){
       int indice = sommetIndice[nomSommet];
       const Sommet& sommet = sommets.at(indice);
       for(map<int,map<string,int> >::const_iterator iter(sommet.relationVoisins.begin()); iter!=sommet.relationVoisins.end(); ++iter){
   	 	map<string,int>::const_iterator rueEtiquette = iter->second.begin();
   	 	if(rueEtiquette->second == max)
   		 	return iter->first;
   	}
      return false;		
}


void Carte::decreaseKey(int sommet1,int sommet2){
       Sommet& sommet = sommets.at(sommet1);
       for(map<int,map<string,int> >::const_iterator iter(sommet.relationVoisins.begin()); iter!=sommet.relationVoisins.end(); ++iter){
   	 	map<string,int>::const_iterator rueEtiquette = iter->second.begin();
		if(iter->first == sommet2){
	       	sommets[sommet1].relationVoisins[sommet2][rueEtiquette->first] = 0;
			sommets[sommet2].relationVoisins[sommet1][rueEtiquette->first] = 0;
			sommets[sommet1].relationDistance[sommet2] = 0.0;
			sommets[sommet2].relationDistance[sommet1] = 0.0;
			return;
		}
       		 	
   	}
}

bool Carte::relationExiste(const string nomSommet,int max){
    int indice = sommetIndice[nomSommet];
    const Sommet& sommet = sommets.at(indice);
    for(map<int,map<string,int> >::const_iterator iter(sommet.relationVoisins.begin()); iter!=sommet.relationVoisins.end(); ++iter){
		 map<string,int>::const_iterator rueEtiquette = iter->second.begin();
	 	if(rueEtiquette->second == max)
		 	return true;
	}
   return false;		
}

string Carte::trouverLaRue(const string nomSommet,int max){
    int indice = sommetIndice[nomSommet];
    const Sommet& sommet = sommets.at(indice);
    for(map<int,map<string,int> >::const_iterator iter(sommet.relationVoisins.begin()); iter!=sommet.relationVoisins.end(); ++iter){
		 map<string,int>::const_iterator rueEtiquette = iter->second.begin();
	 	if(rueEtiquette->second == max)
		 	return rueEtiquette->first;
	}
   return " ";		
}

void Carte::parcoursRechercheLargueur(){
    const string nomSommet = sommets[0].getNom();
    int indice = sommetIndice[nomSommet];
    queue<int> file;
    file.push(indice);
    while(!file.empty()){
	 indice = file.front();
        file.pop();
        const Sommet& sommet = sommets.at(indice);
        if(sommet.visite) continue;
        cout << aide[indice] << " ";
        sommet.visite = true; 
        for(map<int,map<string,int> >::const_iterator iter(sommet.relationVoisins.begin()); iter!=sommet.relationVoisins.end(); ++iter){
		 file.push(iter->first);
 	}
    }
    std::cout <<" "<<std::endl;	
}
	