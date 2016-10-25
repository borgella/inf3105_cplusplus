#if !defined(__GRAPHE_H__)
#define __GRAPHE_H__

#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <map>
#include <vector>

template <class S, class A> 

class Graphe{
	
	public:
		class Sommet{
		      public:
			  Sommet(const S& s_) : s(s_){}
			    S s;
			  std::map<int,A> voisins; // ou arretesSortants qui est egal a un sommet qui rentre aussi dans le graphe, ici int vaut un Sommet
			  mutable bool visite;
			  mutable A courant; // pour avoir l info sur le type de relation 
			  //pour aide Prim
			  std::map<A,int> voisinMini; // a une relation est associe un sommet
		 };
	
	// variable d'instances de la classe Graphe
	// on associe un indice a chaque sommet pour eviter O(n) a chaque fois qu'on veut une info sur un sommet,exmpl: s'il est present etc...	
	std::map<S,int> sommetIndice; // a un sommet est associe un indice
	std::map<int,S> aide; // a un indice est associe un sommet
	std::vector<Sommet> sommets;

	void ajouterSommet(const S& s);
	void ajouterArrete(const S& a, const S& b, const A& etiquette);
	void parcoursRechercheLargueur(const S& s) ;
	void primAlgo(const S& s);	
	 
	void ajouterArrete2(std::list<S>som, const A& etiquette); 
  	bool operator < (const Sommet &autre )const{
	  Sommet autre2 = autre;
	  //return this.courant < autre2.courant;
	  return false;
  	}
};	
	
#include <assert.h>

template <class S,class A>
void Graphe<S,A>::ajouterSommet(const S& s){
	typename std::map<S,int>::iterator it = sommetIndice.find(s);
	assert(!(it != sommetIndice.end()));
	int indice = sommetIndice.size();
	sommetIndice[s] = indice; // ici on associe un sommet a un indice et le premier sommet aura l indice 0
	sommets.push_back(Sommet(s));
	// code pour aide
	aide[indice] = s; // ici on associe un sommet a un indice et le premier sommet aura l indice 0ß
}

template <class S,class A>
void Graphe<S,A>::ajouterArrete(const S& sa, const S& sb, const A& etiquette){
	int iA = sommetIndice[sa];
	int iB = sommetIndice[sb];
	sommets[iA].voisins[iB] = etiquette;
	sommets[iB].voisins[iA] = etiquette;
}

template< class S,class A>
void Graphe<S,A>::ajouterArrete2(std::list<S>listeSommet, const A& etiquette){
    typename std::list<S>::iterator iter(listeSommet.begin());
    if(iter == listeSommet.end())return;
    while(listeSommet.size() > 1){
	    S sommetA = listeSommet.front();
	    listeSommet.remove(sommetA);
	    iter = listeSommet.begin();
	    while(iter != listeSommet.end()){
	    	ajouterArrete(sommetA,*iter,etiquette);
		iter++;
	   }
    }
}


//std::map<int,A> voisins; // voisins
template <class S,class A>
void Graphe<S,A>::parcoursRechercheLargueur(const S& s){
    for(typename std::vector<Sommet>::iterator iter = sommets.begin();iter!=sommets.end();++iter)
        iter->visite = false;
    std::queue<S> file;
    file.push(s);
    while(!file.empty()){
        S suivant = file.front();
        file.pop();
        const Sommet& sommet = sommets.at(sommetIndice[suivant]);
        if(sommet.visite) continue;
        std::cout << suivant << " ";
        sommet.visite = true;
        for(typename std::map<int,A>::const_iterator iter(sommet.voisins.begin());iter!=sommet.voisins.end();++iter)
		 file.push(aide[iter->first]);
    }
    std::cout <<" "<<std::endl;
}

template <class S,class A>
void Graphe<S,A>::primAlgo(const S& s){
       for(typename std::vector<Sommet>::iterator iter = sommets.begin();iter!=sommets.end();++iter)
           iter->visite = false;
       std::queue<S> file;
       file.push(s);
       while(!file.empty()){
           S suivant = file.front();
           file.pop();
           const Sommet& sommet = sommets.at(sommetIndice[suivant]);
           if(sommet.visite) continue;
           std::cout << suivant << " ";
           sommet.visite = true;
	    typename std::map<int,A>::const_iterator iter(sommet.voisins.begin());
	    A mini = iter->second;
	    //++iter;
           for(;iter!=sommet.voisins.end();++iter){
		    if(mini < iter->second)
			    mini = iter->second;
           }
	    typename std::map<A,int>::const_iterator iter2(sommet.voisinMini.begin());
   	    file.push(aide[iter->second]);
       }
       std::cout <<" "<<std::endl;
}



#endif
