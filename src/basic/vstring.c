#include <vstring.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


unsigned int vasprintf(char **strp, const char *fmt, va_list ap) {

    va_list ap1;

    size_t size;

    char *buffer;

    
    va_copy(ap1, ap);

    size = vsnprintf(NULL, 0, fmt, ap1) + 1;

    va_end(ap1);

    buffer = calloc(1, size);

    if (!buffer)
        return -1;

    *strp = buffer;

    return vsnprintf(buffer, size, fmt, ap);
}


unsigned int vstring(char **strp, const char *fmt, ...) {
    
    unsigned int error;
    
    va_list ap;

    va_start(ap, fmt);

    error = vasprintf(strp, fmt, ap);

    va_end(ap);

    return error;
}
