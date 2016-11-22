#pragma once
#include <iterator>
template <typename T>
class Deque {
private:
    static const int EXPANSION_COEFFICIENT = 4;
    static const int MINIMAL_SIZE = 8;
    T *conteiner;
    int first;
    int conteinerSize, dequeLenght;

    void setNewSize(int newSize) {
        if (newSize < MINIMAL_SIZE)
            newSize = MINIMAL_SIZE;
        T *buffer = new T[newSize];
        for (int i = 0; i < dequeLenght; ++i) {
            int copyIndex = (first + i) % conteinerSize;
            buffer[i] = conteiner[copyIndex];
        }

        if (conteiner != nullptr)
            delete[] conteiner;
        conteiner = buffer;
        conteinerSize = newSize;
        first = 0;
    }
    void reload() {
        if (dequeLenght + 1 >= conteinerSize)
            return setNewSize(EXPANSION_COEFFICIENT * conteinerSize);
        if (EXPANSION_COEFFICIENT * EXPANSION_COEFFICIENT * dequeLenght <= conteinerSize)
            return setNewSize(conteinerSize / EXPANSION_COEFFICIENT);
    }
    void checkError(int index) const {
        if (index >= dequeLenght)
            throw true;
    }
    T& getAt(int index) const {
        if (index < -1 || index > dequeLenght)
            throw true;
        int position = (conteinerSize + first + index) % conteinerSize;
        if (position < 0)
            throw true;
        return conteiner[position];
    }
    template <typename El, typename Pointer, typename Reference>
    class MyIterator :
        public std::iterator<std::random_access_iterator_tag, T, long long, Pointer, Reference> {
    private:
        const Deque <El> *parent;
        int index;
    public:
        MyIterator() {
            parent = nullptr;
            index = 0;
        }
        MyIterator(const Deque <El> *father, int position) {
            parent = father;
            index = position;
        }
        MyIterator(const MyIterator &other) {
            parent = other.parent;
            index = other.index;
        }

        MyIterator& operator =(const MyIterator& other) {
            parent = other.parent;
            index = other.index;
            return *this;
        }
        bool operator ==(const MyIterator &other) const {
            return index == other.index;
        }
        bool operator !=(const MyIterator &other) const {
            return index != other.index;
        }
        Reference operator *() const {
            return parent->getAt(index);
        }
        Pointer operator ->() const {
            return &**this;
        }
        MyIterator& operator +=(int n) {
            index += n;
            return *this;
        }
        MyIterator& operator -=(int n) {
            return *this += -n;;
        }
        MyIterator& operator ++() {
            return *this += 1;
        }
        MyIterator& operator --() {
            return *this += -1;
        }
        MyIterator operator ++(int) {
            return (--MyIterator(++(*this)));
        }
        MyIterator operator --(int) {
            return ++MyIterator(--(*this));
        }
        MyIterator operator +(int n) const {
            return MyIterator(*this) += n;
        }
        MyIterator operator -(int n) const {
            return MyIterator(*this) -= n;
        }
        Reference operator [](int n) const {
            return *(*this + n);
        }
        long long operator -(const MyIterator &other) const {
            return index - other.index;
        }

        bool operator <(const MyIterator &other) const {
            return index < other.index;
        }
        bool operator >(const MyIterator &other) const {
            return other < *this;
        }
        bool operator <=(const MyIterator &other) const {
            return *this == other || index < other.index;
        }
        bool operator >=(const MyIterator &other) const {
            return other <= *this;
        }
    };
public:
    Deque() {
        conteiner = new T[MINIMAL_SIZE];
        first = 0;
        conteinerSize = MINIMAL_SIZE;
        dequeLenght = 0;
    }
    Deque(const Deque &other) {
        conteinerSize = other.conteinerSize;
        conteiner = new T[conteinerSize];
        first = other.first;
        dequeLenght = other.dequeLenght;
        for (int i = 0; i < conteinerSize; ++i)
            conteiner[i] = other.conteiner[i];
    }
    ~Deque() {
        delete[] conteiner;
    }
    Deque& operator =(const Deque& other) {
        if (this == &other)
            return *this;
        if (conteiner != nullptr)
            delete[] conteiner;
        conteinerSize = other.conteinerSize;
        conteiner = new T[conteinerSize];
        first = other.first;
        dequeLenght = other.dequeLenght;
        for (int i = 0; i < conteinerSize; ++i)
            conteiner[i] = other.conteiner[i];
        return *this;
    }
    typedef MyIterator <T, T*, T&> iterator;
    typedef MyIterator <T, const T*, const T&> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    const T& operator [](const int& index) const {
        checkError(index);
        return conteiner[(index + first) % conteinerSize];
    }
    T& operator [](const int& index) {
        checkError(index);
        return conteiner[(index + first) % conteinerSize];
    }
    bool empty() const {
        return dequeLenght == 0;
    }
    size_t size() const {
        return static_cast <size_t> (dequeLenght);
    }

    void push_back(const T& newElement) {
        reload();
        conteiner[(first + dequeLenght) % conteinerSize] = newElement;
        ++dequeLenght;
    }
    void pop_back() {
        checkError(0);
        --dequeLenght;
        reload();
    }
    void push_front(const T& newElement) {
        reload();
        first = (first + conteinerSize - 1) % conteinerSize;
        conteiner[first] = newElement;
        ++dequeLenght;
    }
    void pop_front() {
        checkError(0);
        first = (first + 1) % conteinerSize;
        --dequeLenght;
        reload();
    }

    T& back() {
        checkError(0);
        return conteiner[(first + dequeLenght - 1) % conteinerSize];
    }
    const T& back() const {
        checkError(0);
        return conteiner[(first + dequeLenght - 1) % conteinerSize];
    }
    T& front() {
        checkError(0);
        return conteiner[first];
    }
    const T& front() const {
        checkError(0);
        return conteiner[first];
    }

    iterator begin() {
        return iterator(this, 0);
    }
    const_iterator begin() const {
        return const_iterator(this, 0);
    }
    const_iterator cbegin() const {
        return const_iterator(this, 0);
    }

    iterator end() {
        return iterator(this, dequeLenght);
    }
    const_iterator end() const {
        return const_iterator(this, dequeLenght);
    }
    const_iterator cend() const {
        return const_iterator(this, dequeLenght);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(cend());
    }
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(cend());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(cbegin());
    }
    const_reverse_iterator crend() const {
        return const_reverse_iterator(cbegin());
    }
};