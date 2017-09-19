#ifndef __MYSTRINGS_H__
#define __MYSTRINGS_H__

// NOTE: destination memory must be long enough to accomdadate teh desired result
// otherwise memory corruption can happen at run time.
// it is a caller's responsibility to make sure of this.
// ONLY for strings as assumes NULL termination for each input param


// Computes the length of the string str up to but not including the terminating null.
size_t my_strlen(const char *str);


// Appends the string pointed to, by src to the end of the string pointed to by dest.
char *my_strcat(char *dest, const char *src);


// Appends the string pointed to, by src to the end of the string pointed to, by dest
// up to n characters long.
char *my_strncat(char *dest, const char *src, size_t n);


// Compares the string pointed to, by str1 to the string pointed to by str2,
// returns a positive int value if str1>str2, 0 if str1==str2, else negative.
int my_strcmp(const char *str1, const char *str2);


// Compares at most the first n bytes of str1 and str2.
// returns a positive int value if str1>str2, 0 if str1==str2, else negative.
int my_strncmp(const char *str1, const char *str2, size_t n);


// Copies the string pointed to, by src to dest.
char *my_strcpy(char *dest, const char *src);


//Copies up to n characters from the string pointed to, by src to dest.
char *my_strncpy(char *dest, const char *src, size_t n);


// Finds the first occurrence of the character c (an unsigned char) 
// in the string pointed to, by the argument str.
char *my_strchr(const char *str, int c);


// Finds the last occurrence of the character c (an unsigned char) 
// in the string pointed to by the argument str.
char *my_strrchr(const char *str, int c);


// Finds the first character in the string str1 that matches any character specified in str2.
char *my_strpbrk(const char *str1, const char *str2);


// Calculates the length of the initial segment of str1 
// which consists entirely of characters in str2.
size_t my_strspn(const char *str1, const char *str2);


// Calculates the length of the initial segment of str1 
// which consists entirely of characters not in str2.
size_t my_strcspn(const char *str1, const char *str2);


// Finds the first occurrence of the entire string needle (not including the terminating null) 
// which appears in the string haystack. 
// Returns the location of start of needle in haystack, else NULL
char *my_strstr(const char *haystack, const char *needle);


// Reverse given string in place, returns true if it s a pallindrome
int my_strrev(char *str);


// Reverse given string in place between first and last pos (0-based)
char *my_strirev(char *str, int first, int last);


// Reverse sequence of words in a given string without reversing words themselves
char *my_strwrev(char *str);


// Shifts given string to left by sh (rotational shift)
char *my_strshiftl(char *str, int sh);


// Shifts given string to right by sh (rotational shift)
char *my_strshiftr(char *str, int sh);


// Breaks string str into a series of tokens separated by delim.
// first call is with str!=NULL and saved_ptr==NULL
// subsequent calls with str==NULL and saved_ptr!=NULL
// last call with str==NULL and saved_ptr==NULL
char *my_strtok(char *str, const char *delim);


// Find first non repeated char in given string
char my_strnonrepchar( const char *str );


// Replace specified char from given string
// returns number of instances replaced
int my_strreplchar( char *str, char f, char r );


// Remove from str1, occurence of any char in str2
// returns number of instances removed
int my_strremchar( char *str1, const char *str2 );


// Remove from str1, occurence of any non alpha char
int my_strrempunc( char *str1 );


// Convert all chars to lower case
char * my_strlower( char *str );


// Convert all chars to upper case
char * my_strupper( char *str );


// Calculates signature of string in terms of unique char counts
char *my_strsort( const char *str );


// Calculates signature of string in terms of unique char counts
char *my_strgetsign( const char *str, int len );


// Check if str1 is an anagram of str2 (str1 consists of resuffling of chars of str2)
bool my_strisanagram( const char *str1, const char *str2);


// Swap a character with another character in a given string
void my_swapchstr( char *str, int first, int second);


// Generate a permuation of string
void my_strpermute( char *str1, int first, int last );

#endif /* __MYSTRINGS_H__ */