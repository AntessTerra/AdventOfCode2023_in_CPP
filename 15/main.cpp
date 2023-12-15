#include <iostream>
#include <fstream>
#include <sstream>

std::string input[100000];
long long	out = 0, indexLine = 0;

void	printData(){
	for (size_t i = 0; i < indexLine; i++){
		std::cout << input[i] << std::endl;
	}
	std::cout << std::endl;
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line, copy;
	while (std::getline(in, line)){
		copy = line;
		int	at = line.find_last_of(",");
		while (at != line.npos){
			input[indexLine++] = line.substr(at + 1, line.npos);
			line.resize(at);
			at = line.find_last_of(",");
		}
	}
	input[indexLine++] = copy.substr(0, copy.find_first_of(","));
	printData();
	int	curval = 0;
	for (size_t i = 0; i < indexLine; i++){
		curval = 0;
		for (size_t p = 0; p < input[i].length(); p++){
			curval += input[i][p];
		std::cout << input[i][p] << std::endl;

			curval *= 17;
		std::cout << curval << std::endl;

			curval %= 256;
		std::cout << curval << std::endl  << std::endl;

		}
		out += curval;
	}
	std::cout << "Answer: " << out << std::endl;
}

