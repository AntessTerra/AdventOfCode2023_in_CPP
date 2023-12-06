#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

long long 	lenght[1] = {61709066};
long long	distance[1] = {643118413621041};

int main(void){
	long long	numBeat = 0;
	for (size_t i = 0; i < 1; i++){
		for (size_t f = 0; f <= lenght[i]; f++){
			long long movespeed = f;
			long long dist = movespeed * (lenght[i] - movespeed);
			// std::cout << "Move speed: " << movespeed << " distance: " << dist << std::endl;
			if (dist > distance[i])
				numBeat++;
		}
	}
	
	std::cout << "Asnwer: " << numBeat;
}
