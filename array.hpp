#pragma once

#include <stdexcept>
#include <iostream>
#include <memory>

template<typename T>

class Array2D{
    private:
        unsigned width;
        unsigned height;
        std::vector<std::vector<T> > array;

    public:
        Array2D(unsigned width, unsigned height){
            this->width = width;
            this->height = height;
            std::vector<std::vector<T> > arr;
            for (unsigned i = 0; i < width; i++){
                std::vector<T> v(height);
                arr.push_back(v);
            }
            this->array = arr;
        };

        ~Array2D() = default;

        unsigned get_width() const{
            return this->width;
        };

        unsigned get_height() const{
            return this->height;
        };

        T get(unsigned x, unsigned y) const{
            return this->array[x][y];
        };

        void set(unsigned x, unsigned y, T value){
            this->array[x][y] = value;
        };
        
        Array2D(const Array2D&) = delete;
};

