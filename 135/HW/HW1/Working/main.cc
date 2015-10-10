#include "main.h"

alphabet::Recognizer::Recognizer(std::string input)
{
	set(input);
}
void alphabet::Recognizer::advance()
{
	it++;
	if(inputString.size() < (unsigned)(it - inputString.begin())){
		exit(EXIT_FAILURE);
	}
}
void alphabet::Recognizer::assignmnt()
{
	ident();
	match('~');
	exprsn();
	match(';');
}
void alphabet::Recognizer::comprsn()
{
	match('(');
	oprnd();
	oprtr();
	oprnd();
	match(')');
}
void alphabet::Recognizer::error()
{
	auto pos = std::distance(inputString.begin(), it);
	std::cout << "Unexpected token " << getToken() << " at position " << pos <<std::endl;
	errorFlag = 1;
	advance();
}
void alphabet::Recognizer::exprsn()
{
	factor();
	while(terminal(getToken(),SUMOP)){
		match(getToken());
		factor();
	}
}
void alphabet::Recognizer::factor()
{
	oprnd();
	while(terminal(getToken(),PRODOP)){
		match(getToken());
		oprnd();
	}
}
void alphabet::Recognizer::forloop()
{
	match('F');
	match('(');
	assignmnt();
	match(')');
	match('(');
	comprsn();
	match(')');
	match('L');
	if(getToken() == '\\'){
		match('\\');
	}else{
		while(true){
			statemnt();
			if(getToken() == '\\'){
				break;
			}
		}
		match('\\');
	}
}
char alphabet::Recognizer::getToken()
{
	return *it;
}
int alphabet::Recognizer::hasError()
{
	return errorFlag;
}
void alphabet::Recognizer::ident()
{
	if(terminal(getToken(),LETTER)){
		match(getToken());
		while(terminal(getToken(),DIGIT) || terminal(getToken(),LETTER)){
			match(getToken());
		}
	}
}
void alphabet::Recognizer::ifstmnt()
{
	match('I');
	comprsn();
	match('@');
	if(getToken() == '&'){
		match('&');
	}else{
		while(true){
			statemnt();
			if(getToken() == '&'){
				break;
			}
			match('%');
		}
		match('&');
	}
}
void alphabet::Recognizer::input()
{
	match('N');
	ident();
	if(getToken() == ';'){
		match(';');
	}else{
		while(true){
			ident();
			if(getToken() == ';'){
				break;
			}
			match(',');
		}
		match('&');
	}
}
void alphabet::Recognizer::integer()
{
	if(terminal(getToken(),DIGIT)){
		match(getToken());
		while(terminal(getToken(),DIGIT)){
			match(getToken());
		}
	}
}
void alphabet::Recognizer::match(char token)
{
	if(token == getToken()){
		advance();
	}else{
		error();
	}
}
void alphabet::Recognizer::oprnd()
{
	if(getToken() == '('){
		match('(');
		exprsn();
		match(')');
	}else if(terminal(getToken(),LETTER)){
		ident();
	}else{
		integer();
	}
}
void alphabet::Recognizer::oprtr()
{
	if(terminal(getToken(),COMPOP)){
		match(getToken());
	}
}
void alphabet::Recognizer::output()
{
	match('O');
	ident();
	if(getToken() == ';'){
		match(';');
	}else{
		while(true){
			ident();
			if(getToken() == ';'){
				break;
			}
			match(',');
		}
		match('&');
	}
}
void alphabet::Recognizer::resetError()
{
	errorFlag = 0;
}
void alphabet::Recognizer::set(std::string input)
{
	inputString = std::vector<char> (input.begin(),input.end());
	it = inputString.begin();
}
void alphabet::Recognizer::statemnt()
{
	char caseToken = getToken();
	if(caseToken == 'I'){
		ifstmnt();
	}else if(caseToken == 'F'){
		forloop();
	}else if(caseToken == 'N'){
		input();
	}else if(caseToken == 'O'){
		output();
	}else{
		assignmnt();
	}

}
void alphabet::Recognizer::start()
{
	std::cout << "Start Parsing" << std::endl;

	while(getToken() != '$'){
		statemnt();
	}

	match('$');

	if(hasError()){
		std::cout << "Errors found while parsing." << std::endl;
	}else{
		std::cout << "No errors found while parsing." << std::endl;
	}
}
/* TODO Refactor. Too much repeated Code. Low Priority. */
bool alphabet::Recognizer::terminal(char test,int which)
{
	int i = 0;
	switch(which){
		case DIGIT:
			while(digit[i] != '\0'){
				if(digit[i] == test)
					return true;
				i++;
			}
			break;
		case LETTER:
			while(letter[i] != '\0'){
				if(letter[i] == test)
					return true;
				i++;
			}
			break;
		case SUMOP:
			while(sum_operator[i] != '\0'){
				if(sum_operator[i] == test)
					return true;
				i++;
			}
			break;
		case PRODOP:
			while(pro_operator[i] != '\0'){
				if(pro_operator[i] == test)
					return true;
				i++;
			}
			break;
		case COMPOP:
			while(comp_operator[i] != '\0'){
				if(comp_operator[i] == test)
					return true;
				i++;
			}
			break;
		default:
			//error
			break;
	}
	return false;
}


