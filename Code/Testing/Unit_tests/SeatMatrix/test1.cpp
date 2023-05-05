#include "../../../Core/SeatMatrix/SeatMatrix.h"
using namespace std;

int main(){
    map<string,map<string,uint>> matrix;
    matrix["hello"]["student"] = 1;
    SeatMatrix cm(matrix);
    SeatMatrix c = cm;
    c.printSeats();
    cm.printSeats();
    cm.addSeats("hello","student",2);
    cm.printSeats();
    cm.deleteSeats("hello","student",1);
    cm.printSeats();
}
