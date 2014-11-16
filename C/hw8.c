#include "hw8.h"
#include <stdio.h>
#include <ctype.h>

int hw_matches(const char *str1, const char* pattern);

size_t hw_strlen(const char *str) {
  size_t ctr = 0;
  int incr = 0;
  while (*(str+incr) != '\0') {
    ctr++;
    incr+=sizeof(char);
  }
  return ctr;
}

/**
 * Determines if two strings are exactly equal to each other.
 * @param str1 Pointer to a '\0' terminated string.
 * @param str2 Pointer to a '\0' terminated string.
 * @return Returns 1 if equal, else 0.
 */
int hw_strcmp(const char *str1, const char *str2){
  int i;
  int ret=1;
  if(hw_strlen(str1)!=hw_strlen(str2)) {
    return 0;
  }
  else {
    for(i=0;i<hw_strlen(str1);i=i+sizeof(char)) {
      if(*(str1+i)!=*(str2+i)) {
        ret = 0;
        break;
      }
    }
  }
  return ret;
}

/**
 * Copies the string from src into dst.
 * @param dest Buffer to copy into.
 * @param src String to copy.
 * @param n Non-negative maximum about of bytes that can be copied from src.
 * @return Returns the dst pointer.
 */
char* hw_strncpy(char *dst, const char *src, size_t n){
  int i=0;
  char pad = '\0';
  for(i=0;i<n;i=i+sizeof(char)) {
    if (i>=hw_strlen(src)) {
      *(dst+i) = pad;
    }
    else {
      *(dst+i) = *(src+i);
    }
  }
  *(dst+i) = '\0';
  return dst;
}

/**
 * Finds the index of the character c in the string.
 * @param str A `\0` terminated string to search.
 * @param c Character to search for.
 * @return Returns the index of the first occurrence of the character
 * if it exists, else -1.
 */
int hw_indexof(const char *str, char c){
  int a = -1;
  int i;
  for(i=0;i<=hw_strlen(str);i=i+sizeof(char)) {
    if(*(str+i)==c) {
      a=i;
      break;
    }
  }
  return a;
}

/**
 * Reverse the contents of the string.
 * @param str Pointer to a `\0` terminated string.
 */
void hw_reversestr(char *str){
  int length = hw_strlen(str);
  char *beg = str;
  char *end = str+(sizeof(char)*(length-1));
  char temp;
  int i;
  for(i=0;i<length/2;i++) {
    temp = *(beg+i);
    *(beg+i) = *(end-i);
    *(end-i) = temp;
  }
}

/**
 * Determines if two strings are equal to each other ignoring the case.
 * @param str1 Pointer to a `\0` terminated string.
 * @param str2 Pointer to a `\0` terminated string.
 * @return Returns 1 if the strings are equal, else 0.
 */
int hw_equalsIgnoreCase(const char *str1, const char *str2){
    int i;
    int ret=1;
    if(hw_strlen(str1)!=hw_strlen(str2)) {
      return 0;
    }
    else {
      for(i=0;i<hw_strlen(str1);i=i+sizeof(char)) {
        if(toupper(*(str1+i))!=toupper(*(str2+i))) {
          ret = 0;
          break;
        }
      }
    }
    return ret;
}

/**
 * Replace all characters in the pattern with another symbol.
 * @param str String to replace values that match the pattern.
 * @param pattern Array of characters to search and replace for.
 * @param replacement Character to replace with.
 */
void hw_replaceall(char *str, const char *pattern, char replacement){
  int i;
  int j;
  int l = hw_strlen(str);
  int l2 = hw_strlen(str);
  for(i=0;i<l;i++) {
    for(j=0;j<l2;j++) {
      if(*(str+i)==*(pattern+j)) {
        *(str+i) = replacement;
      }
    }
  }
}

/**
 * Searches a string for '\t' characters and replaces them with spaces.
 * @param str A '\0' terminated string to search tabs for.
 * @param tabsize The number of spaces to replace a tab with.
 * @return A dynamically allocated '\0' terminated string
 * If the operation fails it should return NULL.
 */
