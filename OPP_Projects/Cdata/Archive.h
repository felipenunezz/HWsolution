#pragma once
#define STEP_CAPACITY 15
#include <stdexcept>
#include <iostream>

enum State { empty, busy, deleted };

namespace algorithms {
    template<typename T>
    inline void swap(T& val_1, T& val_2) noexcept {
        T tmp = val_1;
        val_1 = val_2;
        val_2 = tmp;
    }
}

template <typename T>
class TArchive {
    T* data;                  
    State* states;            
    size_t capacity;         
    size_t size;              
    size_t deleted;           
public:
    TArchive();
    TArchive(const TArchive& archive);
    TArchive(const T* arr, size_t n);
    TArchive(size_t n, T value);
    TArchive(const TArchive& archive, size_t pos, size_t n);

    ~TArchive();

    void print() const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t _size();
    size_t _capacity();
    const T* _data();

    void swap(TArchive& archive);

    TArchive& assign(const TArchive& archive);

    void clear();
    void resize(size_t n, T value);
    void reserve(size_t n);

    void push_back(T value);
    void pop_back();
    
	void push_front(T value);
    void pop_front();

    TArchive& insert(const T* arr, size_t n, size_t pos);
    TArchive& insert(const TArchive& archive, size_t pos);
    TArchive& insert(T value, size_t pos);

    TArchive& replace(size_t pos, T new_value);

    TArchive& erase(size_t pos, size_t n);
    TArchive& remove_all(T value);
    TArchive& remove_first(T value);
    TArchive& remove_last(T value);
    TArchive& remove_by_index(size_t pos);

    size_t* find_all(T value);
    size_t* find_first(T value);
    size_t* find_last(T value);
private:
    size_t count_value(T value);
};

//
template <typename T>
TArchive<T>::TArchive()
{
	size = 0;
	capacity = STEP_CAPACITY;
	deleted = 0;
	data = new T[capacity];
	states = new State[capacity];
	for (size_t i = 0; i < STEP_CAPACITY; i++) { states[i] = State::empty; }
}
template <typename T>
TArchive<T>::TArchive(const TArchive& archive)
{
	size = archive.size;
	capacity = archive.capacity;
	deleted = archive.deleted;

	states = new State[capacity];
	data = new T[capacity];

	for (size_t i = 0; i < size; i++)
	{
		states[i] = archive.states[i];
		data[i] = archive.data[i];
	}
}
template <typename T>
TArchive<T>::TArchive(const T* arr, size_t n) {
	size = 0;
	while (size < n) size++;
	capacity = (size * STEP_CAPACITY) / STEP_CAPACITY + STEP_CAPACITY;
	deleted = 0;

	data = new T[capacity];
	states = new State[capacity];

	for (size_t i = 0; i < size; i++)
	{
		data[i] = arr[i];
		states[i] = State::busy;
	}
}
template <typename T>
TArchive<T>::TArchive(size_t n, T value)
{
	size = n;
	capacity = (size * STEP_CAPACITY) / STEP_CAPACITY + STEP_CAPACITY;
	deleted = 0;

	data = new T[capacity];
	states = new State[capacity];

	for (size_t i = 0; i < size; i++)
	{
		data[i] = value;
		states[i] = State::busy;
	}
}
template <typename T>
TArchive<T>::TArchive(const TArchive& archive, size_t pos, size_t n)
{
	size = n;
	capacity = (size * STEP_CAPACITY) / STEP_CAPACITY + STEP_CAPACITY;

	data = new T[capacity];
	states = new State[capacity];

	for (size_t i = 0; i < size; i++)
	{
		data[i] = archive.data[pos + i];
		states[i] = archive.states[pos + i];

		if (states[i] == State::deleted) deleted++;
	}

}

template <typename T>
TArchive<T>::~TArchive()
{
	delete[] data;
	data = nullptr;
}

template <typename T>
void TArchive<T>::print() const noexcept
{
	for (size_t i = 0; i < size; i++) {
		if (states[i] != State::deleted) {
			std::cout << data[i] << ", ";
		}
	}
}

template <typename T>
inline bool TArchive<T>::empty() const noexcept { return size == 0; }
template <typename T>
inline bool TArchive<T>::full() const noexcept { return size == capacity; }

template <typename T>
size_t TArchive<T>::_size() { return size; }
template <typename T>
size_t TArchive<T>::_capacity() { return capacity; }
template <typename T>
const T* TArchive<T>::_data() { return data; }

