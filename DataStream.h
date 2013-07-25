// Arduino Stream-like library for data of any type

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
      _currentSize = 0;
      _maxSize = maxSize;
      _head = NULL;
      _tail = NULL;
    }

    DataStream(const unsigned long maxSize, T* data, 
               const unsigned long dataSize) {
      _currentSize = 0;
      _maxSize = maxSize;
      _head = NULL;
      _tail = NULL;

      for (unsigned long i = 0; i < dataSize; i++) {
        write(data[i]);
      }
    }

    DataStream() {
      _currentSize = 0;
      _maxSize = 10;
      _head = NULL;
      _tail = NULL;
    }

    // Destructor
    ~DataStream() {
      // FIXME: implement, free() any memory reserved by malloc()
      // will probably want something very similar to flush()
    }

    T available() {
      return _currentSize;
    }

    T read() {
      StreamItem<T>* oldHead;
      T value; 

      if (available() > 0) {
        oldHead = _head;
        value = _head->_value;
        if (_head == _tail) { 
          _head = NULL;
          _tail = NULL;
        } 
        else { 
          _head->_next->_prev = NULL; 
          _head = _head->_next;
          free(oldHead); 
        } 
        _currentSize--;
      }

      return value;
    }

    T peek() {
      T value;

      if (available() > 0) {
        value = _head->_value;
        return value;
      }

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
}; // end class DataStream

#endif
