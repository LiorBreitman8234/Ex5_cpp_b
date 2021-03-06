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
        newRoot->level = 0;
        auto* oldRoot = this->root;

        if(this->root != nullptr)
        {
            for(auto & node : this->nodes)
            {
                if(node == this->root)
                {
                    node = newRoot;
                }
            }
            delete oldRoot;
        }
        else
        {
            this->nodes.push_back(newRoot);
        }
        this->root = newRoot;
        return *this;
    }

    OrgChart &OrgChart::add_sub(const std::string &father, std::string child) {
        if(this->root == nullptr)
        {
            throw std::logic_error("can't add sub before root");
        }
        bool built = false;
        for (auto* node: nodes) {
            if (node->data == father) {
                auto *childNode = new Node<std::string>(child, node);
                childNode->level = node->level + 1;
                this->nodes.push_back(childNode);
                built = true;
                break;
            }
        }
        if(!built)
        {
            throw std::logic_error("employer doesn't exist");
        }
        return *this;
    }

    OrgChart::Iterator OrgChart::begin_level_order() {
        if(this->nodes.empty())
        {
            throw std::logic_error("chart is empty!");
        }
        order.clear();
        BFS();
        return order.begin();
    }


    OrgChart::Iterator OrgChart::end_level_order() {
        if(this->nodes.empty())
        {
            throw std::logic_error("chart is empty!");
        }
        begin_level_order();
        return order.end();

    }

    OrgChart::Iterator OrgChart::begin_preorder() {
        if(this->nodes.empty())
        {
            throw std::logic_error("chart is empty!");
        }
        pre_order.clear();
        preOrder(this->root);
        return pre_order.begin();
    }

    OrgChart::Iterator OrgChart::begin_reverse_order() {
        if(this->nodes.empty())
        {
            throw std::logic_error("chart is empty!");
        }
        reverseOrder.clear();
        ReverseOrder();
        return reverseOrder.begin();
    }

    OrgChart::Iterator OrgChart::end_preorder() {
        if(this->nodes.empty())
        {
            throw std::logic_error("chart is empty!");
        }
        pre_order.clear();
        preOrder(this->root);
        return pre_order.end();
    }

    OrgChart::Iterator OrgChart::reverse_order() {
        if(this->nodes.empty())
        {
            throw std::logic_error("chart is empty!");
        }
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
        int maxLevel = 0;
        for(auto* node: chart.nodes)
        {
            if(node->level > maxLevel)
            {
                maxLevel = node->level;
            }
        }
        std::vector<std::vector<std::string>> levels = std::vector<std::vector<std::string>>((size_t)(maxLevel + 1));
        for(auto* node: chart.nodes)
        {

            levels.at((size_t)node->level).push_back(node->data);
        }
        for(size_t i = 0; i < maxLevel + 1;i++)
        {
            for(size_t j = 0; j < levels.at(i).size();j++)
            {
                if(j == 0)
                {
                    std::cout << levels.at(i).at(j);
                }
                else
                {
                    std::cout << "----" << levels.at(i).at(j);
                }
            }
            std::cout <<std::endl;
        }
        return os;
    }

    void OrgChart::preOrder(Node<std::string> *head) {
        if(head == nullptr)
        {
            return;
        }
        pre_order.push_back(head->data);
        for(auto* child: head->children)
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
            for (auto* child: v->children) {
                if (child->color == 0) {
                    bfsQueue.push(child);
                    order.push_back(child->data);
                    toReset.push_back(child);

                    child->color = 1;
                }
            }
            v->color = 2;
        }
        for (auto* node: toReset) {
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
                if(v->children.at((unsigned long)i)->color == 0)
                {
                    bfsQueue.push(v->children.at((unsigned long)i));
                    toReset.push_back(v->children.at((unsigned long)i));
                    rlo.push(v->children.at((unsigned long)i));
                    v->children.at((unsigned long)i)->color = 1;
                }
            }
            if(!v->children.empty() && v->children.at(0)->color == 0)
            {
                bfsQueue.push(v->children.at(0));
                toReset.push_back(v->children.at(0));
                rlo.push(v->children.at(0));
                v->children.at(0)->color = 1;
            }

            v->color = 2;
        }
        for (auto* node: toReset) {
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

    OrgChart::~OrgChart()
    {
        size_t i = 0;
        while(!this->nodes.empty())
        {
            auto* currNode = this->nodes.at(i);
            this->nodes.erase(this->nodes.begin());
            delete currNode;
        }
    }

    OrgChart::OrgChart(const OrgChart &other) {
        this->root = nullptr;
        for(auto* node: other.nodes)
        {
            if(other.root == node)
            {
                this->add_root(node->data);
            }
        }
        for(auto* node: other.nodes)
        {
            if(other.root != node)
            {
                this->add_sub(node->data,node->parent->data);
            }
        }


    }

    OrgChart &OrgChart::operator=(const OrgChart& other) {
        if(&other == this)
        {
            return *this;
        }
        for(auto* node: other.nodes)
        {
            if(other.root == node)
            {
                this->add_root(node->data);
            }
        }
        for(auto* node: other.nodes)
        {
            if(other.root != node)
            {
                this->add_sub(node->data,node->parent->data);
            }
        }
        return *this;
    }

    bool OrgChart::operator==(const OrgChart &other) {
        if(this->root != other.root)
        {
            return false;
        }
        for(auto* node: other.nodes)
        {
            for(auto* selfNode: this->nodes)
            {
                if(selfNode == node){
                    break;
                }
                return false;
            }
        }
        return true;
    }

    OrgChart::OrgChart(OrgChart &&other) noexcept {
        try{
            *this = other;
            other.root = nullptr;
            other.nodes.clear();
        }
        catch (std::exception& e)
        {
            std::cout << e.what();
        }

    }

    OrgChart &OrgChart::operator=(OrgChart &&other)  noexcept {
        try{
            *this = other;
            other.root = nullptr;
            other.nodes.clear();
            return *this;
        }
        catch (std::exception& e)
        {
            std::cout << e.what();
        }
        return *this;
    }

}
