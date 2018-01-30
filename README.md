# XParser

一个简单的文法解析器<br>
采用递归下降式解析

## 函数说明
##### Parser::check
```
//该函数检查字符串中是否存在满足规则的前缀串
//函数原型如下:
bool Parser::check(Rule&,const char*)noexcept;
bool Parser::check(Rule&,std::string&)noexcept;
```
##### Parser::checkAll
```
//该函数检查整个串是否全满足规则
//函数原型如下:
bool Parser::checkAll(Rule&,const char*)noexcept;
bool Parser::checkAll(Rule&,std::string&)noexcept;
```
##### Parser::match
```
//该函数返回已经匹配的前缀串
//函数原型如下:
std::string Parser::match(Rule&,const char*)noexcept;
std::string Parser::match(Rule&,std::string&)noexcept;
```

## Example
```
#include <iostream>
#include <string>
#include <utility>
#include "Parser.h"

using namespace std;

//有以下产生式
//digit   -> [0-9] ;单个数字
//number  -> digit number | digit ;数字序列
//snumber -> + number | - number | number ;有符号整数
//real    -> snumber . number ;实数
//realexp -> real[eE]snumber | snumber[eE]snumber ;实数的指数形式

//这个程序能匹配诸如1.42e3  -3.009e2的实数

int main(int argc,char *argv[]){
	//根据产生式构建规则
	string tmp;
	Rule digit;
	for(char c='0';c<='9';++c){
		tmp = std::move(string(1,c));
		digit.addString(tmp);
	}
	Rule number;
		number.addRule(digit,number);
		number.addRule(digit);
	Rule neg,pos;
		tmp = std::move(string(1,'-'));
		neg.addString(tmp);
		tmp = std::move(string(1,'+'));
		pos.addString(tmp);
	Rule snumber;
		snumber.addRule(neg,number);
		snumber.addRule(pos,number);
		snumber.addRule(number);
	Rule point;
		tmp = std::move(string(1,'.'));
		point.addString(tmp);
	Rule real;
		real.addRule(snumber,point,number);
	Rule exp;
		tmp = std::move(string(1,'e'));
		exp.addString(tmp);
		tmp = std::move(string(1,'E'));
		exp.addString(tmp);
	Rule realexp;
		realexp.addRule(real,exp,snumber);
		realexp.addRule(snumber,exp,snumber);


	//匹配一些数字
	if(Parser::checkAll(realexp,"1.454e5"))
		cout<<"1.454e5是指数形式的实数"<<endl;
	if(Parser::check(snumber,"-1278.422"))
		cout<<"-1278.422存在一个有符号整数的前缀:-1278"<<endl;
	cout<<"-10086.88e-3abce的满足实数指数形式的前缀串为:"<<Parser::match(realexp,"-10086.88e-3abce")<<endl;
	return 0;
}
```
