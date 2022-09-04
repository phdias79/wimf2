#include "string_case.hpp"

#include <iostream>
#include <chrono>
#include <memory.h>

int test_error = 0;
int test_correct = 0;

typedef char * convert_t(const char*, std::size_t, char*);

void test_sensitive_single(convert_t convert, const char * function_name, const char * string_in, const char * string_expected, unsigned long number_tests = 1) {
    std::size_t string_in_length = strlen(string_in);
    char * string_out = new char[string_in_length+1];
    for(unsigned long i = 0; i < number_tests; i++) {
        convert(string_in, string_in_length, string_out);
    }
    if (memcmp(string_out, string_expected, string_in_length+1)) {
        std::cout << function_name << "\n";
        std::cout << " in       : '" << string_in << "'\n";
        std::cout << " out      : '" << string_out << "'\n";
        std::cout << " expected : '" << string_expected << "'" << std::endl;
        test_error++;
    }
    else {
        test_correct++;
    }
    delete[](string_out);
}



void test() {

    //string_case::initialize();

    convert_t * function1 = &string_case::to_upper;
    char function_name1[] = "string_case::to_upper";

    test_sensitive_single(*function1, function_name1, "", "");
    test_sensitive_single(*function1, function_name1, "abcd", "ABCD");
    test_sensitive_single(*function1, function_name1, "ABCD", "ABCD");
    test_sensitive_single(*function1, function_name1, "aBcD", "ABCD");
    test_sensitive_single(*function1, function_name1, "-_ #=128", "-_ #=128");

    convert_t * function2 = &string_case::to_lower;
    char function_name2[] = "string_case::to_lower";

    test_sensitive_single(*function2, function_name2, "", "");
    test_sensitive_single(*function2, function_name2, "abcd", "abcd");
    test_sensitive_single(*function2, function_name2, "ABCD", "abcd");
    test_sensitive_single(*function2, function_name2, "aBcD", "abcd");
    test_sensitive_single(*function2, function_name2, "-_ #=128", "-_ #=128");

    convert_t * function3 = &string_case::switch_case;
    char function_name3[] = "string_case::switch_case";

    test_sensitive_single(*function3, function_name3, "", "");
    test_sensitive_single(*function3, function_name3, "abcd", "ABCD");
    test_sensitive_single(*function3, function_name3, "ABCD", "abcd");
    test_sensitive_single(*function3, function_name3, "aBcD", "AbCd");
    test_sensitive_single(*function3, function_name3, "-_ #=128", "-_ #=128");

    std::chrono::duration<double, std::milli> duration;
    std::cout << "Chrono : " << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();


    t1 = std::chrono::high_resolution_clock::now();
    test_sensitive_single(*function1, function_name1, "abcd", "ABCD", 100000000);
    t2 = std::chrono::high_resolution_clock::now();
    duration = t2-t1;
    std::cout << "Duration_upper : " << duration.count() << "\n" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    test_sensitive_single(*function2, function_name2, "ABCD", "abcd", 100000000);
    t2 = std::chrono::high_resolution_clock::now();
    duration = t2-t1;
    std::cout << "Duration_lower : " << duration.count() << "\n" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    test_sensitive_single(*function3, function_name3, "aBcD", "AbCd", 100000000);
    t2 = std::chrono::high_resolution_clock::now();
    duration = t2-t1;
    std::cout << "Duration_switch : " << duration.count() << "\n" << std::endl;

}


int main() {

    test();
    std::cout << "\nBILAN\n";
    std::cout << " - ok  : " << test_correct << "\n";
    std::cout << " - nok : " << test_error << "\n";

}