char* hw_expandtabs(const char *str, size_t tabsize){
  int tabCounter = 0;
  int ts = (int)tabsize;
  int length = hw_strlen(str);
  int i=0, j=0, k=0;
  for(i=0;i<=length;i++) {
    if(*(str+i)=='\t')
      tabCounter++;
  }
  char * expanded = malloc(length - tabCounter + (tabCounter*ts)+1);
  for(i=0;i<length;i++) {
    if(*(str+i)=='\t') {
      for(j=0;j<tabsize;j++) {
        *(expanded+k) = ' ';
        k++;
      }
    }
    else  {
      *(expanded+k) = *(str+i);
      k++;
    }
  }
  *(expanded+k) = '\0';
  return expanded;
}

/**
 * Splits on a character c and stores the pointers to the each separate
 * token in the return value.
 * @param str String to split.
 * @param c Character to search the string and split on.
 * @return Returns a 2D array containing the split tokens.
 * If the operation fails it should return NULL.
 */
char** hw_split(const char *str, char c){
  const char* pat = &c;
  char** splitted;
  int l = hw_strlen(str);
  int l2, l3=0;
  int i;
  int parts = 1;
  char *temp = malloc(l);
  hw_strncpy(temp, str, l);
  while(*temp==c) {
    temp++;
    l--;
  }
  while(*(temp+l-1) == c) {
    *(temp+l-1) = '\0';
     l--;
  }
  for(i=0;i<l;i++) {
    if(*(temp+i)== c) {
      if(*(temp+i-1)!=c)
        parts++;
    }
  }
  splitted = malloc((parts+1)*sizeof(char*));
  if(parts==1) {
    *splitted = temp;
    *(splitted+1) = NULL;
  }
  else  {
    hw_replaceall(temp, pat, '\0');
    for(i=0;i<parts;i++) {
      while(*(temp+l3)=='\0') {
        l3++;
      }
      l2 = hw_strlen(temp+l3);
      *(splitted+i) = temp+l3;
      l3 += l2+1;
    }
    *(splitted+parts) = NULL;
  }
  return splitted;
}

/**
 * Find and replace all occurrences of find_str in str with replace_str. Note find_str
 * and replace_str can be of varying lengths, and not necessarily the same length.
 * @param str A '\0' character terminated string
 * @param find_str A '\0' character terminated string to search for
 * @param replace_str A '\0' character terminated string to replace with
 * @param dst Place to store new string.
 * @return Returns the number of find_str's replaced
 */
int hw_findAndReplace(char **dst, const char *str, const char *find_str, const char* replace_str){
  int ctr = 0;
  int l = hw_strlen(str);
  int l2 = hw_strlen(find_str);
  int l3 = hw_strlen(replace_str);
  int i=0,j=0;
  char* temp;
  temp = malloc(l2);
  for(i=0;i<l;i++) {
      hw_strncpy(temp,(str+i),l2);
      /*printf("temp: %s\nfind: %s\n",temp, find_str);*/
      if(hw_strcmp(temp,find_str)) {
        ctr++;
      }
  }

  *dst = malloc(l-(ctr*l2)+(ctr*l3));
  i=0;j=0;
  while(i<l) {
    hw_strncpy(temp,(str+i),l2);
    if(hw_strcmp(temp,find_str)) {
      hw_strncpy(*dst+j,replace_str,l3);
      j+=l3;
      i+=l2;
    }
    else {
      *(*dst+j) = *(str+i);
      i++;
      j++;
    }
  }
  return ctr;
}

/**
 * Split str into tokens, where each token is delimited by any of the characters given
 * in the delimiter string. Swap the i-th indexed token with the j-th indexed token
 * within the string, assuming the indexes start with 0. Parameter str should not be
 * physically tokenized, meaning is should be still printable as a single string.
 * @param str A '\0' character terminated string
 * @param i The first index of the token to swap
 * @param j The second index of the token to swap
 * @param delimiter Array of characters which should be considered delimiters
 */
