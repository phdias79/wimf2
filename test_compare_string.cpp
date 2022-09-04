#include "compare_string.hpp"
#include "string_case.hpp"

#include <iostream>
#include <chrono>

#define NTESTS 0

int test_error = 0;
int test_correct = 0;

void test_single(int in_str(const char*, char*, std::size_t, std::size_t), const char * function_name, const char * string_ref, const char * string_in, int expected_result, unsigned long number_tests = 1) {
    std::size_t string_ref_length = strlen(string_ref);
    std::size_t string_in_length = strlen(string_in);
    char in_string_non_const[string_in_length+1];
    memcpy(in_string_non_const, string_in, string_in_length+1);
    int comparaison_result;
    for(unsigned long i = 0; i < number_tests; i++) {
        comparaison_result = in_str(string_ref, in_string_non_const, string_ref_length, string_in_length);
    }
    if (expected_result != comparaison_result) {
        std::cout << "REF: '" << string_ref << "'\n";
        std::cout << " IN_STRING : '" << string_in << "'\n";
        std::cout << " " << function_name << " : " << comparaison_result << "\n";
        std::cout << " expected            : " << expected_result << std::endl;
        test_error++;
    }
    else {
        test_correct++;
    }
}

void test_insensitive(int in_str(const char*, char *, std::size_t, std::size_t), const char * function_name) {

    std::cout << "Fonction Insensitive : " << function_name << std::endl;

    test_single(in_str, function_name, "ABC", "", -1);
    test_single(in_str, function_name, "ABC", "A", -1);
    test_single(in_str, function_name, "ABC", "AB", -1);
    test_single(in_str, function_name, "ABC", "ABC", 0);
    test_single(in_str, function_name, "ABC", "ABCD", 0);
    test_single(in_str, function_name, "ABC", "ABCDE", 0);

    test_single(in_str, function_name, "ABC", "", -1);
    test_single(in_str, function_name, "ABC", "A", -1);
    test_single(in_str, function_name, "ABC", "Ab", -1);
    test_single(in_str, function_name, "ABC", "AbC", 0);
    test_single(in_str, function_name, "ABC", "AbCD", 0);
    test_single(in_str, function_name, "ABC", "AbCDE", 0);

    test_single(in_str, function_name, "A", "_", -1);
    test_single(in_str, function_name, "A", "__", -1);
    test_single(in_str, function_name, "ABC", "__", -1);
    test_single(in_str, function_name, "ABC", "__A", -1);
    test_single(in_str, function_name, "ABC", "__AB", -1);
    test_single(in_str, function_name, "ABC", "__AbC", 2);
    test_single(in_str, function_name, "ABC", "__AbCD", 2);
    test_single(in_str, function_name, "ABC", "__AbCDE", 2);


    test_single(in_str, function_name, "", "", -1);
    test_single(in_str, function_name, "", "A", -1);
    test_single(in_str, function_name, "", "AB", -1);
    test_single(in_str, function_name, "", "ABC", -1);
    test_single(in_str, function_name, "", "ABCD", -1);
    test_single(in_str, function_name, "", "ABCDE", -1);
    
    std::chrono::duration<double, std::milli> duration;
    auto t1 = std::chrono::high_resolution_clock::now();
    test_single(in_str, function_name, "ABCDEFdfhjhzeyyd", "  AB _B         ABCDEFdfhjhzeyyddszqs", 16, NTESTS);
    auto t2 = std::chrono::high_resolution_clock::now();
    duration = t2-t1;
    std::cout << " * Duration_F : " << duration.count() << std::endl;;
    t1 = std::chrono::high_resolution_clock::now();
    test_single(in_str, function_name, "ABCDEFdfhjhzeyyd", "  AB _B         AB_DEFdfhjhzeyyddszqs", -1, NTESTS);
    t2 = std::chrono::high_resolution_clock::now();
    duration = t2-t1;
    std::cout << " * Duration_NF : " << duration.count() << std::endl;;

}


