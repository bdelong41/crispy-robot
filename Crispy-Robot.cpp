#include <iostream>
/*List is a c++ list that mimics that of python lists by allowing users to
    1: dynamically add new data to the list
    2: search the list for specific data and index values
    2: traverse the array with index values that can be negative or greater than the array length
    3: features memory cleanup during the end cycle of the variable.*/
template <class dataType>
class List{
private:
    dataType * arrayList;
    int length = 0;

public:
    //initializers
    List(){
        arrayList = nullptr;
    }
    List(dataType * arrayList, int length){
        this->arrayList = arrayList;
        this->length = length;
    }

    //setter methods
    virtual void push_back(dataType val){
        //empty array
        if(arrayList == nullptr){
            length++;
            arrayList = new (std::nothrow) dataType(length);
            *(arrayList + (length-1)) = val;
        }
        //full array
        else{        
            dataType * tmpList = new (std::nothrow) dataType(length + 1);
            for(int index = 0; index < length; index++){
                *(tmpList + index) = *(arrayList + index);
            }
            length++;

            //adding new value
            *(tmpList + length) = val;

            //cleaning up array list
            delete[] arrayList;
            //initializing again
            arrayList = tmpList;
        }
    }

    virtual bool set(dataType val, int indexVal){
        if(!(indexVal <= length)) return false;

        *(arrayList + indexVal) = val;
        return true;
    }

    //getter methods

    //finds the first index of the input instance
    virtual int findIndexOf(dataType val){
        for(int index = 0; index < length; index++){
            if(*(arrayList + index) == val) return index;
        }
        return -1;
    }

    //traverses array backwards and forwards
    virtual bool has(dataType val){
        int counter = length;
        for(int index = 0; index < (length/2); index++){
            if(*(arrayList + index) == val) {return true;}
            else if(*(arrayList + counter) == val) {return true;}
            counter--;
        }
        //capturing last inbetween value
        if(*(arrayList + counter) == val) {return true;}
        return false;
    }

    //opperators
    //indexing
    dataType operator[](int index){
        if(index < 0){
            return *(arrayList + ((index * -1) % length));
        }
        else {return *(arrayList + (index % length));}
    }
    //assignment
    void operator=(dataType * arr){
        delete[] arrayList;
        arrayList = arr;
        return true;
    }

    //destructor
    ~List(){
        delete[] arrayList;
    }
};
