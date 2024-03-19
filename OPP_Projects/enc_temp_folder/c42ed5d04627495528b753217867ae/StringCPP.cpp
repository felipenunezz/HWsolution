#include "StringH.h"

CString::CString() 
{
    size = 0;
    capacity = STEP_CAPACITY;
    data = new char[capacity];
    data[0] = '\0';
}
CString::CString(const CString& str) 
{
    size = str.size;
    capacity = str.capacity;
    data = new char[capacity];
    for (size_t i = 0; i < size; i++) { data[i] = str.data[i]; }
    data[size] = '\0';
}
CString::CString(const char* c_str)
{
    size = 0;
    while (c_str[size] != '\0') { size++; }
    capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    data = new char[capacity];
    for (size_t i = 0; i < size; i++) { data[i] = c_str[i]; }
    data[size] = '\0';
}
CString::CString(const char* c_str, size_t n)
{
    size = 0;
    while (c_str[size] != '\0') { size++; }
    if (size < n) throw std::invalid_argument("Incorrect Input");
    size = n;
    capacity = (n / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    data = new char[capacity];
    for (size_t i = 0; i < n; i++) { data[i] = c_str[i]; }
    data[n] = '\0';

}
CString::CString(size_t n, char c) 
{
    size = n; 
    capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    data = new char[capacity];
    for (size_t i = 0; i < size; i++) { data[i] = c; }
    data[size] = '\0';
}
CString::CString(const CString& str, size_t pos, size_t len) 
{
    if (len + pos > str.size) { throw std::invalid_argument("unmatching size for CString imput"); }
    size = len;
    capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    data = new char[capacity];
    for (size_t i = 0; i < size; i++) { data[i] = str.data[pos + i]; }
    data[size] = '\0';
}

CString::~CString() 
{
    delete[] data;
    data = nullptr;
}

void CString::print() const noexcept  { std::cout << data << std::endl; }

bool CString::empty() const noexcept { return size == 0; }
bool CString::full() const noexcept { return size == capacity; }
bool CString::overflow() const noexcept { return size > capacity; }

size_t CString::_size() const noexcept { return this->size; }
size_t CString::_capacity() const noexcept { return this->capacity; }
const char* CString::_data() const { return this->data; }

void CString::swap(CString& str) 
{
    CString& temp(str);
    
    str.size = size;
    str.capacity = capacity;
    str.data = data;
     
    size = temp._size();
    capacity = temp._capacity();
    for (size_t i = 0; i < size; i++) { data[i] = temp._data()[i]; }
}
//size_t CString::copy (char* buf, size_t len, size_t pos) const 
//{
//    if (len + pos > size) { throw std::invalid_argument("unmatching size for CString imput");}
//
//
//}
CString CString::substr(size_t pos, size_t len) const {
    if (len + pos > size) { throw std::invalid_argument("unmatching size for CString imput");}

    CString SubTemp;
    SubTemp.size = size;
    SubTemp.capacity = (SubTemp.size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;

    for (size_t i = 0; i < size; i++) { if (i >= pos && i <= pos + len) { SubTemp.data[i] = data[i]; } }
    SubTemp.size = len;
    SubTemp.capacity = (SubTemp.size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    SubTemp.data[SubTemp.size] = '\0';

    return SubTemp;
}

//CString& CString::assign(const CString& str) {}
//CString& CString::assign(const CString& str, size_t pos, size_t len) {}
//CString& CString::assign(const char* s) {}
//CString& CString::assign(const char* s, size_t n) {}
//CString& CString::assign(size_t n, char c) {}

int CString::compare(const CString& str) const noexcept 
{
    for (size_t i = 0; i < algorithms::min(size, str.size); i++) 
    {
        if (this->data[i] < str.data[i]) return 1;
        else if (this->data[i] > str.data[i]) return -1;
    }
    if (this->size > str.size) return 1;
    else if (this->size < str.size) return -1;
    else return 0;
}
int CString::compare(size_t pos, size_t len, const CString& str) const 
{
    for (size_t i = 0; i < algorithms::min(len, str.size); i++)
    {
        if (this->data[pos + i] < str.data[i]) return 1;
        else if (this->data[ pos + i] > str.data[i]) return -1;
    }
    if (len > str.size) return 1;
    else if (len < str.size) return -1;
    else return 0;
}
int CString::compare(size_t pos, size_t len, const CString& str, size_t subpos, size_t sublen) const 
{
    for (size_t i = 0; i < algorithms::min(len, sublen); i++)
    {
        if (this->data[pos + i] < str.data[subpos + i]) return 1;
        else if (this->data[pos + i] > str.data[subpos + i]) return -1;
    }
    if (len > sublen) return 1;
    else if (len < sublen) return -1;
    else return 0;
}
int CString::compare(const char* s) const 
{
    for (size_t i = 0; i < algorithms::min(size, sizeof(s)); i++)
    {
        if (this->data[i] < s[i]) return 1;
        else if (this->data[i] > s[i]) return -1;
    }
    if (this->size > sizeof(s)) return 1;
    else if (this->size < sizeof(s)) return -1;
    else return 0;
}
int CString::compare(size_t pos, size_t len, const char* s) const 
{
    for (size_t i = 0; i < algorithms::min(len, sizeof(s)); i++)
    {
        if (this->data[pos + i] < s[i]) return 1;
        else if (this->data[pos + i] > s[i]) return -1;
    }
    if (this->size > sizeof(s)) return 1;
    else if (this->size < sizeof(s)) return -1;
    else return 0;
}
int CString::compare(size_t pos, size_t len, const char* s, size_t n) const 
{
    for (size_t i = 0; i < algorithms::min(len, n); i++)
    {
        if (this->data[pos + i] < s[i]) return 1;
        else if (this->data[pos + i] > s[i]) return -1;
    }
    if (this->size > n) return 1;
    else if (this->size < n) return -1;
    else return 0;
}

void CString::clear() noexcept 
{
    delete[] data;
    size = 0;
    capacity = STEP_CAPACITY;
    data = new char[capacity];
    data[0] = '\0';
}
void CString::resize(size_t n) 
{
    size_t tempS = size; 
    size = n;
    if (n > capacity) capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    if (size > tempS) { for (size_t i = tempS; i < size; i++) { data[i] = ' '; } }
    data[size] = '\0';
}
//void CString::reserve(size_t n) { /*idk what this does*/ } // change capacity +- with saved data;!!!

//void CString::push_back(char c) 
//{
//    if (this->full()) { this->reserve(capacity); }
//
//    data[size] = c;
//    data[++size] = '\0';
//}
void CString::pop_back() 
{
    if (this->empty()) 
    {
        throw std::logic_error("Error in function \
                  \"void pop_back()\": source CString is empty");
    }
    data[--size] = '\0';
}

CString& CString::erase(size_t pos, size_t len) 
{
    if (len + pos > size) { throw std::invalid_argument("unmatching size for CString imput"); }

    CString SubTemp;
    SubTemp.size = size;
    SubTemp.capacity = (SubTemp.size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    size_t i = 0;

    for (i; i < size; i++) { if (!(i >= pos && i <= pos + len)) { SubTemp.data[i] = data[i]; } }
    SubTemp.size = size - len;
    SubTemp.capacity = (SubTemp.size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    SubTemp.data[SubTemp.size] = '\0';
    this->swap(SubTemp);
    return *this;
}

CString& CString::append(const CString& str) 
{
    size_t temp = size;
    size += str.size;

    for (size_t i = 0; i < str.size; i++) { data[temp + i] = str.data[i]; }
    data[size] = '\0';
    if (this->full() || this->overflow()) capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    return *this;
}
CString& CString::append(const CString& str, size_t subpos, size_t sublen) 
{
    CString str_2 = str.substr(subpos, sublen);
    
    size_t temp = size;
    size += str_2.size;

    for (size_t i = 0; i < str_2.size; i++) { data[temp + i] = str_2.data[i]; }
    data[size] = '\0';
    if (this->full() || this->overflow()) capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    return *this;
}
CString& CString::append(const char* s) 
{
    size_t temp = size;
    size += sizeof(s);

    for (size_t i = 0; i < sizeof(s); i++) { data[temp + i] = s[i]; }
    data[size] = '\0';
    if (this->full() || this->overflow()) capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    return *this;
}
CString& CString::append(const char* s, size_t n) 
{
    size_t temp = size;
    size += n;

    for (size_t i = 0; i < n; i++) { data[temp + i] = s[i]; }
    data[size] = '\0';
    if (this->full() || this->overflow()) capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    return *this;
}
CString& CString::append(size_t n, char c) {
    size_t temp = size;
    size += n;

    for (size_t i = 0; i < n; i++) { data[temp + i] = c; }
    data[size] = '\0';
    if (this->full() || this->overflow()) capacity = (size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    return *this;
}

CString& CString::insert(size_t pos, const CString& str) 
{
    if (pos > size) { throw std::invalid_argument("unmatching size for CString imput");}
    
    CString begin(*this, 0, pos);
    CString end(*this, pos, size - pos);
    begin.append(str);
    begin.append(end);
    this->swap(begin);
    return *this;
}
CString& CString::insert(size_t pos, const CString& str, size_t subpos, size_t sublen) 
{
    if (pos > size) { throw std::invalid_argument("unmatching size for CString imput"); }
    if (subpos + sublen > str.size) { throw std::invalid_argument("unmatching size for CString imput"); }

    CString begin(*this, 0, pos);
    CString end(*this, pos, size - pos);
    CString Temp(str, subpos, sublen);

    begin.append(Temp);
    begin.append(end);
    this->swap(begin);
    return *this;
}
CString& CString::insert(size_t pos, const char* s) 
{
    if (pos > size) { throw std::invalid_argument("unmatching size for CString imput"); }

    CString begin(*this, 0, pos);
    CString end(*this, pos, size - pos);
    CString Temp(s);

    begin.append(Temp);
    begin.append(end);
    this->swap(begin);
    return *this;

}
CString& CString::insert(size_t pos, const char* s, size_t n) 
{
    if (pos > size) { throw std::invalid_argument("unmatching size for CString imput"); }

    CString begin(*this, 0, pos);
    CString end(*this, pos, size - pos);
    CString Temp(s, n);

    begin.append(Temp);
    begin.append(end);
    this->swap(begin);
    return *this;
}
CString& CString::insert(size_t pos, size_t n, char c) 
{
    if (pos > size) { throw std::invalid_argument("unmatching size for CString imput"); }

    CString begin(*this, 0, pos);
    CString end(*this, pos, size - pos);
    CString Temp(n, c);

    begin.append(Temp);
    begin.append(end);
    this->swap(begin);
    return *this;
}

CString& CString::replace(size_t pos, size_t len, const CString& str) 
{
    if (len + pos > this->size) { throw std::invalid_argument("unmatching size for CString imput"); }
    for (size_t i = 0; i < len; i++) { this->data[pos + i] = str.data[i]; }
    return *this;
}
CString& CString::replace(size_t pos, size_t len, const CString& str, size_t subpos, size_t sublen) {
    
    if (len + pos > this->size || subpos + sublen > str.size) { throw std::invalid_argument("unmatching size for CString imput"); }
    CString Temp = str.substr(subpos, sublen);
    for (size_t i = 0; i < len; i++) { this->data[pos + i] = Temp.data[i]; }
    return *this;
}
CString& CString::replace(size_t pos, size_t len, const char* s, size_t n) {
    if (len + pos > this->size) { throw std::invalid_argument("unmatching size for CString imput"); }
    for (size_t i = 0; i < algorithms::min(this->size, n); i++) { this->data[pos + i] = s[i]; }
    return *this;
}
CString& CString::replace(size_t pos, size_t len, size_t n, char c) {
    if (len + pos > this->size) { throw std::invalid_argument("unmatching size for CString imput"); }
    for (size_t i = 0; i < len; i++) { this->data[pos + i] = c; }
    return *this;
}

size_t CString::find(const CString& str, size_t pos) const 
{ 
    if (str.empty()) { throw std::invalid_argument("The CString data is empty"); }
    for (size_t i = 0, j = 0; i < size && j < str.size;) {
        if (data[i] == str.data[j])
        {
            if (j == 0) pos = i;
            j++; i++;
            
        }
        else { j = 0; i++; }
    }
    return pos;
    
}
//size_t CString::find(const char* s, size_t pos) const 
//{
//
//}
//size_t CString::find(const char* s, size_t pos, size_t n) const 
//{
//
//}
//size_t CString::find(char c, size_t pos) const 
//{
//    for (size_t i = 0; i < size; i++) {
//        if (data[i] == c) pos = i;
//    }
//    return pos;
//}

size_t CString::find_first_of(const CString& str, size_t pos) const {
    for (size_t i = pos; i < size; i++) {
        for (size_t j = 0; j < str.size; j++) {
            if (data[i] == str.data[j]) {
                return i;
            }
        }
    }
    return -1;
}