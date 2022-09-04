#ifndef COMPARE_STRING_H
#define COMPARE_STRING_H

#include <cstdlib>
#include <cstring>
#include <memory>
#include <iostream>
#include "string_case.hpp"
/* CODES ASCII

A:01000001
Z:01011010
a:01100001
z:01111010
_:01011111
-:00101101

*/
//
int in_string_sensitive_1(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    if (in_string_length < reference_length) { return -1; };
    if (reference_length == 0) { return -1; };
    const char * in_string_initial = in_string;
    const char * reference_end = reference + reference_length;
    const char * in_string_end = in_string + in_string_length - reference_length;
    while(in_string <= in_string_end) {
test:
        const char * in_string_current = in_string;
        const char * reference_current = reference;
        while(reference_current < reference_end) {
            if ((*(reference_current++)) != (*(in_string_current++))) {
                goto different;
            }
        };
test_says_equal:
        return in_string - in_string_initial;
different:
        in_string++;
        in_string_length--;
    };
    return -1;
}

int in_string_sensitive_2(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {    
    if (in_string_length < reference_length) { return -1; };
    if (reference_length == 0) { return -1; };
    const char * in_string_initial = in_string;
    const char * in_string_end = in_string + in_string_length - reference_length;
    while(in_string <= in_string_end) {
        if (memcmp(reference, in_string, reference_length) == 0) {
            return in_string - in_string_initial;
        }
        in_string++;
        in_string_length--;
    };
    return -1;
}

int in_string_sensitive_3(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    if (in_string_length < reference_length) { return -1; };
    if (reference_length == 0) { return -1; };
    static char previous_first_car = 0;
    static uint16_t repeat_first_car_2_times;
    static uint32_t repeat_first_car_4_times;
    static uint64_t repeat_first_car_8_times;
    if (previous_first_car != (* reference)) {
        previous_first_car = (* reference);
        repeat_first_car_2_times = (*reference);
        repeat_first_car_2_times = (repeat_first_car_2_times << 8) + repeat_first_car_2_times;
        repeat_first_car_4_times = repeat_first_car_2_times;
        repeat_first_car_4_times = (repeat_first_car_4_times << 16) + repeat_first_car_4_times;
        repeat_first_car_8_times = repeat_first_car_4_times;
        repeat_first_car_8_times = (repeat_first_car_8_times << 32) + repeat_first_car_8_times;
    }
    // Compare les 8 premiers caractères
    const char * in_string_initial = in_string;
    const char * in_string_end = in_string + in_string_length - reference_length;
    const char * reference_end = reference + reference_length;
    redo:
    while (in_string_length >= 8) {
        if ((* ((uint64_t *) in_string)) & repeat_first_car_8_times) {
            break;
        }
        in_string+=8;
        in_string_length-=8;
        if (in_string > in_string_end) { return -1; }
    }
    // Compare les 4 premiers caractères
    if (in_string_length >= 4) {
        if (!((* ((uint32_t *) in_string)) & repeat_first_car_4_times)) {
            in_string+=4;
            in_string_length-=4;
            if (in_string > in_string_end) { return -1; }
        }
    }
    // Compare le 2 premiers caractères
    if (in_string_length >= 2) {
        if (!((* ((uint16_t *) in_string)) & repeat_first_car_2_times)) {
            in_string+=2;
            in_string_length-=2;
            if (in_string > in_string_end) { return -1; }
        }
    }
    // On arrive ici si on a 1 seul caractère, ou si il y a un match sur l'un des deux premiers caractères
    int c = 0;
    while((* in_string) != (* reference)) {
        in_string+=1;
        in_string_length-=1;
        if (in_string > in_string_end) { return -1; }
        c++;
        if (c > 1) {
            //std::cout << "ERREUR ! : " << c << "\n";
        }
    }
    // On arrive ici si le 1er caractère matche
    if ((* in_string) != (* reference)) {
        //std::cout << "ERREUR !\n";
    }
    
test:
    const char * in_string_current = in_string+1;
    const char * reference_current = reference+1;

    while(reference_current < reference_end) {
        if ((*(reference_current++)) != (*(in_string_current++))) {
            goto different;
        }
    };
test_says_equal:
    return in_string - in_string_initial;
different:
    in_string++;
    in_string_length--;
    if (in_string > in_string_end) { return -1; }
    goto redo;
}


int in_string_sensitive_4(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    if (in_string_length < reference_length) { return -1; };
    if (reference_length == 0) { return -1; };
    const char * in_string_initial = in_string;
    const char * in_string_end = in_string + in_string_length - reference_length;
    const char * reference_end = reference + reference_length;
    compare_first:
    if (in_string <= in_string_end) {
        if ((* in_string) != (* reference)) {
            in_string++;
            goto compare_first;
        }
        const char * in_string_current = in_string+1;
        const char * reference_current = reference+1;
        while(reference_current < reference_end) {
            if ((*(reference_current++)) != (*(in_string_current++))) {
                in_string++;
                goto compare_first;
            }
        };
        return in_string - in_string_initial;
    } else {
        return -1;
    }
}


int in_string_sensitive_5(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    if ((in_string_length >= reference_length) & (reference_length > 0)) {
        const char * in_string_initial = in_string;
        const char * in_string_end = in_string + in_string_length - reference_length;
        const char * reference_end = reference + reference_length;
        compare_first:
        if (in_string <= in_string_end) {
            if ((* in_string) != (* reference)) {
                in_string++;
                goto compare_first;
            }
            const char * in_string_current = in_string+1;
            const char * reference_current = reference+1;
            while(reference_current < reference_end) {
                if ((*(reference_current++)) != (*(in_string_current++))) {
                    in_string++;
                    goto compare_first;
                }
            };
            return in_string - in_string_initial;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int in_string_sensitive_6(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    if ((in_string_length >= reference_length) & (reference_length > 0)) {
        const char * in_string_initial = in_string;
        const char * in_string_end = in_string + in_string_length - reference_length;
        const char * reference_end = reference + reference_length;
        compare_first:
        if (in_string <= in_string_end) {
            if ((* in_string) != (* reference)) {
                in_string++;
                goto compare_first;
            }
            const char * in_string_current = in_string+1;
            const char * reference_current = reference+1;
            while(reference_current < reference_end) {
                if ((*(reference_current++)) != (*(in_string_current++))) {
                    in_string++;
                    goto compare_first;
                }
            };
            return in_string - in_string_initial;
        }
    }
    return -1;
}

int in_string_sensitive_7(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    if (reference_length == 0) { return -1; }
    const char * in_string_initial = in_string;
    const char * reference_p1 = reference+1;
    const char * reference_end = reference + reference_length;
    std::size_t in_string_initial_length = in_string_length;
    std::size_t in_string_current_length;
    compare_first:
    in_string_length = in_string_initial_length - (in_string - in_string_initial);
    if (in_string_length >= reference_length) {
        in_string = (char *) memchr(in_string, (* reference), in_string_length-reference_length+1);
        if (in_string != nullptr) {
            const char * in_string_current = in_string+1;
            const char * reference_current = reference_p1;
            while(reference_current < reference_end) {
                if ((*(reference_current++)) != (*(in_string_current++))) {
                    in_string++;
                    goto compare_first;
                }
            };
            return in_string - in_string_initial;
        }
    }
    return -1;
}

int in_string_sensitive_8(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    if (reference_length == 0) { return -1; }
    const char * in_string_initial = in_string;
    const char * reference_p1 = reference+1;
    std::size_t reference_length_m1 = reference_length-1;
    const char * reference_end = reference + reference_length;
    std::size_t in_string_initial_length = in_string_length;
    const char * in_string_end = in_string_initial + in_string_initial_length;
    std::size_t in_string_current_length;
    compare_first:
    in_string_length = in_string_end - in_string;
    if (in_string_length >= reference_length) {
        in_string = (char *) memchr(in_string, (* reference), in_string_length-reference_length+1);
        if (in_string != nullptr) {
            const char * in_string_current = in_string+1;
            const char * reference_current = reference_p1;
            if (memcmp(in_string+1, reference_p1, reference_length_m1) != 0) {
                in_string++;
                goto compare_first;
            }
            return in_string - in_string_initial;
        }
    }
    return -1;
}

int in_string_sensitive_9(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    const char * reference_p1 = reference+1;
    const char * in_string_initial = in_string;
    char * in_string_end = in_string + in_string_length;
    char * in_string_last = in_string_end - reference_length;
    * in_string_end = * reference;
    const char * reference_end = reference + reference_length; // Vaut 0
    compare:
    while ((* in_string) != (* reference)) { in_string++; }
    if (in_string > in_string_last) {
        * in_string_end = 0;
        return -1;
    }
    char * in_string_current = in_string;
    const char * reference_current = reference_p1;
    while(reference_current < reference_end) {
        if ((*(reference_current)) != (*(++in_string_current))) {
            in_string++;
            goto compare;
        }
        reference_current++;
    };
    * in_string_end = 0;
    if (reference_length == 0) { return -1;}
    return in_string - in_string_initial;
}

int in_string_insensitive_1(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    char * reference_other = new char[in_string_length+1];
    for(auto i = 0; i < reference_length; i++) {
        if (reference[i] < 'A')  {reference_other[i] = reference[i]; continue;}
        if (reference[i] <= 'Z')  {reference_other[i] = reference[i] + ('a' -'A'); continue;}
        if (reference[i] > 'z')  {reference_other[i] = reference[i]; continue;}
        if (reference[i] >= 'a')  {reference_other[i] = reference[i] + ('A' -'a'); continue;}
        reference_other[i] = reference[i];
    }
    const char * reference_p1 = reference+1;
    const char * reference_other_p1 = reference_other+1;
    const char * in_string_initial = in_string;
    char * in_string_end = in_string + in_string_length;
    char * in_string_last = in_string_end - reference_length;
    * in_string_end = * reference;
    const char * reference_end = reference + reference_length; // Vaut 0
    compare_first:
    //while (((* in_string) != (* reference)) & ((* in_string) != (* reference_other))) { in_string++; }
    while(true) {
        if ((* in_string) == (* reference))  {  break; }
        if ((* in_string) == (* reference_other)) { break; }
        in_string++;    
    }
    first_identical:
    if (in_string > in_string_last) {
        * in_string_end = 0;
        return -1;
    }
    char * in_string_current = in_string;
    const char * reference_current = reference_p1;
    const char * reference_other_current = reference_other_p1;
    while(reference_current < reference_end) {
        in_string_current++;
        if ((*(reference_current++)) == (*(in_string_current))) {continue;}
        if ((*(reference_other_current++)) == (*(in_string_current))) {continue;}
        different:
            in_string++;
            goto compare_first;
    };
    * in_string_end = 0;
    if (reference_length == 0) { return -1;}
    return in_string - in_string_initial;
}

int in_string_insensitive_2(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) {
    const char * reference_p1 = reference+1;
    const char * in_string_initial = in_string;
    char * in_string_end = in_string + in_string_length;
    char * in_string_last = in_string_end - reference_length;
    * in_string_end = * reference;
    const char * reference_end = reference + reference_length; // Vaut 0
    compare:
    while (string_case::to_lower(* in_string) != string_case::to_lower(* reference)) { in_string++; }
    if (in_string > in_string_last) {
        * in_string_end = 0;
        return -1;
    }
    char * in_string_current = in_string;
    const char * reference_current = reference_p1;
    while(reference_current < reference_end) {
        if (string_case::to_lower(*(reference_current)) != string_case::to_lower(*(++in_string_current))) {
            in_string++;
            goto compare;
        }
        reference_current++;
    };
    * in_string_end = 0;
    if (reference_length == 0) { return -1;}
    return in_string - in_string_initial;
}

#define in_string_template(CONVERSION_FUNCTION) (const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) { \
    const char * reference_p1 = reference+1; \
    const char * in_string_initial = in_string; \
    char * in_string_end = in_string + in_string_length; \
    char * in_string_last = in_string_end - reference_length; \
    * in_string_end = * reference; \
    const char * reference_end = reference + reference_length; \
    compare: \
    while (CONVERSION_FUNCTION(* in_string) != CONVERSION_FUNCTION(* reference)) { in_string++; } \
    if (in_string > in_string_last) { \
        * in_string_end = 0; \
        return -1; \
    } \
    char * in_string_current = in_string; \
    const char * reference_current = reference_p1; \
    while(reference_current < reference_end) { \
        if (CONVERSION_FUNCTION(*(reference_current)) != CONVERSION_FUNCTION(*(++in_string_current))) { \
            in_string++; \
            goto compare; \
        } \
        reference_current++; \
    }; \
    * in_string_end = 0; \
    if (reference_length == 0) { return -1;} \
    return in_string - in_string_initial; \
}

#define in_string_no_separators_template(CONVERSION_FUNCTION) (const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) { \
    while(string_case::is_separator(*reference)) { \
        reference++; \
        reference_length--; \
    } \
    const char * reference_p1 = reference+1; \
    const char * in_string_initial = in_string; \
    char * in_string_end = in_string + in_string_length; \
    char * in_string_last = in_string_end - reference_length; \
    * in_string_end = * reference; \
    const char * reference_end = reference + reference_length; \
    compare: \
    while (CONVERSION_FUNCTION(* in_string) != CONVERSION_FUNCTION(* reference)) { in_string++; } \
    if (in_string > in_string_last) { \
        * in_string_end = 0; \
        return -1; \
    } \
    char * in_string_current = in_string; \
    const char * reference_current = reference_p1; \
    while(reference_current < reference_end) { \
        while(string_case::is_separator(*(reference_current))) { reference_current++; } \
        while(string_case::is_separator(*(++in_string_current))) { } \
        if (CONVERSION_FUNCTION(*(reference_current)) != CONVERSION_FUNCTION(*(in_string_current))) { \
            in_string++; \
            goto compare; \
        } \
        reference_current++; \
    }; \
    * in_string_end = 0; \
    if (reference_length == 0) { return -1;} \
    return in_string - in_string_initial; \
}

int in_string_sensitive in_string_template();
int in_string_insensitive in_string_template(string_case::to_lower);
int in_string_sensitive_no_separators in_string_no_separators_template();
int in_string_insensitive_no_separators in_string_no_separators_template(string_case::to_lower);

int in_string_insensitive_no_separators_2(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) { \
    bool remove_separators = true;
    char reference_no_separators[reference_length+1];
    const char * in_string_initial = in_string; 
    char * in_string_end = in_string + in_string_length;
    char * in_string_last; 
    const char * reference_current;
    const char * reference_p1;
    const char * reference_end; 
    char * in_string_current;
    if (remove_separators) {
        char * reference_no_separators_current = reference_no_separators;
        std::size_t reference_no_separators_length = 0;
        const char * reference_end = reference + reference_length;
        while(reference < reference_end) {
            if (string_case::is_separator(*(reference)) == 0) { 
                *(reference_no_separators_current++) = string_case::to_lower(*(reference)); 
                reference_no_separators_length++; 
            }
            reference++;
        }
        *reference_no_separators_current = '\0';
        reference = reference_no_separators;
        reference_length = reference_no_separators_length;
        reference_end = reference_no_separators_current;
    } else {
        reference_end = reference + reference_length; 
    }
    in_string_last = in_string_end - reference_length + 1; 
    reference_p1 = reference + 1;
    // Ici remplace le '\0' final par le 1er caractère à rechercher
    // Permet d'éviter une lecture hors zone
    * in_string_end = * reference; 
    compare: 
    while (string_case::to_lower(*(in_string)) != * reference) { in_string++; } 
    // Lorsque fini
    if (in_string > in_string_last) { 
        * in_string_end = 0; 
        return -1;
    }
    reference_current = reference;
    in_string_current = in_string; 
    while(*(++reference_current)) {
        // On passe les separateurs
        // On commence par le ++ car le 1er caractère est identique
        while(string_case::is_separator(*(++in_string_current))) { } 
        // On passe les separateurs de la référence
        if (*(reference_current) != string_case::to_lower(*(in_string_current))) { 
            in_string++;
            goto compare;
        }; 
    }
    * in_string_end = 0; 
    if (reference_length == 0) { return -1;} 
    return in_string - in_string_initial;
}


char reference_no_separators[255];
#define in_string_macro(REMOVE_SEPARATORS, HAS_CONVERSION, CONVERSION_FUNCTION)(const char * reference, char * in_string, std::size_t reference_length, std::size_t in_string_length) { \
    const char * in_string_initial = in_string; \
    char * in_string_end = in_string + in_string_length; \
    char * in_string_last; \
    const char * reference_current; \
    const char * reference_p1; \
    char * in_string_current; \
    if (REMOVE_SEPARATORS | HAS_CONVERSION) { \
        char * reference_no_separators_current = reference_no_separators; \
        const char * reference_end = reference + reference_length; \
        while(reference < reference_end) { \
            if (string_case::is_separator(*(reference)) == 0) {  \
                *(reference_no_separators_current++) = CONVERSION_FUNCTION(*(reference)); \
            } else { \
                reference_length--; \
            }\
            reference++; \
        } \
        *reference_no_separators_current = '\0'; \
        reference = reference_no_separators; \
    } \
    in_string_last = in_string_end - reference_length + 1;  \
    reference_p1 = reference + 1; \
    std::cout << "reference " << reference << "\n"; \
    std::cout << "reference_length " << reference_length << "\n"; \
    std::cout << "in_string " << (void *) in_string << " " << in_string << "\n"; \
    std::cout << "in_string_last " << (void *) in_string_last << " " << in_string_last<< "\n"; \
    * in_string_end = * reference;  \
    compare:  \
    while (CONVERSION_FUNCTION(*(in_string)) != * reference) { in_string++; }  \
    if (in_string > in_string_last) {  \
        * in_string_end = 0;  \
        return -1; \
    } \
    reference_current = reference; \
    in_string_current = in_string;  \
    while(*(++reference_current)) { \
        if (REMOVE_SEPARATORS) { \
            while(string_case::is_separator(*(++in_string_current))) { }  \
        } else {\
            ++in_string_current; \
        }\
        if (*(reference_current) != CONVERSION_FUNCTION(*(in_string_current))) {  \
            in_string++; \
            goto compare; \
        };  \
    } \
    * in_string_end = 0;  \
    if (reference_length == 0) { return -1;}  \
    return in_string - in_string_initial; \
}

int in_string_sensitive_macro_2  in_string_macro(0, 0, );
int in_string_insensitive_macro_2 in_string_macro(0, 1, string_case::to_lower);
int in_string_sensitive_no_separators_macro_2 in_string_macro(1, 0, );
int in_string_insensitive_no_separators_macro_2 in_string_macro(1, 0, string_case::to_lower);

#endif
