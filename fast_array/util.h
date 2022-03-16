#pragma once

#ifndef __UTIL_H__
#define __UTIL_H__


#define _CRT_SECURE_NO_WARNINGS

#include "common.h"

#define __WINDOWS__ // for windows applications
//#define __LINUX__


#define strconcat concat

int getLength(char str[]);
char* concat(const char str1[], const char str2[]);
char* concat_token(const char* str1, const char token);
string_dir dir_join(const char* dir1, const char* dir2);
string_dir dir_joins_va(size_t args, string_dir root_dir, ...);


int write_data_file(dtype* arr, const size_t size, char* file_name, const char token, const type_t data_type);
int read_data_file(dtype* arr, const size_t size, char* file_name, const char token, const type_t data_type);
#endif