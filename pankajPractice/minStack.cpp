#include <iostream>
#include <algorithm>
#include <limits>

class StackImpl
{
    int currIndex;
    int capacity;
    int* stackArr;
    void dataMemberCpy(const StackImpl& st)
    {
        this->currIndex = st.currIndex;
        this->capacity = st.capacity;
        this->stackArr = new int[st.capacity];
        std::copy(st.stackArr, st.stackArr+st.capacity, this->stackArr);
    }
    
    void resize()
    {
        this->capacity *= 2;
        int* newStArr = new int[this->capacity];
        std::copy(this->stackArr, this->stackArr+this->currIndex+1, newStArr);
        delete[] this->stackArr;
        this->stackArr = newStArr;
    }
    
public:
    StackImpl(int cap):capacity(cap),currIndex(-1),stackArr(new int[cap]){}
    StackImpl(const StackImpl& st)
    {
        dataMemberCpy(st);
    }
    StackImpl& operator=(const StackImpl& st)
    {
        if(this == &st)
            return *this;
        
        dataMemberCpy(st);
        return *this;
    }
    
    bool isEmpty()
    {
        if(this->currIndex < 0)
            return true;
        return false;
    }
    
    bool isFull()
    {
        if(this->currIndex+1 >= this->capacity)
            return true;
        return false;
    }
    
    int top()
    {
        return this->stackArr[this->currIndex];
    }
    
    virtual void pop()
    {
        if(isEmpty())
            std::cout << "Stack is empty" << std::endl;
        
        this->stackArr[this->currIndex] = 0;
        this->currIndex--;
    }
    
    virtual void push(int val)
    {
        if(isFull())
            resize();
        
        this->currIndex++;
        this->stackArr[this->currIndex] = val;
    }
    
    virtual void print()
    {
        for(int i = this->currIndex ; i >= 0; i--)
            std::cout << this->stackArr[i] << ", ";
    }
    
    virtual ~StackImpl()
    {
        delete[] this->stackArr;
    }
};

class stackMin : public StackImpl
{
    StackImpl* stMin;
public:
    stackMin(int cap):StackImpl(cap), stMin(new StackImpl(cap)){}
    ~stackMin(){delete this->stMin;}
    
    int min()
    {
        if(stMin->isEmpty())
            return std::numeric_limits<int>::max();
        return stMin->top();
    }
    
    void pop()
    {
        int val = stMin->top();
        if(val == min())
            stMin->pop();
        StackImpl::pop();
    }
    
    void push(int val)
    {
        if(val < min())
            stMin->push(val);
        StackImpl::push(val);
    }
    
    void print()
    {
        this->stMin->print();
        std::cout << std::endl;
        StackImpl::print();
    }
    
};

int main()
{
    stackMin st(10);
    st.push(12);
    st.push(10);
    st.push(22);
    st.push(4);
    st.print();
    std::cout << std::endl;
    std::cout << st.min();
    st.pop();
    std::cout << std::endl;
    std::cout << st.min();
    
}