#ifdef PRODUCTION
int main(int argc,char *args[])
{
	if(args[1] == NULL || args[1][0] == '\0'){
		std::string input;
		std::cout << "\nInput Your Expression" << std::endl;
		std::getline(std::cin,input);
		alphabet::Recognizer rdr(input);	
		rdr.start();
	}else{
		std::cout << "\nNo Options should be passed." << std::endl;
	}

	return 0;
}
#else
/* If Production Compilation is enabled in the makefile, this does not render */
int main(int argc,char *args[])
{
	std::string input = "TestXYZIFNO\0";
	alphabet::Recognizer language(input);
	if(language.terminal('4',DIGIT) && !language.terminal('Z',DIGIT)){
		std::cout << "Class Recognizer::terminal(DIGIT) passed" << std::endl;
	}else{
		std::cout << "Class Recognizer::terminal(DIGIT) failed" << std::endl;
	}
	if(language.terminal('X',LETTER) && !language.terminal('R',LETTER)){
		std::cout << "Class Recognizer::terminal(LETTER) passed" << std::endl;
	}else{
		std::cout << "Class Recognizer::terminal(LETTER) failed" << std::endl;
	}

	if(language.getToken() == 'T'){
		language.advance();
		if(language.getToken() == 'e'){
			std::cout << "Class Recognizer::advance() passed" << std::endl;
			std::cout << "Class Recognizer::getToken() passed" << std::endl;
		}else{
			std::cout << "Class Recognizer::advance() failed" << std::endl;
			std::cout << "Class Recognizer::getToken() failed" << std::endl;
		}
	}
	
	language.match('e');
	if(language.getToken() == 's'){
		std::cout << "Class Recognizer::match() passed" << std::endl;
	}else{
		std::cout << "Class Recognizer::match() failed" << std::endl;
	}

	language.advance();
	language.advance();

	language.set("X~982;");
	language.assignmnt();
	if(language.hasError()){
		std::cout << "Class Recognizer::assignmnt() failed" << std::endl;
	}else{
		std::cout << "Class Recognizer::assignmnt() passed" << std::endl;
	}

	language.resetError();

	language.set("<>!=");
	language.oprtr();
	language.oprtr();
	language.oprtr();
	language.oprtr();

	if(language.hasError()){
		std::cout << "Class Recognizer::oprtr() failed" << std::endl;
	}else{
		std::cout << "Class Recognizer::oprtr() passed" << std::endl;
	}

	language.resetError();
	language.set("XY123");
	language.ident();
	language.set("XY123,ZZ1234,Y198");
	language.ident();

	if(language.hasError()){
		std::cout << "Class Recognizer::ident() failed" << std::endl;
	}else{
		std::cout << "Class Recognizer::ident() passed" << std::endl;
	}

	language.set("NX;");
	language.input();
	language.set("NXYZ;");
	language.input();
	language.set("NXYZZZZZZ;");
	language.input();

	if(language.hasError()){
		std::cout << "Class Recognizer::input() failed" << std::endl;
	}else{
		std::cout << "Class Recognizer::input() passed" << std::endl;
	}

	language.set("OX;");
	language.output();
	language.set("OXYZ;");
	language.output();
	language.set("OXYZZZZZZ;");
	language.output();

	if(language.hasError()){
		std::cout << "Class Recognizer::output() failed" << std::endl;
	}else{
		std::cout << "Class Recognizer::output() passed" << std::endl;
	}

	language.set("I(X=XZ)@&");
	language.ifstmnt();
	language.set("I(4=4)@NX;&");
	language.set("I(4=4)@NX;%NZZZ;&");
	language.ifstmnt();
	if(language.hasError()){
		std::cout << "Class Recognizer::ifstmnt() failed" << std::endl;
	}else{
		std::cout << "Class Recognizer::ifstmnt() passed" << std::endl;
	}

	language.set("F(Z~28989;)((XY<99))L\\$");
	language.forloop();
	language.set("F(Z~28989;)((XY<99))LZXYYZ~(ZXY/98);\\$");
	language.forloop();
	if(language.hasError()){
		std::cout << "Class Recognizer::forloop() failed" << std::endl;
	}else{
		std::cout << "Class Recognizer::forloop() passed" << std::endl;
	}

	language.resetError();
	language.set("F(Z~28989;)((XY<99))LZXYYZ~(ZXY/98);\\$");
	language.set("F(Z~28989;)((XY<99))LZXYYZ~(ZXY/98);\\I(4=4)@&$");
	language.set("F(Z~28989;)((XY<99))LZXYYZ~(ZXY/98);\\I(4=4)@NX;%NZZZ;&$");
	language.set("F(Z~28989;)((XY<99))LZXYYZ~(ZXY/98);\\I(4=4)@NX;%NZZZ;&X~23+24;OXYZ;$");
	language.set("F(Z~28989;)((XY<99))LZXYYZ~(ZXY/98);\\I(4=4)@NX;%NZZZ;&X~23+24;OXYZ;F(X~982;)((9=9))L\\$");
	language.start();
	if(language.hasError()){
		std::cout << "Class Recognizer::statemnt() failed" << std::endl;
	}else{
		std::cout << "Class Recognizer::statemnt() passed" << std::endl;
	}

	return 0;
}
#endif
//F(Z~28989;)((XY<99))LZXYYZ~(ZXY/98);\I(4=4)@NX;%NZZZ;&X~23+24;OXYZ;F(X~982;)((9=9))L\$
