#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include "Rule.h"

class Parser{
	public:
		//检查是否存在满足规则的前缀串
		static bool check(Rule &rule,const char *s){
			std::string str(s);
			try{
				rule.check(str.begin(),str.end());
			}catch(ErrFailed &e){
				return false;
			}
			return true;
		}
		static bool check(Rule &rule,std::string &s){
			try{
				rule.check(s.begin(),s.end());
			}catch(ErrFailed &e){
				return false;
			}
			return true;
		}
		//检查整个串是否全满足匹配规则
		static bool checkAll(Rule &rule,const char *s){
			std::string str(s);
			std::string::iterator itr;
			try{
				itr = rule.check(str.begin(),str.end());
			}catch(ErrFailed &e){
				return false;
			}
			if(itr == str.end())return true;
			return false;
		}
		static bool checkAll(Rule &rule,std::string &s){
			std::string::iterator itr;
			try{
				itr = rule.check(s.begin(),s.end());
			}catch(ErrFailed &e){
				return false;
			}
			if(itr == s.end())return true;
			return false;
		}
		//返回已经匹配的前缀串
		static std::string match(Rule &rule,const char *s){
			std::string str(s);
			std::string::iterator itr;
			try{
				itr = rule.check(str.begin(),str.end());
			}catch(ErrFailed &e){
				return std::string("");
			}
			return std::string(str.begin(),itr);
		}
		static std::string match(Rule &rule,std::string &s){
			std::string::iterator itr;
			try{
				itr = rule.check(s.begin(),s.end());
			}catch(ErrFailed &e){
				return std::string("");
			}
			return std::string(s.begin(),itr);
		}
	protected:
	private:
};

#endif
