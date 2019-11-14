#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "ArgumentManager.h"
using namespace std;

#define size 100

int LookUp[size][size];
//Dynamic String
class DynamicString {
public:

    DynamicString(int StringSize);
    string getElement(int indx);
    void addElement(string txt);
    void removeAll();

private:

    string *arr;
    int stringSize;
    int numOfElements;
};

//Dynamic String

DynamicString::DynamicString(int StringSize){

    if (StringSize < 1){
        stringSize = 1;
    }else{
        stringSize = StringSize;
    }

    numOfElements = 0;
    arr = new string[stringSize];
}

//Add Elements
void DynamicString::addElement(string txt){
    if (numOfElements == stringSize){
        int temp = stringSize;
        stringSize  = stringSize*2;
        string* newStr = new string[stringSize];
        for (int i = 0; i <temp; i++){
            newStr[i] = arr[i];
        }
        delete[] arr;
        arr = newStr;
        arr[numOfElements] = txt;
        numOfElements ++ ;
    }else{
        arr[numOfElements] = txt;
        numOfElements ++ ;
    }
    cout<<endl<<txt;
}


string DynamicString::getElement(int indx){

    return arr[indx];

}

void DynamicString::removeAll(){

    string *temp = new string[0];
    this->arr = temp;
    this->stringSize = 0;
    this->numOfElements = 0;
    delete [] temp;

}

int getLen(DynamicString* A, int);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "Invalid parameters" << std::endl;
        return -1;
    }

    int scount; //string counter

    ArgumentManager am(argc, argv);
    
    string infilename = am.get("input");// get the input filename

    string outfilename = am.get("output"); // get the output filename
    
    ifstream infile;

    infile.open(infilename);
    string line = "";
    // count no of lines in file
    while (getline(infile, line)){
        if (line != "") scount++;
    }

    infile.clear();
    infile.seekg(0, ios::beg);

    DynamicString ds(scount);

    cout<<endl<<"Input File Content: ";
    while (getline(infile, line))
    {
        if (line != ""){
            ds.addElement(line);
        }
    }

    infile.close();

    ofstream outfile; 
    outfile.open(outfilename);

    if (outfile.is_open())
    {
        outfile <<"Len: "<<getLen(&ds, scount)<<endl;
    }
    outfile.close();

    ds.removeAll();
    return 0;
}

string LCS(string X, string Y, int m, int n) //Longest common subsequence
{
    if (m == 0 || n == 0)
        return string("");

    if (X[m - 1] == Y[n - 1])
    {
        
        return LCS(X, Y, m - 1, n - 1) + X[m - 1];
    }
    if (LookUp[m - 1][n] > LookUp[m][n - 1])
        return LCS(X, Y, m - 1, n);
    else
        return LCS(X, Y, m, n - 1);
}

string calcSeqLen(string A, string B){
    int m = A.length();
    int n = B.length();
    
    string commonTxt;
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){            
            if (A[i - 1] == B[j - 1]){
                LookUp[i][j] = LookUp[i - 1][j - 1] + 1;
            }else{
                LookUp[i][j] = max(LookUp[i - 1][j], LookUp[i][j - 1] );
            }
        }
    }
    commonTxt = LCS (A,B,m,n);

    return commonTxt;
}

string calcSeqLen(string A, string B, string C){
    string temp = calcSeqLen(A, B);
    temp = calcSeqLen(temp, C);
    return temp;
}

string calcSeqLen(string A, string B, string C, string D){
    string temp = calcSeqLen(A, B);
    temp = calcSeqLen(temp, C);
    temp = calcSeqLen(temp, D);
    return temp;
}


int getLen(DynamicString* Str, int noOfLine){
    int len = 0;
    string LCS;
    switch (noOfLine) {
        case 1:
            break;

        case 2:{
            LCS = calcSeqLen(Str->getElement(0),Str->getElement(1));
            len = LCS.length();
            break;
        }
        case 3:{
            LCS = calcSeqLen(Str->getElement(0), Str->getElement(1), Str->getElement(2));
            len = LCS.length();
            break;
        }

        case 4:{
            LCS = calcSeqLen(Str->getElement(0), Str->getElement(1), Str->getElement(2), Str->getElement(3));
            len = LCS.length();
            break;
        }

        default:{
            break;
        }
    }
    cout<<endl<<endl<<"Longest Common Sequence: "<<endl<<LCS<<endl<<endl;
    return len;
}
