#include "SeatMatrix.h"
using namespace std;

void SeatMatrix::addSeats(string dep,string category,uint32_t seats){
    if(matrix.find(dep) != matrix.end() && matrix[dep].find(category) != matrix[dep].end()){
        matrix[dep][category] += seats;
    }
    else{
        std::cout<<"Given department or category does not exist in the seat matrix\n";
        exit(0);
    }
}

void SeatMatrix::deleteSeats(string dep,string category,uint32_t seats){
    if(matrix.find(dep) != matrix.end() && matrix[dep].find(category) != matrix[dep].end()){
        if(matrix[dep][category] < seats){
            std::cout<<"Cannot perform this operation as there are not enough seats in the seat matrix to assign\n";
        }
        else
            matrix[dep][category] -= seats;
    }
    else{
        std::cout<<"Given department or category does not exist in the seat matrix\n";
        exit(0);
    }
}

map<string,map<string,uint>> SeatMatrix::getMatrix(){
    return matrix;
}

SeatMatrix::SeatMatrix(map<string,map<string,uint32_t>> m){
    this->matrix = m;
}

SeatMatrix::SeatMatrix(const SeatMatrix& a){
    this->matrix = a.matrix;
}

void SeatMatrix::printSeats(){
    for(auto dep=matrix.begin();dep!=matrix.end();dep++){
        for(auto category=matrix[dep->first].begin();category!=matrix[dep->first].end();category++){
            cout<<"Department: "<<dep->first<<"\t"<<"Category: "<<category->first<<"\t"<<"Seats: "<<category->second<<endl;
        }
    }
}

// int main(){
//     map<string,map<string,uint>> matrix;
//     matrix["hello"]["student"] = 1;
//     SeatMatrix cm(matrix);
//     SeatMatrix c = cm;
//     c.printSeats();
//     cm.printSeats();
//     cm.addSeats("hello","student",2);
//     cm.printSeats();
//     cm.deleteSeats("hello","student",1);
//     cm.printSeats();
// }
