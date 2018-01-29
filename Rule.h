#ifndef _RULE_H_
#define _RULE_H_

#include <set>
#include <list>
#include <string>
#include <vector>
#include <exception>

class ErrFailed:public std::exception{
	public:
		const char *what()const noexcept{
			return "Cannot match!";
		}
	protected:
	private:
};

class Rule{
	public:
		Rule(){}
		
		inline void addRule(Rule &r1){
			m_rules.push_back(std::vector<Rule*>());
			m_rules.rbegin()->push_back(&r1);
		}
		inline void addRule(Rule &r1,Rule &r2){
			m_rules.push_back(std::vector<Rule*>());
			m_rules.rbegin()->push_back(&r1);
			m_rules.rbegin()->push_back(&r2);
		}
		inline void addRule(Rule &r1,Rule &r2,Rule &r3){
			m_rules.push_back(std::vector<Rule*>());
			m_rules.rbegin()->push_back(&r1);
			m_rules.rbegin()->push_back(&r2);
			m_rules.rbegin()->push_back(&r3);
		}
		inline void addRule(Rule &r1,Rule &r2,Rule &r3,Rule &r4){
			m_rules.push_back(std::vector<Rule*>());
			m_rules.rbegin()->push_back(&r1);
			m_rules.rbegin()->push_back(&r2);
			m_rules.rbegin()->push_back(&r3);
			m_rules.rbegin()->push_back(&r4);
		}
		inline void addRule(Rule &r1,Rule &r2,Rule &r3,Rule &r4,Rule &r5){
			m_rules.push_back(std::vector<Rule*>());
			m_rules.rbegin()->push_back(&r1);
			m_rules.rbegin()->push_back(&r2);
			m_rules.rbegin()->push_back(&r3);
			m_rules.rbegin()->push_back(&r4);
			m_rules.rbegin()->push_back(&r5);
		}
		
		inline void addString(std::string &str){
			m_set.insert(str);
		}
		inline void addString(const char *cstr){
			std::string str(cstr);
			m_set.insert(str);
		}
		
		std::string::iterator check(std::string::iterator string_itr,
									std::string::iterator end_itr);
	protected:
	private:
		std::set<std::string> m_set;
		std::list<std::vector<Rule*>> m_rules;
};

std::string::iterator Rule::check(  std::string::iterator string_itr,
									std::string::iterator end_itr){
	bool all_right = true;
	auto temp_itr = string_itr;
	if(!m_set.empty()){
		for(auto &set_itr:m_set){//set_itr is a string
			temp_itr = string_itr;
			all_right = true;
			for(auto set_str_itr:set_itr){//set_str_itr is a char
				if(((*temp_itr)!=set_str_itr)||(temp_itr==end_itr)){
					all_right = false;
					break;
				}
				++temp_itr;
			}
			if(all_right){
				return temp_itr;
			}
		}
		throw ErrFailed();
		return string_itr;
	}
	for(auto &list_itr:m_rules){
		temp_itr = string_itr;
		all_right = true;
		for(auto &itr:list_itr){
			try{
				temp_itr = itr->check(temp_itr,end_itr);
			}catch(ErrFailed &e){
				all_right = false;
				break;
			}
		}
		if(all_right)return temp_itr;
	}
	throw ErrFailed();
	return string_itr;
}

#endif
