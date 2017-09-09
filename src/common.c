#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include "../include/common.h"

/*****************************************************************
 * Function: writesock
 * Purpose: write data thrue socket
 * Arguments:
 *****************************************************************/
void writesock(char *message,int length,int newsock)
{
    	send(newsock,message,length,0);
}
/***************************************************************
 **
 ** Function    : GetConfigValue
 **
 ** Description : Get config parameters.
 **
 ***************************************************************/
char *GetConfigValue(char *value)
{
        dictionary  *   ini;
	char *s;	

	ini = iniparser_load(CONFIGFILE);
	if (ini==NULL)        
	{
		return NULL;
	}
	
	s = iniparser_getstring(ini,value, NULL);
	return s;
}

/***************************************************************
 **
 ** Function    : GetBoolConfigValue
 **
 ** Description : Get config parameters.
 **
 ***************************************************************/
int GetBoolConfigValue(char *value)
{
        dictionary  *   ini;
        int b;

        ini = iniparser_load(CONFIGFILE);
        if (ini==NULL)
        {
                return 0;
        }

      	b = iniparser_getboolean(ini,value, -1); 
	return b;
}
/***************************************************************
 **
 ** Function    : GetIntConfigValue
 **
 ** Description : Get config parameters.
 **
 ***************************************************************/
int GetIntConfigValue(char *value)
{
        dictionary  *   ini;
        int i;

        ini = iniparser_load(CONFIGFILE);
        if (ini==NULL)
        {
                return 0;
        }

	i = iniparser_getint(ini,value, -1);
        return i;
}
/***************************************************************
 **
 ** Function    : wcount
 **
 ** Description : Returns the number of words in a string.
 **
 ***************************************************************/
int wcount( char *s, char *cc )
{
    int ok      = 0;
    int n       = 0;
    int c       = 0;
    int l       = 0;

    l = strlen( s );

    for (n = 0; n < l; n++ )
    {
        if ( ok == 0 && s[n] != *cc )
        {
            ok = 1;
            c++;
        }
        if (ok == 1 && s[n] == *cc)
            ok = 0;
    }

    return (c);
} /* wcount */

/***************************************************************
 **
 ** Function    : rword
 **
 ** Description : Extracts a word from a string.
 **
 ***************************************************************/
char * rword( char *s, int nr, char *delim )
{
    static char t[BUFFER_SIZE];
    int         quote   = 0;
    int         f       = 0;
    int         n       = 1;
    int         l       = 0;
    int         len     = 0;

    len = strlen( s );

    for (f = 0; f < len; f++)
    {
        /* oops quotes ... dont match delimiter */
        if ( s[f] == '"' )
            quote = !quote;

        if (strchr( delim, s[f] ) && !quote )
        {
            if (!strchr(delim, s[f + 1]))
                n++;
            if (n > nr)
                break;
            continue;
        }
        if (n == nr)
            t[l++] = s[f];
    }

    t[l] = 0x00;

    return ((char *) t);
} /* rword */

/***************************************************************
 **
 ** Function    : rword_r
 **
 ** Description : Extracts a word from a string.
 **¨              Thread safe version
 ***************************************************************/
char * rword_r( char *s, int nr, char *delim , char *buf_r)
{
    int         quote   = 0;
    int         f       = 0;
    int         n       = 1;
    int         len     = 0;
    char       *dest = buf_r;

    len = strlen( s );

    *buf_r = '\0';

    for (f = 0; f < len; f++)
    {
        /* oops quotes ... dont match delimiter */
        if ( s[f] == '"' )
            quote = !quote;

        if (strchr( delim, s[f] ) && !quote )
        {
            if (!strchr(delim, s[f + 1]))
                n++;
            if (n > nr)
                break;
            continue;
        }
        if (n == nr) {
            *buf_r = s[f];
            buf_r++;
        }
    }

    *buf_r = 0x00;

    return (dest);
} /* rword_r */

/***************************************************************
 **
 ** Function    : rword_r2
 **
 ** Description : Extracts a word from a string.
 **¨              Thread safe version
 ***************************************************************/
