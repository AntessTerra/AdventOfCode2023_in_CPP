#include <iostream>
#include <fstream>
#include <sstream>

std::string	input[200];

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	int	out = 0, indexLine = 0;
	while (std::getline(in, line)){
		input[indexLine] = line;
		indexLine++;
	}
	for (size_t i = 0; i < indexLine; i++){
		int symbolAt = input[i].find_last_not_of(".0123456789"), foundSomething = 0;
		// std::cout << symbolAt << std::endl;
		if (symbolAt != input[i].npos){
			for (size_t j = 0; j < 9; j++){
				if (isdigit(input[i - 1 + (j / 3)][symbolAt - 1 + (j % 3)])){
					std::cout << "Found number " << input[i - 1 + (j / 3)][symbolAt - 1 + (j % 3)] << std::endl;
					foundSomething = 1;
				}
			}
			if (foundSomething){
				input[i].replace(symbolAt, 1, ".");
				// std::cout << input[i] << std::endl;
				i--;
			}
		}

	}

	std::cout << "Answer: " << out << std::endl;

}
