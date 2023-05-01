#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class SeatMatrix {
    private: 
        map<string, map<string,uint> > matrix;
    protected:
    public:
        SeatMatrix(map<string,map<string,uint>> matrix);
        void addSeats(string dep,string category,unit seats);
        void deleteSeats(string dep,string category,unit seats);
        //void checkSystemHealth(shared_ptr<MetaSystemHandler>);
};