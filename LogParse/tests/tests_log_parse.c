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
#include "../dict/dict.c"
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
  dict * d;
  char* userip;
  char* serverip;
  char* date;
  struct parsed_log *log_obj = NULL;
  if (NULL != (fp = fopen("bstrlib.txt", "rb"))) {
    bstring b = bread((bNread) fread, fp);
    fclose (fp);
    if (NULL != (lines = bsplit(b, '\n'))) {
      for (i=0; i < lines->qty; i++) {
        printf("%04d: %s\n", i, bdatae(lines->entry[i], "NULL"));
        d = logHandle(bstr2cstr(lines->entry[i],z));
        userip = dict_get(d, "userip", "UNDEF");
        serverip = dict_get(d, "serverip", "UNDEF");
        date = dict_get(d, "date", "UNDEF");
        printf("%s %s %s\n", userip, serverip, date);
        binsert(lines->entry[i], 0, &prefix, '?');
      }
      bstrListDestroy(lines);
    }
    bdestroy(b);
  }
  return 1;
}
