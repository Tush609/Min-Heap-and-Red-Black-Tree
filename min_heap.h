#include "node.h"

using namespace std;

class min_heap
{
    m_node *temp;
    m_node *queue[2000];
    int qp;

    public:

    // Constructor used to Assign the size of the heap
    min_heap()
    {
        this->qp = 0;
        this->queue[2000] = {nullptr};
    }

    // Heapify Algorithm used to send the Smallest node from bottom to top
    void heapify(int i)
    {
        while (i!=0 && queue[i]->rideCost <= queue[(i-1)/2]->rideCost)
        {
            if (queue[i]->rideCost == queue[(i-1)/2]->rideCost && queue[i]->tripDuration < queue[(i-1)/2]->tripDuration)
            {
                queue[i]->index = (i-1)/2;
                queue[(i-1)/2]->index = i;
                swap(queue[i],queue[(i-1)/2]);
            }
            else if (queue[i]->rideCost < queue[(i-1)/2]->rideCost)
            {
                queue[i]->index = (i-1)/2;
                queue[(i-1)/2]->index = i;
                swap(queue[i],queue[(i-1)/2]);
            }
            
            i = (i-1)/2;
        }
    }

    // Heapify Algorithm used to send the Biggest node from any location to its best place
    void rev_heapify(int i)
    {
        int j;
        while (true)
        {
            if (queue[(i*2)+1] == nullptr && queue[(i*2)+2] == nullptr)
            {
                break;
            }

            if (queue[(i*2)+1] == nullptr)
            {
                j = (i*2)+2; 
            }
            else if (queue[(i*2)+2] == nullptr)
            {
                j = (i*2)+1;
            }
            else
            {
                if (queue[(i*2)+1]->rideCost > queue[(i*2)+2]->rideCost)
                {
                    j = (i*2)+2;
                }
                else if (queue[(i*2)+1]->rideCost < queue[(i*2)+2]->rideCost)
                {
                    j = (i*2)+1;
                }
                else
                {
                    if (queue[(i*2)+1]->tripDuration > queue[(i*2)+2]->tripDuration)
                    {
                        j = (i*2)+2;
                    }
                    else
                    {
                        j = (i*2)+1;
                    }
                }
            }

            if (queue[i]->rideCost >= queue[j]->rideCost)
            {
                if (queue[i]->rideCost == queue[j]->rideCost && queue[i]->tripDuration > queue[j]->tripDuration)
                {
                    queue[i]->index = j;
                    queue[j]->index = i;
                    swap(queue[i],queue[j]);
                }
                else if (queue[i]->rideCost > queue[j]->rideCost)
                {
                    queue[i]->index = j;
                    queue[j]->index = i;
                    swap(queue[i],queue[j]);
                }
            }
            i=j;
        }
    }

    // Inserts the Node in the Heap Tree
    void insert(m_node* temp)
    {
        queue[qp] = temp;
        queue[qp]->index = qp;
        heapify(qp);
        
        qp++;
    }

    // Remove the current element whose index is provided
    m_node* remove(int i)
    {
        if (qp == 0)
        {
            return nullptr;
        }
        m_node* min = queue[i];
        queue[i] = queue[qp-1];
        queue[i]->index = i;
        queue[qp-1] = nullptr;
        qp--;
        rev_heapify(i);
        return min;
    }

    void output()
    {
        int qpt = 0;
        while (queue[qpt] != nullptr)
        {
            cout << "\nRide Number - " << queue[qpt]->rideNumber 
                 << "\nRide Cost - " << queue[qpt]->rideCost
                 << "\nTrip Duration - " << queue[qpt]->tripDuration 
                 << "\nIndex - " << queue[qpt]->index << endl;
            qpt++;
        }
    }
}m; // Object of the <class> min_heap