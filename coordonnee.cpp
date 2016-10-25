/*  INF3105 - Structures de données et algorithmes       *
 *  UQAM / Département d'informatique                    *
 *  Automne 2015/ TP3                                   *
 *  Eric Beaudry - beaudry.eric@uqam.ca - ericbeaudry.ca 
 * BORGELLA JEAN MARY	
*/

#include <math.h>
#include <assert.h>
#include "coordonnee.h"
#define RAYONTERRE 6371000  // en mètres
#define PI 3.14159265359

Coordonnee::Coordonnee(const Coordonnee& coor)
  : latitude(coor.latitude), longitude(coor.longitude)
{
}

Coordonnee::Coordonnee(double latitude_, double longitude_) 
  : latitude(latitude_), longitude(longitude_)
{
}

double Coordonnee::distance(const Coordonnee& coor) const {
    double s1 = sin((coor.latitude-latitude)/2);
    double s2 = sin((coor.longitude-longitude)/2);
    return 2*RAYONTERRE * asin(sqrt(s1*s1 + cos(latitude)*cos(coor.latitude)*s2*s2));
}

bool Coordonnee::operator == (const Coordonnee &autre)const{
	return latitude == autre.latitude && longitude == autre.longitude ;
}

bool Coordonnee::operator < (const Coordonnee &autre1)const{
	Coordonnee autre = autre1;
	return latitude  < autre.latitude ;
}


std::istream& operator >> (std::istream& is, Coordonnee& coor) {
    char po, vir, pf;
    is >> po;
    if(is){
        is >> coor.latitude >> vir >> coor.longitude >> pf;
        assert(po =='(');
        assert(vir ==',');
        assert(pf ==')');
        coor.longitude *= PI / 180.0;
        coor.latitude  *= PI / 180.0;
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const Coordonnee& coor) {
    os << "(" 
       << (coor.latitude * 180.0 / PI)
       << "," 
       << (coor.longitude * 180.0 / PI)
       << ")";
    return os;
}