template <typename T>
void TArchive<T>::swap(TArchive& archive)
{
	TArchive temp(this);
	if (temp.empty() || this->empty()) { throw std::logic_error("Error in function \"void swap(TArchive& archive)\": One of the archives was empty."); }

	size = archive.size;
	capacity = archive.capacity;
	deleted = archive.deleted;

	delete[] data;
	data = new T[capacity];
	delete[] states;
	states = new State[capacity];

	for (size_t i = 0; size; i++)
	{
		states[i] = archive.states[i];
		data[i] = archive.data[i];
	}

	archive.size = temp.size;
	archive.capacity = temp.capacity;
	archive.deleted = temp.deleted;

	delete[] archive.data;
	archive.data = new T[capacity];
	delete[] archive.states;
	archive.states = new State[capacity];

	for (size_t i = 0; archive.size; i++)
	{
		archive.states[i] = temp.states[i];
		archive.data[i] = temp.data[i];
	}
}

template <typename T>
TArchive<T>& TArchive<T>::assign(const TArchive& archive)
{
	size = archive.size;
	capacity = archive.capacity;
	deleted = archive.deleted;

	data = new T[capacity];
	states = new State[capacity];

	for (size_t i = 0; i < size; i++)
	{
		data = archive.data[i];
		states = archive.states[i];
	}

	return *this;
}

template <typename T>
void  TArchive<T>::clear()
{
    delete[] data;
	delete[] states;

	size = 0;
	capacity = STEP_CAPACITY;
	deleted = 0;
	data = new T[capacity];
	states = new State[capacity];
	for (size_t i = 0; i < STEP_CAPACITY; i++) { states[i] = State::empty; }
}
template <typename T>
void TArchive<T>::resize(size_t n, T value)
{
	size_t tempS = size;
	size = n;
	if (n > capacity) capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
	if (size > tempS) for (size_t i = tempS; i < size; i++)  data[i] = value;
}
template <typename T>
void TArchive<T>::reserve(size_t n)
{
	if (n > size)  capacity = (n / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
	else throw std::invalid_argument("The sated value is too small.");
}

template <typename T>
void TArchive<T>::push_back(T value) 
{
	if (this->full()) this->reserve(capacity);

	data[size] = value;
	states[size] = State::busy;
	data[++size] = '\0';
}
template <typename T>
void TArchive<T>::pop_back() 
{
	if (this->empty()) { throw std::logic_error("Error in function \"void pop_back()\": source CString is empty"); }
	data[--size] = '\0';
}

template <typename T>
void TArchive<T>::push_front(T value) 
{
	TArchive<T> archive(*this);
	if (this->full()) this->reserve(capacity);
	size++;
	if (states[0] != State::empty) {
		for (size_t i = 1; i <= size; i++) { this->data[i] = archive.data[i - 1]; }
	}
	states[0] = busy;
	data[0] = value;

	states[size - 1] = busy;
	data[size] = '\0';
}
template <typename T>
void TArchive<T>::pop_front() 
{
	TArchive<T> archive(*this);
	if (this->empty()) { throw std::logic_error("Error in function \"void pop_front()\": source CString is empty"); }
    for (size_t i = 0; i < size; i++) { this->data[i] = archive.data[i + 1]; }
	data[size--] = '\0';	
}

template <typename T>
TArchive<T>& TArchive<T>::insert(const T* arr, size_t n, size_t pos)
{
	if (size < pos) { throw std::logic_error("Error in function \"TArchive<T>& insert(T value, size_t pos)\": wrong position value."); }

	this->reserve(size + n);
	size += n;


	for (size_t i = size; i > pos; i--)
	{
		data[i] = data[i - n];
		states[i] = states[i - n];
	}

	for (size_t i = 0; i < n; i++)
	{
		data[pos + i] = arr[i];
		states[pos + i] = State::busy;
	}

	return *this;
}
template <typename T>
TArchive<T>& TArchive<T>::insert(T value, size_t pos)
{
	if (size < pos) { throw std::logic_error("Error in function \"TArchive<T>& insert(T value, size_t pos)\": wrong position value."); }
	if (this->full()) { this->reserve(1); }

	for (size_t i = size; i > pos; i--) { data[i] = data[i - 1]; }
	data[pos] = value;
	states[pos] = State::busy;
	size++;
	return *this;
}
template <typename T>
TArchive<T>& TArchive<T>::insert(const TArchive<T>& archive, size_t pos) {
	if (size < pos) { throw std::logic_error("Error in function \"TArchive<T>& insert(T value, size_t pos)\": wrong position value."); }
	if (archive.empty()) { throw std::logic_error("Error in function \"TArchive<T>& insert(T value, size_t pos)\": Archive was empty."); }
	if (this->full()) { this->reserve(size + archive.size); }
	size += archive.size; 

	for (size_t i = size; i > pos; i--) { data[i] = data[i - archive.size]; states[i] = states[i - archive.size];}
	for (size_t i = 0; i < archive.size; i++) { data[pos + i] = archive.data[i]; states[pos + i] = State::busy; }
	
	return *this;
}

template <typename T>
TArchive<T>& TArchive<T>::replace(size_t pos, T new_value)
{
	if (size < pos) { throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::replace(size_t pos, T new_value)\": wrong position value."); }
	data[pos] = new_value;
}

