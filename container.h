//
// Created by Valerii Kovalchuk on 5/6/18.
//

#ifndef LAB2_CONTAINER_H
#define LAB2_CONTAINER_H

#define CAPACITY 10


template<class Item>
class Container {
    Item **items;
    uint length, capacity;
public:
    Container();
    ~Container();
    bool append(Item *se);
    uint get_length() { return length; }
    Item **get_items() { return items; }
    Item *operator[](int index);
};


template<class Item>
Container<Item>::Container() {
    capacity = CAPACITY;
    length = 0;
    items = new Item*[capacity];
}


template<class Item>
Container<Item>::~Container() {
    std::cout << "Calling container destructor" << std::endl;
    if (items) {
        for (int i = 0; i < length; i++) {
            delete items[i];
        }
        delete[] items;
    }
}


template<class Item>
bool Container<Item>::append(Item *se) {
    if (length >= capacity) {
        auto temp = new Item*[capacity + CAPACITY];
        for (int i = 0; i < capacity; i++) {
            temp[i] = items[i];
        }
        capacity += CAPACITY;
        delete[] items;
        items = temp;
    }
    items[length++] = se;
    return true;
}


template<class Item>
Item *Container<Item>::operator[](int index) {
    if (index < 0 || index >= length) return nullptr;
    return items[index];
}

#endif //LAB2_CONTAINER_H
