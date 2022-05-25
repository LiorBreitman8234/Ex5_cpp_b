//
// Created by bravo8234 on 18/05/2022.
//

#include "Node.hpp"
namespace ariel{
    template<typename T>
    Node<T>::Node(T &data, Node *parent) {
        this->data = data;
        this->color = 0;
        this->next = nullptr;
        this->parent = parent;
        this->parent->children.push_back(this);
        if(!this->parent->children.empty())
        {
            Node* lastChild = parent->children.back();
            lastChild->next = this;
        }
    }
}
