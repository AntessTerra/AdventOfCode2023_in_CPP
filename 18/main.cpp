#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <climits>

typedef struct s_pos{
	int x, y;
}				t_pos;

long long	mapSize = 1000, out = 0;
std::string	map[1000], color;

void	printData(){
	for (size_t d = 0; d < mapSize; d++)
		std::cout << map[d] << std::endl;
}

void	floodFill(int x, int y){
	if (x < 0 || y < 0 || y >= mapSize + 1 || x >= mapSize)
		return ;
	if (map[y][x] == '#')
		return ;

	map[y][x] = '#';
	// std::cout << "Am at X: " << x << " Y: " << y << std::endl;

	floodFill(x + 1, y);
	floodFill(x - 1, y);
	floodFill(x + 1, y + 1);
	floodFill(x - 1, y - 1);
	floodFill(x, y + 1);
	floodFill(x, y - 1);
	floodFill(x - 1, y + 1);
	floodFill(x + 1, y - 1);
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	long long num = 0;
	t_pos pos;
	pos.x = 300;
	pos.y = 300;
	for (size_t d = 0; d < mapSize; d++)
		map[d].insert(0, mapSize, '.');
	while (std::getline(in, line)){
		int	numAt = line.find_first_of("-0123456789");
		std::string numS = line.substr(numAt);
		num = atoll(numS.c_str());
		map[pos.y][pos.x] = '#';
		if (line[0] == 'R'){
			for (;num > 0;num--){
				pos.x++;
				map[pos.y][pos.x] = '#';
			}
		}
		else if (line[0] == 'D'){
			for (;num > 0;num--){
				pos.y++;
				map[pos.y][pos.x] = '#';
			}
		}
		else if (line[0] == 'L'){
			for (;num > 0;num--){
				pos.x--;
				map[pos.y][pos.x] = '#';
			}
		}
		else if (line[0] == 'U'){
			for (;num > 0;num--){
				pos.y--;
				map[pos.y][pos.x] = '#';
			}
		}
		// printData();
	}
	// map[pos.y][pos.x] = '#';
	floodFill(301, 301);
	for (size_t d = 0; d < mapSize; d++){
		for	(int t = 0; t < map[d].length(); t++){
			if (map[d][t] == '#')
				out++;
		}
	}
	printData();
	std::cout << "Answer: " << out << std::endl;
}
