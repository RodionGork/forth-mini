#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void iwRet(void) {
    ip = rstack[--rp];
}

void iwBye(void) {
    exit(0);
}

void iwEmit(void) {
    fputc(pstack[--pp], stdout);
}

void iwKey(void) {
    pstack[pp++] = fgetc(stdin);
}

void iwDot(void) {
    printf("%ld ", pstack[--pp]);
}

void iwAdd(void) {
    pp--;
    pstack[pp-1] += pstack[pp];
}

void iwSub(void) {
    pp--;
    pstack[pp-1] -= pstack[pp];
}


void iwMul(void) {
    pp--;
    pstack[pp-1] *= pstack[pp];
}


void iwDiv(void) {
    pp--;
    pstack[pp-1] /= pstack[pp];
}

void iwDup(void) {
    pstack[pp++] = pstack[pp-1];
}

void iwOver(void) {
    pstack[pp++] = pstack[pp-2];
}

void iwPick(void) {
    pstack[pp-1] = pstack[pp-1-pstack[pp-2]];
}

void iwDrop(void) {
    pp--;
}

