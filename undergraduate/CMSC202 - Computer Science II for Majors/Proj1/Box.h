//---------------------------------------------------
// File       : Box.h
// Author     : Patrick Trinkle
// Date       : September 26 2004
// UMBC Email : tri1@umbc.edu
// Project    : 1
// Section    : 0101
// Description: Function definitions That access the
//              members of Box Struct Used for Proj1
//---------------------------------------------------

#ifndef _Box_h
#define _Box_h

#include "RoundToy.h"

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

typedef struct BOX
{
      int length;
      int width;
      int height;
      vector<RoundToy> toysinbox;
}BOX;


//---------------------------------------
// BoxInit
// PreConditions:
//         a box declared with dimensions
// PostConditions
//         a box with initialized
//         dimensions
//---------------------------------------
void BoxInit(BOX& box, int length, int width, int height);

//---------------------------------------
// BoxUnused
// PreConditions:
//         a box structure defined
// PostConditions
//         returns the unused volume of
//         the box structure
//---------------------------------------
double BoxUnused(const BOX& box);

//---------------------------------------
// BoxStore
// PreConditions:
//         a box structure defined, and
//         a toy
// PostConditions
//         None
//---------------------------------------
bool BoxStore(BOX& box, const RoundToy& toy);

//---------------------------------------
// BoxPrint
// PreConditions:
//         a box structure defined
// PostConditions
//         None
//---------------------------------------
void BoxPrint(ostream& out, const BOX& box);

#endif
