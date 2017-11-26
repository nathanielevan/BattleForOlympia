/**
Filename: pcolor.c (implementation of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 30/10/2017
**/

#include <stdio.h>
#include "pcolor.h"

void print_white(char c) {
    if (c == 'K') {
        printf(" %s♛ ", WHITE);
        printf("%s", WHITE);
    }
    else if (c == 'W') {
        printf(" %s☤ ", WHITE);
        printf("%s", WHITE);
    }
    else if (c == 'S') {
        printf(" %s⚔️ ", WHITE);
        printf("%s", WHITE);
    }
    else if (c == 'A') {
        printf(" %s🏹", WHITE);
        printf("%s", WHITE);
    }
    else if (c == 'C') {
        printf(" %s🏰", WHITE);
        printf("%s", WHITE);
    }
    else if (c == 'T') {
        printf(" %s🗼", WHITE);
        printf("%s", WHITE);
    }
    else if (c == 'V') {
        printf(" %s🏠", WHITE);
        printf("%s", WHITE);
    }
    else {
        printf(" %s%c ", WHITE, c);
        printf("%s", WHITE);
    }
}

void print_red(char c) {
    if (c == 'K') {
        printf(" %s♛ ", RED);
        printf("%s", WHITE);
    }
    else if (c == 'W') {
        printf(" %s☤ ", RED);
        printf("%s", WHITE);
    }
    else if (c == 'S') {
        printf(" %s⚔️ ", RED);
        printf("%s", WHITE);
    }
    else if (c == 'A') {
        printf(" %s🏹", RED);
        printf("%s", WHITE);
    }
    else if (c == 'C') {
        printf(" %s🏰", RED);
        printf("%s", WHITE);
    }
    else if (c == 'T') {
        printf(" %s🗼", RED);
        printf("%s", WHITE);
    }
    else if (c == 'V') {
        printf(" %s🏠", RED);
        printf("%s", WHITE);
    }
    else {
        printf(" %s%c ", RED, c);
        printf("%s", WHITE);
    }
}

void print_green(char c) {
    if (c == 'K') {
        printf(" %s♛ ", GREEN);
        printf("%s", WHITE);
    }
    else if (c == 'W') {
        printf(" %s☤ ", GREEN);
        printf("%s", WHITE);
    }
    else if (c == 'S') {
        printf(" %s⚔️ ", GREEN);
        printf("%s", WHITE);
    }
    else if (c == 'A') {
        printf(" %s🏹", GREEN);
        printf("%s", WHITE);
    }
    else if (c == 'C') {
        printf(" %s🏰", GREEN);
        printf("%s", WHITE);
    }
    else if (c == 'T') {
        printf(" %s🗼", GREEN);
        printf("%s", WHITE);
    }
    else if (c == 'V') {
        printf(" %s🏠", GREEN);
        printf("%s", WHITE);
    }
    else {
        printf(" %s%c ", GREEN, c);
        printf("%s", WHITE);
    }
}

void print_yellow(char c) {
    if (c == 'K') {
        printf(" %s♛ ", YELLOW);
        printf("%s", WHITE);
    }
    else if (c == 'W') {
        printf(" %s☤️ ", YELLOW);
        printf("%s", WHITE);
    }
    else if (c == 'S') {
        printf(" %s⚔️ ", YELLOW);
        printf("%s", WHITE);
    }
    else if (c == 'A') {
        printf(" %s🏹", YELLOW);
        printf("%s", WHITE);
    }
    else if (c == 'C') {
        printf(" %s🏰", YELLOW);
        printf("%s", WHITE);
    }
    else if (c == 'T') {
        printf(" %s🗼", YELLOW);
        printf("%s", WHITE);
    }
    else if (c == 'V') {
        printf(" %s🏠", YELLOW);
        printf("%s", WHITE);
    }
    else {
        printf(" %s%c ", YELLOW, c);
        printf("%s", WHITE);
    }
}

void print_blue(char c) {
    if (c == 'K') {
        printf(" %s♛ ", BLUE);
        printf("%s", WHITE);
    }
    else if (c == 'W') {
        printf(" %s☤ ", BLUE);
        printf("%s", WHITE);
    }
    else if (c == 'S') {
        printf(" %s⚔️ ", BLUE);
        printf("%s", WHITE);
    }
    else if (c == 'A') {
        printf(" %s🏹", BLUE);
        printf("%s", WHITE);
    }
    else if (c == 'C') {
        printf(" %s🏰", BLUE);
        printf("%s", WHITE);
    }
    else if (c == 'T') {
        printf(" %s🗼", BLUE);
        printf("%s", WHITE);
    }
    else if (c == 'V') {
        printf(" %s🏠", BLUE);
        printf("%s", WHITE);
    }
    else {
        printf(" %s%c ", BLUE, c);
        printf("%s", WHITE);
    }
}

void print_magenta(char c) {
    if (c == 'K') {
        printf(" %s♛ ", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'W') {
        printf(" %s☤ ", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'S') {
        printf(" %s⚔️ ", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'A') {
        printf(" %s🏹", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'C') {
        printf(" %s🏰", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'T') {
        printf(" %s🗼", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'V') {
        printf(" %s🏠", MAGENTA);
        printf("%s", WHITE);
    }
    else {
        printf(" %s%c ", MAGENTA, c);
        printf("%s", WHITE);
    }
}

void print_cyan(char c) {
    if (c == 'K') {
        printf(" %s♛ ", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'W') {
        printf(" %s☤ ", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'S') {
        printf(" %s⚔️ ", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'A') {
        printf(" %s🏹", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'C') {
        printf(" %s🏰", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'T') {
        printf(" %s🗼", MAGENTA);
        printf("%s", WHITE);
    }
    else if (c == 'V') {
        printf(" %s🏠", MAGENTA);
        printf("%s", WHITE);
    }
    else {
        printf(" %s%c ", MAGENTA, c);
        printf("%s", WHITE);
    }
}
