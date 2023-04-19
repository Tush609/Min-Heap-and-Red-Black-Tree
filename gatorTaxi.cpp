#include <string>

#include "RBT.h"

using namespace std;

int main(int argc, char **argv)
{
    string filename(argv[1]); // Dynamic File name from the termianl

    if (filename.substr(filename.size()-4,filename.size()).compare(".txt")) // Checks if the file name given is provided with ".txt." or not
    {
        filename = filename + ".txt";
    }
     
    int rideNumber; 
    int rideCost,tripDuration; 
    int new_tripDuration,low,high,count;
    m_node *tempm, *temp;
    r_node *tempr, *ride;
    bool tf;
    string line,operation,between,String;
    RBT r;

    fstream fin,fout;

    fin.open(filename, ios::in);
    fout.open("output_file.txt", ios::out);

    while (fin) // Runs until the end of file(eof)
    {
        getline(fin,line);
        string::iterator i = line.begin();
        count = 0;
        char ch = *i;
        operation = "";
        between = "";
        
        count = line.find('(');
        operation = line.substr(0,count);
        int firstComma = line.find(',',count+1);

        if (!operation.compare("Insert")) // Inserts in both the Trees
        {
            int firstComma = line.find(',',count+1);
            int secondComma = line.find(',',firstComma+1);
            int bracket = line.find(')',secondComma+1);

            rideNumber = stoi(line.substr(count+1, firstComma-count-1));
            rideCost = stoi(line.substr(firstComma+1, bracket-firstComma-1));
            tripDuration = stoi(line.substr(secondComma+1, line.length()-secondComma-2));

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
                fout << "Duplicate RideNumber";
                fin.close();
                fout.close();
                exit(0);
            }

        }

        else if (!operation.compare("GetNextRide")) // Find the Min Value from heap and deletes from both the Trees
        {
            temp = m.remove(0);
            if (temp == nullptr)
            {
                r.head = r.Enode;
                fout << "No active ride request\n";
            }
            else
            {
                String = "(" + to_string(temp->rideNumber) + "," +to_string(temp->rideCost) + "," + to_string(temp->tripDuration) + ")";
                fout << String << endl;
                r.Delete(temp->rideNumber);
            }     
        }

        else if (!operation.compare("CancelRide")) // Deletes the Ride Node from both the Trees
        {
            int bracket = line.find(')',count+1);
            rideNumber = stoi(line.substr(count+1, bracket-count-1));
            ride = r.search(rideNumber,r.head);
            if (ride != nullptr)
            {
                m.remove(ride->clone->index);
                r.Delete(ride->rideNumber);
            }
        }

        else if (!operation.compare("UpdateTrip")) // Updates the request with proper conditions
        {
            int firstComma = line.find(',',count+1);
            int bracket = line.find(')',firstComma+1);
            rideNumber = stoi(line.substr(count+1, firstComma-count-1));
            new_tripDuration = stoi(line.substr(firstComma+1, bracket-firstComma-1));            ride = r.search(rideNumber,r.head);
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
        }

        else if (!operation.compare("Print")) 
        {
            if (!(line[line.find(',')] == ',')) // Prints Single Node
            {
                int bracket = line.find(')',count+1);
                rideNumber = stoi(line.substr(count+1, bracket-count-1));
                ride = r.search(rideNumber,r.head);
                if (ride == nullptr)
                {
                    fout << "(0,0,0)\n";
                }
                else
                {
                    String = "(" + to_string(ride->rideNumber) + "," + to_string(ride->rideCost) + "," + to_string(ride->tripDuration) + ")";
                
                    fout << String << endl;
                }
            }
            else    // Prints all the Nodes between the given range
            {
                int firstComma = line.find(',',count+1);
                int bracket = line.find(')',firstComma+1);
                low = stoi(line.substr(count+1, firstComma-count-1));
                high = stoi(line.substr(firstComma+1, bracket-firstComma-1));
                between = r.outputbetween(r.head,low,high,between);
                if (!between.compare(""))
                {
                    fout << "(0,0,0)\n";
                }
                else
                {
                    fout << between << endl;
                }

            }
        }
    }

    fin.close();
    fout.close();
}