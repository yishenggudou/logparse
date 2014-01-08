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
#include "../LogParse.h"
//#include <bstraux.h>
//#include <bstrlib.h>

//#include "bstraux.h"
//#include "bstrlib.h"



FILE *fp;
int i, ret;
struct bstrList * lines;
struct tagbstring prefix = bsStatic("-> ");



int main(){
  char z = ' ';
  struct parsed_log *log_obj = NULL;
  if (NULL != (fp = fopen("bstrlib.txt", "rb"))) {
    bstring b = bread((bNread) fread, fp);
    fclose (fp);
    if (NULL != (lines = bsplit(b, '\n'))) {
      for (i=0; i < lines->qty; i++) {
        printf("%04d: %s\n", i, bdatae(lines->entry[i], "NULL"));
        log_obj = handle_log(bstr2cstr(lines->entry[i],z));
        //printf("%d\n", &log_obj);
        binsert(lines->entry[i], 0, &prefix, '?');
      }
      bstrListDestroy(lines);
    }
    bdestroy(b);
  }
  return 1;
}
