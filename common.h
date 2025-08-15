#ifndef __COMMON_H_
#define __COMMON_H_

#define IWMASK 0x40000000
#define UWMASK 0x80000000

typedef long cell;
typedef void (*iwordFunc)(void);

typedef struct {
    char wlen;
    cell addr;
    char word[1];
} worddef;

extern cell pstack[];
extern cell rstack[];
extern cell code[];
extern char dict[];
extern int ip, pp, rp, cp;
extern iwordFunc iwords[];

void wordAdd(char* w, cell addr);
void initIwords(void);

#endif

