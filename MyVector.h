#pragma once

#include <initializer_list>
#include <cstddef>


template<typename T>
class MyVector {
    T* data;            // 동적 배열을 가리키는 포인터
    size_t cap;         // 현재 할당된 배열 크기
    size_t length;      // 실제 저장된 요소 개수    
public:

    MyVector(std::initializer_list<T> init) {
        length = init.size();
        cap = length;
        data = new T[cap];
        size_t i = 0;
        for (const auto& val : init) {
            data[i++] = val;
        }
    }

    MyVector(): data(nullptr), length(0), cap(0) {}
    ~MyVector() { delete[] data; }

    void push_back(const T& val){
        if(length>=cap){
            size_t newCap=(cap==0)?1:cap*2;
            T* newData = new T[newCap];
            for(size_t i=0; i<length; ++i)
                newData[i]=data[i];
            delete[] data;
            data=newData;
            cap=newCap;
        }
        data[length++]=val;
    }
    void pop_back(){
        if(length>0)--length;
    }               // Vector의 마지막 항목을 제거하는 함수 구현
    size_t size() const{return length;}            // Vecotr에 있는 항목 개수(length)를 리턴하는 함수 구현
    T& operator[](int i) {return data[i];}          // [] 연산자 구현

    bool operator==(const MyVector& other) const{
        if (length != other.length) return false;
        for(size_t i=0; i<length; ++i)
            if(data[i] != other.data[i]) return false;
            return true;
    }

    bool operator!=(const MyVector& other) const{ return !(*this==other);}

    bool operator<(const MyVector& other) const{
        size_t n = std::min(length, other.length);
        for(size_t i =0; i<n; ++i){
            if(data[i]<other.data[i])return true;
            if(data[i]>other.data[i])return false;
        }   
        return length < other.length;
    }

    bool operator>(const MyVector& other) const{return other < *this;}

    bool operator<=(const MyVector& other) const{return !(*this > other);}

    bool operator>=(const MyVector& other) const{return !(*this < other);}


    // Vector에 대한 반복자
    class Iterator {
        T* ptr;         // 항목에 대한 포인터
    public:
        Iterator(T* p = nullptr): ptr(p) {}

        T& operator*(){return *ptr;}// 역참조 연산자 구현 

        Iterator& operator++() {++ptr; return *this;}   //전위 증가 연산자 구현
        Iterator& operator--() {--ptr; return *this;}   //전위 감소 연산자 구현
        Iterator operator+(int n) const {return Iterator(ptr+n);}   // 산술 연산자 구현
        Iterator operator-(int n) const {return Iterator(ptr-n);}   // 산술 연산자 구현

        bool operator==(const Iterator& other) const {return ptr==other.ptr;}
        bool operator!=(const Iterator& other) const {return ptr!=other.ptr;}

        int operator-(const Iterator& other) const {return static_cast<int>(ptr-other.ptr);}
    };

    // 첫번째 항목에 대한 iterator 리턴 함수 구현
    Iterator begin() {return Iterator(data);}
    // 마지막 항목에 대한 iterator 리턴 함수 구현 
    Iterator end() {return Iterator(data+length);}


    // insert: 지정 위치에 요소 삽입 함수 구현
    Iterator insert(Iterator pos, const T& value) {
        int idx=pos-begin();
        push_back(T());
        for(int i=static_cast<int>(length)-1; i>idx; --i)
            data[i]=data[i-1];
        data[idx]=value;
        return Iterator(data+idx);
    }

    // erase: 지정 위치 요소 제거 함수 구현
    Iterator erase(Iterator pos) {
        int idx=pos-begin();
        for(size_t i=idx; i<length-1; ++i)
            data[i]=data[i+1];
        --length;
        return Iterator(data+idx);
    }

    // clear: 모든 요소 제거 함수 구현 (size = 0 초기화)
    void clear() {length =0;}

    // at: 범위 체크 후, i번째 항목 접근 함수 구현
    T& at(size_t i) {
        if (i>=length) throw std::out_of_range("Index out of range");
        return data[i];
    }

    // front/back
    T& front() {return data[0];}    // 첫번째 항목 리턴 함수 구현
    T& back() {return data[length-1];}     // 마지막 항목 리턴 함수 구현

    // capacity
    size_t capacity() const {return cap;}   // cap 값 리턴하는 함수 구현

    // empty
    bool empty() const {return length ==0;}    // 현재 vector가 empty인지 확인하는 함수 구현

};