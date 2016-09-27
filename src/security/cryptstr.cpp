#include "security/cryptstr.hpp"
char *string_to_charArray (string s)
{
    char *d = (char*)malloc((s.size())*sizeof(char) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s.c_str());                // Copy the characters
    return d;                            // Return the new string
}
