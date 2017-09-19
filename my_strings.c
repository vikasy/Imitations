/********************************************************************
  Author: Vikas YADAV (vikasy@gmail.com)
  Filename: my_strings.c
  Topic: Implementaton of various tring related functions
   
  Objective: Implement a host of string related functions, most of them 
  are found in C strings.h definitions.
  
  ***********************************************************************/
  
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my_strings.h"

char haystack[10000000];
char needle[100];

// test driver
int main( void )
{
    int i;
    char *c1, *c2;
    char *tok;
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strlen vs my_strlen:%lu vs %lu\n", (unsigned long)strlen(s1), (unsigned long)my_strlen(s1));
        printf("strlen vs my_strlen:%lu vs %lu\n", (unsigned long)strlen(s2), (unsigned long)my_strlen(s2));
        printf("strlen vs my_strlen:%lu vs %lu\n", (unsigned long)strlen(s3), (unsigned long)my_strlen(s3));

        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strcmp vs my_strcmp:%d vs %d\n", strcmp(s2, s2), my_strcmp(s2, s2));
        printf("strcmp vs my_strcmp:%d vs %d\n", strcmp(s3, s1), my_strcmp(s3, s1));
        printf("strcmp vs my_strcmp:%d vs %d\n", strcmp(s1, s2), my_strcmp(s1, s2));
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strncmp vs my_strncmp:%d vs %d\n", strncmp(s2, s2, 10), my_strncmp(s2, s2, 10));
        printf("strncmp vs my_strncmp:%d vs %d\n", strncmp(s3, s1, 100), my_strncmp(s3, s1, 100));
        printf("strncmp vs my_strncmp:%d vs %d\n", strncmp(s1, s2, 0), my_strncmp(s1, s2, 0));
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strcpy vs my_strcpy:\n%s\n%s\n", strcpy(s1, s2), my_strcpy(s1, s2));
        printf("strcpy vs my_strcpy:\n%s\n%s\n", strcpy(s2, s3), my_strcpy(s2, s3));
        printf("strcpy vs my_strcpy:\n%s\n%s\n", strcpy(s3, s1), my_strcpy(s3, s1));
    }

    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strncpy vs my_strncpy:\n%s\n%s\n", strncpy(s1, s2, 100), my_strncpy(s1, s2, 100));
        printf("strncpy vs my_strncpy:\n%s\n%s\n", strncpy(s2, s3, 5), my_strncpy(s2, s3, 5));
        printf("strncpy vs my_strncpy:\n%s\n%s\n", strncpy(s3, s1, 10), my_strncpy(s3, s1, 10));
    }
    
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strcat vs my_strcat:\n%s\n%s\n", strcat(s2, s3), my_strcat(s2, s3));
        printf("strcat vs my_strcat:\n%s\n%s\n", strcat(s3, s1), my_strcat(s3, s1));
        printf("strcat vs my_strcat:\n%s\n%s\n", strcat(s1, s2), my_strcat(s1, s2));
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strncat vs my_strncat:\n%s\n%s\n", strncat(s2, s3, 5), my_strncat(s2, s3, 5));
        printf("strncat vs my_strncat:\n%s\n%s\n", strncat(s3, s1, 10), my_strncat(s3, s1, 10));
        printf("strncat vs my_strncat:\n%s\n%s\n", strncat(s1, s2, 5), my_strncat(s1, s2, 5));
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strchr vs my_strchr:\n%s\n%s\n", strchr(s2, 'd'), my_strchr(s2, 'd'));
        printf("strchr vs my_strchr:\n%s\n%s\n", strchr(s3, 'd'), my_strchr(s3, 'd'));
        printf("strchr vs my_strchr:\n%s\n%s\n", strchr(s1, 'd'), my_strchr(s1, 'd'));
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strrchr vs my_strrchr:\n%s\n%s\n", strrchr(s2, 'd'), my_strrchr(s2, 'd'));
        printf("strrchr vs my_strrchr:\n%s\n%s\n", strrchr(s3, 'd'), my_strrchr(s3, 'd'));
        printf("strrchr vs my_strrchr:\n%s\n%s\n", strrchr(s1, 'd'), my_strrchr(s1, 'd'));
    }

    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strspn vs my_strspn:\n%lu\n%lu\n",(unsigned long)strspn(s2,"d"),(unsigned long)my_strspn(s2,"d"));
        printf("strspn vs my_strspn:\n%lu\n%lu\n",(unsigned long)strspn(s3,"d"),(unsigned long)my_strspn(s3,"d"));
        printf("strspn vs my_strspn:\n%lu\n%lu\n",(unsigned long)strspn(s1,"d"),(unsigned long)my_strspn(s1,"d"));
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strcspn vs my_strcspn:\n%lu\n%lu\n",(unsigned long)strcspn(s2,"d"),(unsigned long)my_strcspn(s2,"d"));
        printf("strcspn vs my_strcspn:\n%lu\n%lu\n",(unsigned long)strcspn(s3,"d"),(unsigned long)my_strcspn(s3,"d"));
        printf("strcspn vs my_strcspn:\n%lu\n%lu\n",(unsigned long)strcspn(s1,"d"),(unsigned long)my_strcspn(s1,"d"));
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("strpbrk vs my_strpbrk:\n%s\n%s\n", strpbrk(s2, "efg"), my_strpbrk(s2, "efg"));
        printf("strpbrk vs my_strpbrk:\n%s\n%s\n", strpbrk(s3, "efg"), my_strpbrk(s3, "efg"));
        printf("strpbrk vs my_strpbrk:\n%s\n%s\n", strpbrk(s1, "efg"), my_strpbrk(s1, "efg"));
    }


    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        my_strrev(s1);
        my_strrev(s2);
        my_strrev(s3);
        printf("my_strrev:\n%s\n", s1 );
        printf("my_strrev:\n%s\n", s2 );
        printf("my_strrev:\n%s\n", s3 );
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strirev:\n%s\n", my_strirev(s1,2,5) );
        printf("my_strirev:\n%s\n", my_strirev(s2,2,5) );
        printf("my_strirev:\n%s\n", my_strirev(s3,2,5) );
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strwrev:\n%s\n", my_strwrev(s1) );
        printf("my_strwrev:\n%s\n", my_strwrev(s2) );
        printf("my_strwrev:\n%s\n", my_strwrev(s3) );
    }
    
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strshiftl:\n%s\n", my_strshiftl(s1,4) );
        printf("my_strshiftl:\n%s\n", my_strshiftl(s2,0) );
        printf("my_strshiftl:\n%s\n", my_strshiftl(s3,7) );
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strshiftr:\n%s\n", my_strshiftr(s1,4) );
        printf("my_strshiftr:\n%s\n", my_strshiftr(s2,0) );
        printf("my_strshiftr:\n%s\n", my_strshiftr(s3,7) );
    }
    
    {
        char ss4[100] = "--What  a wonderful night..\tit is yay! yay!! ya!!!\n";
        
        char *s4 = &ss4[0];
        
        printf("\n\nstrtok:");
        printf("%s\n",s4);
        tok = strtok (s4," ,.-\t");
        while (tok != NULL)
        {
            printf ("%s\n",tok);
            tok = strtok (NULL, " ,.-\t");
        }
    }
    
    {
        char ss4[100] = "--What  a wonderful night..\tit is yay! yay!! ya!!!\n";
        
        char *s4 = &ss4[0];
        
        printf("\n\nmy_strtok:");
        printf("%s\n",s4);
        tok = my_strtok (s4," ,.-\t");
        while (tok != NULL)
        {
            printf ("%s\n",tok);
            tok = my_strtok (NULL, " ,.-\t");
        }
    }


    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed, Mr. Duddley!";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strnonrepchar:\n%c\n", my_strnonrepchar(s1) );
        printf("my_strnonrepchar:\n%c\n", my_strnonrepchar(s2) );
        printf("my_strnonrepchar:\n%c\n", my_strnonrepchar(s3) );

        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strreplchar:\n%d\n", my_strreplchar(s1,'e','E') );
        printf("my_strreplchar:\n%d\n", my_strreplchar(s2,'e','E') );
        printf("my_strreplchar:\n%d\n", my_strreplchar(s3,'e','E') );
        printf("%s\n%s\n%s\n",s1,s2,s3);

        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strremchar (remove \"deda\"):\n%d\n", my_strremchar(s1,"deda") );
        printf("my_strremchar (remove \"deda\"):\n%d\n", my_strremchar(s2,"d") );
        printf("my_strremchar (remove \"deda\"):\n%d\n", my_strremchar(s3,"d") );
        printf("%s\n%s\n%s\n",s1,s2,s3);
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strrempunc:\n%d\n", my_strrempunc(s1) );
        printf("my_strrempunc:\n%d\n", my_strrempunc(s2) );
        printf("my_strrempunc:\n%d\n", my_strrempunc(s3) );
        printf("%s\n%s\n%s\n",s1,s2,s3);

    }
    
    {
        char *haystack1="Hello world is here";
        char *needle1="world";
        c1 = strstr(haystack1, needle1);
        c2 = my_strstr(haystack1,needle1);
        printf("\n\n");
        printf("strstr vs my_strstr:\n%c\n%c\n", *c1, *c2);
    }

    {
        clock_t start_time, end_time;
        float   time_in_sec = 0.0f;
        //size_t  d1,d2;
        
        // cpu efficiency time test
        printf("\nTime test...\n");
        
        for(i=0; i<90; i++)
            needle[i] = 'a';
        for(i=0; i<10000000; i++)
            haystack[i] = 'b';
        for(i=9000000; i<9000090; i++)
            haystack[i] = 'a';
    
        start_time = clock();        
        //d1 = strcspn(haystack, needle );
        //c1 = strchr(haystack, 'a');
        c1 = strstr(haystack, needle);
        end_time = clock();
        printf("Total time in cpu ticks = %ld\n", end_time-start_time);
        time_in_sec = (float)(end_time-start_time)/CLOCKS_PER_SEC;
        printf("Total time in sec = %f\n", time_in_sec);
        
        start_time = clock();
        //d2 = my_strcspn(haystack, needle );
        //c2 = my_strchr(haystack, 'a');
        c2 = my_strstr(haystack,needle);
        end_time = clock();
        printf("Total time in cpu ticks = %ld\n", end_time-start_time);
        time_in_sec = (float)(end_time-start_time)/CLOCKS_PER_SEC;
        printf("Total time in sec = %f\n", time_in_sec);
        
        //printf("strcspn vs my_strcspn:\n%ul\n%ul\n", d1, d2);
        //printf("strchr vs my_strchr:\n%c\n%c\n", *c1, *c2);
        printf("strstr vs my_strstr:\n%c\n%c\n", *c1, *c2);
        
    }
    
    {
        char ss1[100] = "Wow! Today is a wonderful day!";
        char ss2[100] = "Isn't it...  wonderful?";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strsort:\n%s\n", my_strsort(s1) );
        printf("my_strsort:\n%s\n", my_strsort(s2) );
        printf("my_strsort:\n%s\n", my_strsort(s3) );
    }
    
    {
        char ss1[100] = "Here is the classroom, Dan.";
        char ss2[100] = "And, schoolmaster is here.";
        char ss3[100] = "Yes, Indeed";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strisanagram:(0=no,1=yes)\n%d\n", my_strisanagram(s1, s2) );
        printf("my_strisanagram:(0=no,1=yes)\n%d\n", my_strisanagram(s3, s3) );
        printf("my_strisanagram:(0=no,1=yes)\n%d\n", my_strisanagram(s1, s3) );
    }
    
    {
        char ss1[100] = "Classroom";
        char ss2[100] = "schoolmaster";
        char ss3[100] = "RiverMissisippie";
        
        char *s1 = &ss1[0];
        char *s2 = &ss2[0];
        char *s3 = &ss3[0];
        
        printf("\n\n");
        printf("%s\n%s\n%s\n",s1,s2,s3);
        printf("my_strgetsign:(Calmo2rs2)\n%s\n", my_strgetsign(s1, 9) );
        printf("my_strgetsign:(acehlmo2rs2)\n%s\n", my_strgetsign(s2, 13) );
        printf("my_strgetsign:(MRe2i5p2s3v)\n%s\n", my_strgetsign(s3, 17) );
        
    }
    
    {
        char teststr[] = "ABCA";
        my_strpermute(teststr,0,4);
    }
    
    return 0;
}

