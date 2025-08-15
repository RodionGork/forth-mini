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

void iwPrnstk(void) {
    for (int i = 0; i < pp; i++)
        printf("%ld ", pstack[i]);
}

void iwDepth(void) {
    pstack[pp++] = pp;
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

void iwMod(void) {
    pp--;
    pstack[pp-1] %= pstack[pp];
}

void iwGt(void) {
    pp--;
    pstack[pp-1] = (pstack[pp-1] > pstack[pp]);
}

void iwLt(void) {
    pp--;
    pstack[pp-1] = (pstack[pp-1] < pstack[pp]);
}

void iwEq(void) {
    pp--;
    pstack[pp-1] = (pstack[pp-1] == pstack[pp]);
}

void iwNot(void) {
    pstack[pp-1] = pstack[pp-1] ? 0 : -1;
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

void iwSwap(void) {
    cell t = pstack[pp-1];
    pstack[pp-1] = pstack[pp-2];
    pstack[pp-2] = t;
}

void iwAgain(void) {
    if (pstack[--pp])
        ip -= 2;
}

void iwSkip(void) {
    if (pstack[--pp])
        ip += 1;
}

iwordFunc iwords[] = {iwRet, iwBye, iwEmit, iwKey, iwDot, iwPrnstk, iwDepth,
    iwAdd, iwSub, iwMul, iwDiv, iwMod, iwGt, iwLt, iwEq, iwNot,
    iwDup, iwOver, iwPick, iwDrop, iwSwap, iwAgain, iwSkip};

char* iwordNames[] = {"ret", "bye", "emit", "key", ".", ".s", "depth",
    "+", "-", "*", "/", "mod", ">", "<", "=", "not",
    "dup", "over", "pick", "drop", "swap", "?again", "?skip"};

void initIwords(void) {
    for (int i = 1; i < sizeof(iwords) / sizeof(*iwords); i++)
        wordAdd(iwordNames[i], IWMASK | i);
}

