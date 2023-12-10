#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

int	indexLine = 0, out = 0;

int main(void){
	std::fstream in;
	in.open("AskChat.xpm", std::ios::in);
	std::string	line, dot;
	while (std::getline(in, line)){
		indexLine++;
		if (indexLine > 500){
			int	numAt = line.find("I18<I");
			while (numAt != line.npos){
				out++;
				line[numAt] = ' ';
				line[numAt + 1] = ' ';
				line[numAt + 2] = ' ';
				line[numAt + 3] = ' ';
				line[numAt + 4] = ' ';
				numAt = line.find("I18<I");
			}
		}
	}

	std::cout << "Answer: " << out / 2 << std::endl;

}
