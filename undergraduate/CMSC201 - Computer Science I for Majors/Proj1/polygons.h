#include <stdio.h>
#include <math.h>

void   PrintGreeting (void);

void   GenerateTable (int min, int max);

void   PrintInstructions (void);

int    GetValidNumSides (int sentinel, int min, int max);

double GetPositiveValue (void);

void   PrintName (int numSides);

double FindExteriorAngles (int numSides);

int    FindAngleSum (int numSides);

double FindInteriorAngles (double angleSum, int numSides);

int    FindNumDiagonals(int numSides);

double FindPerimeter (int numSides, double side);

double FindArea (int numSides, double side);

double ConvertDegreesToRadians (double degrees);
