//
//  File.c
//  LogParse
//
//  Created by haibo zhang on 12/22/13.
//  Copyright (c) 2013 DaFeng. All rights reserved.
//

#include <stdio.h>

#include "../bstring/bstraux.h"
#include "../bstring/bstrlib.h"
//#include <bstraux.h>
//#include <bstrlib.h>

//#include "bstraux.h"
//#include "bstrlib.h"

FILE *fp;
int i, ret;
struct bstrList * lines;
struct tagbstring prefix = bsStatic("-> ");

int main(){
  if (NULL != (fp = fopen("bstrlib.txt", "rb"))) {
    bstring b = bread((bNread) fread, fp);
    fclose (fp);
    if (NULL != (lines = bsplit(b, '\n'))) {
      for (i=0; i < lines->qty; i++) {
        binsert(lines->entry[i], 0, &prefix, '?');
        printf("%04d: %s\n", i, bdatae(lines->entry[i], "NULL"));
      }
      bstrListDestroy(lines);
    }
    bdestroy(b);
  }
  return 1;
}
