#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdint.h>

/* MPI STUFF */
#define DISTROSERVER 1 
#define PRINTSERVER 0 
#define SERVERTAG 31
#define PRINTTAG 32

/* buffer length stuff */
#define MAX_PATH_LENGTH 1024
#define MAX_TOKEN_LENGTH 128
#define STOPWORDS_CNT 50

//#define PRINT_STATUS

/* this holds the terms for a user */
typedef struct
{
	char     user[MAX_PATH_LENGTH];
	uint32_t counts[STOPWORDS_CNT];
} userContainer;

int
process_user(const char *userfolder);

void
process_file(const char *filepath);

/* global container for current user */
userContainer user_terms;

/* 50 stop words we care about */
char *terms[STOPWORDS_CNT] = {
"the",  "to",     "and",      "of",    "a",
"in",   "for",    "on",       "that",  "this",
"from", "with",   "it",       "by",    "as",	
"at",   "or",     "if",       "not",   "please",
"an",   "any",    "original", "all",   "power",
"but",  "thanks", "energy",   "know",  "said",
"mail", "up",     "gas",      "new",   "about",
"time", "what",   "so",       "there", "which",
"out",  "no",     "company",  "need",  "get",
"one",  "let",    "should",   "also",  "more"};

#endif
