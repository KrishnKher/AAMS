#include "SeatMatrix.h"
using namespace std;

void SeatMatrix::addSeats(string dep,string category,unit seats){
    if(matrix.find(dep) != matrix.end() && matrix[dep].find(category) != matrix[dep].end()){
        matrix[dep][category] += seats;
    }
    else{
        std::cout<<"Given department or category does not exist in the seat matrix\n";
        exit(0);
    }
}

void SeatMatrix::deleteSeats(string dep,string category,unit seats){
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

SeatMatrix::SeatMatrix(map<string,map<string,uint>> matrix){
    this->matrix = matrix;
}
