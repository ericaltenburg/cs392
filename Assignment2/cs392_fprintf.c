/* Eric Altenburg
 * I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "cs392_fprintf.h"

/**
 * Absolute value function used in itoa to not use libraries
**/
int abs(int value) {
	if (value > 0) {
		return value;
	} else {
		return value * -1;
	}

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
	if (value < 0 && (base == 10)) {
		str[i++] = '-';
	}

	str[i] = '\0'; // null terminate string

	// reverse the string and return it
	return reverse(str, 0, i - 1);
}


int cs392_fprintf(FILE *stream, const char *format, ...) {
	int count = 0;

	if (stream == NULL) {
		printf("Error: File does not exist/could not open file.");
		return 0;
	}

	va_list args;
	va_start(args, format);
	 
	//iterative over “format” and find specifiers
	while (*format != '\0') {

		// get the first argument with va_arg
		// the following is an example of handling integer format “%d”

		if(*format == '%') {
			format ++;
					
			if(*format == 'd') {
				int arg_int = va_arg(args, int); 
				// this helps you get the argument corresponding to “%d”
				int temp = arg_int;
				int digits;

				// Calculate the number of digits in the number for the string
				if (temp != 0) {
					digits = 0;
					if (arg_int < 0) {
						++digits;
					}
					while(temp != 0) {
						temp = temp / 10;
						++digits;
					}
				} else {
					digits = 1;
				}
				
				// Holds the digit converted to 
				char str[digits];

				size_t temp1 = fwrite(itoa(arg_int, str, 10), sizeof(str), 1, stream);

				if (temp1 < 0) { // Error handling
					printf("Error with writing to the file.");
					return -1;
				}

				count += digits;
			}
			if(*format == 'x') {
				int arg_hex = va_arg(args, int);
				char str_out[80];

				// Actual string holding character
				char * temp = itoa(arg_hex, str_out, 16);

				size_t temp2 = fwrite(temp, sizeof(char), strlen(temp), stream);

				if (temp2 < 0) { // Error Handling
					printf("Error with writing to the file.");
					return -1;
				}

				count += temp2;
	    	}
	    	if (*format == 's') {
	    		char * arg_str = va_arg(args, char*);

	    		size_t temp3 = fwrite(arg_str, sizeof(char), strlen(arg_str), stream);

				if (temp3 < 0) { // Error Handling
					printf("Error with writing to the file.");
					return -1;
				}
				
				count += temp3;
	    	}
	    	if (*format == 'c') {
	    		char arg_char = va_arg(args, int);

	    		size_t temp4 = fwrite(&arg_char, sizeof(char), 1, stream);

				if (temp4 < 0) { // Error Handling
					printf("Error with writing to the file.");
					return -1;
				}
				
				count += temp4;
	    	}
	    } else {
	    	// Print the rest of the input to the file
	    	size_t temp5 = fwrite(format, 1, 1, stream);
	    	if (temp5 < 0) { // Error handling
	    		printf("Error with writing to the file.");
	    		return -1;
	    	}

	    	count += temp5;
	    }
	    ++format;
	}
	
	va_end(args);
	return count;
}


// int main (int argc, char ** argv) {
// 	FILE * fp1 = fopen("text.txt", "w+");

// 	// cs392_fprintf(fp1, "This is a test %d\n%s\n%c\nThis is another test", 2, "yeet", 'A');
// 	int x = cs392_fprintf(fp1, "Test 10 with mixed specifiers %d, %x, %c, %s\n", 1, 1, 'A', "Everything Here");
// 	int y = fprintf(fp1, "Test 10 with mixed specifiers %d, %x, %c, %s\n", 1, 1, 'A', "Everything Here");


// 	// int x = cs392_fprintf(fp1, "test %x and %d\n", 255, 255);
// 	// int y = fprintf(fp1, "test %x and %d\n", 255, 255);
// 	fclose(fp1);

// 	printf("This is the amount of bytes: %d\n", x);
// 	printf("This is the amount of bytes: %d\n", y);	
// 	return 0;
// }
