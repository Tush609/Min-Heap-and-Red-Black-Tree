#include "min_heap.h"

class RBT
{
    public:

    r_node* Enode;
    r_node *head;
    r_node *traverse;
    
    RBT()
    {
        Enode = new r_node(0,0,0);
        Enode->color = 'b';
        Enode->left = nullptr;
        Enode->right = nullptr;
        this->head = Enode;
    }

	// Function to perform left rotation on red-black tree.
    void RBLRotate(r_node *a) 
	{
		r_node* y = a->right;		
		a->right = y->left;			
		if (y->left != Enode) 
		{
			y->left->parent = a;	
		}
		y->parent = a->parent;
		if (a->parent == nullptr) 	
		{
			head = y;
		} 
		else if (a == a->parent->left) 		
		{
			a->parent->left = y;
		} 
		else 
		{
			a->parent->right = y;	
		}
		y->left = a;
		a->parent = y;
	}

	// Function to perform right rotation on red-black tree.
    void RBRRotate(r_node *a) 
	{
		r_node* y = a->left;
		a->left = y->right;
		if (y->right != Enode) 
		{
			y->right->parent = a;	
		}
		y->parent = a->parent;		
		if (a->parent == nullptr) 
		{
			head = y;
		} 
		else if (a == a->parent->right) 	
		{
			a->parent->right = y;
		} 
		else 
		{
			a->parent->left = y;
		}
		y->right = a;
		a->parent = y;			
	}

	// Fixes The Insert Anomolies
    void fixinsert(r_node *traverse)
    {
        r_node *uncle;			
        while(traverse->parent->color == 'r')		
        {
            if (traverse->parent == traverse->parent->parent->right) {
				uncle = traverse->parent->parent->left;
				if (uncle->color == 'r') {
					uncle->color = 'b';
					traverse->parent->color = 'b';
					traverse->parent->parent->color = 'r';
					traverse = traverse->parent->parent;
				} else {
					if (traverse == traverse->parent->left) {
						traverse = traverse->parent;
						RBRRotate(traverse);
					}
					traverse->parent->color = 'b';
					traverse->parent->parent->color = 'r';
					RBLRotate(traverse->parent->parent);
				}
			} else {
				uncle = traverse->parent->parent->right;

				if (uncle->color == 'r') {
					uncle->color = 'b';
					traverse->parent->color = 'b';
					traverse->parent->parent->color = 'r';
					traverse = traverse->parent->parent;	
				} else {
					if (traverse == traverse->parent->right) {
						traverse = traverse->parent;
						RBLRotate(traverse);
					}
					traverse->parent->color = 'b';
					traverse->parent->parent->color = 'r';
					RBRRotate(traverse->parent->parent);
				}
			}

            if (traverse == head)
            {
                break;
            }
        }
        head->color = 'b';
    }

	// Inserts Node into the Red Black Tree
    bool insert(r_node *temp)
    {
        if (head == Enode)
        {
            head = temp;
            head->parent = nullptr;
            head->left = Enode;
            head->right = Enode;
            head->color = 'b';
        }
        else
        {
            traverse = head;
            while (traverse!=Enode)
            {
                if (temp->rideNumber == traverse->rideNumber)
                {
                    return false;
                }

                if (temp->rideNumber > traverse->rideNumber)
                {
                    if (traverse->right == Enode)
                    {
                        temp->parent = traverse;
                        traverse->right = temp;
                        temp->left = temp->right = Enode;
                        fixinsert(temp);
                        break;
                    }
                    else
                    {
                        traverse = traverse->right;
                    }
                }
                else if (temp->rideNumber < traverse->rideNumber)
                {
                    if (traverse->left == Enode)
                    {
                        temp->parent = traverse;
                        traverse->left = temp;
                        temp->left = temp->right = Enode;
						fixinsert(temp);
                        break;
                    }
                    else
                    {
                        traverse = traverse->left;
                    }
                }
            }
        }
        return true;
    }

	//Searches the Node in the Reb-Black Tree
    r_node* search(int rno,r_node* traverse)
    {
        while (traverse!=Enode)
        {
            if (rno == traverse->rideNumber)
            {
                return traverse;
            }

            if (rno > traverse->rideNumber)
            {
                traverse = traverse->right;
            }
            else if (rno < traverse->rideNumber)
            {
                traverse = traverse->left;
            }
        }
		return nullptr;
    }

