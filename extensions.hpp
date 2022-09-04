#ifndef EXTENSIONS_H
#define EXTENSIONS_H
#include <stdint.h>

// Longueur des extensions 
// Important il faut que 2**(5*EXTENSION_LENGTH) < nombre de bits de EXTENSION_CODE_TYPE
// Pour 32 bits => max length == 6
// Pout 64 bits => max length == 12
#define EXTENSION_SHIFT  5
#define EXTENSION_MAX_LENGTH 4
#define extension_code_t uint32_t
static_assert((sizeof(extension_code_t)*8)>=(EXTENSION_MAX_LENGTH*EXTENSION_SHIFT), "Attention les extensions sont trop longues");
static_assert(1<<EXTENSION_SHIFT >= 26, "Attention EXTENSION_SHIFT insuffisant");

#include "extensions.cpp"

#endif

