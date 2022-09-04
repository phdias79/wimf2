#ifndef CATALOG_H
#define CATALOG_H

#include <cstdlib>
#include <cstring>
//#include <stdint.h>
#include <memory>
#include "dynamic_table.hpp"
#include "extensions.hpp"


// Taille du buffer
#define BANK_DEFAULT_SIZE 64000
#define BANK_DEFAULT_DYNAMIC_EXTEND 1000

#define file_size_t uint32_t
#define file_date_t uint32_t


const char BankFullException_message[] = "L'espace mémoire est plein";
class BankFullException : public std::exception {
    const char * what() {
         return BankFullException_message;
    }
};

class DynamicBank {
    protected:
        std::shared_ptr<char []> _buffer;
        std::size_t _buffer_size;
        std::size_t _extension_size;
        std::size_t _size;
        char * _buffer_current_pointer;  // Pointeur pour l'écriture d'un nouveau fichier
        char * _buffer_end_pointer;      // Pointeur pour la fin du buffer (1er octet hors mémoire)
    public:
        std::unique_ptr<DynamicTable<extension_code_t>> file_extension_code;
        std::unique_ptr<DynamicTable<file_size_t>> file_size;
        std::unique_ptr<DynamicTable<file_date_t>> file_date;
        std::unique_ptr<DynamicTable<char *>> file_name;
        const std::size_t& size;
        DynamicBank(std::size_t buffer_size = BANK_DEFAULT_SIZE, std::size_t extension_size = BANK_DEFAULT_DYNAMIC_EXTEND);
        void add(const char * filename, file_size_t filesize, file_date_t filedate);
        inline void add_filename(const char * filename);
};

DynamicBank::DynamicBank(std::size_t buffer_size,  std::size_t extension_size):size(_size) {
    _buffer_size = buffer_size;
    _buffer = std::shared_ptr<char []>(new char[buffer_size]);
    _extension_size = extension_size;
    _size = 0;
    _buffer_current_pointer = _buffer.get();
    _buffer_end_pointer = _buffer_current_pointer + _buffer_size; // Cette position = hors mémoire 
    file_extension_code = std::unique_ptr<DynamicTable<extension_code_t>> (new DynamicTable<extension_code_t>(extension_size));
    file_size = std::unique_ptr<DynamicTable<file_size_t>> (new DynamicTable<file_size_t>(extension_size));
    file_date = std::unique_ptr<DynamicTable<file_date_t>> (new DynamicTable<file_date_t>(extension_size));
    file_name = std::unique_ptr<DynamicTable<char *>> (new DynamicTable<char *>(extension_size));
}

void DynamicBank::add(const char * filename, file_size_t filesize, file_date_t filedate) {
    // Copie du nom de fichier
    std::size_t filename_length = strlen(filename);
    std::size_t filename_length_with_zero = filename_length+1;
    char * _next_buffer_current_pointer = _buffer_current_pointer + filename_length_with_zero;
    if (_next_buffer_current_pointer > _buffer_end_pointer) {
        throw BankFullException();
    }
    file_name->append(_buffer_current_pointer);
    file_extension_code->append(extension_code_with_length(filename, filename_length));
    memcpy(_buffer_current_pointer, filename, filename_length_with_zero);
    _buffer_current_pointer = _next_buffer_current_pointer;
    // Copie autres infos
    file_size->append(filesize);
    file_date->append(filedate);
    // Update de la taille
    _size++;
}

inline void DynamicBank::add_filename(const char * filename) {
    add(filename, 0, 0);
};

#endif