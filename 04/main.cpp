#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <algorithm>

int	winNumbers[10];
int	cards[300];


int main(void){
	std::fill_n(cards, 300, 1);
	// memset(cards, 0, 300 * sizeof(int));
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line, dot;
	int	out = 0, cardNum = 1, num = 0, nCards = 0;
	while (std::getline(in, line)){
		std::string	cut = line.substr(line.find_first_of(":"));
		int	numAt = cut.find_first_of("0123456789"), nnum = 0, ncorrect = 0;
		std::cout << "Card num: " << cardNum << std::endl;
		// nCards++;
		while (numAt != cut.npos){
			std::string numS = cut.substr(numAt);
			num = atoi(numS.c_str());
			// std::cout << num << std::endl;
			if (nnum < 10){
				winNumbers[nnum++] = num;
				// std::cout << "win num:" << num << std::endl;
			}
			else {
				for (size_t i = 0; i < nnum; i++){
					if (num == winNumbers[i]){
						ncorrect++;
						std::cout << num << " is winning num!!" << std::endl;
						break;
					}
				}
				
			}
			
			for (size_t f = numAt; isdigit(cut[f]); f++)
				cut[f] = '.';
			numAt = cut.find_first_of("0123456789");
		}
		std::cout << "Will add " << cards[cardNum] << " times" << std::endl;
		for (size_t i = 0; i < cards[cardNum]; i++)
		{
			nCards++;
			int	tmp = ncorrect;
			while (tmp > 0)
			{
				// nCards++;
				// std::cout << "Adding card of index " << cardNum + tmp << std::endl;
				cards[cardNum + tmp] += 1;
				tmp--;
			}
		}
		
		cardNum++;
		std::cout << std::endl;
	}
	std::cout << "Answer: " << nCards << std::endl;
	// std::cout << "Answer: " << out << std::endl;

}
