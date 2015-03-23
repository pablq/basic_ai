/*
 * I'm toying with the idea of having my program accept the output filename as an argument
 * after the command line.  This will prevent the user from accidentally overwriting a file that is
 * meant to be an input file.  So, i'm toying with the idea of using these safe getstring() functions
 * instead of writing my own.  Why reinvent the wheel right?
 *
 * Right now I have two to choose from.  I will end up using the first one (from Harvard's CS50 library) 
 * because it returns a string that will be easy for me to use in my program.
 *
 * I'm including the second option for now as a way for me to look at another way of doing it.
 * It won't, however, work for me, because it's more complex, and returns an int instead of the char* that I want!
 *
 * getstring.h
 *
 * By Pablo Philipps (sort of) 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //for the second version

#define UINT_MAX 4294967295U

// This first version is taken from Harvard's CS50 library.
// It can be found at: http://dkui3cmikz357.cloudfront.net/library50/c/cs50-library-c-3.0/cs50.c

/* reads a line of text from standard input and returns it as a
 * string (char *), sans trailing newline character.  (Ergo, if
 * user inputs only "\n", returns "" not NULL.)  Returns NULL
 * upon error or no input whatsoever (i.e., just EOF).  Leading
 * and trailing whitespace is not ignored.  Stores string on heap
 * (via malloc); memory must be freed by caller to avoid leak.
 */

char* GetString(void)
{
    // growable buffer for chars
    char* buffer = NULL;

    // capacity of buffer
    unsigned int capacity = 0;

    // number of chars actually in buffer
    unsigned int n = 0;

    // character read or EOF
    int c;

    // iteratively get chars from standard input
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        // grow buffer if necessary
        if (n + 1 > capacity)
        {
            // determine new capacity: start at 32 then double
            if (capacity == 0)
                capacity = 32;
            else if (capacity <= (UINT_MAX / 2))
                capacity *= 2;
            else
            {
                free(buffer);
                return NULL;
            }

            // extend buffer's capacity
            char* temp = realloc(buffer, capacity * sizeof(char));
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        // append current character to buffer
        buffer[n++] = c;
    }

    // return NULL if user provided no input
    if (n == 0 && c == EOF)
        return NULL;

    // minimize buffer
    char* minimal = malloc((n + 1) * sizeof(char));
    strncpy(minimal, buffer, n);
    free(buffer);

    // terminate string
    minimal[n] = '\0';

    // return string
    return minimal;
}

// the following version of getstring comes from this url:
// http://stackoverflow.com/questions/7831755/what-is-the-simplest-way-of-getting-user-input-in-c

void quit() // write error message and quit
{
    fprintf(stderr, "memory exhausted\n");
    exit(1);
}

int getString()
{
    int max = 20;
    char* name = (char*)malloc(max); // allocate buffer
    if (name == 0) quit();

    printf("Enter a file name: ");

    int loop = 1;
    while (loop == 1) 
    { // skip leading whitespace
        int c = getchar();
        if (c == EOF) // end of file!
        {
            loop = 0;
        }
        if (!isspace(c)) 
        {
             ungetc(c, stdin);
             loop = 0;
        }
    }

    loop = 1;
    int i = 0;
    while (loop == 1) 
    {
        int c = getchar();
        if (isspace(c) || c == EOF) // at end, add terminating zero
	{
            name[i] = 0;
            loop = 0;
        }
        name[i] = c;
        if (i==max-1) // buffer full
        {
            max = max+max;
            name = (char*)realloc(name,max); // get a new and larger buffer
            if (name == 0) quit();
        }
        i++;
    }

    printf("The filename is %s\n", name);
    free(name); // release memory
    return 0;
}
