#ifndef _LLDIRS_
#define _LLDIRS_

#include "Dir.h"

typedef struct nodeDirs* pnodeDirs;
struct nodeDirs {
    pDir dir;
    pnodeDirs next;
};

void LLdirsinit(pnodeDirs*);
void LLdirsinsert(pnodeDirs*, pDir);
void LLdirsfree(pnodeDirs*);
pDir LLdirslookup(pnodeDirs*, char*);
pDir LLdirslookuppath(pnodeDirs*, char*);
pDir LLdirssearch(pnodeDirs*, char*);
void LLdirsprint(pnodeDirs*, pDir);
void LLdirsdelete(pnodeDirs*, pDir);

#endif