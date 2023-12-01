#include <iostream>
#include <fstream>
#include <sstream>

std::string	numbers[10] = {
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	"ten"
};

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	int	result = 0, out = 0;
	while (std::getline(in, line)){
		int foundResult = 0;
		for (int i = 0; i < line.length() && !foundResult; i++){
			if (isdigit(line[i])){
				result = 10 * (line[i]-'0');
				foundResult = 1;
				std::cout << "Digit: " << line[i] << std::endl;
			}
			else {
				for (int j = 0; j < 10 && !foundResult; j++){
					// std::cout << "Debug:\n" << line.find(numbers[j].c_str(), i, numbers[j].length()) << numbers[j] << std::endl << std::endl;
					if (line.find(numbers[j].c_str(), i, numbers[j].length()) <= i){
						result = 10 * (j + 1);
						foundResult = 1;
						std::cout << "Word: " << numbers[j] << std::endl;
					}
				}
			}
		}
		std::cout << "Result: " << result << std::endl;

		foundResult = 0;
		for (int i = line.length(); i >= 0 && !foundResult; i--){
			if (isdigit(line[i])){
				result += (line[i]-'0');
				foundResult = 1;
				std::cout << "Digit: " << line[i] << std::endl;
			}
			else {
				for (int j = 0; j < 10 && !foundResult; j++){
					// std::cout << "Debug:\n" << line.find(numbers[j].c_str(), i, numbers[j].length()) << numbers[j] << std::endl << std::endl;
					if (line.find(numbers[j].c_str(), i, numbers[j].length()) <= i){
						result += (j + 1);
						foundResult = 1;
						std::cout << "Word: " << numbers[j] << std::endl;
					}
				}
			}
		}
		std::cout << "Result: " << result << std::endl << std::endl;
		out += result;
	}
	std::cout << "Answer: " << out << std::endl;
}
