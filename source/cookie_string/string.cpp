#include "string.hpp"

cookie::string::string() noexcept : _data(nullptr) {
    #if defined(WARNING) || defined(ERROR)
    std::cerr << "string created without size or c string" << std::endl;
    #endif
}

cookie::string::string(const int size) {
    if (size == 0) {
        #if defined(WARNING) || defined(ERROR)
        std::cerr << "string created without size or c string" << std::endl;
        #endif
    } else {
        try {
            this->_data = new char[size + 1];
        } catch (std::bad_alloc& error) {
            throw;
        }

        this->_data[size] = '\0';
        this->_size = 0;
    }
}

cookie::string::string(const char *c_string) {
    while(c_string[this->_size])
        this->_size++;

    try {
        this->_data = new char[this->_size + 1];
    } catch (std::bad_alloc& error) {
        throw;
    }

    for (int index = 0; index < this->_size; index++) {
        this->_data[index] = c_string[index];
    };

    this->_data[this->_size] = '\0';
}

cookie::string::string(const cookie::string &ref) {
    if (ref._data == nullptr) {
        #if defined(WARNING) || defined(ERROR)
        std::cerr << "string created without size or c string" << std::endl;
        #endif
    } else {
        try {
            this->_data = new char[ref._size + 1];
        } catch (std::bad_alloc& error) {
            throw;
        }

        this->_data[ref._size] = '\0';

        for (int index = 0; index < _size; index++) {
            this->_data[index] = ref._data[index];
        }

        this->_size = ref._size;
    }
}

cookie::string::string(cookie::string &&ref) {
    this->_data = ref._data;
    this->_size = ref._size;

    ref._data = nullptr;
    ref._size = 0;
}

cookie::string& cookie::string::operator=(const cookie::string &ref) {
    if (&ref == this)
        return *this;

    if (ref._data == nullptr) {
        #if defined(WARNING) || defined(ERROR)
        std::cerr << "string created without size or c string" << std::endl;
        #endif
    } else {
        try {
            this->_data = new char[ref._size + 1];
        } catch (std::bad_alloc& error) {
            throw;
        }

        this->_data[ref._size] = '\0';

        for (int index = 0; index < _size; index++) {
            this->_data[index] = ref._data[index];
        }

        this->_size = ref._size;
    }

    return *this;
}

cookie::string& cookie::string::operator=(cookie::string &&ref) noexcept {
    if (&ref == this)
        return *this;

    this->_data = ref._data;
    this->_size = ref._size;

    ref._data = nullptr;
    ref._size = 0;

    return *this;
}

cookie::string cookie::string::operator+(const cookie::string &rhs) const {
    cookie::string result(this->_size + rhs._size);

    for (int index = 0; index < this->_size; index++) {
        result._data[index] = this->_data[index];
    }

    for (int index = 0; index < _size; index++) {
        result._data[index + this->_size] = rhs._data[index];
    }

    result._data[result._size] = '\0';

    return result;
}

cookie::string& cookie::string::operator+=(const cookie::string &rhs) {
    char* result = new char[this->_size + rhs._size + 1];

    for (int index = 0; index < this->_size; index++) {
        result[index] = this->_data[index];
    }

    for (int index = 0; index < _size; index++) {
        result[index + this->_size] = rhs._data[index];
    }

    result[this->_size + rhs._size] = '\0';

    delete[] this->_data;
    this->_data = result;
    this->_size = this->_size + rhs._size;

    return *this;
}

const char* cookie::string::data() const {
    return this->_data;
}

cookie::string::~string() {
    delete[] this->_data;
}

std::ostream& cookie::operator<<(std::ostream& os, const cookie::string& string) {
    os << string.data();

    return os;
}