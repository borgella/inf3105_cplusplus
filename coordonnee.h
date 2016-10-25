/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  été 2015   / TP3                                     *
 *  Eric Beaudry - beaudry.eric@uqam.ca - ericbeaudry.ca */

#if !defined(_COORDONNEE__H_)
#define _COORDONNEE__H_
#include <iostream>

class Coordonnee {
  private:
    double latitude;
    double longitude;	
  public:
    Coordonnee(){}
    Coordonnee(double latitude_, double longitude_);
    Coordonnee(const Coordonnee&);
    double distance(const Coordonnee&) const;
    bool operator == (const Coordonnee &autre)const;
    bool operator < (const Coordonnee &autre)const;
  private: 
  	friend std::ostream& operator << (std::ostream&, const Coordonnee&);
 	  friend std::istream& operator >> (std::istream&, Coordonnee&);
};

#endif

