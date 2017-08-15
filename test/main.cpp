#include <iostream>
#include "PolynomialParser.h"

using namespace std;
int main(int argc, char** argv) {
    //if variables are x, y z, then x > y > z
    //if variables are x_1, x_2, y_1, then x_1 > x_2 > y_1
    //if variables are x1, x2, y1, then x1 > x2 > y1
    std::string temp = "3*x1^2 +   2*y1^4*x2^8";
    
    PolynomialParser p(temp);
    
    std::vector<std::string> out = p.getmAllPolyTerms();
    std::vector<std::string> var = p.getmAllPolyVariables();
    std::vector<std::vector<int> > exp = p.getmAllPolyTermsExponents();
    std::vector<std::vector<int> > coef = p.getmAllPolyTermsCoefficients();
    std::vector<std::string>::iterator it;
    
    cout << "All the terms: " << endl;
    for(it = out.begin(); it!=out.end(); ++it){
        cout << *it << endl;
    }
    
    cout << "All the variables: " << endl;
    for(it = var.begin(); it!=var.end(); ++it){
        cout << *it << endl;
    }
    
    cout << "All the exponents: " << endl;
    for(int i=0; i<exp.size(); i++){
        cout << "[ " ;
        for(int j=0; j<exp[i].size(); j++){
            cout << exp[i][j] << " ";
        }    
        cout << "]"<<endl;
    }
    
    cout << "All the exponents: " << endl;
    for(int i=0; i<coef.size(); i++){
        cout << "[ " ;
        for(int j=0; j<coef[i].size(); j++){
            cout << coef[i][j] << " ";
        }    
        cout << "]"<<endl;
    }
    
    
    return 0;
}