char * rword_r2( char *s, int nr, char *delim , char *buf_r,int maxlen)
{
    int         quote   = 0;
    int         f       = 0;
    int         n       = 1;
    int         i       = 0;
    int         len     = 0;
    char       *dest = buf_r;


    len = strlen( s );

    *buf_r = '\0';

    for (f = 0; f < len; f++)
    {
        /* oops quotes ... dont match delimiter */
        if ( s[f] == '"' )
            quote = !quote;

        if (strchr( delim, s[f] ) && !quote )
        {
            if (!strchr(delim, s[f + 1]))
                n++;
            if (n > nr)
                break;
            continue;
        }
        if (n == nr) {
            *buf_r = s[f];
            buf_r++;
            i++;
            /* max length reached ? */
            if ( i >= maxlen )
                break;
        }
    }

    *buf_r = 0x00;

    return (dest);
} /* rword_r2 */

/***************************************************************
 **
 ** Function    : rword3
 **
 ** Description : Extracts a word from a string.
 **
 ** Note        : This version returns the word in a string var
 **               specified by the caller.
 **
 ***************************************************************/
char *rword3( char *s, int nr, char *delim, char *t, int maxsize )
{
    int         quote   = 0;
    int         f       = 0;
    int         n       = 1;
    int         l       = 0;
    int         len     = 0;

    len = strlen( s );

    for (f = 0; f < len && l < maxsize; f++)
    {
        /* oops quotes ... dont match delimiter */
        if ( s[f] == '"' )
            quote = !quote;

        if (strchr( delim, s[f] ) && !quote )
        {
            if (!strchr(delim, s[f + 1]))
                n++;
            if (n > nr)
                break;
            continue;
        }
        if (n == nr)
            t[l++] = s[f];
    }

    t[l] = 0x00;

    return ((char *) t);
} /* rword3 */
/***********************************
 * Function: myiswhite(c)
 * Arguments
 * Purpose: find out if whitespace.
 ***********************************/
int myiswhite(char c)
{
   if(c==' ' || c=='\t' || c=='\n' || c=='\r')
        return 1;

   return 0;
}
/***************************************
 * Function: ltrim(s)
 * Arguments:
 * Purpose: trim whitespace from left. 
 ***************************************/
void ltrim(char *s)
{
   int i;
   char t[255];

  memset(t,0x00,sizeof(t));

   for(i=0;i < strlen(s); i++){
     if(myiswhite(*(s+i)))
        s++;
     else
        break;
   }

   strcpy(t,s);
   strcpy(s,t);
}
/***************************************
 * Function: rtrim(s)
 * Arguments:
 * Purpose: Trim whitespace from right.
 ***************************************/
void rtrim(char *s)
{
   int i=strlen(s)-1;

   while(i>=0){
     if(myiswhite(*(s+i)))
        *(s+i)=0x00;
     else
        break;
     i--;
   }
}

/***************************************
 * Function: trim(s)
 * Arguments:
 * Purpose: trim from left and right.
 **************************************/
void ttrim(char *s)
{
   ltrim(s);
   rtrim(s);
}
/***************************************************************
 ** 
 ** Function     : trim
 ** 
 ** Description  : String trim.
 **        typ=0 trim leading & trailing whitespace from string
 **        typ=1 trim leading & trailing quotes from string
 ** 
 ***************************************************************/
void trim( char *s, int typ )
{
    char        *t      = NULL;
    int         n       = strlen(s);
    int         f       = 0;

    if(!n)
    {
        return;
    }

    t = ( char * ) malloc( n+1 );
        memset(t, 0x00, n+1 );

    if(!typ)
    {
        while(n--)
            if(!iswhite(*(s+n)))
               break;
    }
    else
    {
        while(n--)
            if(*(s+n)!='"')
                break;
    }

    *(s+n+1)=0x00;
    n=0;

    if(!typ)
    {
        while(iswhite(*(s+n)))
            n++;
    }
    else
    {
        while(*(s+n)=='"')
            n++;
    }

    while(*(s+n))
    {
        t[f++] = *(s+n);
        n++;
    }
    t[f]=0x00;
    strcpy(s,t);
    free(t);

    return;
} /* trim */
