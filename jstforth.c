#include <stdio.h>
#include <string.h>
#include "common.h"

cell pstack[256];
cell rstack[256];
cell code[16384];
char dict[16384] = {0};
int ip, pp, rp, cp, mode;
FILE* input;

void wordAdd(char* w, cell addr) {
   char* next = (void*) dict;
    while (*next)
        next += *next + sizeof(cell) + 1; 
    *next = strlen(w);
    strncpy(next+1, w, *next);
    *(cell*)(void*)(next + 1 + *next) = addr;
    next += *next + sizeof(cell) + 1;
    *next = 0;
}

int charCmp(char a, char b) {
    return a == b
        || a > 'Z' && a - 0x20 == b
        || b > 'Z' && b == b - 0x20;
}

int wordCmp(char* word, char* s) {
    for (int i = 0; i < *word; i++)
        if (!charCmp(s[i], word[i+1]))
            return 0;
    return s[*word] == 0;
}

cell wordSeek(char* w) {
    char* next = (void*) dict;
    cell res = 0;
    while (*next) {
        if (wordCmp(next, w))
            res = *(cell*)(void*)(next + *next + 1);
        next += *next + sizeof(cell) + 1;
    }
    return res;
}

void run(void) {
    rstack[0] = -1;
    rp = 1;
    while (ip >= 0) {
        cell w = code[ip++];
        switch (w & (IWMASK | UWMASK)) {
            case IWMASK:
                iwords[w & ~IWMASK]();
                break;
            case UWMASK:
                rstack[rp++] = ip;
                ip = (w & ~UWMASK);
                break;
            default:
                pstack[pp++] = w;
        }
    }
}

int trynum(char* s, cell* res) {
    int sign = 1;
    *res = 0;
    if (*s == '-') {
        sign = -1;
        s++;
    }
    if (!*s)
        return 0;
    for (; *s; s++) {
        if (*s < '0' || *s > '9')
            return 0;
        *res = (*res * 10) + *s - '0';
    }
    return 1;
}

void compileStart(char* w) {
    mode = 1;
    wordAdd(w, UWMASK | cp);
}

void compileEnd(void) {
    code[cp++] = IWMASK;
    mode = 0;
}

void doWord(char* w) {
    cell wcode;

    if (trynum(w, &wcode)) {
        if (mode)
            code[cp++] = wcode;
        else
            pstack[pp++] = wcode;
        return;
    }

    if (mode == 2) {
        compileStart(w);
        return;
    }

    wcode = wordSeek(w);
    if (wcode == 0) {
        if (strcmp(w, ":") == 0)
            mode = 2;
        else if (strcmp(w, ";") == 0)
            compileEnd();
        else
            printf("Unrecognized word: %s\n", w);
        return;
    }
    if (mode) {
        code[cp++] = wcode;
        return;
    }
    if (wcode & IWMASK)
        iwords[wcode & ~IWMASK]();
    else {
        ip = (wcode & ~UWMASK);
        run();
    }
}

void repl(void) {
    char wbuf[32];
    int c, wlen = 0;
    do {
        c = fgetc(input);
        if (c > ' ') {
            wbuf[wlen++] = c;
            continue;
        }
        if (wlen) {
            wbuf[wlen] = 0;
            doWord(wbuf);
            wlen = 0;
        }
        if ((c == 13 || c == 10 || c < 0) && input == stdin)
            if (!mode)
                printf(" ok <%d>\n", pp);
            else
                printf(" compiling...\n");
    } while (c >= 0);
}

void initDict(void) {
    initIwords();
}

int main(int argc, char** argv) {
    ip = pp = rp = cp = mode = 0;
    initDict();
    input = (argc == 1) ? stdin : fopen(argv[1], "rb");
    repl();
    if (input != stdin)
        fclose(input);
}

