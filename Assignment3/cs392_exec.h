/* 
 * Name: Eric Altenburg
 * Date: 20 November 2019
 * Course: CS-392
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#ifndef CS_392_EXEC_H
#define CS_392_EXEC_H

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static void freeup(char**, int);
void ex(char *);
static void runsource(int*, char**);
static void rundest(int*, char**);


#endif