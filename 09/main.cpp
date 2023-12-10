#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <climits>

long long	nseq = 0, ndiff = 1, out = 0;
int			seq[50][1000];

void	printData(){
	for (size_t d = 0; d < ndiff; d++){
		for (size_t i = 0; i < nseq - d; i++){
			std::cout << seq[i][d] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool	isSeqZero(){
	for (size_t i = 0; i < nseq - ndiff + 1; i++)
		if (seq[i][ndiff - 1] > 0 || seq[i][ndiff - 1] < 0)
			return false;
	return true;
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	long long num = 0;
	while (std::getline(in, line)){
		int	numAt = line.find_first_of("-0123456789");
		nseq = 0, ndiff = 1;
		while (numAt != line.npos){
			std::string numS = line.substr(numAt);
			num = atoll(numS.c_str());
			seq[nseq++][0] = num;
			for (size_t i = numAt; isdigit(line[i]) || line[i] == '-'; i++){
				line[i] = ' ';
			}
			numAt = line.find_first_of("-0123456789");
		}
		while (!isSeqZero()){
			// printData();
			for (size_t i = 0; i < nseq - ndiff; i++){
				seq[i][ndiff] = seq[i + 1][ndiff - 1] - seq[i][ndiff - 1];
				// std::cout << seq[i][ndiff] << " ";
			}
			ndiff++;
		}
		printData();
		long long tmp = 0;
		for (size_t d = ndiff - 1; d > 0; d--){
			std::cout << seq[0][d] << std::endl;
			tmp = seq[0][d] - tmp;
		}
		std::cout << seq[0][0] << std::endl;
		tmp = seq[0][0] - tmp;
		out += tmp;
		std::cout << std::endl;
	}


	std::cout << "Answer: " << out << std::endl;
}
