#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <climits>

typedef struct s_hand{
	std::string	cards;
	int			bid;
	int			rank = 0;
}				t_hand;

long long	nhands = 0, out = 0;
t_hand		hands[1000];

int			score[13] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

int	getScore(int ch){
	for (size_t i = 0; i < 13; i++){
		if (score[i] == ch)
			return (i);
	}
	return 0;

}

void	printData(){
	for (size_t i = 0; i < nhands; i++){
		std::cout << hands[i].rank << ": "
		<< hands[i].cards << " | "
		<< hands[i].bid << std::endl;
	}
	std::cout << std::endl;
}

void	swap(t_hand *one, t_hand *other){
	t_hand tmp = *one;
	*one = *other;
	*other = tmp;
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	while (std::getline(in, line)){
		int	spaceAt = line.find_first_of(" ");
		if (spaceAt != line.npos){
			hands[nhands].cards = line.substr(0, 5);
			std::string numS = line.substr(spaceAt + 1);
			hands[nhands].bid = atoll(numS.c_str());
		}
		nhands++;
	}
	printData();
	for (size_t i = 0; i < nhands; i++){
		if (hands[i].cards.find_first_not_of(hands[i].cards[0]) == hands[i].cards.npos){
				std::cout << hands[i].cards << " Five of a kind" << std::endl;
				hands[i].rank = 7;
		}
		else {
			int most = 0, nPairs = 0, wasJoker = 0;
			for (size_t j = 0; j < 5; j++){
				int	nSame = 0;
				for (size_t g = 0; g < 5; g++){
					if (hands[i].cards[j] == hands[i].cards[g] && hands[i].cards[g] != 'J')
						nSame++;
				}
				if (hands[i].cards[j] == 'J')
					wasJoker++;
				if (nSame == 2){
					nPairs++;
				}
				if (nSame > most)
					most = nSame;
			}
			nPairs /= 2;
			while (wasJoker){
				most++;
				if (nPairs == 2)
					nPairs--;
				else
					nPairs++;
				wasJoker--;
			}
			if (most >= 5){
				std::cout << hands[i].cards << " Five of a kind" << std::endl;
				hands[i].rank = 7;
			}
			else if (most == 4){
				std::cout << hands[i].cards << " Four of a kind" << std::endl;
				hands[i].rank = 6;
			}
			else if (most == 3 && nPairs == 1){
				std::cout << hands[i].cards << " Full house" << std::endl;
				hands[i].rank = 5;
			}
			else if (most == 3){
				std::cout << hands[i].cards << " Three of a kind" << std::endl;
				hands[i].rank = 4;
			}
			else if (most == 2 && nPairs == 2){
				std::cout << hands[i].cards << " Two pair" << std::endl;
				hands[i].rank = 3;
			}
			else if (most == 2 && nPairs == 1){
				std::cout << hands[i].cards << " One pair" << std::endl;
				hands[i].rank = 2;
			}
			else {
				std::cout << hands[i].cards << " High card" << std::endl;
				hands[i].rank = 1;
			}
			// std::cout << hands[i].cards << " Has " << most << " of a kind and " << nPairs << " pairs" << std::endl;
		}
	}
	// printData();
	for (size_t i = 0; i < nhands; i++){
		int	pos = 0;
		if (hands[i].rank == 7){
			pos = 0;
			for (size_t j = 0; j < nhands; j++){
				if (hands[j].rank >= 7)
					pos++;
				else
					break;
			}
			swap(&hands[i], &hands[pos]);
		}
	}
	for (size_t i = 0; i < nhands; i++){
		int	pos = 0;
		if (hands[i].rank == 6){
			pos = 0;
			for (size_t j = 0; j < nhands; j++){
				if (hands[j].rank >= 6)
					pos++;
				else
					break;
			}
			swap(&hands[i], &hands[pos]);
		}
	}
	for (size_t i = 0; i < nhands; i++){
		int	pos = 0;
		if (hands[i].rank == 5){
			pos = 0;
			for (size_t j = 0; j < nhands; j++){
				if (hands[j].rank >= 5)
					pos++;
				else
					break;
			}
			swap(&hands[i], &hands[pos]);
		}
	}
	for (size_t i = 0; i < nhands; i++){
		int	pos = 0;
		if (hands[i].rank == 4){
			pos = 0;
			for (size_t j = 0; j < nhands; j++){
				if (hands[j].rank >= 4)
					pos++;
				else
					break;
			}
			swap(&hands[i], &hands[pos]);
		}
	}
	for (size_t i = 0; i < nhands; i++){
		int	pos = 0;
		if (hands[i].rank == 3){
			pos = 0;
			for (size_t j = 0; j < nhands; j++){
				if (hands[j].rank >= 3)
					pos++;
				else
					break;
			}
			swap(&hands[i], &hands[pos]);
		}
	}
	for (size_t i = 0; i < nhands; i++){
		int	pos = 0;
		if (hands[i].rank == 2){
			pos = 0;
			for (size_t j = 0; j < nhands; j++){
				if (hands[j].rank >= 2)
					pos++;
				else
					break;
			}
			swap(&hands[i], &hands[pos]);
		}
	}
	// printData();

	for (size_t i = 0; i < nhands; i++){
		for (size_t f = 0; f < nhands - i; f++){
			if (hands[f].rank == 7 && hands[f + 1].rank == 7){
				if (getScore(hands[f].cards[0]) > getScore(hands[f + 1].cards[0])
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) > getScore(hands[f + 1].cards[1]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) > getScore(hands[f + 1].cards[2]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) > getScore(hands[f + 1].cards[3]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) == getScore(hands[f + 1].cards[3]) && getScore(hands[f].cards[4]) > getScore(hands[f + 1].cards[4]))){
					swap(&hands[f], &hands[f + 1]);
				}
			}
			if (hands[f].rank == 6 && hands[f + 1].rank == 6){
				if (getScore(hands[f].cards[0]) > getScore(hands[f + 1].cards[0])
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) > getScore(hands[f + 1].cards[1]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) > getScore(hands[f + 1].cards[2]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) > getScore(hands[f + 1].cards[3]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) == getScore(hands[f + 1].cards[3]) && getScore(hands[f].cards[4]) > getScore(hands[f + 1].cards[4]))){
					swap(&hands[f], &hands[f + 1]);
				}
			}
			if (hands[f].rank == 5 && hands[f + 1].rank == 5){
				if (getScore(hands[f].cards[0]) > getScore(hands[f + 1].cards[0])
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) > getScore(hands[f + 1].cards[1]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) > getScore(hands[f + 1].cards[2]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) > getScore(hands[f + 1].cards[3]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) == getScore(hands[f + 1].cards[3]) && getScore(hands[f].cards[4]) > getScore(hands[f + 1].cards[4]))){
					swap(&hands[f], &hands[f + 1]);
				}
			}
			if (hands[f].rank == 4 && hands[f + 1].rank == 4){
				if (getScore(hands[f].cards[0]) > getScore(hands[f + 1].cards[0])
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) > getScore(hands[f + 1].cards[1]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) > getScore(hands[f + 1].cards[2]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) > getScore(hands[f + 1].cards[3]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) == getScore(hands[f + 1].cards[3]) && getScore(hands[f].cards[4]) > getScore(hands[f + 1].cards[4]))){
					swap(&hands[f], &hands[f + 1]);
				}
			}
			if (hands[f].rank == 3 && hands[f + 1].rank == 3){
				if (getScore(hands[f].cards[0]) > getScore(hands[f + 1].cards[0])
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) > getScore(hands[f + 1].cards[1]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) > getScore(hands[f + 1].cards[2]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) > getScore(hands[f + 1].cards[3]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) == getScore(hands[f + 1].cards[3]) && getScore(hands[f].cards[4]) > getScore(hands[f + 1].cards[4]))){
					swap(&hands[f], &hands[f + 1]);
				}
			}
			if (hands[f].rank == 2 && hands[f + 1].rank == 2){
				if (getScore(hands[f].cards[0]) > getScore(hands[f + 1].cards[0])
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) > getScore(hands[f + 1].cards[1]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) > getScore(hands[f + 1].cards[2]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) > getScore(hands[f + 1].cards[3]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) == getScore(hands[f + 1].cards[3]) && getScore(hands[f].cards[4]) > getScore(hands[f + 1].cards[4]))){
					swap(&hands[f], &hands[f + 1]);
				}
			}
			if (hands[f].rank == 1 && hands[f + 1].rank == 1){
				if (getScore(hands[f].cards[0]) > getScore(hands[f + 1].cards[0])
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) > getScore(hands[f + 1].cards[1]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) > getScore(hands[f + 1].cards[2]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) > getScore(hands[f + 1].cards[3]))
				|| (getScore(hands[f].cards[0]) == getScore(hands[f + 1].cards[0]) && getScore(hands[f].cards[1]) == getScore(hands[f + 1].cards[1]) && getScore(hands[f].cards[2]) == getScore(hands[f + 1].cards[2]) && getScore(hands[f].cards[3]) == getScore(hands[f + 1].cards[3]) && getScore(hands[f].cards[4]) > getScore(hands[f + 1].cards[4]))){
					swap(&hands[f], &hands[f + 1]);
				}
			}
		}
	}
	for (size_t i = 0; i < nhands; i++)
		hands[i].rank = nhands - i;
	printData();
	for (size_t i = 0; i < nhands; i++)
		out += hands[i].bid * hands[i].rank;
	std::cout << "Answer: " << out;
}
