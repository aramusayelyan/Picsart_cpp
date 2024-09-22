#include<iostream>

template <typename T>
class unique_ptr{
    private:
        T* ptr;
    public:
        unique_ptr(T* _ptr){
            ptr = _ptr;
        }
        ~unique_ptr(){
            delete ptr;
        }
        unique_ptr(const unique_ptr & other) = delete;

        unique_ptr(unique_ptr && other) {
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }

        unique_ptr<T>& operator=(unique_ptr && other){ 
            unique_ptr<T> tmp(other);
            swap(tmp);
            return *this;
        }

        void swap(unique_ptr& b){
            std::swap(this->ptr,b.ptr);
        }

        T* release(){
            T* tmp = ptr;
            delete ptr;
            return tmp;
        }

        void reset(T* _new){
            delete ptr;
            ptr = _new;
        }

        T* get(){
            return ptr;
        }

        T& operator*() const{
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

};

int main(){
    unique_ptr<int> a(new int);
    *a = 5;
    unique_ptr<int> b = std::move(a);

    std::cout << *b;
}
