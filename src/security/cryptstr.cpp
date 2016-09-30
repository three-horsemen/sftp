#include "security/cryptstr.hpp"
char *string_to_charArray (string s)
{
    char *d = (char*)malloc((s.size())*sizeof(char) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s.c_str());                // Copy the characters
    d[s.size()] = '\0';
    return d;                            // Return the new string
}

string charArray_to_string (char *s, int len)
{
    string res = "";
    for(int i = 0; i < len && s[i] != '\0'; i++)
        res.push_back(s[i]);
    return res;
}
string charArray_to_string (char *s)
{
    int len = strlen(s);
    string res = "";
    for(int i = 0; i < len && s[i] != '\0'; i++)
        res.push_back(s[i]);
    return res;
}

string int_to_string(int a)
{
    return std::to_string(a);
}
