#include <string.hpp>

cookie::string::string() noexcept {
    #if defined(WARNING)
    std::cerr << "string created without size or c string" << std::endl;
    #endif
}

cookie::string::string(const unsigned int size) {
    if (size == 0) {
        #if defined(WARNING)
        std::cerr << "string created without size or c string" << std::endl;
        #endif
    } else {
        this->_data = new char[size + 1];

        this->_data[size] = '\0';
        this->_size = size;
    }
}

cookie::string::string(const char *c_string) {
    while(c_string[this->_size])
        this->_size++;

    this->_data = new char[this->_size + 1];

    for (int index = 0; index < this->_size; index++) {
        this->_data[index] = c_string[index];
    };

    this->_data[this->_size] = '\0';
}

cookie::string::string(const string &ref) {
    if (ref._data == nullptr) {
        #if defined(WARNING)
        std::cerr << "string created without size or c string" << std::endl;
        #endif
    } else {
        this->_data = new char[ref._size + 1];

        this->_data[ref._size] = '\0';

        for (int index = 0; index < ref._size; index++) {
            this->_data[index] = ref._data[index];
        }

        this->_size = ref._size;
    }
}

cookie::string::string(string &&ref) noexcept {
    this->_data = ref._data;
    this->_size = ref._size;

    ref._data = nullptr;
    ref._size = 0;
}

cookie::string& cookie::string::operator=(const string &ref) {
    if (&ref == this)
        return *this;

    if (ref._data == nullptr) {
        #if defined(WARNING)
        std::cerr << "string created without size or c string" << std::endl;
        #endif
    } else {
        delete[] this->_data;
        this->_data = new char[ref._size + 1];

        this->_data[ref._size] = '\0';

        for (int index = 0; index < _size; index++) {
            this->_data[index] = ref._data[index];
        }

        this->_size = ref._size;
    }

    return *this;
}

cookie::string& cookie::string::operator=(string &&ref) noexcept {
    if (&ref == this)
        return *this;

    delete[] this->_data;

    this->_data = ref._data;
    this->_size = ref._size;

    ref._data = nullptr;
    ref._size = 0;

    return *this;
}

cookie::string& cookie::string::operator=(const char *c_string) {
    delete[] this->_data;

    this->_data = new char[strlen(c_string) + 1];
    this->_size = strlen(c_string);

    for (int index = 0; index < this->_size; index++) {
        this->_data[index] = c_string[index];
    }

    return *this;
}

cookie::string& cookie::string::operator+=(const string &rhs) {
    char* result = new char[this->_size + rhs._size + 1];

    for (int index = 0; index < this->_size; index++) {
        result[index] = this->_data[index];
    }

    for (int index = 0; index < rhs._size; index++) {
        result[index + this->_size] = rhs._data[index];
    }

    result[this->_size + rhs._size] = '\0';

    delete[] this->_data;
    this->_data = result;
    this->_size = this->_size + rhs._size;

    return *this;
}

cookie::string& cookie::string::operator+=(const char *rhs) {
    unsigned int size_rhs = 0;

    while (rhs[size_rhs])
        size_rhs++;

    char* result = new char[this->_size + size_rhs + 1];

    for (int index = 0; index < this->_size; index++) {
        result[index] = this->_data[index];
    }

    for (int index = 0; index < size_rhs; index++) {
        result[index + this->_size] = rhs[index];
    }

    result[this->_size + size_rhs] = '\0';

    delete[] this->_data;
    this->_data = result;
    this->_size = this->_size + size_rhs;

    return *this;
}

const char* cookie::string::data() const {
    return this->_data;
}

unsigned long cookie::string::size() const {
    return this->_size;
}


cookie::string::~string() {
    delete[] this->_data;
}

std::ostream& cookie::operator<<(std::ostream& os, const string& string) {
    os << string.data();

    return os;
}

std::istream& cookie::operator>>(std::istream& is, string& string) {
    char buffer[1024] = {};

    string = "";

    do {
        is >> buffer;
        string += buffer;

        if (is.eof())
            return is;
    } while (strlen(buffer) == 1023 && is.peek() != '\n');
    
    return is;
}

bool cookie::operator==(const string& lhs, const string& rhs) {
    if (lhs.size() != rhs.size())
        return false;

    for (int index = 0; index < lhs.size(); index++) {
        if (lhs.data()[index] != rhs.data()[index])
            return false;
    }

    return true;
}

bool cookie::operator==(const string& lhs, const char* rhs) {
    for (int index = 0; index < lhs.size() && rhs[index]; index++) {
        if (lhs.data()[index] != rhs[index])
            return false;
    }

    if (lhs.data()[lhs.size()] != rhs[lhs.size()])
        return false;
    return true;
}

bool cookie::operator==(const char* lhs, const string& rhs) {
    for (int index = 0; index < rhs.size() && lhs[index]; index++) {
        if (rhs.data()[index] != lhs[index])
            return false;
    }

    if (rhs.data()[rhs.size()] != lhs[rhs.size()])
        return false;
    return true;
}

bool cookie::operator!=(const string& lhs, const string& rhs) {
    if (lhs.size() != rhs.size())
        return true;

    for (int index = 0; index < lhs.size(); index++) {
        if (lhs.data()[index] != rhs.data()[index])
            return true;
    }

    return false;
}

bool cookie::operator!=(const string& lhs, const char* rhs) {
    for (int index = 0; index < lhs.size() && rhs[index]; index++) {
        if (lhs.data()[index] != rhs[index])
            return true;
    }

    if (lhs.data()[lhs.size()] != rhs[lhs.size()])
        return true;
    return false;
}

bool cookie::operator!=(const char* lhs, const string& rhs) {
    for (int index = 0; index < rhs.size() && lhs[index]; index++) {
        if (rhs.data()[index] != lhs[index])
            return true;
    }

    if (rhs.data()[rhs.size()] != lhs[rhs.size()])
        return true;
    return false;
}

cookie::string cookie::operator+(const string& lhs, const string& rhs) {
    string result(lhs);

    result += rhs;

    return result;
}

cookie::string cookie::operator+(const string& lhs, const char* rhs) {
    string result(lhs);

    result += rhs;

    return result;
}

cookie::string cookie::operator,(const string& lhs, const string& rhs) {
    string result(lhs);

    result += " ";
    result += rhs;

    return result;
}

cookie::string cookie::operator,(const string& lhs, const char* rhs) {
    string result(lhs);

    result += " ";
    result += rhs;

    return result;
}

unsigned long cookie::strlen(const string& string) {
    return string.size();
}

unsigned long cookie::strlen(const char* string) {
    unsigned long length = 0;

    while (string[length] != '\0') {
        length++;
    }

    return length;
}
