/**
 * @file
 * @author  Aapo Kyrola <akyrola@cs.cmu.edu>
 * @version 1.0
 *
 * @section LICENSE
 *
 * Copyright [2012] [Aapo Kyrola, Guy Blelloch, Carlos Guestrin / Carnegie Mellon University]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 
 *
 * @section DESCRIPTION
 *
 * Variable size typed vector (type must be a plain old datatype) that
 * allows adding and removing of elements. 
 */


#ifndef DEF_GRAPHCHI_CHIVECTOR
#define DEF_GRAPHCHI_CHIVECTOR

#include <vector>
#include <stdint.h>

namespace graphchi {
    
#define MINCAPACITY 2

/**
  * Pool the extension parts of chi-vectors
  */
template <typename T>
class extension_pool {
        
};
    
template <typename T>
class chivector {

    size_t nsize;
    size_t ncapacity;
    T * data;
    std::vector<T> * extensions;  // TODO: use a more memory efficient system?
    
public:
    typedef T element_type_t;
    typedef size_t sizeword_t;
    chivector() {
        extensions = NULL;
    }
    
    chivector(size_t sz, size_t cap, T * dataptr) : data(dataptr) {
        nsize = sz;
        ncapacity = cap;
        assert(cap >= nsize);
        extensions = NULL;
    }
    
    ~chivector() {
        if (extensions != NULL) {
            delete extensions;
            extensions = NULL;
        }
    }
    
    void write(T * dest) {
        size_t sz = this->size();
        for(size_t i=0; i < sz; i++) {
            dest[i] = get(i);  // TODO: use memcpy
        }
    }
    
    size_t size() {
        return nsize;
    }
    
    size_t capacity() {
        return nsize > MINCAPACITY ? nsize : MINCAPACITY;
    }
    
    void add(T val) {
        nsize ++;
        if (nsize > ncapacity) {
            if (extensions == NULL) extensions = new std::vector<T>();
            extensions->push_back(val);
        } else {
            data[nsize - 1] = val;
        }
    }
    //idx should already exist in the array
    void set(int idx, T val){
	if (idx >= ncapacity) {
            (*extensions)[idx - ncapacity] = val;
        } else {
            data[idx] = val;
        }
    }
  
    // TODO: addmany()
    
    T get(size_t idx) {
        if (idx >= ncapacity) {
            return (* extensions)[idx - ncapacity];
        } else {
            return data[idx];
        }
    }
    
    void remove(size_t idx) {
        assert(false);
    }
    
    int find(T val) {
        assert(false);
        return -1;
    }
    
    void clear() {
        nsize = 0;
    }
    
    // TODO: iterators
};
    
}

#endif
