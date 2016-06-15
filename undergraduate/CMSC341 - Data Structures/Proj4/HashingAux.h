#ifndef _HASHINGAUX_H
#define _HASHINGAUX_H

#include <string>

using namespace std;

int hash( const string & key, int tableSize );

int hash( int key, int tableSize );

bool isPrime ( int n );

int nextPrime( int n );

#endif
