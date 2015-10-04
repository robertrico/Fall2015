#include<iostream>
#ifndef ALPHATYPE
#define DIGIT 0
#define LETTER 1
#define ALPHATYPE 1
#endif

/* PsuedoHeader File (Restricted to single Source File */
/* main.h */
int testmain(int argc,char *args[]);
int main(int argc,char *args[]);

namespace alphabet{
	class Recognizer{
		private:
			const char letter[4] = {'X','Y','Z','\0'};
			const char digit[11] = {'0','1','2','3','4','5','6','7','8','9','\0'};
		public:
			Recognizer(){
			}
			bool exists(char test,int which){
				int i = 0;
				if(which == DIGIT){
					while(digit[i] != '\0'){
						if(digit[i] == test)
							return true;
						i++;
					}
				}else if(which == LETTER){
					while(letter[i] != '\0'){
						if(letter[i] == test)
							return true;
						i++;
					}
				}
				return false;
			}
	};
}
/* End PsuedoHeader File */

	int testmain(int argc,char *args[])
	{
		alphabet::Recognizer language;
		if(language.exists('4',DIGIT) && !language.exists('Z',DIGIT)){
			std::cout << "Class Recognizer::exists(DIGIT) successful" << std::endl;
		}
		if(language.exists('X',LETTER) && !language.exists('R',LETTER)){
			std::cout << "Class Recognizer::exists(LETTER) successful" << std::endl;
		}
		return 0;
	}

int main(int argc,char *args[])
{
	if(args[1] == NULL || args[1][0] == '\0'){
		std::cout << "Hello World" << std::endl;
	}else{
		std::string arg1(args[1]);
		if(arg1 == "test"){
			testmain(argc,args);
			return 0;
		}
	}

	return 0;
}
