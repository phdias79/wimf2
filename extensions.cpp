#include "extensions.hpp"
#include <memory.h>

extension_code_t extension_code_with_length(const char * filename, unsigned int filename_length) {
    unsigned int ext_length;
    extension_code_t code;
    char car;
    ext_length = 0;
    code = 0;
    while (filename_length > 0) {
        filename_length--;
        car = filename[filename_length];
        if (car == '.') { return code; }
        ext_length++;
        if (ext_length > EXTENSION_MAX_LENGTH) { return 0; }
        if ((car >= 'a') & (car <= 'z')) {
            car -= 'a';
        } else
        if ((car >= 'A') & (car <= 'Z')) {
            car -= 'A';
        } else {
            return 0;
        }
        code = code << 5 + car; // 2**5 = 32 > 26
    }
    return 0;
}

extension_code_t extension_code(const char * filename) {
    return extension_code_with_length(filename, strlen(filename));
}

