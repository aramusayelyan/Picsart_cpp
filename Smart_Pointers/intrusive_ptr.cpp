#include <iostream>
#include <utility>

template <typename T>
struct data
{
    int *count;
    T *ptr;
};

template <typename T>
class intrusive_ptr
{
private:
    data<T> *ob;

public:
    intrusive_ptr(T *_new)
    {
        ob = new data<T>;
        ob->count = new int(1);
        ob->ptr = _new;
    }

    void add()
    {
        (*ob->count)++;
    }

    void sub()
    {
        (*ob->count)--;
    }

    intrusive_ptr(const intrusive_ptr<T> &other)
    {
        ob = other.ob;
        add();
    }

    intrusive_ptr(intrusive_ptr<T> &&other)
    {
        ob = other.ob;
        other.ob = nullptr;
    }

    ~intrusive_ptr()
    {
        sub();
        if (*ob->count == 0)
        {
            delete ob->count;
            delete ob->ptr;
            delete ob;
        }
    }

    intrusive_ptr &operator=(const intrusive_ptr &other)
    {
        intrusive_ptr<T> tmp(other);
        swap(tmp);
        return *this;
    }

    intrusive_ptr &operator=(intrusive_ptr &&other)
    {
        swap(other);
        return *this;
    }

    void swap(intrusive_ptr &other)
    {
        std::swap(ob, other.ob);
    }

    T* get() {
        return ob->ptr;
    }

    T operator*(){
        return *(ob->ptr);
    } 
    T* operator->(){
        return ob->ptr;
    } 
};


int main(){}