void test_insensitive_no_separators(int in_str(const char*, char *, std::size_t, std::size_t), const char * function_name) {

    std::cout << "Fonction Insensitive : " << function_name << std::endl;

    test_single(in_str, function_name, "ABC", "", -1);
    test_single(in_str, function_name, "ABC", "A", -1);
    test_single(in_str, function_name, "ABC", "AB", -1);
    test_single(in_str, function_name, "ABC", "ABC", 0);
    test_single(in_str, function_name, "ABC", "ABCD", 0);
    test_single(in_str, function_name, "ABC", "ABCDE", 0);

    test_single(in_str, function_name, "_ABC", "", -1);
    test_single(in_str, function_name, "A_BC", "A", -1);
    test_single(in_str, function_name, "AB_C", "AB", -1);
    test_single(in_str, function_name, "A__B_C_", "ABC", 0);
    test_single(in_str, function_name, "A_B_C", "ABCD", 0);
    test_single(in_str, function_name, "__AB___C__", "ABCDE", 0);

    test_single(in_str, function_name, "ABC", "__", -1);
    test_single(in_str, function_name, "ABC", "_A_", -1);
    test_single(in_str, function_name, "ABC", "A__B", -1);
    test_single(in_str, function_name, "A_B_C_", "__ABC", 2);
    test_single(in_str, function_name, "__AB_C", "--_ABCD", 3);
    test_single(in_str, function_name, "-__A_B_C_", "AB-__CDE", 0);

    test_single(in_str, function_name, "ABC", "__", -1);
    test_single(in_str, function_name, "ABC", "_A_", -1);
    test_single(in_str, function_name, "ABC", "A__b", -1);
    test_single(in_str, function_name, "A_B_C_", "__aBC", 2);
    test_single(in_str, function_name, "__AB_C", "--_ABcD", 3);
    test_single(in_str, function_name, "-__A_B_C_", "Ab-__CDE", 0);


    test_single(in_str, function_name, "___--", "", -1);
    test_single(in_str, function_name, "", "A", -1);
    test_single(in_str, function_name, "", "AB", -1);
    test_single(in_str, function_name, "", "ABC", -1);
    test_single(in_str, function_name, "", "ABCD", -1);
    test_single(in_str, function_name, "", "ABCDE", -1);
    
    std::chrono::duration<double, std::milli> duration;
    auto t1 = std::chrono::high_resolution_clock::now();
    test_single(in_str, function_name, "ABCDEFdfhjhzeyyd", "  AB _B         ABCDEFdfhjhzeyyddszqs", 16, NTESTS);
    auto t2 = std::chrono::high_resolution_clock::now();
    duration = t2-t1;
    std::cout << " * Duration_F : " << duration.count() << std::endl;;
    t1 = std::chrono::high_resolution_clock::now();
    test_single(in_str, function_name, "ABCDEFdfhjhzeyyd", "  AB _B         AB_DEFdfhjhzeyyddszqs", -1, NTESTS);
    t2 = std::chrono::high_resolution_clock::now();
    duration = t2-t1;
    std::cout << " * Duration_NF : " << duration.count() << std::endl;;

}

