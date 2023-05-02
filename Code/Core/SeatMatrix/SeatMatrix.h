#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class SeatMatrix {
    private: 
        map<string, map<string,uint> > matrix;
    protected:
    public:
        SeatMatrix(){};
        SeatMatrix(SeatMatrix& a);
        SeatMatrix(map<string,map<string,uint>> m);
        void addSeats(string dep,string category,uint seats);
        void deleteSeats(string dep,string category,uint seats);
        void printSeats();
        //void checkSystemHealth(shared_ptr<MetaSystemHandler>);
};