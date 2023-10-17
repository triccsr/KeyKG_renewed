//
// Created by tricc on 2023/10/16.
//

#ifndef KEYKG_MAIN_UTILS_ARRAYONHEAP_ARRAYONHEAP_H_
#define KEYKG_MAIN_UTILS_ARRAYONHEAP_ARRAYONHEAP_H_

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <string>

template <class T>
class ArrayOnHeap {
  T* _arr;
  size_t _size;
 public:
  ArrayOnHeap():_arr(nullptr),_size(0){};
  explicit ArrayOnHeap(size_t size):_arr(new T[size]),_size(size){}
  explicit ArrayOnHeap(ArrayOnHeap<T>&& rValue):_arr(rValue._arr),_size(rValue._size){
    rValue._arr= nullptr;
    rValue._size=0;
  }
  explicit ArrayOnHeap(size_t size, T initialValue):_arr(new T[size]),_size(size){
    for(size_t i=0;i<_size;++i){
      _arr[i]=initialValue;
    }
  }
  ~ArrayOnHeap(){
    delete[] _arr;
  }
  ArrayOnHeap operator = (ArrayOnHeap<T>&& rValue){
    delete[] _arr;
    _arr=rValue._arr;
    _size=rValue._size;
    rValue=_arr= nullptr;
  }
  void memset_all(int val){
    memset(_arr,val,sizeof(T)*_size);
  }
  T& operator [] (size_t index){
    return _arr[index];
  }
  T& at(size_t index){
    try{
      if(index>=_size){
        throw(std::out_of_range("ArrayOnHeap Overflow: size is "+std::to_string(_size)+", you are trying visiting index "+std::to_string(index)));
      }
    }
    catch (const std::out_of_range &e){
      std::cerr<<e.what()<<std::endl;
    }
    return (*this)[index];
  }
  size_t size(){return _size;}
  void resize(size_t newSize){
    T* newArr=new T[newSize];
    std::memcpy(newArr,_arr,sizeof(T)*std::min(newSize,_size));
    delete[] _arr;
    _arr=newArr;
    _size=newSize;
  }
  T* begin(){
    return _arr;
  }
  T* end(){
    return _arr+_size;
  }
};

#endif //KEYKG_MAIN_UTILS_ARRAYONHEAP_ARRAYONHEAP_H_
