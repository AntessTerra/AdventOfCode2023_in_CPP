#include <iostream>
#include <fstream>
#include <sstream>

std::string	colors[3] = {
	"red",
	"green",
	"blue"
};



int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	int	out = 0;
	while (std::getline(in, line)){
		int i = line.find_last_of("0123456789");
		int	ncolors[3] = {
			0,
			0,
			0
		};
		while (i > 7){
			int foundColor = 0, num = 0;
			num = line[i] - '0';
			if (isdigit(line[i - 1])){
				num += 10 * (line[i - 1] - '0');
			}
			for (int n = 0; n < 3; n++){
				// std::cout << "Debug: " << line.find(colors[n], i) << "i: " << i;
				if (line.find(colors[n], i) != line.npos && !foundColor){
					// std::cout << colors[n];
					if (num > ncolors[n])
						ncolors[n] = num;
					foundColor = 1;
				}
			}

			// std::cout << line << std::endl;
			// std::cout << num << " ";
			line.erase(i, line.length() - i);
			i = line.find_last_of("0123456789");
		}
		// std::cout << "Game: " << indexLine << std::endl
		// << "Red cubes: " << ncolors[0] << std::endl
		// << "Green cubes: " << ncolors[1] << std::endl
		// << "Blue cubes: " << ncolors[2] << std::endl;
		// std::cout << std::endl;
		out += ncolors[0] * ncolors[1] * ncolors[2];
	}
	std::cout << "Answer: " << out << std::endl;

}
