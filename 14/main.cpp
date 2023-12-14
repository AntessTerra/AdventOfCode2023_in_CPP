#include <iostream>
#include <fstream>
#include <sstream>

std::string input[10000];
long long	out = 0, indexLine = 1;

void	printData(){
	for (size_t i = 1; i < indexLine; i++){
		std::cout << input[i] << std::endl;
	}
	std::cout << std::endl;
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	while (std::getline(in, line)){
		input[indexLine++] = line;
	}
	input[0].insert(0, input[1].length(), ' ');
	for (int loop = 0; loop < 1000; loop++){
		int out = 0;
		for	(int i = 1; i < indexLine; i++){
			for	(int j = 0; j < input[i].length(); j++){
				if (input[i][j] == 'O'){
					int n = 0;
					while (input[i - n - 1][j] == '.' && (i - n) > 0){
						input[i - n][j] = '.';
						input[i - n - 1][j] = 'O';
						n++;
					}
				}
			}
		}
		// printData();

		for	(int i = 1; i < indexLine; i++){
			for	(int j = 0; j < input[i].length(); j++){
				if (input[i][j] == 'O'){
					int n = 0;
					while (input[i][j - n - 1] == '.' && (j - n) > 0){
						input[i][j - n] = '.';
						input[i][j - n - 1] = 'O';
						n++;
					}
				}
			}
		}
		// printData();

		for	(int i = indexLine; i > 0; i--){
			for	(int j = 0; j < input[i].length(); j++){
				if (input[i][j] == 'O'){
					int n = 0;
					while (input[i + n + 1][j] == '.' && (i + n) > 0){
						input[i + n][j] = '.';
						input[i + n + 1][j] = 'O';
						n++;
					}
				}
			}
		}
		// printData();

		for	(int i = 1; i < indexLine; i++){
			for	(int j = input[i].length(); j >= 0; j--){
				if (input[i][j] == 'O'){
					int n = 0;
					while (input[i][j + n + 1] == '.' && (j + n) >= 0){
						input[i][j + n] = '.';
						input[i][j + n + 1] = 'O';
						n++;
					}
				}
			}
		}
		std::cout << loop + 1 << std::endl;
		for	(int i = 1; i < indexLine; i++){
			for	(int j = 0; j < input[i].length(); j++){
				if (input[i][j] == 'O'){
					out += indexLine - i;
				}
			}
		}
		std::cout << "Answer: " << out << std::endl;

	}
// 	printData();

// 	for	(int i = 1; i < indexLine; i++){
// 		for	(int j = 0; j < input[i].length(); j++){
// 			if (input[i][j] == 'O'){
// 				out += indexLine - i;
// 			}
// 		}
// 	}
// 	printData();
// 	std::cout << "Answer: " << out << std::endl;
}
