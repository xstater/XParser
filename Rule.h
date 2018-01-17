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
		Rule(const char *str){
			std::string s(str);
			for(auto i:s){
				m_set.insert(i);
			}
		}
		
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
		void addRule(Rule &r1,Rule &r2,Rule &r3,Rule &r4){
			m_rules.push_back(std::vector<Rule*>());
			m_rules.rbegin()->push_back(&r1);
			m_rules.rbegin()->push_back(&r2);
			m_rules.rbegin()->push_back(&r3);
			m_rules.rbegin()->push_back(&r4);
		}
		void addRule(Rule &r1,Rule &r2,Rule &r3,Rule &r4,Rule &r5){
			m_rules.push_back(std::vector<Rule*>());
			m_rules.rbegin()->push_back(&r1);
			m_rules.rbegin()->push_back(&r2);
			m_rules.rbegin()->push_back(&r3);
			m_rules.rbegin()->push_back(&r4);
			m_rules.rbegin()->push_back(&r5);
		}
		
		std::string::iterator check(std::string::iterator string_itr,
									std::string::iterator end_itr);
	protected:
	private:
		std::set<char> m_set;
		std::list<std::vector<Rule*>> m_rules;
};

std::string::iterator Rule::check(  std::string::iterator string_itr,
									std::string::iterator end_itr){
	if(string_itr == end_itr){
		throw ErrFailed();
		return string_itr;
	}
	if(!m_set.empty()){
		for(auto set_itr:m_set){
			if(*string_itr == set_itr){
				return (++string_itr);
			}
		}
		throw ErrFailed();
		return string_itr;
	}
	for(auto &list_itr:m_rules){
		auto temp_itr = string_itr;
		bool all_right = true;
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
