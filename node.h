#include <fstream>
#include <iostream>

using namespace std;

// Node for Heap Tree
class m_node;

// Node for Red-Black Tree
class r_node
{
    public :

    int rideNumber;
    int rideCost;
    int tripDuration;
    char color;
    r_node* left;
    r_node* right;
    r_node* parent;
    m_node* clone;

    r_node(int rideNumber,int rideCost,int tripDuration)
    {
        this->rideNumber = rideNumber;
        this->rideCost = rideCost;
        this->tripDuration = tripDuration;
        this->color = 'r';
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->clone = nullptr;
    } 
};

class m_node
{
    public :

    int rideNumber;
    int rideCost;
    int tripDuration;
    int index;
    r_node* clone;

    m_node(int rideNumber,int rideCost,int tripDuration)
    {
        this->rideNumber = rideNumber;
        this->rideCost = rideCost;
        this->tripDuration = tripDuration;
        this->index = -1;
        this->clone = nullptr;
    } 
};