/**
Copyright <2017> <Amha Tsegaye>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef POLYNOMIALPARSER_H
#define POLYNOMIALPARSER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>
#include <gmpxx.h>
#include <gmp.h>



#define MINUS "-"
#define STAR "*"

typedef struct {
        std::string poly;
        int exp;
}PolyAndExp;

class PolynomialParser {

private:
	std::string polynomial;
    std::string mPoly;

    std::vector<std::string> mAllPolyTerms; 
    std::vector<std::string> mAllPolyVariables;
    std::vector<std::vector<int> > mAllPolyTermsExponents; 
    std::vector<std::vector<mpz_class> > mAllPolyTermsCoefficients;
    int mOuterExponent;
        
        
	
	bool is_digit_cpp98(const std::string &str);
	bool isMinus(const std::string &str, const std::string &str1);
	void remove_all_space(std::string &str);
	size_t findCharPosition(std::string &v, std::string s);
	std::string getSubString(std::string &s, int spos, int epos);
	std::string TermReorder(std::string &str);
	std::vector<std::string> SplitPolyToTerms(const std::string poly, std::string delim);
	std::vector<std::string> SimpleMultiDelimStringTokenizer(const std::string poly, std::string delim);
	std::vector<std::string> AllPolyVaraibles(std::vector<std::string>& allTerms);
	std::vector<std::vector<int> >  AllPolyTermsExponents(std::vector<std::string>& allvariables, std::vector<std::string>& polyterms);
	std::vector<std::vector<mpz_class> > AllPolyTermsCoeffs(std::vector<std::string>& allvariables, std::vector<std::string>& polyterms);
	PolyAndExp SplitPolyInBracket();
	bool ValidPoly();
	int PolyExponent();
        
    bool isFloat( std::string myString );

public:
	PolynomialParser();
	PolynomialParser(std::string poly);
        
    std::vector<std::string> getmAllPolyTerms();
    std::vector<std::string> getmAllPolyVariables();
    std::vector<std::vector<int> > getmAllPolyTermsExponents();
    std::vector<std::vector<mpz_class> > getmAllPolyTermsCoefficients();

        
};

#endif /* POLYNOMIALPARSER_H */




