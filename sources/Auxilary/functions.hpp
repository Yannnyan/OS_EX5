
#include <string>
#define BUFFERSIZE 1024

// checks if the target starts with the prefix, by iterating through the prefix.
// 1 = yes, 0 = no.
int startsWith(char * target, char * prefix);
// this function returns all the characters that come after space
// the function allocates memory on the heap should be freed later
char * getArg(char * target);

char * convert_string_to_array(std::string const & str);
std::string convertArrToString(char inp[BUFFERSIZE]);