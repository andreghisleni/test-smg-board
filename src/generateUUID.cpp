
#include "settings.h"


#define MAX_UID 28 /* Change to whatever length you need */

const char * generateUID(){
  /* Change to allowable characters */
  const char possible[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-/\\|[{=-+!@#$%&*}]";
  static char uid[MAX_UID + 1];
  for(int p = 0, i = 0; i < MAX_UID; i++){
    int r = random(0, strlen(possible));
    uid[p++] = possible[r];
  }
  uid[MAX_UID] = '\0';
  return uid;
}
