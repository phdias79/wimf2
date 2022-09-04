#ifndef DYNAMIC_TABLE_H
#define DYNAMIC_TABLE_H

#include <cstring>
#include <memory>

template <typename V>
class DynamicTable;


template <typename V>
class FixedTable {
    protected:
        friend class DynamicTable<V>;
        std::size_t _size;
        std::unique_ptr<V[]> _table;
        V * _pointer;
    public:
        FixedTable(std::size_t size);
        inline V operator[](std::size_t index);
        const std::size_t &size;
};


template <typename V>
class SegmentDynamicTable {
    protected:
        friend class DynamicTable<V>;
        std::size_t _allocated_size; // Taille mémoire du segment
        std::size_t _size;           // Mémoire utilisée dans le segment
        std::unique_ptr<V[]> _table;
        V * _pointer;
        std::unique_ptr<SegmentDynamicTable<V>> _next_table;
        SegmentDynamicTable<V> * _previous;
        SegmentDynamicTable<V> * _next;
    public:
        SegmentDynamicTable(std::size_t segment_size);
};


template <typename V>
class DynamicTable {
    protected:
        friend class FixedTable<V>;
        std::size_t _segment_size;
        std::size_t _size;
        std::unique_ptr<SegmentDynamicTable<V>> _table;
        SegmentDynamicTable<V> * _pointer_first_segment;
        SegmentDynamicTable<V> * _pointer_last_segment;        
    public:
        DynamicTable(std::size_t segment_size);
        const std::size_t &size;
        V operator[](std::size_t index);
        void append(V value);
        FixedTable<V> to_FixedTable();
};

// On ajoute un include cpp pour permettre le bon fonctionnement des templates
#include "dynamic_table.cpp"

#endif