// NOTE: destination memory must be long enough to accomdadate teh desired result
// otherwise memory corruption can happen at run time.
// it is a caller's responsibility to make sure of this.
// ONLY for strings as assumes NULL termination for each input param

//Computes the length of the string str up to but not including the terminating null character.
size_t my_strlen(const char *str)
{
    size_t n = 0;
    while( *str++ ) n++;
    return n;
}

//Appends the string pointed to, by src to the end of the string pointed to by dest.
char *my_strcat(char *dest, const char *src)
{
    char *retptr = dest;
    // go to the end of dest 
    while( *dest ) dest++;
    // now add the src at the end of dest
    while( (*dest++ = *src++) );
    return retptr;
}


//Appends the string pointed to, by src to the end of the string pointed to, by dest up to n characters long.
char *my_strncat(char *dest, const char *src, size_t n)
{
    char   *retptr = dest;
    // go to the end of dest 
    while( *dest ) dest++;
    // now add the src at the end of dest
    while( n--)
        if( !(*dest++ = *src++) ) return retptr;
    *dest = '\0';
    return retptr;
}


//Compares the string pointed to, by str1 to the string pointed to by str2.
//Returns 
int my_strcmp(const char *str1, const char *str2)
{
    while( *str1 && *str1 == *str2 )
        str1++, str2++;
    return *str1 - *str2;
}


