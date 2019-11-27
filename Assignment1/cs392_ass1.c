/** Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 *	Author:			Eric Altenburg
 * 	Date:			12 September 2019
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Method that is used for exponents
**/
int power(int x, unsigned int y) {
    if (y == 0) {
        return 1;
    } else if (y % 2 == 0) {
        return power(x, y/2) * power(x, y/2);
    } else {
        return x * power(x, y/2) * power(x, y/2);
    }
}

/**
 *	Method removed charactes in string that aren't lowercase a to z or upppercase, and 0-9.
**/
char* remChar(char *string) {
    int length = strlen(string);
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            if(!((string[j] >= 'a' && string[j] <= 'z') || (string[j] >= 'A' && string[j] <= 'Z') || (string[j] >= '0' && string[j] <= '9' ) || (string[j] == '-'))) {
                for(int k = j; k < length; k++) {
                    string[k] = string[k+1];
                }
                length --;
            }
        }
    }

    return string;
}

/**
 * Traverses through the entire string to see if there are any characters that don't belong, then returns a 1 if they are there.
**/
int remCharExists(char *string) {
	int exists = 1;
	int length = strlen(string);

	for (int i = 0; i < length; i++) {
		if(!((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= '0' && string[i] <= '9' ) || (string[i] == '-'))) {
        	return exists;  
        }
	}

	exists = 0;
	return exists;
}


/**
 * Method converts desired base-number to an integer decimal
**/
int toInt(int val, int base) {
	int remainder;
	int op = 0;
	int p = 1;

	while (val != 0) {
		remainder = val%10;
		val = val / 10;
		op = op + remainder * p;
		p = p * base;
	}

	return op;
}

/**
 * Converts Hexadecimal to decimal
**/
int hexTo(char str[]) {
	int val;
	int dec_val = 0;
	int len = strlen(str);
	int base = 1;
	int i = 0;
	len--;

	// Iterate over the digits
	while (str[i] != '\0') {
		if (str[i] >= '0' && str[i] <= '9') {
			val = str[i] - 48;
		} else if (str[i]>='a' && str[i]<='f') {
			val = str[i] - 97 + 10;
		} else if (str[i]>='A' && str[i]<='F') {
			val = str[i] - 65 + 10;
		}

		dec_val += val * power(16, len);
		len--;
		i++;
	}

	return dec_val;
}

/**
 * Inline function that swaps two characters in an array of chars
**/
void swap(char *x, char *y) {
	char t = *x;
	*x = *y;
	*y = t;
}

/**
 * Reverses the string that was created in itoa
**/
char* reverse(char *str, int start, int end) {
	while (start < end) {
		swap(&str[start++], &str[end--]);
	}

	return str;
}

/**
 * itoa function that takes in a decimal integer and converts it to a string in the desired base
**/
char* itoa(int value, char* str, int base)
{
	// invalid input
	if (base < 2 || base > 16)
		return str;

	// consider absolute value of number
	int n = abs(value);

	// For iterating through the while loop
	int i = 0;

	// While the number is absolute value
	while (n) {
		int r = n % base;

		if (r >= 10) {
			str[i++] = 97 + (r - 10);
		} else {
			str[i++] = 48 + r;
		}

		n = n / base;
	}

	// if number is 0
	if (i == 0) {
		str[i++] = '0';
	}

	// Only for base 10, if the number is negative, then you append an negative sign
	if (value < 0 && base == 10) {
		str[i++] = '-';
	}

	str[i] = '\0'; // null terminate string

	// reverse the string and return it
	return reverse(str, 0, i - 1);
}


/**
 * Returns the base of two numbers that can either be octal or decimal. 8 or 10 is returned respectively.
**/
int isOct(char *string) {
	int base = 10;
	int length = strlen(string);

	// First char is a 0 so further testing is necessary
	if (string[0] == '0') {
		for (int i = 1; i < length; i++) {
			if (string[i] == '0' || string[i] > '7') { // This is base 10
				return base;
			}
		}
	} else { // The string doesn't start with 0 so it is by defualt a decimal
		return base;
	}

	base = 8;
	return base;
}

/**
 * Main method
**/
int main() {
	// TODO: implement NegBinConverter and add in the conditional

    char str_in[65];
    char str_out[65];
    int val;
    int base = 0;
    
    //Reading in the string
    int input_len = scanf("%s", str_in);


    if (remCharExists(str_in) == 1) { // There are bad chars, return lower case
    	printf("%s\n", remChar(str_in));
        return 0;
    }
   	
    if (str_in[0] == '-' && str_in[1] == '0' && str_in[2] == 'b') { // Special case where there is '-' before binary number
    	val = (int)strtol(str_in + 3, NULL, 2);
    	base = 2;
    	printf("0b%s\n" , itoa(val, str_out, base));
    	return 0;
    } else if(str_in[0] == '0' && str_in[1] == 'b') { // Checking for regular binary string
    	val = (int)strtol(str_in + 2, NULL, 2);
        base = 2;
        printf("0b%s\n" , itoa(val, str_out, base));
        return 0;
    } else if (str_in[0] == '0' && (str_in[1] == 'x' || str_in[1] == 'X')) { // Checking to see if the number is a regular hex string
        val = hexTo(str_in + 2);
        base = 16;

        	// Check to see if the newly converted integer is less than 0, which means it is too large
        	if (val < 0) {

        		int length = strlen(str_in);

        		for (int i = 0; i < length; i++) {
        			if (str_in[i] >= 'A' && str_in[i] <= 'Z') {
        				str_in[i] = str_in[i] + 32;
        			}
        		}

        		printf("0x%s\n", str_in + 2);
        		return 0;
        	} else {
        		printf("0x%s\n", itoa(val, str_out, base));
        		return 0;
        	}
    } else { // Else, it must either be an octal or decimal

    	// If there is a negative it is decimal
        if(str_in[0] == '-') {
            val = atoi(str_in);
            base = 10;
            printf("%s\n", itoa(val, str_out, base));
            return 0;
        } else { // Could still be octal
        	base = isOct(str_in);

        	// Decimal
        	if (base == 10) {
       			val = atoi(str_in);
        		printf("%s\n", itoa(val, str_out, base));
        		return 0;
        	}

        	// Octal
        	if (base == 8) {
        		val = (int)strtol(str_in, NULL, 8);
        		printf("0%s\n", itoa(val, str_out, base));
        		return 0;
        	}
        }
    }
    
    return 0;
}