template <typename T>
TArchive<T>& TArchive<T>::erase(size_t pos, size_t n)
{
	if (this->empty()) throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::erase(size_t pos, size_t n)\": Archive is empty.");
	if (size < pos + n) { throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::erase(size_t pos, size_t n)\": wrong position value."); }

	for (size_t i = 0; i < n; i++)
	{
		data[pos + i] = NULL;
		states[pos + i] = State::deleted;
		deleted++;
	}

	return *this;
}
template <typename T>
TArchive<T>& TArchive<T>::remove_all(T value)
{
	if (this->empty()) throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::remove_all(T value)\": Archive is empty.");

	size_t* pos = find_all(value);
	if (pos == nullptr) throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::remove_all(T value)\": No matching value found.");

	for (size_t i = 1; i <= pos[0]; i++)
	{
		if (pos[i] == size) { states[size] = State::empty; }
		else { states[pos[i]] = State::deleted; }
		deleted++;
	}

	return *this;
}
template <typename T>
TArchive<T>& TArchive<T>::remove_first(T value)
{
	if (this->empty()) throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::remove_first(T value)\": Archive is empty.");

	size_t* pos = this->find_first(value);
	if (pos == nullptr) throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::remove_first(T value)\": position is not found.");

	if (pos[1] == size) states[size] = State::empty;
	else states[pos[1]] = State::deleted;
	deleted++;

	return *this;
}
template <typename T>
TArchive<T>& TArchive<T>::remove_last(T value)
{
	if (this->empty()) throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::remove_last(T value)\": Archive is empty.");

	size_t* pos = this->find_last(value);
	if (pos == nullptr) throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::remove_last(T value)\": position is not found.");

	if (pos[1] == size) states[size] = State::empty;
	else states[pos[1]] = State::deleted;
	deleted++;

	return *this;
}
template <typename T>
TArchive<T>& TArchive<T>::remove_by_index(size_t pos)
{
	if (this->empty()) throw std::logic_error("Error in function \"TArchive<T>& TArchive<T>::remove_by_index(size_t pos)\": Archive is empty.");

	if (pos == size) states[pos] = State::empty;
	else states[pos] = State::deleted;
	deleted++;

	return *this;
}

template <typename T>
size_t* TArchive<T>::find_all(T value)
{
	size_t count = this->count_value(value);
	if (count == 0) { return nullptr; }
	size_t* found_positions = new size_t[count + 1];
	found_positions[0] = count;

	for (size_t i = 0, j = 1; j < count + 1; i++)
	{
		if (data[i] == value) { found_positions[j] = i; j++; }
	}

	return found_positions;
}
template <typename T>
size_t* TArchive<T>::find_first(T value)
{
	size_t* found_positions = new size_t[2];
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == value) { found_positions[1] = i; found_positions[0]++; return found_positions; }
	}
	return found_positions;
}
template <typename T>
size_t* TArchive<T>::find_last(T value)
{
	size_t* found_positions = new size_t[2];
	for (size_t i = size; i > 0; i--)
	{
		if (data[i] == value) { found_positions[1] = i; found_positions[0] ++; return found_positions; }
	}
	return found_positions;
}

template <typename T>
size_t TArchive<T>::count_value(T value)
{
	size_t count = 0;
	for (size_t i = 0; i <= this->size; i++)
	{
		if (this->data[i] == value) count++;
	}
	return count;
}