#include<iostream>
#include<vector>

/* CONSTANT Definitions to make human readability easier */
#ifndef ALPHATYPE
#define DIGIT 0
#define LETTER 1
#define PRODOP 3
#define SUMOP 4
#define COMPOP 5
#define ALPHATYPE 1
#endif

int main(int argc,char *args[]);

namespace alphabet{
	class Recognizer{
		private:
			static const char letter[4];
			static const char digit[11];
			static const char sum_operator[3];
			static const char pro_operator[3];
			static const char comp_operator[5];
			static std::vector<char> inputString;
			static std::vector<char>::iterator it;
			static char currentToken;
			static int errorFlag;
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
