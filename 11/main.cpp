#include <iostream>
#include <fstream>
#include <sstream>

typedef struct s_hash{
	int	x, y, xplus, yplus;
}				t_hash;

t_hash		hashes[500];
std::string	input[10000000];
long long	out = 0, indexLine = 1, nHashes = 0, nPairs = 0;

void	printData(){
	for (size_t i = 1; i < indexLine; i++){
		for (size_t j = 1; j < input[i].length() - 1; j++)
			std::cout << input[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line, dot;
	while (std::getline(in, line)){
		dot = ".";
		input[indexLine++] = dot.append(line).append(".");
	}
	input[0].insert(0, input[1].length(), '.');
	input[indexLine].insert(0, input[1].length(), '.');
	// printData();

	for (size_t i = 1; i < indexLine; i++){
		for (size_t j = 1; j < input[i].length() - 1; j++){
			if (input[i][j] == '#'){
				hashes[nHashes].x = j;
				hashes[nHashes].y = i;
				hashes[nHashes].xplus = 0;
				hashes[nHashes++].yplus = 0;
				// input[i][j] = nHashes - 1 + '0';
			}
		}
	}
	printData();

	for (size_t i = 1; i < indexLine; i++){
		if (input[i].find_first_of("#") == input[i].npos){
			std::cout << "Found an empty line!!" << std::endl;
			for (size_t h = i; h < indexLine; h++){
				for (size_t j = 1; j < input[h].length() - 1; j++){
					if (input[h][j] == '#'){

						for (size_t g = 0; g < nHashes; g++){

							if (hashes[g].x == j && hashes[g].y == h){

								hashes[g].yplus += 999999;
								break ;
							}
						}
					}
				}
			}
		}
	}
	for (size_t i = 1; i < input[1].length() - 1; i++){
		int foundHash = 0;
		for (size_t j = 1; j < indexLine; j++)
			if (input[j][i] == '#'){
				foundHash = 1;
				break ;
			}
		if (!foundHash){
			std::cout << "Found an empty column!!" << std::endl;
			for (size_t h = i; h < input[1].length() - 1; h++){
				for (size_t l = 0; l < indexLine; l++)
					if (input[l][h] == '#'){
						for (size_t g = 0; g < nHashes; g++){
							// std::cout << "Hex with index: " << g << " looking for x: " << h << " has " << hashes[g].x << " and for y: " << l << " has " << hashes[g].y << std::endl;

							if (hashes[g].x == h && hashes[g].y == l){
								hashes[g].xplus += 999999;
								break ;
							}
						}
					}

			}
		}

	}
	for (size_t i = nHashes - 1; i > 0; i--){
		for (size_t j = 0; j < i; j++){
			// std::cout << "Star dist from: " << i << " to: " << j << std::endl;
			out += abs((hashes[i].x + hashes[i].xplus) - (hashes[j].x + hashes[j].xplus)) + abs((hashes[i].y + hashes[i].yplus) - (hashes[j].y + hashes[j].yplus));
		}
	}
	std::cout << "Answer: " << out << std::endl;
}
