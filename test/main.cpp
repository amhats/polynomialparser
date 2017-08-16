#include <iostream>
#include "PolynomialParser.h"

using namespace std;
int main(int argc, char** argv) {
    //if variables are x, y z, then x > y > z
    //if variables are x_1, x_2, y_1, then x_1 > x_2 > y_1
    //if variables are x1, x2, y1, then x1 > x2 > y1
    std::string temp = "-36060069696996960696969.44696969696969*x1^2 +  4*y1^4*x2^8";
    
    PolynomialParser p(temp);
    
    std::vector<std::string> out = p.getmAllPolyTerms();
    std::vector<std::string> var = p.getmAllPolyVariables();
    std::vector<std::vector<int> > exp = p.getmAllPolyTermsExponents();
    std::vector<std::vector<mpz_class> > coef = p.getmAllPolyTermsCoefficients();
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
    
    cout << "All the coefficients: " << endl;
    for(int i=0; i<coef.size(); i++){
        cout << "[ " ;
        for(int j=0; j<coef[i].size(); j++){
            cout << coef[i][j] << " ";
        }    
        cout << "]"<<endl;
    }
    
    
    string s = "-95959595949949599595959595050049499493939949394939949394939459.1232326565656565456545464565456454656546546456";
    
    std::istringstream iss(s);
    double f;
    mpq_class a;
    iss >> std::noskipws >> a; 
    cout << a << endl;
    
    
    
    return 0;
}