//Compares at most the first n chars of str1 and str2.
int my_strncmp(const char *str1, const char *str2, size_t n)
{
    while( n-- )
        if( *str1++ != *str2++ ) return *(str1-1) - *(str2-1);
    return 0;
}


// Copies the string pointed to, by src to dest.
char *my_strcpy(char *dest, const char *src)
{
    char *retptr = dest;
    while( (*dest++ = *src++) );
    return retptr;
}


//Copies up to n characters from the string pointed to, by src to dest.
char *my_strncpy(char *dest, const char *src, size_t n)
{
    char *retptr = dest;
    while( n-- )
        if( !(*dest++ = *src++) ) return retptr;
    return retptr;
}


//Searches for the first occurrence of the character c (an unsigned char) in the string pointed to, by the argument str.
char *my_strchr(const char *str, int c)
{
    while( *str != (char)c )
        if( !*str++ ) return NULL;
    return (char *)str;
}


//Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str.
char *my_strrchr(const char *str, int c)
{ 
    char *retptr = NULL;
    while( *str++ )
        if( *str == c ) retptr = (char *)str;
    return retptr;
}


//Finds the first occurrence of the entire string needle (not including the terminating null character) 
//which appears in the string haystack.
char *my_strstr(const char *haystack, const char *needle)
{
    size_t    len = strlen(needle);

    if( strlen(haystack) < len )
        return NULL;
    
    while( *haystack ) {
        if( !my_strncmp( haystack++, needle, len ) )
            return (char *)haystack-1;
    }
    return NULL;
    
}


