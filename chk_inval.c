/*
 * Check functions used for checking input values
 * All functions return 1 if input value is valid
 */

#include <string.h>
#include <stdio.h>



/* Master template check function 
 * Arguments: 
 * 	- 'check function' pointer
 * 	-  string value to check
 * Return: 1 if value is valid -1 otherwise
 */
static int _chk( int (*f)(char), const char *val){
	
	char c;
	int i, len = strlen(val);

	for(i=0; i<len; i++){

		c = val[i];

		if( f(c) != 1)
			return -1;
	}

	return 1;
}


/* 
 * Return 1 if char is a valid hexadecimal char. return -1 otherwise. 
 * Both upper and lowercase are valid.
 */
static inline int ishexchar(char c)
{

	if ( (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') ){
 		return 1;
	}

	return -1;
}


/*
 * Hex prefix check
 * Check if string's first 2 chars are a valid hexadecimal number prefix,
 * if prefix isn't valid, return -1. If there is no prefix return 0
 * if prefix is found, return number of chars that constitute that prefix
 */
int hex_prfx_chk(const char *hex_str)
{
	int str_len = strlen(hex_str);
	char c1 = hex_str[0];
	int c2 = -1;

	if (str_len > 1)
		c2 = hex_str[1];


	/* first check if there is no prefix (only hex digits are used) */
	if (ishexchar(c1) == 1){

		if (c2 != -1){
			if(ishexchar(c2) == 1){
				return 0;
			}
		}
		else{
			return 0;
		}
	}

	switch(c1){

		case '0':
		case '\\':
			if(c2 != -1 && (c2 == 'X' || c2 == 'x'))
				return 2;
			break;

		case '%':
			if(c2 != -1 && (c2 == 'X' || c2 == 'x'))
				return 2; 
			else if(c2 != -1 && ishexchar(c2) == 1)
				return 1;
			break;
		case '#':
			if (c2 != -1 && ishexchar(c2) == 1)
				return 1;
			break;
	}

	return -1;
	
}


static inline int _chkoct(char c){
	if (c < '0' || c > '8')
		return -1;
	return 1;
}

/* replaced by ishexchar()
static inline int _chkhex(char c){
	if ( (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') 
	  || (c >= 'A' && c <= 'F') )
		return 1;

	return -1;
}
*/

static inline int _chkdec(char c){
	if (c < '0' || c > '9')
		return -1;
	return 1;
}


static inline int _chkbin(char c){
	if (c < '0' || c > '1')
		return -1;
	return 1;
}


int chksoct(const char *val){
	return _chk(_chkoct, val);
}

int chkshex(const char *val){

	int prfx_len = hex_prfx_chk(val);

	if (prfx_len == -1)
		return -1;

	/* if prefix is found, skip it with pointer arithmetics */
	return _chk(ishexchar, val+prfx_len);
}

int chksdec(const char *val){
	return _chk(_chkdec, val);
}

int chksbin(const char *val){
	return _chk(_chkbin, val);
}

int chksfloat(const char *val){
	return 1;
}
