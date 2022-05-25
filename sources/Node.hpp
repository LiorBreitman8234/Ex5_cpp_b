//
// Created by bravo8234 on 17/05/2022.
//

#ifndef EX5_CPP_A_NODE_HPP
#define EX5_CPP_A_NODE_HPP
#include <vector>
#include <iostream>
namespace ariel{
    template<typename T>
    class Node{
    public:
        int color{}; //used for bfs
        T data;
        Node* parent;
        Node* next;
        std::vector<Node*> children;
        explicit Node(T& data){this->color = 0;this->data = data;this->next = nullptr; this->parent = nullptr; this->children = std::vector<Node*>();};
        Node (T& data, Node* parent);

    };


}
#endif //EX5_CPP_A_NODE_HPP
