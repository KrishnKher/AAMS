#include <iostream>
#include <bits/stdc++.h>
using namespace std;

namespace Project{
class Project {
    private: 
        Rule currRule;
        uint currRoundState;
        vector<string> filePaths;
        SeatMatrix currSeatMatrix;
        //vector<shared_ptr<UIObservers>> uiObservers; 
    protected:
    public:
        void sort();
        // checkSystemHealth(shared_ptr<MetaSystemHandler>);

};

}