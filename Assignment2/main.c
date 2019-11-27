#include <stdio.h>
#include "cs392_fprintf.h"

int main(int argc, char ** argv){

	FILE * fp1 = fopen("fprintf.log", "w+");
	FILE * fp2 = fopen("cs392_fprintf.log", "w+");
	

	//test 1	
	int a = fprintf(fp1, "Test 1 Hello CS 392 Assignment 2\n");
	int b = cs392_fprintf(fp2, "Test 1 Hello CS 392 Assignment 2\n");
	fprintf(fp1, "Test 1 size: %d\n", a);
	fprintf(fp2, "Test 1 size: %d\n", b);

	//test 2
	int c = fprintf(fp1, "Test 2 with integer %d\n", 1);
	int d = cs392_fprintf(fp2, "Test 2 with integer %d\n", 1);
	fprintf(fp1, "Test 2 size: %d\n", c);
	fprintf(fp2, "Test 2 size: %d\n", d);

	//test 3
	int e = fprintf(fp1, "Test 3 with hex %x\n", 255);
	int f = cs392_fprintf(fp2, "Test 3 with hex %x\n", 255);
	fprintf(fp1, "Test 3 size: %d\n", e);
	fprintf(fp2, "Test 3 size: %d\n", f);

	//test 4
	int g = fprintf(fp1, "Test 4 with string %s\n", "this is a string");
	int h = cs392_fprintf(fp2, "Test 4 with string %s\n", "this is a string");
	fprintf(fp1, "Test 4 size: %d\n", g);
	fprintf(fp2, "Test 4 size: %d\n", h);

	//test 5
	int i = fprintf(fp1, "Test 5 with char %c\n", 'A');
	int j = cs392_fprintf(fp2, "Test 5 with char %c\n", 'A');
	fprintf(fp1, "Test 5 size: %d\n", i);
	fprintf(fp2, "Test 5 size: %d\n", j);

	//test 6	
	int k = fprintf(fp1, "Test 6 with mixed specifiers %d %x\n", 255, 255);
	int l = cs392_fprintf(fp2, "Test 6 with mixed specifiers %d %x\n", 255, 255);
	fprintf(fp1, "Test 6 size: %d\n", k);
	fprintf(fp2, "Test 6 size: %d\n", l);

	//test 7
	int m = fprintf(fp1, "Test 7 with mixed specifiers %d %s\n", 255, "string after integer");
	int n = cs392_fprintf(fp2, "Test 7 with mixed specifiers %d %s\n", 255, "string after integer");
	fprintf(fp1, "Test 7 size: %d\n", m);
	fprintf(fp2, "Test 7 size: %d\n", n);

	//test 8
	int o = fprintf(fp1, "Test 8 with mixed specifiers %d %c\n", 255, '@');
	int p = cs392_fprintf(fp2, "Test 8 with mixed specifiers %d %c\n", 255, '@');
	fprintf(fp1, "Test 8 size: %d\n", o);
	fprintf(fp2, "Test 8 size: %d\n", p);

	//test 9
	int q = fprintf(fp1, "Test 9 with mixed specifiers %x %s\n", 255, "string after hex");
	int r = cs392_fprintf(fp2, "Test 9 with mixed specifiers %x %s\n", 255, "string after hex");
	fprintf(fp1, "Test 9 size: %d\n", q);
	fprintf(fp2, "Test 9 size: %d\n", r);

	//test 10
	int s = fprintf(fp1, "Test 10 with mixed specifiers %d, %x, %c, %s\n", 255, 255, 'A', "Everything Here");
	int t = cs392_fprintf(fp2, "Test 10 with mixed specifiers %d, %x, %c, %s\n", 255, 255, 'A', "Everything Here");
	fprintf(fp1, "Test 10 size: %d\n", s);
	fprintf(fp2, "Test 10 size: %d\n", t);

	fclose(fp1);
	fclose(fp2);
}
