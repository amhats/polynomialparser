PolynomialParser::PolynomialParser(){
	this.polynomial = " ";
}

PolynomialParser::PolynomialParser(std::string polynomial){
	this.polynomial = polynomial;
}

/**
 * This helper function check if a digit is numeric. Compatable with c++98 compiler.
 *
 * @param str : string value of number or ... .
 * @return True if number else false.
 */
bool PolynomialParser::is_digit_cpp98(const std::string &str)
{
    unsigned int i =0;
    std::locale loc;
    for(i=0; i<str.length(); i++)
    {
        if(i==0 && str.length()>1 && str[i]=='-')
        {
            continue;
        }
        if(!std::isdigit(str[i], loc))
            return false;
    }
    return true;
}

/**
 * This helper function compare c++ strings.
 * @param str : string to compare
 * @param str1 : second string to compare
 * @return 0 if match else non zero value.
 */
bool PolynomialParser::isMinus(const std::string &str, const std::string &str1)
{
    return !str.compare(str1);
}

/**
 * This helper function modifies a string by removing all the space.
 *
 * @param str string to modifiy.
 */
void PolynomialParser::remove_all_space(std::string &str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

/**
 * This helper function return the exact position of a character in a string.
 *
 * @param v String to search the character.
 * @param s String format of the character to search.
 * @return numeric position of the character in the string.
 */
size_t SparseMultivariateRationalPolynomial::findCharPosition(std::string &v, std::string s)
{
    size_t it = v.find(s);
    if(it != std::string::npos)
        return it;
    else
        return -1;
}

/**
 * This helper function return a substring from a string.
 *
 * @param s :The original string where the substring is extracted from.
 * @param spos : Starting position.
 * @param epos : ending position.
 * @return  Substring of the original string.
 */
std::string PolynomialParser::getSubString(std::string &s, int spos, int epos)
{
    return (s.substr(spos, epos));
}

/**
 * The helper function rearrange a polynomial term by putting the coefficient
 * to the front and followed by the rest of the term components.
 * Example: -x11^4*(56*x12^3) return -56*x11^4*x12^3.
 *
 * @param str string polynomial term.
 * @return rearrange string polynomial term.
 */
std::string PolynomialParser::TermReorder(std::string &str)
{
    //term contains bracket , split it
    std::vector<std::string> ret = SimpleMultiDelimStringTokenizer(str, "()");
    int tempcoeff = 1;              // hold the coeff of the term by collecting all the numbers within the bracket
    std::string finalString = "";   // after all the reordering done everything concatinated to this string
    std::locale loc;                // used in std::isdigit

    std::vector<std::string>::iterator it;      //iterator to loop through the splitted tokens
    // remove any "*" at the beginning , ending or if exists by itself.
    for(it= ret.begin(); it<ret.end(); it++)
    {
        std::string stemp = *it;

        if(stemp=="*")
        {
            ret.erase(it);  // by itself
        }
        else if(findCharPosition(stemp, "*")==0)
        {
            *it = getSubString(stemp, 1, stemp.length());   // at beginning
        }
        else if(findCharPosition(stemp, "*")==(stemp.length()-1))
        {
            *it = getSubString(stemp, 0, stemp.length()-1); // at the end of the term
        }
    }
    for(it= ret.begin(); it<ret.end(); it++)
    {
        std::string stemp = *it;
        // not one char, 1st char is '-' and 1st char is not digit, coeff is -1 and
        // '-' sign is removed from the token
        if(stemp.length()>1 && stemp[0]=='-' && !is_digit_cpp98(std::string(1, stemp[1])))
        {
            tempcoeff *= -1;
            *it = getSubString(stemp, 1, stemp.length());
        }
        // token start with digit strings, extract those digit
        // convert them and multply them to the tempcoeff temporary storage variable
        // then adjust the token  so it only contain the substring after the "*" sign.
        else if(stemp[0]!='-' && std::isdigit(stemp[0], loc))
        {
            int tempint;
            int pos = findCharPosition(stemp, "*");
            std::string tempstring = getSubString(stemp, 0, pos);
            std::stringstream ss(tempstring);
            ss >> tempint;
            tempcoeff = tempcoeff * tempint;
            *it = getSubString(stemp, pos+1, stemp.length());
        }
        else if(stemp[0]=='-' && std::isdigit(stemp[1], loc))
        {
            int tempint;
            int pos = findCharPosition(stemp, "*");
            std::string tempstring = getSubString(stemp, 0, pos);
            std::stringstream ss(tempstring);
            ss >> tempint;
            tempcoeff = tempcoeff * tempint;
            *it = getSubString(stemp, pos+1, stemp.length());
        }
        else if(stemp.size()==1 && stemp[0]=='-')
        {
            tempcoeff = tempcoeff * -1;
            //ret.erase(it);
            //*it=getSubString(stemp, 3, stemp.length()-1);
        }
        else if(findCharPosition(stemp, "*")>1 && is_digit_cpp98(getSubString(stemp, findCharPosition(stemp, "*")+1, stemp.length())))
        {
            int tempint;
            int pos = findCharPosition(stemp, "*");
            std::string tempstring = getSubString(stemp, findCharPosition(stemp, "*")+1, stemp.length());
            std::stringstream ss(tempstring);
            ss >> tempint;
            tempcoeff = tempcoeff * tempint;
            *it = getSubString(stemp, 0, pos);
        }
    }
    std::ostringstream oss;
    oss << tempcoeff;
    finalString += oss.str();
    for(it= ret.begin(); it<ret.end(); it++)
    {
        std::string stemp = *it;
        finalString+="*";
        finalString+=stemp;
    }
    return finalString;
}


std::vector<std::string> PolynomialParser::SplitPolyToTerms(const std::string poly, std::string delim)
{
     //PrintToConsole(poly);
    std::vector<std::string> tokens;
    std::vector<std::string>::iterator tokenit;
    std::size_t prev_pos = 0;
    std::size_t cur_pos;
    std::size_t prev_pos_temp = 0;

    while((cur_pos = poly.find_first_of(delim, prev_pos)) != std::string::npos)
    {
        if(poly[cur_pos-1]!='(')
        {
            if((cur_pos > prev_pos_temp) )
            {
                if(prev_pos != 0  && strncmp(&poly.at(prev_pos_temp-1), MINUS, 1) == 0)
                    tokens.push_back(poly.substr(prev_pos_temp-1, cur_pos-prev_pos_temp+1));
                else
                    tokens.push_back(poly.substr(prev_pos_temp, cur_pos-prev_pos_temp));
            }
            prev_pos_temp = cur_pos+1;
        }

        prev_pos = cur_pos+1;
    }

    if(prev_pos_temp < poly.length())
    {
        if(prev_pos_temp!=0 && strncmp(&poly.at(prev_pos_temp-1), MINUS, 1) == 0 )
            tokens.push_back(poly.substr(prev_pos_temp-1, std::string::npos));
        else
            tokens.push_back(poly.substr(prev_pos_temp, std::string::npos));
    }

    for(tokenit=tokens.begin(); tokenit<tokens.end(); tokenit++)
    {
        std::string tempstring = *tokenit;
        if(findCharPosition(tempstring, "(")!=-1 && findCharPosition(tempstring, ")")!=-1)
        {
            *tokenit = TermReorder(tempstring);
        }
    }

    return tokens;
}

std::vector<std::string> PolynomialParser::SimpleMultiDelimStringTokenizer(const std::string poly, std::string delim)
{
    std::vector<std::string> tokens;
    std::size_t prev_pos = 0;
    std::size_t cur_pos;

    while((cur_pos = poly.find_first_of(delim, prev_pos)) != std::string::npos)
    {
        if((cur_pos > prev_pos) )
        {
            std::string stemp = poly.substr(prev_pos, cur_pos-prev_pos);
            remove_all_space(stemp);
            tokens.push_back(stemp);
        }
        prev_pos = cur_pos+1;
    }

    if(prev_pos < poly.length())
    {
        std::string stemp = poly.substr(prev_pos, std::string::npos);
        remove_all_space(stemp);
        tokens.push_back(stemp);
    }

    return tokens;
}

std::vector<std::string> PolynomialParser::AllPolyVaraibles(std::vector<std::string>& allTerms)
{
    std::vector<std::string> vars(0);

    std::vector<std::string>::iterator iterm(0);
    for( iterm=allTerms.begin(); iterm<allTerms.end(); iterm++)
    {

        std::vector<std::string> r = SimpleMultiDelimStringTokenizer(*iterm, "-*^()");

        std::vector<std::string>::iterator it(0);
        for( it=r.begin(); it<r.end(); it++)
        {
            std::string temp = *it;
            remove_all_space(temp); // clean unnecessary space eg.-yyy when tokenized by "-" return " yyy" and !="yyy"
            if(r.size() == 1)   //term split result is one, meaning no "*^", its is either eg.5x, x or -7y
            {
                    if( (!is_digit_cpp98(temp)) && (std::find(vars.begin(), vars.end(), temp) == vars.end()) )
                    {
                        vars.push_back(temp/*ctos*/);
                    }
            }
            else if( (!is_digit_cpp98(temp)) && (std::find(vars.begin(), vars.end(), temp) == vars.end()) )
            {
                vars.push_back(temp);
            }
        }
    }
    std::sort(vars.begin(), vars.end());

    return vars;
}


std::vector<std::vector<int> >  PolynomialParser::AllPolyTermsExponents(std::vector<std::string>& allvariables, std::vector<std::string>& polyterms)
{
    std::vector<std::vector<int> > exponent(polyterms.size(), std::vector<int>(0));

    for(unsigned int i=0; i<polyterms.size(); i++)
    {
        std::vector<std::string> termtokenized = SimpleMultiDelimStringTokenizer(polyterms[i], "^*");
        std::vector<std::string>::iterator ivars;
        for( ivars=allvariables.begin(); ivars<allvariables.end(); ivars++)
        {

            unsigned int position;
            //check if length of string is one, same for the second else if
            //if(isMinus(std::string(1, termtokenized[0][0]), MINUS) && std::isalpha(termtokenized[0][1]))
            if(isMinus(std::string(1, termtokenized[0][0]), MINUS) && !is_digit_cpp98(termtokenized[0].substr(1, termtokenized[0].length())))
            {
                //termtokenized[0] = termtokenized[0][1];
                termtokenized[0] = termtokenized[0].substr(1, termtokenized[0].length());
                position = std::find(termtokenized.begin(), termtokenized.end(), *ivars) - termtokenized.begin();
            }
            //else if(isMinus(std::string(1, termtokenized[0][0]), MINUS) && std::isdigit(termtokenized[0][1]) )
            else if(isMinus(std::string(1, termtokenized[0][0]), MINUS) && is_digit_cpp98(termtokenized[0].substr(1, termtokenized[0].length())))
            {
                //termtokenized[0] = termtokenized[0][2]; // remove the '-' find position of variable in the token
                termtokenized[0] = termtokenized[0].substr(2, termtokenized[0].length());
                position = std::find(termtokenized.begin(), termtokenized.end(), *ivars) - termtokenized.begin();
            }
            else
            {
                position = std::find(termtokenized.begin(), termtokenized.end(), *ivars) - termtokenized.begin();
            }
            if(position < termtokenized.size())
            {
                if((position == termtokenized.size()-1) || !is_digit_cpp98(termtokenized[position+1])/*(std::isalpha(*termtokenized.at(position+1).c_str()))*/)
                {
                    exponent[i].push_back(1);
                }
                else
                {
                    exponent[i].push_back(std::atoi(termtokenized.at(position+1).c_str()));
                }
            }
            else if(position == termtokenized.size())
            {
                exponent[i].push_back(0);
            }
        }
    }

    return exponent;
}

std::vector<std::vector<int> > PolynomialParser::AllPolyTermsCoeffs(std::vector<std::string>& allvariables, std::vector<std::string>& polyterms)
{
    // contain all the coeffs
    std::vector<std::vector<int> > coeff(polyterms.size(), std::vector<int>(0));

    // start with the first poly term that is provided in the argument
    for(unsigned int i=0; i<polyterms.size(); i++)
    {
        // split the term based the given delimeter and store them in a container
        std::vector<std::string> termtokenized = SimpleMultiDelimStringTokenizer(polyterms[i], "^*");
            // first string is a minus sign by itself and second string a string made of alphabets
            if(isMinus(std::string(1, termtokenized[0][0]), MINUS) && !is_digit_cpp98(termtokenized[0].substr(1, termtokenized[0].length())))
            {
                coeff[i].push_back(-1);
            }
            // first string a string made of alphabets
            else if((termtokenized.size()==1) && !is_digit_cpp98(termtokenized[0]))
            {
                coeff[i].push_back(1);
            }
            // termtokenized is not size=1 and first char is alpha
            else if(!is_digit_cpp98(termtokenized[0]))
            {
                coeff[i].push_back(1);
            }
            else if(isMinus(std::string(1, termtokenized[0][0]), MINUS) && !is_digit_cpp98(termtokenized[0].substr(1, termtokenized[0].length())))
            {
                coeff[i].push_back(-1);
            }
            // or termtokenizer is in the form -8*x^8 or 9*y^7 and so....
            else
            {
                int tempint;
                std::string tempstring;
                remove_all_space(termtokenized[0]);
                tempstring = termtokenized[0];
                std::stringstream(tempstring) >> tempint;
                coeff[i].push_back(tempint);
            }
    }

    return coeff;
}

PolyAndExp PolynomialParser::SplitPolyInBracket()
{
    /*potental bug in this function, if for example
      f = (x^5+y-(x^6*5)+z^3)^4 is given, the function
      will split it into 3 part based on the given delimeters, "()".
      so not recommanded to nest bracket if a polynomial
      has an outer bracket.

    */
  PolyAndExp retVal;
  std::vector<std::string> vals(0);
  if(mPoly.at(0) == '(')
  {
    vals = SimpleMultiDelimStringTokenizer(mPoly, "()");
    vals[1]= getSubString(vals[1], 1, vals[1].length()); //remove the carrot sign
  }
  else
  {
    vals.push_back(mPoly);
  }
    // the returned token contain bracket and carrot sign or exponent
    if((ValidPoly()) && (mPoly.find("(") != std::string::npos) && (mPoly.find(")") != std::string::npos) && (vals.size() == 2))
    {

        retVal.exp = std::atoi(vals.at(1).c_str());
        retVal.poly = vals.at(0);

        return retVal;
    }
    // the return token only contain brakets so set the exponent to 1
    else if((ValidPoly()) && (mPoly.find("(") != std::string::npos) && (mPoly.find(")") != std::string::npos))
    {
        retVal.exp = 1;
        retVal.poly = vals.at(0);

        return retVal;
    }
    // no bracket but valid poly
    else if(ValidPoly())
    {
        retVal.exp = 1;
        retVal.poly = mPoly;

        return retVal;
    }
    // invalid polynomial
    else
    {
        std::cout << "Invalid Polynomial Format ! " << std::endl;
        retVal.exp = -1;
        retVal.poly = " ";
        return retVal;
    }
}


bool PolynomialParser::ValidPoly()
{
    if(mPoly[0] == '*')
        return false;
    else if(mPoly[0] == '+')
        return false;
    else if(mPoly.find("((") != std::string::npos)
        return false;
    else if(mPoly.find("))") != std::string::npos)
        return false;
    else if(mPoly.find("++") != std::string::npos)
        return false;
    else if(mPoly.find("--") != std::string::npos)
        return false;
    else if(mPoly.find("**") != std::string::npos)
        return false;
    else if(mPoly[mPoly.length()-1] == '^')
        return false;
    else
        return true;
}



int PolynomialParser::PolyExponent()
{
    PolyAndExp exp = SplitPolyInBracket();
    return exp.exp;
}