//Calculates the length of the initial segment of str1 which consists entirely of characters in str2.
size_t my_strspn(const char *str1, const char *str2)
{
    size_t retval = 0;
    // traverse str1 char by char
    // and for each char in str1, check if it is str2
    while( *str1 && my_strchr( str2, *str1++) )
        retval++;
    return retval;
}


//Calculates the length of the initial segment of str1 which consists entirely of characters not in str2.
size_t my_strcspn(const char *str1, const char *str2)
{
    size_t retval = 0;
    // traverse str1 char by char
    // and for each char in str1, check if it is str2
    while( *str1 && !my_strchr( str2, *str1++) )
        retval++;
    return retval;
}


//Finds the first character in the string str1 that matches any character specified in str2.
char *my_strpbrk(const char *str1, const char *str2)
{
    // traverse str1 char by char
    // and for each char in str1, check if it is str2
    while( *str1 )
        if( my_strchr( str2, *str1++) )
            return (char *) --str1;
    return 0;
}


//Reverse a given string in place
// returns a 1 if string is a palindrome
int my_strrev(char *str)
{
    char     *start = str;
    char     *end = str + strlen( str ) - 1;
    char      temp;
    int       is_palindrome = (*start == *end);

    while( start < end ) {
        temp= *end;
        *end = *start;
        *start = temp;
        if( *start++ != *end-- )
            is_palindrome = 0;  // not a palindrome anymore
    }
    
    return is_palindrome;
}

