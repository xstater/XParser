#XParser

简单的文法解析器

## Example
```
#include <iostream>
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
	Rule digit("0123456789");
	Rule number;
		number.addRule(digit,number);
		number.addRule(digit);
	Rule neg("-"),pos("+");
	Rule snumber;
		snumber.addRule(neg,number);
		snumber.addRule(pos,number);
		snumber.addRule(number);
	Rule point(".");
	Rule real;
		real.addRule(snumber,point,number);
	Rule exp("eE");
	Rule realexp;
		realexp.addRule(real,exp,snumber);
		realexp.addRule(snumber,exp,snumber);


	//匹配一些数字
	if(Parse::checkAll(realexp,"1.454e5"))
		cout<<"1.454e5是指数形式的实数"<<endl;
	if(Parse::check(snumber,"-1278.422"))
		cout<<"-1278.422存在一个有符号整数的前缀:-1278"<<endl;
	cout<<"-10086.88e-3abce的满足实数指数形式的前缀串为:"<<Parse::match(realexp,"-10086.88e-3abce")<<endl;
	return 0;
}
```
