//
// Created by bravo8234 on 17/05/2022.
//

#ifndef EX5_CPP_A_ORGCHART_HPP
#define EX5_CPP_A_ORGCHART_HPP
#include "Node.hpp"
#include <string>
#include <iostream>
#include <utility>
#include <exception>
#include <queue>
#include <stack>
namespace ariel{
    class OrgChart{
        Node<std::string>* root;
        std::vector<std::string> order;
        std::vector<std::string> pre_order;
        std::vector<std::string> reverseOrder;
        std::vector<Node<std::string>*> nodes;
    public:
        using Iterator = std::vector<std::string>::iterator;

        OrgChart(){this->root = nullptr;};
        void preOrder(Node<std::string>* head);
        void BFS();
        void ReverseOrder();
        OrgChart& add_root(std::string name);
        OrgChart& add_sub(const std::string& father, std::string child);
        Iterator begin_level_order();
        //#Todo create preorder iterator
        Iterator begin_preorder();
        Iterator begin_reverse_order();
        Iterator end_level_order();
        //#Todo create reverse iterator
        Iterator end_preorder();
        Iterator reverse_order();

        Iterator begin();
        Iterator end();
        friend std::ostream &operator<<(std::ostream &os, OrgChart &chart);
    };
}
#endif //EX5_CPP_A_ORGCHART_HPP