//Reverse a given string in place, based on start and end index
char *my_strirev(char *str, int start, int end)
{
    char temp;
    
    while( start < end ) {
        temp = *(str+end);
        *(str+end) = *(str+start);
        *(str+start) = temp;
        start++, end--;
    }
    
    return str;
}


//Reverse words in a given string in place
char *my_strwrev(char *str)
{
    size_t   len = strlen( str );
    int      first = 0, last = 0;
    int i = 0;

    // reverse the whole string 
    str = my_strirev( str, 0, len-1 );
    
    // next reverse every word in it
    do {
        // skip ws, get to first char in a word
        while( *(str+i) == ' ' ) i++, first++; 
        // increase i to avoid rechecking str+i
        i++;
        last = first;
        // get to the last char in a word
        while( *(str+i) != ' ' && *(str+i) != '\0' ) 
            i++, last++;
        // reverse the word between first and last
        str = my_strirev( str, first, last );
        // increase i to avoid rechecking str+i
        i++;
        first = last+2;
    } while( first < len );

    return str;
}


//Shift a given string in place, left shift by x
// [a,b] -> [b,a] where a is subtring of length x
// Reverse a and b -> ar and br
// Reverse [ar,br] -> [b,a]
char *my_strshiftl(char *str, int sh)
{
    size_t  len = strlen(str);

    str = my_strirev( str, 0, sh-1);
    str = my_strirev( str, sh, len-1);
    str = my_strirev( str, 0, len-1);
    
    return str;
}


//Shift a given string in place, right shift by x
// [a,b] -> [b,a] where b is subtring of length x
// Reverse a and b -> ar and br
char *my_strshiftr(char *str, int sh)
{
    size_t  len = strlen(str);
    
    str = my_strirev( str, 0, len-sh-1);
    str = my_strirev( str, len-sh, len-1);
    str = my_strirev( str, 0, len-1);
    
    return str;
}


//Breaks string str into a series of tokens separated by delim string.
char *my_strtok(char *str, const char *delim)
{
    size_t    skip_len = 0;
    size_t    token_len = 0;
    size_t    str_len = 0;
    
    static char  *saved_ptr = NULL;
    
    // first call is with str!=NULL (and saved_ptr init to NULL)
    // subsequent calls with str==NULL and saved_ptr!=NULL
    // last call with str==NULL and saved_ptr==NULL
    if( str == NULL ) {
        if( saved_ptr != NULL )
            str = saved_ptr;
        else
            return NULL;
    }
    
    str_len = strlen( str );
    
    skip_len = my_strspn( str, delim);
    if( skip_len == str_len )
        return NULL;
    
    str += skip_len;
    str_len = strlen( str );
    token_len = my_strcspn( str, delim);
    if( token_len < str_len ) {
        *(str+token_len) = '\0';
        saved_ptr = (str + token_len +1);
    }
    else 
        saved_ptr = NULL;

    return str;
}


// Find first non repeated alpha char in given string
char my_strnonrepchar( const char *str )
{
    int  Index[128] = {0};
    int  i = 0;
    int  len = 0;
    int  min;
    char retchar = 0;
    
    // Index is an array of first 128 ascii chars
    // each element of Index is init to 0
    // after processing the string, each element of Index
    // is set to the index of char in string if it is present only once or 
    // set to -1 if a char is present more than one time
    while( *(str+i) ) {
        if( Index[(int)*(str+i)] == 0 )
            Index[(int)*(str+i)] = i+1;
        else
            Index[(int)*(str+i)] = -1;
        i++, len++;
    }
    
    // The first non repeating char is smallest positive number in Index
    min = len+1;
    for( i=0; i<128; i++ ) {
        if( Index[i] > 0 && Index[i] < min ) {
            min = Index[i];
            retchar = (char)i;
        }
    }
    
    return retchar;
    
}


