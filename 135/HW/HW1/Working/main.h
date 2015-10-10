#include<iostream>
#include<vector>
#ifndef ALPHATYPE
#define DIGIT 0
#define LETTER 1
#define PRODOP 3
#define SUMOP 4
#define COMPOP 5
#define ALPHATYPE 1
#endif

int testmain(int argc,char *args[]);
int main(int argc,char *args[]);

namespace alphabet{
	class Recognizer{
		private:
			const char letter[4] = {'X','Y','Z','\0'};
			const char digit[11] = {'0','1','2','3','4','5','6','7','8','9','\0'};
			const char sum_operator[3] = {'+','-','\0'};
			const char pro_operator[3] = {'*','/','\0'};
			const char comp_operator[5] = {'<','=','>','!','\0'};
			std::vector<char> inputString;
			char currentToken = '\0';
			std::vector<char>::iterator it;
			int errorFlag = 0;
		public:
			Recognizer(std::string input);

			void advance();
			void assignmnt();
			void comprsn();
			void error();
			void exprsn();
			void factor();
			void forloop();
			char getToken();
			int hasError();
			void ident();
			void ifstmnt();
			void input();
			void integer();
			void match(char token);
			void oprnd();
			void oprtr();
			void output();
			void resetError();
			void set(std::string input);
			void statemnt();
			void start();
			bool terminal(char test,int which);
	};
}
