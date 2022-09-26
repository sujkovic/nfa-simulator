#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <iostream>
#include <sstream>

static const char *WHITESPACE = " \t\n\r";
static const char *UNEXPECTED_ARGS = "unexpected arguments";
static const char *MISSING_ARGS = "missing arguments";

class Parser {
   public:
      Parser(std::string line) : operation(""), arg1(""), arg2(""),
                                 arg3(""), arg4("") {
	 num_args = 0;
         std::stringstream is;	       
         trim_whitespace(line);
         is.str(line);
	 if (is >> operation)
            if ((is >> arg1) && (++num_args))
               if ((is >> arg2) && (++num_args))
                  if ((is >> arg3) && (++num_args)) {
                     getline(is, arg4);
                     arg4.erase(0, arg4.find_first_not_of(WHITESPACE));
		     if (!arg4.empty()) 
		        ++num_args;
                  }
      }
      unsigned numArgs() const {return num_args;};
      std::string getOperation() {return operation;};
      std::string getArg1() const {return arg1;};
      std::string getArg2() const {return arg2;};
      std::string getArg3() const {return arg3;};
      std::string getArg4() const {return arg4;};
      
      static std::string splitFirst(std::string &s) {
         s.erase(0, s.find_first_not_of(WHITESPACE));
         std::string first;
         std::stringstream is(s);
         is >> first;
         s.erase(0, s.find_first_of(WHITESPACE));
	 return first; 
      }

      static void trim_whitespace(std::string &s) {
         s.erase(0, s.find_first_not_of(WHITESPACE));
         s.erase(s.find_last_not_of(WHITESPACE) + 1);
      }

      static bool isInteger(const std::string &str) {
         for (const char &c : str)
            if (!std::isdigit(c)) 
	       return false;
         return true;
      }

   private:
      unsigned num_args;
      std::string operation;
      std::string arg1;
      std::string arg2;
      std::string arg3;
      std::string arg4;
};

#endif
