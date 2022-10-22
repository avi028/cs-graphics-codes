
#include "cylinder.hpp"

namespace handle {
    /**
     * @brief handle will have 4 cylinders 2 rectangles. 
     * ---          ---
     *     \       /
     *      \ _ _ /
    */

    Cylinder * hanleTip;
    Cylinder * handleBar;
    Cylinder * join;
    Cylinder * jointop;

    csX75::HNode* root_node;
    csX75::HNode* curr_node;
    csX75::HNode* node1;
    csX75::HNode* node2;
    csX75::HNode* node3;

    void drawhandle();        
}