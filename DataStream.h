/*
 * DataStream - Arduino Stream-like library for data of any type
 *
 * Copyright 2013 Karl Ward and contributors
 * See the file CREDITS for contributors and external code referenced/incorporated
 * See the file COPYING for details on software licensing
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Version 0.1.4 */

#ifndef DataStream_h
#define DataStream_h

#include "Arduino.h"

template <class T>
class StreamItem { 
  private:
    T _value;
    StreamItem<T>* _next;
    StreamItem<T>* _prev;
  public:
    //T read() { return(_value); }
    template<class> friend class DataStream;
}; 

template <class T>
class DataStream {
  private:
    unsigned long _currentSize; 
    StreamItem<T>* _head;
    unsigned long _maxSize; 
    StreamItem<T>* _tail;

  public:
    DataStream(const unsigned long maxSize) {
      begin();
      _maxSize = maxSize;
    }

    DataStream(const unsigned long maxSize, T* data, 
               const unsigned long dataSize) {
      begin();
      _maxSize = maxSize;

      for (unsigned long i = 0; i < dataSize; i++) {
        write(data[i]);
      }
    }

    DataStream() {
      begin();
      _maxSize = 10;
    }

    // Destructor
    ~DataStream() {
      flush();
    }

    unsigned long available() const {
      return(_currentSize);
    }

    void begin() {
      _currentSize = 0;
      _maxSize = 0;
      _head = NULL;
      _tail = NULL;
    }

    T read() {
      StreamItem<T>* oldHead;
      T value; 

      if (available() > 0) {
        oldHead = _head;
        value = _head->_value;
        if (_head == _tail) { 
          _head = NULL;
          _tail = _head;
        } 
        else { 
          _head->_next->_prev = NULL; 
          _head = _head->_next;
        } 
        free(oldHead); 
        _currentSize--;
      }

      return(value);
    }

    T peek() const {
      T value;

      if (available() > 0) {
        value = _head->_value;
      }
      return(value);
    }

    T peek(const long index) const {
      T value;
      if (available() > index) {
        StreamItem<T>* cur = _head;
        long i = 0;
        while ((cur != NULL) && (i <= index)) {
          if (i == index) {
            value = cur->_value;
          }
          cur = cur->_next;
          i++;
        }
      }
      return(value);
    }

    void flush() {
      if (_head != NULL) { 
        StreamItem<T>* cur = _head;
        StreamItem<T>* next = _head;
        while (cur != NULL) {
          next = cur->_next;
          free(cur); 
          cur = next;
        }
      }
      _currentSize = 0;
      _head = NULL;
      _tail = _head;
    }

    size_t write(const T incoming) {
      StreamItem<T>* item;
      item = (StreamItem<T>*) malloc(sizeof(StreamItem<T>));
      item->_value = incoming;
      if (_currentSize == 0) { // stream empty
        _head = item;
        _head->_next = NULL;
        _head->_prev = NULL;
        _tail = _head;
        _currentSize++;
      }
      else if (_currentSize < _maxSize) { // stream has items but is not full
        StreamItem<T>* oldTail = _tail;
        oldTail->_next = item;
        _tail = item;
        _tail->_prev = oldTail;
        _tail->_next = NULL;
        _currentSize++;
      }
      else { // stream is full
        StreamItem<T>* oldHead = _head;
        if (_maxSize == 1) { // special case
          _head = item;
          _tail = item;
          _head->_prev = NULL;
          _head->_next = NULL;
        }
        else {
          StreamItem<T>* oldTail = _tail;
          if (_currentSize > 1) {
            _head = _head->_next;
            _head->_prev = NULL;
          }
          _tail->_next = item;
          _tail = item;
          _tail->_prev = oldTail;
          _tail->_next = NULL;
        }
        free(oldHead);
      }
      return(1);
    }

    void resize(const long newSize) {
      _maxSize = newSize; 
      // FIXME: check for negative newSize?
      if (_currentSize > _maxSize) { // we have to shrink
        StreamItem<T>* forward = _head;
        while ((forward != NULL) && (_currentSize > _maxSize)) { 
          StreamItem<T>* old = forward; 
          forward = forward->_next; 
          _head = forward;
          free(old); 
          _currentSize--; 
        }
        if (_head != NULL) {
          _head->_prev = NULL;
        }
      }
    }

    void writeOrdered(const T value) {
      StreamItem<T>* item;
      item = (StreamItem<T>*) malloc(sizeof(StreamItem<T>));
      item->_value = value;

      if (_head == NULL) { // first element
        _head = item;
        _head->_next = NULL;
        _head->_prev = NULL;
        _tail = _head;
        _currentSize++;
      }
      else {
        StreamItem<T>* cur = _head;
        while (cur != NULL) {
          if (value < cur->_value) { // NOTE: type must have operator <
            if (cur == _head) { // special case, reset _head
              item->_prev = NULL;
              item->_next = _head;
              _head->_prev = item;
              _head = item;
            }
            else {
              item->_prev = cur->_prev;
              item->_next = cur;
              cur->_prev->_next = item;
              cur->_prev = item;
            }
            _currentSize++;
            cur = NULL; // break out of the method
          }
          else if (cur == _tail) { //special case, reset _tail
            item->_next = NULL;
            item->_prev = _tail;
            _tail->_next = item;
            _tail = item;
            _currentSize++;
            cur = NULL;; // break out of the method
          }
          else {
            cur = cur->_next;
          }
        }
      }
      while (_currentSize > _maxSize) { // if too big, must delete oldest value(s)
        read(); // easy way to delete the oldest value
      }
    }

    unsigned long capacity() const {
      return(_maxSize);
    }

}; // end class DataStream

#endif
