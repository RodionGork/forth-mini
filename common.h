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
extern int ip, pp, rp;

void iwRet(void);
void iwBye(void);
void iwEmit(void);
void iwKey(void);
void iwDot(void);
void iwAdd(void);
void iwSub(void);
void iwMul(void);
void iwDiv(void);
void iwDup(void);
void iwOver(void);
void iwPick(void);
void iwDrop(void);

#endif

