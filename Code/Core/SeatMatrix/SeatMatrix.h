#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class SeatMatrix {
    private: 
        map<string, map<string,uint32_t> > matrix;
    protected:
    public:
        SeatMatrix(){};
        SeatMatrix(const SeatMatrix& a);
        SeatMatrix(map<string,map<string,uint32_t>> m);
        uint32_t getSeats(string dep,string category);
        void addSeats(string dep,string category,uint32_t seats);
        void deleteSeats(string dep,string category,uint32_t seats);
        void printSeats();
        map<string,map<string,uint32_t>> getMatrix();
        //void checkSystemHealth(shared_ptr<MetaSystemHandler>);
};
