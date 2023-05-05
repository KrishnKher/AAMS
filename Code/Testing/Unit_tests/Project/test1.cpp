#include "../../../Core/Project/Project.h"
using namespace std;

int main(){

    map<string,map<string,uint32_t>> matrix;
    matrix["CSE"]["GEN"] = 1;
    matrix["CSE"]["OBC"] = 1;
    matrix["CSE"]["SC"] = 1;
    matrix["CSE"]["ST"] = 1;

    matrix["AI"]["GEN"] = 1;
    matrix["AI"]["OBC"] = 1;
    matrix["AI"]["SC"] = 1;
    matrix["AI"]["ST"] = 1;

    matrix["EE"]["GEN"] = 1;
    matrix["EE"]["OBC"] = 1;
    matrix["EE"]["SC"] = 1;
    matrix["EE"]["ST"] = 1;

    matrix["MnC"]["GEN"] = 1;
    matrix["MnC"]["OBC"] = 1;
    matrix["MnC"]["SC"] = 1;
    matrix["MnC"]["ST"] = 1;

    matrix["BM"]["GEN"] = 1;
    matrix["BM"]["OBC"] = 1;
    matrix["BM"]["SC"] = 1;
    matrix["BM"]["ST"] = 1;

    matrix["CE"]["GEN"] = 1;
    matrix["CE"]["OBC"] = 1;
    matrix["CE"]["SC"] = 1;
    matrix["CE"]["ST"] = 1;

    matrix["CH"]["GEN"] = 1;
    matrix["CH"]["OBC"] = 1;
    matrix["CH"]["SC"] = 1;
    matrix["CH"]["ST"] = 1;
    
    matrix["MSME"]["GEN"] = 1;
    matrix["MSME"]["OBC"] = 1;
    matrix["MSME"]["SC"] = 1;
    matrix["MSME"]["ST"] = 1;

    Project::Project p;
    string basePath  = "/home/sujeeth/project_graph/SWE/modCOAP.csv";
    p.setBaseFileSeatMatrix(basePath,matrix);

    // first round
    p.sortData();

    p.printCurrState();

    p.addRound();

    // round two
    string coapPath1 = "/home/sujeeth/project_graph/SWE/COAP_resp.csv"; 
    p.sortData(coapPath1);

    p.printCurrState(); 

    p.addRound();

    // round three
    string coapPath2 = "/home/sujeeth/project_graph/SWE/COAP_resp_2.csv";
    p.sortData(coapPath2);

    p.printCurrState();

    return 0;
}
