#include <conio.h>
#include <cstring>
#include <string>
#include "RBT.h"

using namespace std;

int main()
{
    int rideNumber,rno,num; 
    int rideCost,tripDuration; 
    int new_tripDuration,low,high,count;
    m_node *tempm, *temp;
    r_node *tempr, *ride;
    bool tf;
    string line,operation,between,String;
    RBT r;

    while (true)
    {
        cout << "\n1. Insert\n"
             << "2. Get Next Ride\n"
             << "3. Cancel Ride\n"
             << "4. Update Ride\n"
             << "5. Print All\n"
             << "6. Print Ride\n"
             << "7. Print Between\n"
             << "8. Exit\n"
             << "\n Enter The Number of Operation : ";

        cin >> num;

        

        switch (num)
        {
            case 1:
                cout << "Enter The rideNumber : ";
                cin >> rideNumber;
                cout << "Enter the rideCost : ";
                cin >> rideCost;
                cout << "Enter the Trip Duration : ";
                cin >> tripDuration;
                tempm = new m_node(rideNumber,rideCost,tripDuration);
                tempr = new r_node(rideNumber,rideCost,tripDuration);
                tempm->clone = tempr;
                tempr->clone = tempm;
                tf = r.insert(tempr);
                if (tf)
                {
                    m.insert(tempm);
                }
                else
                {
                    cout << "\nDuplicate RideNumber\n";
                    exit(0);
                }
                break;

        case 2:
            temp = m.remove(0);
            if (temp == nullptr)
            {
                cout << "\nNo active ride request\n";
            }
            else
            {
                r.Delete(temp->rideNumber);
                cout << "\nRide Number : " << temp->rideNumber
                     << "\nRide Cost : " << temp->rideCost
                     << "\nTrip Duration : " << temp->tripDuration << endl;
            }     
            break;
        
        case 3:
            cout << "Enter the Ride Number : ";
            cin >> rno;
            ride = r.search(rno,r.head);
            if (ride != nullptr)
            {
                m.remove(ride->clone->index);
                r.Delete(ride->rideNumber);
            }
            break;

        case 4:
            cout << "Enter the Ride Number : ";
            cin >> rno;
            cout << "Enter the new Trip Duration : ";
            cin >> new_tripDuration;
            ride = r.search(rno,r.head);
            if (ride->tripDuration > new_tripDuration)
            {
                ride->tripDuration = new_tripDuration;
                ride->clone->tripDuration = new_tripDuration;
                m.heapify(ride->clone->index);
            }
            else if (new_tripDuration > ride->tripDuration && new_tripDuration <= 2*ride->tripDuration )
            {
                ride->tripDuration = ride->clone->tripDuration = new_tripDuration;
                ride->rideCost = ride->clone->rideCost += 10;
                m.rev_heapify(ride->clone->index);
            }
            else
            {
                m.remove(ride->clone->index);
                r.Delete(ride->rideNumber);
            }
            break;
        
        case 5:
            m.output();
            r.output(r.head);
            break;

        case 6:
            cout << "Enter the Ride Number : ";
            cin >> rno;
            ride = r.search(rno,r.head);
            if (ride == nullptr)
            {
                cout << "\nFailed to find the RideNumber\n";
            }
            else
            {
                cout << "\nRide Number : " << ride->rideNumber
                     << "\nRide Cost : " << ride->rideCost
                     << "\nTrip Duration : " << ride->tripDuration << endl;
            }
            break;
        
        case 7:
            cout << "Enter the lower range : ";
            cin >> low;
            cout << "Enter the upper range : ";
            cin >> high;
            r.outputbetween(r.head,low,high,between);
            break;
        
        case 8:
            exit(0);
            break;

        default:
            cout << "\nSelect a suitable Option !!\n";
            break;
        }
    }
}