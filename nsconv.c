/*=====================================
	     nsconv module 
  Conversions between `numeral systems`	
=======================================*/

/*
 * In function identifiers, 's' prefix to three letter `number system` abbreviation
 * string part, signifies that it's member (which is symbolized by that string part)
 * in that function has a string representation.
 */

/*
 * TO DO:
 * Check if machine is LSB or MSB and adapt
 * Set all calculations and return values to the highest possible value (long int?)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> /* for pow() */
#include <chk_inval.h> /* for hex_prfx_chk() */
#include "wam_unit.h"
#include "global_def.h"


const char DEC[] = "decimal";
const char BIN[] = "binary";
const char OCT[] = "octal";
const char HEX[] = "hexadecimal";

//enum { BIN_ID, DEC_ID, OCT_ID, HEX_ID };
int BIN_ID = 'b';
int DEC_ID = 'd';
int OCT_ID = 'o';
int HEX_ID = 'h';



/*
 * Allocate heap space for the string of length 'len'. 
 */
static char *ns_malloc(int len)
{
	char *heap = xmalloc( sizeof(char)*(len+1) );

	return heap;
}




/*
 * Remove hexadecimal prefix from string.
 * For supported hex prefixes read hex_prfx_chk() implementation
 */
char *rm_hex_prfx(char *hex_str)
{

	char *clean_hexstr;
	int hpc = hex_prfx_chk(hex_str);

	if(hpc > 0)	
		clean_hexstr = hex_str+hpc;
	else
		clean_hexstr = hex_str;

	return clean_hexstr;
}


/* 
 * Convert a number given as a string to a number decimal as an integer
 * based on a given `numeral system` base.
 *
 * Parameters: 
 * 	num_str - string number, 
 * 	base - `numeral system` base (radix)
 * Return: integer
 *
 * NOTE: current calculation is based on two's complement in 32-CPU register (vars are int)
 */
static int _sx_to_dec(const char *num_str, int base)
{
	int i, pm, dec = 0, ss = 0, sign = 1, len = strlen(num_str);
	char c;

	if (num_str[0] == '-'){
		ss = 1; sign = -1;
	}

	for(i=len; i>ss; i--){

		c = num_str[i-1];
		pm = (int) pow(base, len-i); /* positional multiplier */

		if (c >= '0' && c <= '9'){
			dec += (c - '0') * pm;
		}
		else if (c >= 'A' && c <= 'F'){
			/* A-F hex */
			dec += (c - 'A' + 10) * pm;
		}
		else if (c >= 'a' && c <= 'f'){ 
			/* a-f hex */
			dec += (c - 'a' + 10) * pm;
		}
		else {
			fprintf(stderr, "error! _x_to_dec(): invalid member '%c'"
				" of a number string \"%s\" for the base of %d\n",
				c, num_str, base);
			exit(EXIT_FAILURE);
		}
		
	}

	return sign * dec;
}

/* NOTE: same repr code in this function as in dec_to_shex() */
char *sbin_to_shex(const char *bin_str, char repr)
{
	char format_str[] = "%X";

	if (repr == 'l' || repr == 'L')
		format_str[1] = 'x';
	else if (repr == 'u' || repr == 'U')
		;
	else{
		fprintf(stderr, "invalid char argument '%c' given to " \
			"sbin_to_shex(). Valid only 'l[L]' or 'u[U]'\n", repr);
		exit(EXIT_FAILURE);
	}

	int dec = _sx_to_dec(bin_str, 2);
	char *hex_str = ns_malloc( strlen(bin_str) );	
	
	sprintf(hex_str, format_str, dec);

	return hex_str;
}

char *sbin_to_soct(const char *bin_str)
{
	int dec = _sx_to_dec(bin_str, 2);
	char *oct_str = ns_malloc( strlen(bin_str) );	
	
	sprintf(oct_str, "%o", dec);

	return oct_str;
}

int sbin_to_dec(const char *bin_str)
{
	return _sx_to_dec(bin_str, 2);
}

/* NOTE: same repr code in this function and sbin_to_shex */
char *dec_to_shex(int dec, char repr)
{
	char format_str[] = "%X";
	char *hex_str = ns_malloc(64);

	if (repr == 'l' || repr == 'L')
		format_str[1] = 'x';
	else if (repr == 'u' || repr == 'U')
		;
	else{
		fprintf(stderr, "invalid char argument '%c' given to " \
			"dec_to_shex(). Valid only 'l[L]' or 'u[U]'\n", repr);
		exit(EXIT_FAILURE);
	}

	sprintf(hex_str, format_str, dec);

	return hex_str;

}


char *dec_to_soct(int dec)
{
	char *oct_str = ns_malloc(64);
	
	sprintf(oct_str, "%o", dec);

	return oct_str;
}


char *sdec_to_shex(const char *num_str, char repr)
{
	return dec_to_shex( atoi(num_str), repr );
}