void test_sensitive(int in_str(const char*, char *, std::size_t, std::size_t), const char * function_name) {

    std::cout << "Fonction Sensitive : " << function_name << std::endl;

    test_single(in_str, function_name, "ABC", "", -1);
    test_single(in_str, function_name, "ABC", "A", -1);
    test_single(in_str, function_name, "ABC", "AB", -1);
    test_single(in_str, function_name, "ABC", "ABC", 0);
    test_single(in_str, function_name, "ABC", "ABCD", 0);
    test_single(in_str, function_name, "ABC", "ABCDE", 0);

    test_single(in_str, function_name, "ABC", "", -1);
    test_single(in_str, function_name, "ABC", "A", -1);
    test_single(in_str, function_name, "ABC", "Ab", -1);
    test_single(in_str, function_name, "ABC", "AbC", -1);
    test_single(in_str, function_name, "ABC", "AbCD", -1);
    test_single(in_str, function_name, "ABC", "AbCDE", -1);

    test_single(in_str, function_name, "A", "_", -1);
    test_single(in_str, function_name, "A", "__", -1);
    test_single(in_str, function_name, "ABC", "__", -1);
    test_single(in_str, function_name, "ABC", "__A", -1);
    test_single(in_str, function_name, "ABC", "__AB", -1);
    test_single(in_str, function_name, "ABC", "__ABC", 2);
    test_single(in_str, function_name, "ABC", "__ABCD", 2);
    test_single(in_str, function_name, "ABC", "__ABCDE", 2);


    test_single(in_str, function_name, "", "", -1);
    test_single(in_str, function_name, "", "A", -1);
    test_single(in_str, function_name, "", "AB", -1);
    test_single(in_str, function_name, "", "ABC", -1);
    test_single(in_str, function_name, "", "ABCD", -1);
    test_single(in_str, function_name, "", "ABCDE", -1);
    
    std::chrono::duration<double, std::milli> duration;
    auto t1 = std::chrono::high_resolution_clock::now();
    test_single(in_str, function_name, "ABCDEFdfhjhzeyyd", "  AB _B         ABCDEFdfhjhzeyyddszqs", 16, NTESTS);
    auto t2 = std::chrono::high_resolution_clock::now();
    duration = t2-t1;
    std::cout << " * Duration_F : " << duration.count() << std::endl;;
    t1 = std::chrono::high_resolution_clock::now();
    test_single(in_str, function_name, "ABCDEFdfhjhzeyyd", "  AB _B         ABcDEFdfhjhzeyyddszqs", -1, NTESTS);
    t2 = std::chrono::high_resolution_clock::now();
    duration = t2-t1;
    std::cout << " * Duration_NF : " << duration.count() << std::endl;;

}


int main() {

    //test_single(in_string_sensitive_3, "in_string_sensitive_3", "ABC", "ABCD", 0);
    //test_single(in_string_sensitive_9, "in_string_sensitive_9", "ABC", "ABCD", 0);
    //return 0;
    /*test_sensitive(in_string_sensitive_1, "in_string_sensitive_1");
    test_sensitive(in_string_sensitive_2, "in_string_sensitive_2");
    test_sensitive(in_string_sensitive_3, "in_string_sensitive_3");
    test_sensitive(in_string_sensitive_4, "in_string_sensitive_4");
    test_sensitive(in_string_sensitive_5, "in_string_sensitive_5");
    test_sensitive(in_string_sensitive_6, "in_string_sensitive_6");
    test_sensitive(in_string_sensitive_7, "in_string_sensitive_7");
    test_sensitive(in_string_sensitive_8, "in_string_sensitive_8");
    test_sensitive(in_string_sensitive_9, "in_string_sensitive_9");
    test_sensitive(in_string_sensitive, "in_string_sensitive");
    test_sensitive(in_string_sensitive_no_separators, "in_string_sensitive_no_separators");
 
    test_insensitive(in_string_insensitive_1, "in_string_insensitive_1");
    test_insensitive(in_string_insensitive_2, "in_string_insensitive_2");
    test_insensitive(in_string_insensitive, "in_string_insensitive_macro");
    */
    test_insensitive(in_string_insensitive_macro_2, "in_string_insensitive_macro_2");
    test_insensitive_no_separators(in_string_insensitive_no_separators_macro_2, "in_string_insensitive_no_separators_macro_2");
    test_sensitive(in_string_sensitive_macro_2, "in_string_sensitive_macro_2");
//    test_sensitive_no_separators(in_string_sensitive_no_separators_macro_2, "in_string_sensitive_no_separators_macro_2");
    //test_insensitive_no_separators(in_string_insensitive_no_separators_2, "in_string_insensitive_no_separators_2");
 //   test_insensitive_no_separators(in_string_insensitive_no_separators_macro_2, "in_string_insensitive_no_separators_macro_2");
 
//int in_string_sensitive_macro_2  in_string_macro(, false);
//int in_string_insensitive_macro_2 in_string_macro(string_case::to_lower, false);
//int in_string_sensitive_no_separators_macro_2 in_string_macro(, true);

    std::cout << "\nBILAN\n";
    std::cout << " - ok  : " << test_correct << "\n";
    std::cout << " - nok : " << test_error << "\n";

}