#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <climits>

typedef struct s_map{
	long long	dest_range_from[50];
	long long	source_range_from[50];
	long long	rangle_length[50];
}				t_map;

long long	seeds[50], nseeds = 0;
t_map		maps[7];

void	printData(){
	std::cout << "SEEDS: \n\n";
	for (size_t i = 0; i < nseeds; i++){
		std::cout << seeds[i] << std::endl;
	}
	std::cout << "\nMAPS: \n\n";
	for (size_t j = 0; j < 7; j++){
		std::cout << j << ":\n";
		for (size_t i = 0; maps[j].rangle_length[i] > 0; i++){
			std::cout << maps[j].dest_range_from[i] << " | " 
			<< maps[j].source_range_from[i] << " | " 
			<< maps[j].rangle_length[i] << std::endl;
		}
	}
	std::cout << std::endl;
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	long long	indexLine = 0, num = 0, s = 0;
	while (std::getline(in, line)){
		int	numAt = line.find_first_of("0123456789"), nnum = 0;
		while (numAt != line.npos){
			std::string numS = line.substr(numAt);
			num = atoll(numS.c_str());
			if (indexLine == 0)
				seeds[nseeds++] = num;
			else {
				if (nnum % 3 == 0){
					maps[indexLine - 1].dest_range_from[s] = num;
					nnum = 0;
				}
				else if (nnum % 3 == 1)
					maps[indexLine - 1].source_range_from[s] = num;
				else if (nnum % 3 == 2)
					maps[indexLine - 1].rangle_length[s++] = num;
				nnum++;
				// std::cout << indexLine - 1 << " line setting num: " << num << std::endl;
			}
			for (size_t i = numAt; isdigit(line[i]); i++){
				line[i] = ' ';
			}
			numAt = line.find_first_of("0123456789");
		}		
		if (line.length() == 0){
			indexLine++;
			s = 0;
			// std::cout << "HI Im a new line" << std::endl;
		}
	}
	printData();
	long long lowest = LLONG_MAX;
	for (size_t s = 0; s < nseeds; s += 2){
		long long now_seed = seeds[s], go_till = seeds[s] + seeds[s + 1];
		std::cout << "STARTING RANGE: " << s << " FROM: " << seeds[s] << " TO " << seeds[s] << " + " << seeds[s + 1] << std::endl;
		while (now_seed < go_till){
			/* code */
		
			// std::cout << seeds[s] << std::endl;
			// std::cout << s + 1 << ": seed: " << seeds[s] << std::endl;
			for (size_t j = 0; j < 7; j++){
				for (size_t i = 0; maps[j].rangle_length[i] > 0; i++){
					if (now_seed >= maps[j].source_range_from[i] && now_seed <= maps[j].source_range_from[i] + maps[j].rangle_length[i]){
						// std::cout << "NUMBER IS IN MAP " << j << std::endl
						// << "In range " << maps[j].source_range_from[i] << " to " << maps[j].source_range_from[i] + maps[j].rangle_length[i] << std::endl;
						// if (maps[j].dest_range_from[i] > maps[j].source_range_from[i])
						// 	shift = maps[j].dest_range_from[i] - maps[j].source_range_from[i];
						// else
						// 	shift = maps[j].source_range_from[i] - maps[j].dest_range_from[i];
						now_seed += maps[j].dest_range_from[i] - maps[j].source_range_from[i];
						// std::cout << "Shifted number by " << shift << " to " << now_seed << std::endl;
						break ;
					}
				}
			}
			// std::cout << now_seed << " | " << seeds[s] << std::endl;
			if (now_seed < lowest){
				lowest = now_seed;
				std::cout << "NEW LOWEST: " << lowest << std::endl;
			}
			now_seed = seeds[s]++;
		}
	}
	// printData();
	std::cout << "Asnwer: " << lowest << "FOR SOME REASON THE CORRECT ANSWER IF ONE LOWER";
}
