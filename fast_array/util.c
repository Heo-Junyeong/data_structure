/**
* @ author : junyeong heo
*
\brief
** This source code defines utility functions 
** such as data or file I/O that make program 
** development overall easier.
*/

#include "util.h"

// Get length of char array
int getLength(char* str)
{
    int i, len = 0;
    for (i = 0; str[i] != '\0'; i++) len++; return len;
}

char* concat(const char* str1, const char* str2)
{
    char* strto = (char*)malloc(getLength(str1) + getLength(str2) + 1);
    int tlen = getLength(str1), i;
	for (i = 0; str2[i] != '\0'; i++) strto[i] = str1[i];
    for (i = 0; str2[i] != '\0'; i++) strto[tlen + i] = str2[i];
    strto[tlen + i] = '\0';
    return strto;
}

char* concat_token(const char* str1, const char token)
{
    char* strto = (char*)malloc(strlen(str1) + 2);
    int tlen = strlen(str1), i;
    for (i = 0; i < tlen; i++) strto[i] = str1[i];
    strto[tlen] = token, strto[tlen + 1] = '\0';
    return strto;
}
string_dir dir_join(const char* dir1, const char* dir2)
{
    /*
       join directory ,, ex) "directory1 // directory2"
    */
#ifdef __WINDOWS__
    return concat(concat(dir1, "\\"), dir2);
#endif
#ifdef __LINUX__
    return concat(concat(dir1, "/"), dir2);
#endif

}

string_dir dir_joins_va(size_t args, string_dir root_dir, ...)
{
    /*
      strcats for directory
    */
    int i;
    va_list ap;
    string_dir sd, dir = root_dir;

    va_start(ap, root_dir);

    for (i = 0; i < args - 1; i++)
    {
        sd = va_arg(ap, string_dir);
        dir = dir_join(dir, sd);
    }
    va_end(ap);

    return dir;
}

int write_data_file(dtype* arr, const size_t size, char* file_name, const char token, const type_t data_type)
{
	int i; // for iteration
	FILE* inout_fp;
	char* fn = NULL; // temp file name

	if ((strstr(file_name, ".dat") == NULL) || (strstr(file_name, ".txt") == NULL))
	{
		if ((inout_fp = fopen(concat(file_name, ".dat"), "w")) == NULL)
		{
			fprintf(stderr, "File Open Error!\n");
			return -1;
		}
	}
	else
	{
		if ((inout_fp = fopen(file_name, "w")) == NULL)
		{
			fprintf(stderr, "File Open Error!\n");
			return -1;
		}
	}

	fseek(inout_fp, NULL, SEEK_SET);

	// data type
	if (!(strcmp(data_type, "int") && strcmp(data_type, "int32") && strcmp(data_type, "signed int") && strcmp(data_type, "signed int32")))
		fn = concat_token("%d", token);

	else if (!(strcmp(data_type, "uint") && strcmp(data_type, "uint32") && strcmp(data_type, "unsigned int") && strcmp(data_type, "unsigned int32")))
		fn = concat_token("%u", token);

	else if (!(strcmp(data_type, "short") && strcmp(data_type, "int16") && strcmp(data_type, "signed short") && strcmp(data_type, "signed int16")))
		fn = concat_token("%d", token);

	else if (!(strcmp(data_type, "ushort") && strcmp(data_type, "uint16") && strcmp(data_type, "unsigned short") && strcmp(data_type, "unsigned int16")))
		fn = concat_token("%u", token);

	else if (!(strcmp(data_type, "float") && strcmp(data_type, "float32") && strcmp(data_type, "signed float") && strcmp(data_type, "signed float32")))
		fn = concat_token("%f", token);

	else if (!(strcmp(data_type, "double") && strcmp(data_type, "float64") && strcmp(data_type, "signed double") && strcmp(data_type, "signed float64")))
		fn = concat_token("%lf", token);

	else
	{
		printf("write_data_file : \"(%s)\" is Unsuppored data type \n", data_type);
		return -1;
	}

	for (i = 0; i < size; i++) fprintf(inout_fp, fn, arr[i]);

	fclose(inout_fp);

	return 0;
}

int read_data_file(dtype* arr, const size_t size, char* file_name, const char token, const type_t data_type)
{
	int i; // for iteration
	FILE* inout_fp;
	char* fn = NULL; // temp file name

	if ((strstr(file_name, ".dat") == NULL) || (strstr(file_name, ".txt") == NULL))
	{
		if ((inout_fp = fopen(concat(file_name, ".dat"), "r")) == NULL)
		{
			fprintf(stderr, "File Open Error!\n");
			return -1;
		}
	}
	else
	{
		if ((inout_fp = fopen(file_name, "r")) == NULL)
		{
			fprintf(stderr, "File Open Error!\n");
			return -1;
		}
	}

	fseek(inout_fp, NULL, SEEK_SET);

	// data type
	if (!(strcmp(data_type, "int") && strcmp(data_type, "int32") && strcmp(data_type, "signed int") && strcmp(data_type, "signed int32")))
		fn = concat_token("%d", token);

	else if (!(strcmp(data_type, "uint") && strcmp(data_type, "uint32") && strcmp(data_type, "unsigned int") && strcmp(data_type, "unsigned int32")))
		fn = concat_token("%u", token);

	else if (!(strcmp(data_type, "short") && strcmp(data_type, "int16") && strcmp(data_type, "signed short") && strcmp(data_type, "signed int16")))
		fn = concat_token("%d", token);

	else if (!(strcmp(data_type, "ushort") && strcmp(data_type, "uint16") && strcmp(data_type, "unsigned short") && strcmp(data_type, "unsigned int16")))
		fn = concat_token("%u", token);

	else if (!(strcmp(data_type, "float") && strcmp(data_type, "float32") && strcmp(data_type, "signed float") && strcmp(data_type, "signed float32")))
		fn = concat_token("%f", token);

	else if (!(strcmp(data_type, "double") && strcmp(data_type, "float64") && strcmp(data_type, "signed double") && strcmp(data_type, "signed float64")))
		fn = concat_token("%lf", token);

	else
	{
		printf("write_data_file : \"(%s)\" is Unsuppored data type \n", data_type);
		return -1;
	}

	for (i = 0; i < size; i++) fscanf(inout_fp, fn, &arr[i]);

	fclose(inout_fp);

	return 0;
}