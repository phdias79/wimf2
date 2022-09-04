#include "dynamic_table.hpp"

template <typename V>
FixedTable<V>::FixedTable(std::size_t i_size):size(_size) {
    _size = i_size;
    _table = std::unique_ptr<V[]>(new V[size]);
    _pointer = _table.get();
}

template <typename V>
inline V FixedTable<V>::operator[](std::size_t index) {
    return _pointer[index];
}

template <typename V>
SegmentDynamicTable<V>::SegmentDynamicTable(std::size_t segment_size) {
    _allocated_size = segment_size;
    _size = 0;
    _table = std::unique_ptr<V[]>(new V[segment_size]);
    _next_table = nullptr;
    _pointer = _table.get();
    _previous = nullptr;
    _next = nullptr;
}

template <typename V>
DynamicTable<V>::DynamicTable(std::size_t segment_size):size(_size) {
    _size = 0;
    _segment_size = segment_size;
    _table = std::unique_ptr<SegmentDynamicTable<V>>(new SegmentDynamicTable<V>(segment_size));
    _pointer_first_segment = _table.get();
    _pointer_last_segment = _pointer_first_segment;
}

template <typename V>
V DynamicTable<V>::operator[](std::size_t index) {
    SegmentDynamicTable<V> * current_table = _pointer_first_segment;
    while(index >= _segment_size) {
        index -= _segment_size;
        current_table = current_table->_next;
    }
    return current_table->_pointer[index];
}

template <typename V>
void DynamicTable<V>::append(V value) {
    if (_pointer_last_segment->_size == _segment_size) {
        SegmentDynamicTable<V> * new_last = new SegmentDynamicTable<V>(_segment_size);
        new_last->_previous = _pointer_last_segment;
        _pointer_last_segment->_next = new_last;
        _pointer_last_segment->_next_table = std::unique_ptr<SegmentDynamicTable<V>>(new_last);
        _pointer_last_segment = new_last;
    }
    _pointer_last_segment->_pointer[_pointer_last_segment->_size] = value;
    _pointer_last_segment->_size++;
    _size++;
}

template <typename V>
FixedTable<V> DynamicTable<V>::to_FixedTable() {
    FixedTable<V> flatten_table(_size);
    V * current_pointer = flatten_table._pointer;
    std::size_t memory_size = _segment_size*sizeof(V);
    for(SegmentDynamicTable<V> * current_table = _pointer_first_segment; current_table != nullptr; current_table = current_table->_next) {
        memcpy((void *) current_pointer, (void *) current_table->_pointer, memory_size);
        current_pointer += _segment_size;
    }
    return flatten_table;
}