// Replace specified char from given string
// returns number of instances replaced
int my_strreplchar( char *str, char f, char r )
{
    int count = 0;
    while( *str ) {
        if( *str == f ) 
            *str = r, count++;
        str++;
    }
    return count;
}


// Remove from str1, occurence of any char in str2
// returns number of instances removed
int my_strremchar( char *str1, const char *str2 )
{
    int    i, j; 
    int    len = strlen(str1);
    
    int Index[128] = {0};
    // Index is an array of first 128 ascii chars, init to 0
    // each element of Index is set to 1 if the index is a char in str2
    // each char of str1 for which Index element is 1 is removed
    while( *str2 ) Index[(int)(*str2++)] = 1; 
    
    for( i=j=0; i<len+1; i++ ) {
        if( Index[(int)(*(str1+i))] ) continue;
        *(str1+j) = *(str1+i);
        j++;
    }
    
    return (i-j-1);
}


// Remove from str1, occurence of any non alpha char
int my_strrempunc( char *str1 )
{
    int    i, j; 
    int    len = strlen(str1);
       
    for( i=j=0; i<len+1; i++ ) {
        // skip if char is not alpha
        if( *(str1+i)<65 || (*(str1+i)>90&&*(str1+i)<97) || *(str1+i) > 122 ) 
            continue;
        *(str1+j) = *(str1+i);
        j++;
    }
    *(str1+j) = 0;

    return (i-j-1);
}


// Convert all chars to lower case
char * my_strlower( char *str )
{
    char *ret = str;
    
    while( *str ) {
        if( *str >= 65 && *str <= 90 ) *str += 32;
        str++;
    }

    return ret;
}


int charcmp(const void *item1, const void  *item2)
{
    return (*(char *)item1 - *(char *)item2);
}

// Sorts given string in lexicographical order
char * my_strsort( const char *str )
{
    size_t len = strlen(str);
    // sort given string
    qsort( (void *)str, len, 1, charcmp);

    return (char *)str;
}


// Calculates signature of string in terms of unique char counts
// eg. apple = aelp2, missisippie=ei4mp2s3
// overwrites input string
char * my_strgetsign( const char *str, int len )
{
    int   Index[128] = {0};
    int   i=0, j=0;
    char *retstrptr;

    retstrptr=my_strsort(str);
    
    // Index is an array of first 128 ascii chars, each element is set to number of 
    // occurence of the ascii char in the given string
    while( *(retstrptr+i) ) {
        Index[(int)*(retstrptr+i)] += 1;
        i++;
    }
    for(i=0;i<128;i++) {
        if(Index[i]>0) {
            retstrptr[j++]=i;
            if(Index[i]>1) 
                retstrptr[j++]=Index[i]+'0';
        }
    }
    retstrptr[j]='\0';
    
    return retstrptr;
}


// Check if str1 is an anagram of str2 (str1 consists of resuffling of chars of str2)
bool my_strisanagram( const char *str1, const char *str2)
{
    char *str1s, *str2s;
    
    // all lower case
    str1s = my_strlower((char *)str1);
    str2s = my_strlower((char *)str2);
    // remove non-alphas
    my_strrempunc(str1s);
    my_strrempunc(str2s);
    // sort alphas
    str1s = my_strsort(str1s);
    str2s = my_strsort(str2s);

    return (strcmp(str1s, str2s) == 0);

}


// Swap a character with another character in a given string
void my_swapchstr( char *str, int first, int second)
{
    char temp;
    temp = str[first];
    str[first]=str[second];
    str[second]=temp;
}


// Generate all permuations of string
void my_strpermute( char *str1, int first, int last )
{
    int i;
    
    if( first >= last ) printf("%s\n",str1);
    else {
        for(i=first; i<last; ++i) {
            // one by one select from first char to the last and bring to first pos 
            my_swapchstr(str1,first,i); 
            // permute the remaining string from first+1 to last
            my_strpermute(str1, first+1, last);
            // backtrack: restore the selected char at first post to its original position
            my_swapchstr(str1,i,first);
        }
    }
}

