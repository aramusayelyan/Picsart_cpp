#include<iostream>

template<typename T>
class shared_ptr{
    private:
        T* ptr;
        int * control;
    public:
        shared_ptr(T * _ptr){
            ptr = _ptr;
            control = new int;
            *control = 1;
        }

        ~shared_ptr(){
            if(!((*control)--)){
                delete ptr;
                delete control;
            }
        }

        shared_ptr(const shared_ptr& other){
            this->ptr = other.ptr;
            this->control = other.control; 
            this->control++;
        }

        shared_ptr(shared_ptr&& other){
            this->ptr = other.ptr;
            other.ptr = nullptr;
            this->control = other.control;
            other.control = nullptr;
        }

        void swap(shared_ptr& other){
            std::swap(this->ptr, other.ptr);
            std::swap(this->control, other.control);
        }

        shared_ptr<T>& operator=(shared_ptr&& other){
            shared_ptr<T> tmp(other);
            swap(*this,tmp);
            return *this; 
        }

        shared_ptr<T>& operator=(const shared_ptr& other){
            if(ptr && control){
                delete ptr;
                delete control;
            }
            shared_ptr<T> tmp(other);
            swap(*this,tmp);
            return *this;
        }

        T* get(){
            return ptr;
        }

        int use_count(){
            return *control;
        }
        T operator*(){
            return *ptr;
        }

        T* operator->(){
            return ptr;
        }

};

int main(){

}
