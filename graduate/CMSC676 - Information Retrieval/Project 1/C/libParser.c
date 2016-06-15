/*
 * libParser
 */

/********************************************************************************
 * Includes
 *******************************************************************************/

#include "libParser.h"

#include "string.h" /* assuming this has bzero */

/********************************************************************************
 * Defines
 *******************************************************************************/

#define MAX_TOKEN_LENGTH 1024
#define MAX_OPEN_PARSERS 5

/********************************************************************************
 * Data Structures
 *******************************************************************************/

struct Token_t
{
  char         str[MAX_TOKEN_LENGTH];
  unsigned int len;
};

typedef Token_t Token;

typedef unsigned int ParserHandle;

/********************************************************************************
 * Enums
 *******************************************************************************/

enum ParseState
{
    ParseEngine_Init = 0, /* the state before and during initialization */
    ParseEngine_Wait, /* the state before we know what we're looking at */
    ParseEngine_Toss, /* if we're in a tag all will be tossed until end */
    ParseEngine_Keep, /* we are going to keep the data we're parsing */
};

/********************************************************************************
 * Local Prototypes
 *******************************************************************************/

static char
readChar(FILE *fd);

static unsigned int
isAlphaNum(char c);

/********************************************************************************
 * Local Variables
 *******************************************************************************/

static unsigned char HoldingBuffer[MAX_OPEN_PARSERS][MAX_TOKEN_LENGTH];
static enum ParseState state[MAX_OPEN_PARSERS];
static ParserHandle[MAX_OPEN_PARSERS];
static unsigned int nextHandle = 0;
static FILE *files[MAX_OPEN_PARSERS];

/********************************************************************************
 * Public Functions
 *******************************************************************************/

ParserHandle
initializeParser(FILE *fd)
{
  /* set up new ParserHandle */

  ParserHandle[nextHandle] = nextHandle;
  state[nextHandle] = ParseEngine_init;
 
  bzero(&(HoldingBuffer[nextHandle]), MAX_TOKEN_LENGTH);

  nextHandle++;
  /* open file pointer */

  return (nextHandle - 1);
}

struct Token
getNextToken(ParserHandle handle)
{
  struct Token t;
  char c;
  unsigned int nextChar = 0;

  bzero(&(HoldingBuffer[handle]), MAX_TOKEN_LENGTH);
  bzero(&(t.str[0]), MAX_TOKEN_LENGTH);

  /* read chars until you have read in a new token */
  c = readchar(files[handle]);

  if (isAlphaNum(c)) {
    /* it's a normal character */
    HolderBuffer[handle][nextChar] = c;
  } else {
    switch(c) {
    case '<':
      break;
    case '>':
      break;
    default:
      break;
    }
  }
  
  return t;
}

/********************************************************************************
 * Prviate Functions
 *******************************************************************************/

static char
readChar(FILE *fd)
{
  char c = 'a';

  /* this just needs to read the next character from the filestream */

  return c;
}

static unsigned int
isAlphaNum(char c)
{
  unsigned int isAlphaNum = 0;

  if (c <= 'z' && c >= 'A'
      || c <= '9' && c >= '0') {
    /* it may very well be a normal char */
    isAlphaNum = 1;
  }

  return isAlphaNum;
}
