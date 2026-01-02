#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "motori.h"

class Controller
{
public:

   Controller(Motore  (&motori)[4]): _motori(motori) {};
   Motore (&_motori)[4];

};


#endif