    void output(r_node *traverse)
    {
        if (traverse != Enode)
        {
            cout << "\nRide Number: " << traverse->rideNumber << " color : " << traverse->color;
            output(traverse->left);
            output(traverse->right);
        }
    }
    
	// Fixes Delete Anomolies
    void fixdelete(r_node* x) 
    {
		r_node* traverse;
		while (x != head && x->color == 'b') 
        {
			if (x == x->parent->left) 
            {
				traverse = x->parent->right;
				if (traverse->color == 'r') 
                {
					traverse->color = 'b';
					x->parent->color = 'r';
					RBLRotate(x->parent);
					traverse = x->parent->right;
				}

				if (traverse->left->color == 'b' && traverse->right->color == 'b') 
                {
					traverse->color = 'r';
					x = x->parent;
				} 
                else 
                {
					if (traverse->right->color == 'b') 
                    {
						traverse->left->color = 'b';
						traverse->color = 'r';
						RBRRotate(traverse);
						traverse = x->parent->right;
					} 
					traverse->color = x->parent->color;
					x->parent->color = 'b';
					traverse->right->color = 'b';
					RBLRotate(x->parent);
					x = head;
				}
			} 
            else 
            {
				traverse = x->parent->left;
				if (traverse->color == 'r') 
                {
					traverse->color = 'b';
					x->parent->color = 'r';
					RBRRotate(x->parent);
					traverse = x->parent->left;
				}

				if (traverse->left->color == 'b' && traverse->right->color == 'b') 
                {
					traverse->color = 'r';
					x = x->parent;
				} 
                else 
                {
					if (traverse->left->color == 'b') 
                    {
						traverse->right->color = 'b';
						traverse->color = 'r';
						RBLRotate(traverse);
						traverse = x->parent->left;
					} 
					traverse->color = x->parent->color;
					x->parent->color = 'b';
					traverse->left->color = 'b';
					RBRRotate(x->parent);
					x = head;
				}
			} 
		}
		x->color = 'b';
	}

	// Used to Join Adjacent Node to its parent
	void RBTplant(r_node* u, r_node* v)
    {
		if (u->parent == nullptr) 
        {
			head = v;
		} 
        else if (u == u->parent->left)
        {
			u->parent->left = v;
		} 
        else 
        {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	//Deletes the Node from the Red-Black Tree
	void Delete(int ridenumber) 
    {
		traverse = head;
		r_node* z = Enode;
		r_node *x, *y;
		while (traverse != Enode)
        {
			if (traverse->rideNumber == ridenumber) 
            {
				z = traverse;
			}

			if (traverse->rideNumber <= ridenumber) 
            {
				traverse = traverse->right;
			} 
            else 
            {
				traverse = traverse->left;
			}
		}

		if (z == Enode) 
        {
			return;
		} 

		y = z;

		int y_og_color = y->color;

		if (z->left == Enode) 
        {
			x = z->right;
			RBTplant(z, z->right);
		} 
        else if (z->right == Enode) 
        {
			x = z->left;
			RBTplant(z, z->left);
		} 
        else 
        {
			y = minimum(z->right);
			y_og_color = y->color;
			x = y->right;
			if (y->parent == z) 
            {
				x->parent = y;
			} 
            else 
            {
				RBTplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			RBTplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_og_color == 'b')
        {
			fixdelete(x);
		}
	}

	// Used to find the Leftmost minimum element
    r_node* minimum(r_node* traverse) 
    {
		while (traverse->left != Enode) 
        {
			traverse = traverse->left;
		}
		return traverse;
	}

	// Function to find element betweeen Low and High
	string outputbetween(r_node* traverse,int low, int high, string &between)
	{
		if (traverse == Enode)
		{
			return between;
		}

		if (traverse->rideNumber > low)
		{
			outputbetween(traverse->left,low,high,between);
		}

		if (traverse->rideNumber >= low && traverse->rideNumber <= high)
		{
			between = between + "(" + to_string(traverse->rideNumber) + "," + to_string(traverse->rideCost) + "," + to_string(traverse->tripDuration) + ")";
		}

		if (traverse->rideNumber < high)
		{
			outputbetween(traverse->right,low,high,between);
		}

		return between;
	}
}r; // Object of the <class> RBT