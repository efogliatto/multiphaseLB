#include <dictIO.h>

int main() {

    // Open dictionary
    
    struct dictionary dict = openDict("input");


    char* entry = 0;

    unsigned int status;
    
    status = bracedEntry( "g", dict.content, entry );

    
    
    return 0;

}
