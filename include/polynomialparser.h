#ifndef _POLYNOMIALPARSER_H_
#define _POLYNOMIALPARSER_H_

#define MINUS "-"
#define STAR "*"

typedef struct {
        std::string poly;
        int exp;
}PolyAndExp;



class PolynomialParser{

private:
	std::string polynomial;

public:
	PolynomialParser();
	PolynomialParser(std::string polynomial);
	
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
	std::vector<std::vector<int> > AllPolyTermsCoeffs(std::vector<std::string>& allvariables, std::vector<std::string>& polyterms);
	PolyAndExp SplitPolyInBracket();
	bool ValidPoly();
	int PolyExponent();
}


#endif
