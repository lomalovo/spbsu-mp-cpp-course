#include <string.h>
#include "str.h"
#include <assert.h>

void test_my_strlen(){
    assert(strlen("aaa") == my_strlen("abc"));
    assert(strlen("") == my_strlen(""));
    assert(strlen("aa") != my_strlen("aaa"));
};

void test_my_strcat(){
    char str1[100] = "";
    char str2[100] = "";
    my_strcat(str1, "Hello ");
    my_strcat(str1, "World! ");
    my_strcat(str1, "Call me ");
    my_strcat(str1, "88005553535");
    strcat(str2, "Hello ");
    strcat(str2, "World! ");
    strcat(str2, "Call me ");
    strcat(str2, "88005553535");
    assert(strcmp(str1, str2) == 0);
};

void test_my_strcmp(){
    assert(my_strcmp("abc", "aaa") > 0);
    assert(my_strcmp("", "aaa") < 0);
    assert(my_strcmp("abc", "abcc") < 0);
    assert(my_strcmp("aaa", "aaa") == 0);
    assert(my_strcmp("aaaa", "aaa") > 0);
};

void test_my_strcpy(){
    char str1[100] = "";
    my_strcpy(str1, "aaa");
    assert(strcmp(str1, "aaa") == 0);
    my_strcpy(str1, "");
    assert(strcmp(str1, "") == 0);
};