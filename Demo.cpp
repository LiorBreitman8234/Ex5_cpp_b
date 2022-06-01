/**
 * Demo file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "Ex5_cpp_b/sources/OrgChart.hpp"
using namespace ariel;

int main() {
    OrgChart theAvengers;
    theAvengers.add_root("nick fury");
    theAvengers.add_sub("nick fury","iron man");
    theAvengers.add_sub("nick fury","Hulk");
    theAvengers.add_sub("nick fury","thor");
    theAvengers.add_sub("nick fury","Captain america");
    theAvengers.add_sub("nick fury","Hawkeye");
    theAvengers.add_sub("nick fury","Black widow");
    theAvengers.add_sub("iron man","spider man");
    theAvengers.add_sub("thor","jane foster");
    theAvengers.add_sub("Captain america","the falcon");
    theAvengers.add_sub("Captain america","The winter solider");
    theAvengers.add_sub("Hawkeye","Scarlet witch");
    theAvengers.add_sub("Hawkeye","QuickSilver");



    for(auto it = theAvengers.begin_level_order(); it != theAvengers.end_level_order();++it)
    {
        std::cout << (*it) << " ";
    }
    std::cout << endl;

    for(auto it = theAvengers.begin_preorder(); it != theAvengers.end_preorder();++it)
    {
        std::cout << (*it)<< " ";
    }
    std::cout << endl;


    for(auto it = theAvengers.begin_reverse_order(); it != theAvengers.reverse_order();++it)
    {
        std::cout << (*it)<< " ";
    }
    std::cout << endl;


    std::cout << theAvengers;






}
