//---------------------------------------------------
// File       : RoundToy.h
// Author     : Patrick Trinkle
// Date       : September 26 2004
// UMBC Email : tri1@umbc.edu
// Project    : 1
// Section    : 0101
// Description: Function definitions That access the
//              members of RoundToy Struct Used for 
//              Proj1
//---------------------------------------------------


#ifndef _RoundToy_h
#define _RoundToy_h

#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

const double PI = 3.14159265359;

typedef struct RoundToy
{
      double diameter;
      string color;
      int    holes;
}RoundToy;



//---------------------------------------
// RoundToyDiameter
// PreConditions:
//         the toy needs to have some
//         double as a diamter
// PostConditions
//         it retuns the diameter
//         associated with the toy
//---------------------------------------
double RoundToyDiameter(const RoundToy& toy);

//---------------------------------------
// RoundToyColor
// PreConditions:
//         the toy needs to have some
//         valid color as a string
// PostConditions
//         it retuns the color
//         associated with the toy
//---------------------------------------
string RoundToyColor(const RoundToy& toy);

//---------------------------------------
// RoundToyHoles
// PreConditions:
//         the toy needs to have some
//         valid integer of holes
// PostConditions
//         it retuns the number of holes
//         in the toy
//---------------------------------------
int RoundToyHoles(const RoundToy& toy);

//---------------------------------------
// RoundToyVolume
// PreConditions:
//         the toy needs to have a valid
//         diameter, needs to be greater
//         than negative 1
// PostConditions
//         it calculates and returns a
//         nonnegative volume
//---------------------------------------
double RoundToyVolume(const RoundToy& toy);

//---------------------------------------
// RoundToyInit
// PreConditions:
//         the toy needs to exist and
//         you need to enter in
//         nonnegative values and a valid
//         color
// PostConditions
//         it sets all the members to the
//         values sent to the function
//---------------------------------------
void RoundToyInit(RoundToy& toy, double diameter, string color, int nrHoles);








#endif
