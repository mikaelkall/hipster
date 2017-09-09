/* Include iniparser to handle configfiles */
#include "iniparser.h"

#define BUFFER_SIZE             255
#define SHORT_BUFFER		50

/* Number of pre forks */
#define PREFORKS 10
/* PATH to configfile */
#define CONFIGFILE "/opt/hipster/hipster.cfg"

#define iswhite(c)  (c == ' ' || c == '\t' || c=='\n' || c=='\r')

/* String slicing functions */
int             wcount(char*,char*);
char            *rword(char*,int,char*);
char            *rword2(char*,int,char*);
char            *rword3(char*,int,char*, char *, int);
char            *rword_r( char *s, int nr, char *delim , char *buf_r);
char            *rword_r2( char *s, int nr, char *delim , char *buf_r,int maxlen);
void            trim(char*s,int typ);
int 		myiswhite(char c);
void 		ltrim(char *s);
void 		rtrim(char *s);
void		ttrim(char *s);
char 		*GetConfigValue();
int 		GetBoolConfigValue(char *value);
int 		GetIntConfigValue(char *value);

/* Write socket function */
void writesock(char *message,int length,int newsock);