void hw_swapTokens(char *str, size_t i, size_t j, const char *delimiters){
  int ctr = 0;
  int l1 = hw_strlen(str);
  int l2 = hw_strlen(delimiters);
  int iLength;
  int jLength;
  int k=0,l=0,m=0,n=0;
  char *temp = malloc(l1);
  hw_strncpy(temp,str,l1);
  for(k=0;k<l1;k++) {
    for(l=1;l<l2;l++) {
      if(*(temp+k) == *(delimiters+l)) {
        *(temp+k)=*delimiters;
      }
    }
  }
  k=0;
  char ** tokens = hw_split(str,*delimiters);
  while(*(tokens+ctr)!=NULL) {
    ctr++;
  }
  if(i>ctr || j>ctr) {
    return;
  }
  iLength = hw_strlen(*(tokens+i));
  jLength = hw_strlen(*(tokens+j));
  char *temp2 = *(tokens+i);
  *(tokens +i) = *(tokens+j);
  *(tokens+j) = temp2;
  m=0;
  while(*(tokens+m)!=NULL) {
    /*printf("Token %d : %s\n",m,*(tokens+m));*/
    m++;
  }
  temp = malloc(l1);
  hw_strncpy(temp,str,l1);

    k=0;l=0;m=0;
    while(k<l1) {
      if(hw_indexof(delimiters,*(temp+l))!=-1) {
        *(str+k) = *(temp+l);
        k++;l++;
      }
      else {
        for(n=0;n<hw_strlen(*(tokens+m));n++) {
          *(str+k) = *(*(tokens+m)+n);
          k++;
        }
        if(m==i){
          l+=iLength;
        }
        else if (m==j) {
          l+=jLength;
        }
        else {
          l+=hw_strlen(*(tokens+m));
        }
        m++;
      }
    }

  /*printf("\nS: %s\n",str);*/
}

/**
 * Find and replace all occurrences of find_str in str with replace_str. Note
 * find_str and replace_str can be of varying lengths, and not necessarily the
 * same length. Additionally, find_str can have any number of `*` characters
 * within it. Each star can match to any SINGLE non-whitespace character.
 *
 * @param str A '\0' character terminated string
 * @param find_str A '\0' character terminated string to search for
 * @param replace_str A '\0' character terminated string to replace with
 * @param dst Place to store new string.
 * @return Returns the number of find_str's replaced
 */
int ec_findAndReplace(char **dst, const char *str, const char *find_str, const char* replace_str){
  int ctr = 0;
  int l = hw_strlen(str);
  int l2 = hw_strlen(find_str);
  int l3 = hw_strlen(replace_str);
  int i=0,j=0;
  char* temp;
  temp = malloc(l2);
  for(i=0;i<l;i++) {
      hw_strncpy(temp,(str+i),l2);
      if(hw_matches(temp,find_str)) {
        ctr++;
      }
  }

  *dst = malloc(l-(ctr*l2)+(ctr*l3));
  i=0;j=0;
  while(i<l) {
    hw_strncpy(temp,(str+i),l2);
    if(hw_matches(temp,find_str)) {
      hw_strncpy(*dst+j,replace_str,l3);
      j+=l3;
      i+=l2;
    }
    else {
      *(*dst+j) = *(str+i);
      i++;
      j++;
    }
  }
  return ctr;
}



int hw_matches(const char *str1, const char* pattern) {
  int i;
  int ret=1;
  if(hw_strlen(str1)!=hw_strlen(pattern)) {
    return 0;
  }
  else {
    for(i=0;i<hw_strlen(str1);i++) {
      if(*(pattern+i) == '*') {
        if(isspace(*(str1+i))) {
          ret = 0;
          break;
        }
      }
      else if(*(str1+i)!=*(pattern+i)) {
        ret = 0;
        break;
      }
    }
  }
  return ret;
}
