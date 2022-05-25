//
// Created by bravo8234 on 18/05/2022.
//

#include "OrgChart.hpp"

namespace ariel {

    OrgChart &OrgChart::add_root(std::string name) {
        auto *newRoot = new Node<std::string>(name);
        if (root != nullptr) {
            newRoot->children = root->children;
        }
        this->root = newRoot;
        this->nodes.push_back(root);
        return *this;
    }

    OrgChart &OrgChart::add_sub(const std::string &father, std::string child) {
        Node<std::string> *fatherNode;
        for (auto node: nodes) {
            if (node->data == father) {
                fatherNode = node;
                break;
            }
        }
        auto *childNode = new Node<std::string>(child, fatherNode);
        this->nodes.push_back(childNode);
        return *this;
    }

    OrgChart::Iterator OrgChart::begin_level_order() {
        order.clear();
        BFS();
        return order.begin();
    }


    OrgChart::Iterator OrgChart::end_level_order() {
        begin_level_order();
        return order.end();

    }

    OrgChart::Iterator OrgChart::begin_preorder() {
        pre_order.clear();
        preOrder(this->root);
        return pre_order.begin();
    }

    OrgChart::Iterator OrgChart::begin_reverse_order() {
        reverseOrder.clear();
        ReverseOrder();
        return reverseOrder.begin();
    }

    OrgChart::Iterator OrgChart::end_preorder() {
        pre_order.clear();
        preOrder(this->root);
        return pre_order.end();
    }

    OrgChart::Iterator OrgChart::reverse_order() {
        reverseOrder.clear();
        ReverseOrder();
        return reverseOrder.end();
    }

    OrgChart::Iterator OrgChart::begin() {
        return this->begin_level_order();
    }

    OrgChart::Iterator OrgChart::end() {
        return this->end_level_order();
    }

    std::ostream &operator<<(std::ostream &os, OrgChart &chart) {
        chart.begin_level_order();
        for (auto node: chart.nodes) {
            if (node->next == nullptr) {
                std::cout << node->data << std::endl;
            }
            else
            {
                std::cout<< node->data << "---";
            }
        }
        return os;
    }

    void OrgChart::preOrder(Node<std::string> *head) {
        if(head == nullptr)
        {
            return;
        }
        pre_order.push_back(head->data);
        for(auto child: head->children)
        {
            preOrder(child);
        }
    }

    void OrgChart::BFS() {
        Node<std::string> *s = root;
        std::queue<Node<std::string>*> bfsQueue = std::queue<Node<std::string>*>();
        std::vector<Node<std::string>*> toReset = std::vector<Node<std::string>*>();
        s->color = 1;
        bfsQueue.push(s);
        toReset.push_back(s);
        order.push_back(s->data);
        while (!bfsQueue.empty()) {
            Node<std::string> *v = bfsQueue.front();
            bfsQueue.pop();
            Node<std::string> *keep = v;
            while (v->next != nullptr && v->next->color == 0) {
                bfsQueue.push(v->next);
                order.push_back(v->next->data);
                toReset.push_back(v->next);
                v->next->color = 1;
                v = v->next;
            }
            v = keep;
            for (auto child: v->children) {
                if (child->color == 0) {
                    bfsQueue.push(child);
                    order.push_back(child->data);
                    toReset.push_back(child);

                    child->color = 1;
                }
            }
            v->color = 2;
        }
        for (auto node: toReset) {
            node->color = 0;
        }
    }

    void OrgChart::ReverseOrder() {
        Node<std::string> *s = root;
        std::queue<Node<std::string>*> bfsQueue = std::queue<Node<std::string>*>();
        std::vector<Node<std::string>*> toReset = std::vector<Node<std::string>*>();
        std::stack<Node<std::string>*> rlo = std::stack<Node<std::string>*>();
        s->color = 1;
        bfsQueue.push(s);
        toReset.push_back(s);
        rlo.push(s);
        while (!bfsQueue.empty()) {
            Node<std::string> *v = bfsQueue.front();
            bfsQueue.pop();
            Node<std::string> *keep = v;
            while (v->next != nullptr && v->next->color == 0) {
                bfsQueue.push(v->next);
                toReset.push_back(v->next);
                rlo.push(v);
                v->next->color = 1;
                v = v->next;
            }
            v = keep;
            for(int i = (int)v->children.size()-1; i > 0 ;i--)
            {
                if(v->children.at(i)->color == 0)
                {
                    bfsQueue.push(v->children.at(i));
                    toReset.push_back(v->children.at(i));
                    rlo.push(v->children.at(i));
                    v->children.at(i)->color = 1;
                }
            }
            if(v->children.size() != 0 && v->children.at(0)->color == 0)
            {
                bfsQueue.push(v->children.at(0));
                toReset.push_back(v->children.at(0));
                rlo.push(v->children.at(0));
                v->children.at(0)->color = 1;
            }

            v->color = 2;
        }
        for (auto node: toReset) {
            node->color = 0;
        }
        while(!rlo.empty())
        {
            reverseOrder.push_back(rlo.top()->data);
            rlo.pop();
        }

    }

    template<typename T>
    Node<T>::Node(T &data, Node *parent) {
        this->data = data;
        this->color = 0;
        this->next = nullptr;
        this->parent = parent;
        this->parent->children.push_back(this);
        if (!this->parent->children.empty()) {
            Node *lastChild = parent->children.back();
            lastChild->next = this;
        }
    }

}
