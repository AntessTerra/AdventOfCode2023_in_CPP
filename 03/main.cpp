#include <iostream>
#include <fstream>
#include <sstream>

std::string	input[200];

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line, dot;
	int	out = 0, indexLine = 1, num = 0;
	while (std::getline(in, line)){
		dot = ".";
		input[indexLine++] = dot.append(line).append(".");
	}
	input[0].insert(0, input[1].length(), '.');
	input[indexLine].insert(0, input[1].length(), '.');
	for (size_t i = 1; i < indexLine; i++){
		int	numAt = input[i].find_first_of("0123456789"), nnum = 0;
		while (numAt != input[i].npos){
			std::string numS = input[i].substr(numAt);
			num = atoi(numS.c_str());
			std::cout << num << std::endl;
			for (size_t b = numAt; isdigit(input[i][b]); b++){
				for (size_t g = 0; g < 9; g++){
					if (input[i - 1 + (g / 3)][b - 1 + (g % 3)] == '*'){
						std::cout << "FOUND STAR" << std::endl;
						int	starx = i - 1 + (g / 3), stary = b - 1 + (g % 3);
						for (size_t f = numAt; isdigit(input[i][f]); f++)
							input[i][f] = '.';
						for (size_t l = 0; l < 9; l++){
							if (isdigit(input[starx - 1 + (l / 3)][stary - 1 + (l % 3)])){
								std::cout << "FOUND second NUMBER" << std::endl;
								int numx = starx - 1 + (l / 3), numy = stary - 1 + (l % 3);
								while (isdigit(input[numx][numy]))
									numy--;
								std::string numS2 = input[numx].substr(numy + 1);
								int num2 = atoi(numS2.c_str());
								std::cout << num2 << std::endl;
								for (size_t f = numy + 1; isdigit(input[numx][f]); f++)
									input[numx][f] = '.';
								out += num * num2;
								
							}
							std::cout << "Symbol aroud is " << input[starx - 1 + (l / 3)][stary - 1 + (l % 3)] << std::endl;
							if (l % 3 == 2)
							std::cout << std::endl;
						}
					}
					// std::cout << "Symbol aroud is " << input[i - 1 + (g / 3)][b - 1 + (g % 3)] << std::endl;
				}
			}
			for (size_t f = numAt; isdigit(input[i][f]); f++)
				input[i][f] = '.';
			numAt = input[i].find_first_of("0123456789");
		}	
	}

	std::cout << "Answer: " << out << std::endl;

}