char *sdec_to_soct(const char *num_str)
{
	return dec_to_soct( atoi(num_str) );
}


/* 
 * Convert decimal number given as an integer
 * to a binary number returned as array of short integers
 * 
 * Parameters:
 * 	> num - input number which is to be converted.
 * 	> bit_width - pointer to the adddress of an integer which holds the value
 * 	  of bit register width. If it's value is 0, it will be overwritten with 
 * 	  the calculated width (storage size in bits) of the input number.
 * 	> hb1_pos - pointer to the address of an integer in which this function 
 * 	  will store position of the first bit which is set to 1
 */
short *dec_to_binarr(int num, int *bit_width, int *hb1_pos)
{
	short bit, i, *bn_arr;
	int msb_1, bits; /* register size in bits */

	*hb1_pos = -1; /* set default value */

	/* If bit_width is 0, set register size according to the size of number type, and
	copy value of bits to bit_width, so that caller function knows the size of return array */
	if (*bit_width == 0){ 
		bits = sizeof(num)*8; 
		*bit_width = bits; 	
	}
	else
		bits = *bit_width;


 	/* alloc mem for array representation of a binary number */
	bn_arr = xmalloc(sizeof(short)*bits);

	/* msb_1 value is an int number calculated as => int number with all bits set
  	   to 0 except the most significant bit, which is set to 1 */
	msb_1 = (int) pow(2, bits-1); /* bits-1 -> binary lsb exponantiation exponent is 0 */

	for(i=0; i<bits; i++){

		bit = num & msb_1 ? 1 : 0;

		if (*hb1_pos == -1 && bit == 1) /* store position of the highest bit set to 1 */
			*hb1_pos = i;
		
		bn_arr[i] = bit;
 
		num <<= 1;
	}

	/* this situation occurs when all bits are 0 */
	if (*hb1_pos == -1)
		*hb1_pos = bits - 1;


	return bn_arr;
}

/* 
 * Convert decimal number given as integer to a binary number 
 * represented as a string
 * */
static char *dec_to_sbin(int num, int *width, char repr){

	int i, hb1_pos;
	short *bin_arr = dec_to_binarr(num, width, &hb1_pos);
	char *bin_str = ns_malloc(*width);


	for(i=0; i<*width; i++){
		bin_str[i] = '0' + bin_arr[i];
	}

	free(bin_arr);

	bin_str[i] = '\0';

	if (repr == 'f')
	/* move pointer to the first occurence of 1 from the start of the string */
		return bin_str + hb1_pos; 
	else
		return bin_str;
}

/* 
 * Convert decimal number represented as a string 
 * to a binary number returned as a string
 */
char *sdec_to_sbin(const char *num_str, char repr)
{
	
	int width = 0;
	int num = atoi(num_str);

	return dec_to_sbin(num, &width, repr);
}


int shex_to_dec(const char *str_hex)
{
	char *cln_hex = ns_malloc(strlen(str_hex));
	char *tofree = cln_hex; /* save original value. rm_hex_prfx can change it */
	strcpy(cln_hex, str_hex);

	cln_hex = rm_hex_prfx(cln_hex);
	int dec = _sx_to_dec(cln_hex, 16);

	free(tofree);
	
	return dec;
}


char *shex_to_sbin(const char *str_hex, char repr)
{
	int width = 0;
	int dec = shex_to_dec(str_hex);

	return dec_to_sbin(dec, &width, repr);	
}


char *shex_to_soct(const char *str_hex)
{
	int dec = shex_to_dec(str_hex);

	return dec_to_soct(dec);	
}


int soct_to_dec(const char *str_oct)
{
	int dec = _sx_to_dec(str_oct, 8);

	return dec;

}

char *soct_to_sbin(const char *str_oct, char repr)
{
	int width = 0;
	int dec = soct_to_dec(str_oct);

	return dec_to_sbin(dec, &width, repr);	
}


char *soct_to_shex(const char *str_oct, char repr)
{
	int dec = soct_to_dec(str_oct);

	return dec_to_shex(dec, repr);	
}


/* create number system units and return them as linked list*/
unit_t *ns_list(unit_t **tail)
{

	unit_t *head = NULL;


	/* binary */
	*tail =
	nodeunit(BIN_ID, Q_NUMBER, NUMBER_SYS, "binary", "bin", DEC_ID, -1, -1,
		 -1, -1, &head);
	/* octal */
	nodeunit(OCT_ID, Q_NUMBER, NUMBER_SYS, "octal", "oct", DEC_ID, -1, -1,
		 -1, -1, &head);
	/* decimal */
	nodeunit(DEC_ID, Q_NUMBER, NUMBER_SYS, "decimal", "dec", DEC_ID, -1, -1,
		 -1, -1, &head);
	/* hexadecimal */
	nodeunit(HEX_ID, Q_NUMBER, NUMBER_SYS, "hexadecimal", "hex", DEC_ID, -1,
		 -1, -1, -1, &head);


	return head;
}
