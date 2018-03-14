
#pragma once
#include <cstddef>
#include <iostream>

//template<typename T> class shared_ptr<T>;

template<typename T>
class __shared_inner_ptr {
    public:
        __shared_inner_ptr(T *ptr): _ptr(ptr){
            if (ptr == nullptr || ptr == NULL) 
                _count = 0;
            else
                _count = 1;
        }

        ~__shared_inner_ptr() {
            if (_ptr != nullptr && _ptr != NULL) {
                std::cout << "release the memory of shared_ptr(value: " << *_ptr << ")" << std::endl;
                delete _ptr;
            }
        }
        //friend class shared_ptr<T>;

        T *_ptr;
        long _count;

};

template<typename T>
class shared_ptr {
    public:
        shared_ptr(): inner_ptr(nullptr){}

        shared_ptr(T* ptr) {
            if (ptr == NULL || ptr == nullptr) {
                
                inner_ptr = nullptr;
                return ;
            }
            inner_ptr = new __shared_inner_ptr<T>(ptr);
        }

        shared_ptr(const shared_ptr &rhs) {
            inner_ptr = rhs.inner_ptr;
            inner_ptr->_count += 1;
        }

        T operator*() {
            return *(inner_ptr->_ptr);
        }

        T* operator->() {
            return inner_ptr->_ptr;
        }

        shared_ptr<T>& operator=(const shared_ptr<T> &rhs) {

            if (rhs.inner_ptr != this->inner_ptr) {
                decrease_usecount();
                this->inner_ptr = rhs.inner_ptr;
                this->inner_ptr->_count += 1;
            }

            return *this;
        }

        ~shared_ptr(){
            if (inner_ptr->_ptr == nullptr || inner_ptr->_ptr == NULL)
                return;
            decrease_usecount();
        }

        long get_usecount();
    private:
        __shared_inner_ptr<T> *inner_ptr;

        void decrease_usecount();
};

template<typename T> void
shared_ptr<T>::decrease_usecount() {
    --inner_ptr->_count;
    if (inner_ptr->_count == 0) {
        delete(inner_ptr);
        inner_ptr = nullptr;
    }
}

template<typename T> long
shared_ptr<T>::get_usecount() {
    return inner_ptr->_count;
}


