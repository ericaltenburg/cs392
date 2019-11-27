/* 
 * Name: Eric Altenburg
 * Date: 20 November 2019
 * Course: CS-392
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#ifndef CS392_SIGNAL_H
#define CS392_SIGNAL_H

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void hdl(int, siginfo_t*, void*);
void handles();

#endif