#include <iostream>
#include <fstream>
#include <sstream>

typedef struct s_pattern{
	std::string	data[500];
	int			nLines = 0;
}				t_pattern;

t_pattern	patterns[5000];
long long	out = 0, nPaterns = 0;

void	printData(){
	for (size_t i = 0; i <= nPaterns; i++){
		for (size_t j = 0; j < patterns[i].nLines; j++)
			std::cout << patterns[i].data[j] << std::endl;
		std::cout << std::endl;
	}
	// std::cout << std::endl;
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	while (std::getline(in, line)){
		if (line.length() > 0)
			patterns[nPaterns].data[patterns[nPaterns].nLines++] = line.append(" ");
		else {
			patterns[nPaterns].data[patterns[nPaterns].nLines].insert(0, patterns[nPaterns].data[0].length(), ' ');
			nPaterns++;
		}
	}
	// printData();
	for (size_t i = 0; i <= nPaterns; i++){
		int nChars = (patterns[i].data[0].length() - 1) * patterns[i].nLines, lowestHor = 1000, lowestVer = 1000, lowestHorBefore = 1000, lowestVerBefore = 1000;
		// std::cout << nChars << std::endl;
		for (int s = -1; s < nChars; s++){

			// std::cout << s % (patterns[i].data[0].length() - 1) << " | " << s % patterns[i].nLines << std::endl;
			if (s >= 0 && patterns[i].nLines != (patterns[i].data[0].length() - 1)){
				if (patterns[i].data[s % patterns[i].nLines][s % (patterns[i].data[0].length() - 1)] == '.')
					patterns[i].data[s % patterns[i].nLines][s % (patterns[i].data[0].length() - 1)] = '#';
				else
					patterns[i].data[s % patterns[i].nLines][s % (patterns[i].data[0].length() - 1)] = '.';
			}
			else if (s >= 0){
				if (patterns[i].data[s % patterns[i].nLines][s / (patterns[i].data[0].length() - 1)] == '.')
					patterns[i].data[s % patterns[i].nLines][s / (patterns[i].data[0].length() - 1)] = '#';
				else
					patterns[i].data[s % patterns[i].nLines][s / (patterns[i].data[0].length() - 1)] = '.';
			}
			// printData();
			for (size_t j = 0; j < patterns[i].nLines; j++){
				if (!patterns[i].data[j].compare(patterns[i].data[j + 1])){
					int n = 1, mirror = 1;
					while (j - n + 1 > 0 && j + 1 + n < patterns[i].nLines){
						if (patterns[i].data[j - n].compare(patterns[i].data[j + 1 + n])){
							mirror = 0;
							break ;
						}
						n++;
					}
					if (mirror){
						std::cout << i + 1 << ": HAS A HORIZONTAL MIRROR BETWEEN LINES " << j + 1 << " AND " << j + 2 << std::endl;
						if (s == -1){
								lowestHorBefore = j + 1;
						}
						else if (j + 1 != lowestHorBefore)
							lowestHor = j + 1;
						// printData();
						// out += (j + 1) * 100;
					}

				}
			}
			for (size_t j = 0; j < patterns[i].data[0].length(); j++){
				for (int h = 0; patterns[i].data[h][j] == patterns[i].data[h][j + 1]; h++){
					if (h == patterns[i].nLines){
						// std::cout << i << ": HAS A POTENCIAL VERTICAL MIRROR BETWEEN LINES " << j + 1 << " AND " << j + 2 << std::endl;
						int n = 1, mirror = 1;
						while (j - n + 1 > 0 && j + 1 + n < patterns[i].data[0].length() - 1){
							for (int f = 0; f < patterns[i].nLines; f++){
								// std::cout << "CHECKING ON COLUMN: " << j - n + 1 << " AND " << j + n + 1 + 1 << std::endl;
								if (patterns[i].data[f][j - n] != patterns[i].data[f][j + n + 1]){
									mirror = 0;
									break ;
								}
							}
							n++;
						}
						if (mirror){
							std::cout << i + 1 << ": HAS A VERTICAL MIRROR BETWEEN LINES " << j + 1 << " AND " << j + 2 << std::endl;
						// printData();
							if (s == -1){
									lowestVerBefore = j + 1;
							}
							else if (j + 1 != lowestVerBefore)
								lowestVer = j + 1;
						}
						break ;
					}
				}
			}
			if (s >= 0 && patterns[i].nLines != (patterns[i].data[0].length() - 1)){
				if (patterns[i].data[s % patterns[i].nLines][s % (patterns[i].data[0].length() - 1)] == '.')
					patterns[i].data[s % patterns[i].nLines][s % (patterns[i].data[0].length() - 1)] = '#';
				else
					patterns[i].data[s % patterns[i].nLines][s % (patterns[i].data[0].length() - 1)] = '.';
			}
			else if (s >= 0){
				if (patterns[i].data[s % patterns[i].nLines][s / (patterns[i].data[0].length() - 1)] == '.')
					patterns[i].data[s % patterns[i].nLines][s / (patterns[i].data[0].length() - 1)] = '#';
				else
					patterns[i].data[s % patterns[i].nLines][s / (patterns[i].data[0].length() - 1)] = '.';
			}
		}
		std::cout << "LowestHor: " << lowestHor << " Before: " << lowestHorBefore << " lowestVer: " << lowestVer << " Before: " << lowestVerBefore << std::endl;
		// if (lowestVer == 1000 && lowestHor == 1000)
			// std::cout << i + 1 << " MISTAKE!!!" << std::endl;
		if (lowestHor == 1000 && lowestVer != 1000){
			std::cout << "Using lowestVer" << std::endl;
			out += lowestVer;
		}
		else if (lowestHor != 1000){
			out += lowestHor * 100;
			std::cout << "Using lowestHor" << std::endl;
		}
	}
	// printData();
	std::cout << "Answer: " << out << std::endl;
}
