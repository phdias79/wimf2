#ifndef CASE_H
#define CASE_H

#define SEPARATORS "_+-=()~#`'\\/\""

#include <cstdlib>
#include <iostream>
#include <cstring>
//#include <memory>

namespace string_case {
    char _lower[256];
    char _upper[256];
    char _switch_case[256];
    char _is_separator[256] = { '\0' };
    void _initialize() {
        for(int i = 0; i<256; i++) {
            if ((i >= 'A') & (i <= 'Z')) {
                _upper[i] = i;
                _lower[i] = i + 'a' - 'A';
                _switch_case[i] = _lower[i];
            } else if ((i >= 'a') & (i <= 'z')) {
                _lower[i] = i;
                _upper[i] = i + 'A' - 'a';
                _switch_case[i] = _upper[i];
            } else {
                _lower[i] = i;
                _upper[i] = i;
                _switch_case[i] = i;
            }
        }
        for(int i = 0; i<strlen(SEPARATORS); i++) {
            _is_separator[SEPARATORS[i]] = 1;
        }
    };
    // Cette partie permet de lancer l'initialisation
    struct __INIT {
        __INIT() { _initialize(); }
    };
    __INIT __init;
    //
    template <char table[]>
    char * _transform(const char * source, std::size_t length, char * destination) {
        char * destination_end = destination + length + 1;
        char * destination_current = destination;
        while(destination_current < destination_end) {
            *(destination_current++) = table[*(source++)];
        }
        return destination;
    };
    template <char table[]>
    char * _transform(const char * source, std::size_t length) {
        length++;
        char * destination = new char[length];
        char * destination_end = destination + length + 1;
        char * destination_current = destination;
        while(destination_current < destination_end) {
            *(destination_current++) = table[*(source++)];
        }
        return destination;
    };

    inline char * to_lower(const char * source, std::size_t length, char * destination) {
        return _transform<_lower>(source, length, destination) ;
    }
    inline char * to_lower(const char * source, std::size_t length) {
        return _transform<_lower>(source, length) ;
    }
    char to_lower(const char source) {
        return _lower[source];
    }
    inline char * to_upper(const char * source, std::size_t length, char * destination) {
        return _transform<_upper>(source, length, destination) ;
    }
    inline char to_upper(const char source) {
        return _upper[source];
    }
    inline char * to_upper(const char * source, std::size_t length) {
        return _transform<_upper>(source, length) ;
    }
    inline char * switch_case(const char * source, std::size_t length, char * destination) {
        return _transform<_switch_case>(source, length, destination) ;
    }
    inline char * switch_case(const char * source, std::size_t length) {
        return _transform<_switch_case>(source, length) ;
    }
    inline char switch_case(const char source) {
        return _switch_case[source];
    }
    inline char is_separator(const char source) {
        return _is_separator[source];
    }
}

#endif