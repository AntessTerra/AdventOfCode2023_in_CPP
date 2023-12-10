#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

typedef struct s_point{
	int y, x, dist;
}				t_point;

std::string	input[200], down("|LJ"), up("|F7"), left("-LF"), right("-J7"), origin[200];
int	out = 0, indexLine = 1, falsePositive = 0;
t_point		start, along, against, fill;

void	printData(){
	for (size_t i = 0; i <= indexLine; i++){
		std::cout << input[i] << std::endl;
	}
}

void	escape(int x, int y){

}

void	floodFill(int x, int y, int passage){
	if (!passage){
		if (x < 0 || y < 0 || y >= indexLine + 1 || x >= input[y].length())
			return ;
		if (input[y][x] == 'a' || input[y][x] == '0')
			return ;

		input[y][x] = '0';
		// std::cout << "Am at X: " << x << " Y: " << y << std::endl;

		floodFill(x + 1, y, 0);
		floodFill(x - 1, y, 0);
		floodFill(x + 1, y + 1, 0);
		floodFill(x - 1, y - 1, 0);
		floodFill(x, y + 1, 0);
		floodFill(x, y - 1, 0);
		floodFill(x - 1, y + 1, 0);
		floodFill(x + 1, y - 1, 0);
	}
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line, dot;
	along.x = 0;
	along.y = 0;
	along.dist = 1;
	against.x = 0;
	against.y = 0;
	against.dist = 1;
	while (std::getline(in, line)){
		dot = ".";
		input[indexLine++] = dot.append(line).append(".");
	}
	input[0].insert(0, input[1].length(), '.');
	input[indexLine].insert(0, input[1].length(), '.');
	printData();
	for (size_t i = 0; i <= indexLine; i++)
		origin[i] = input[i];
	for (size_t i = 1; i < indexLine; i++){
		if (input[i].find_first_of('S') != input[i].npos){
			start.x = input[i].find_first_of('S');
			start.y = i;
			fill.x = start.x;
			fill.y = start.y;
		}
	}
	if (down.find_first_of(input[start.y + 1][start.x]) != down.npos){
		std::cout << "Can go DOWN from start!!" << std::endl;
		if (along.x == 0 && along.y == 0){
			along.x = start.x;
			along.y = start.y + 1;
		}
		else if (against.x == 0 && against.y == 0){
			against.x = start.x;
			against.y = start.y + 1;
		}
	}
	if (left.find_first_of(input[start.y][start.x - 1]) != left.npos){
		std::cout << "Can go LEFT from start!!" << std::endl;
		if (along.x == 0 && along.y == 0){
			along.x = start.x - 1;
			along.y = start.y;
		}
		else if (against.x == 0 && against.y == 0){
			against.x = start.x - 1;
			against.y = start.y;
		}
	}
	if (up.find_first_of(input[start.y - 1][start.x]) != up.npos){
		std::cout << "Can go UP from start!!" << std::endl;
		if (along.x == 0 && along.y == 0){
			along.x = start.x;
			along.y = start.y - 1;
		}
		else if (against.x == 0 && against.y == 0){
			against.x = start.x;
			against.y = start.y - 1;
		}
	}
	if (right.find_first_of(input[start.y][start.x + 1]) != right.npos){
		std::cout << "Can go RIGHT from start!!" << std::endl;
		if (along.x == 0 && along.y == 0){
			along.x = start.x + 1;
			along.y = start.y;
		}
		else if (against.x == 0 && against.y == 0){
			against.x = start.x + 1;
			against.y = start.y;
		}
	}
	std::cout << "Start found at x: " << start.x << " y: " << start.y << std::endl;
	std::cout << "Along found at x: " << along.x << " y: " << along.y << std::endl;
	std::cout << "Againts found at x: " << against.x << " y: " << against.y << std::endl;
	while (along.x - against.x != 0 || along.y - against.y != 0){
		if (down.find_first_of(input[along.y + 1][along.x]) != down.npos && up.find_first_of(input[along.y][along.x]) != up.npos){
			input[along.y][along.x] = 'a';
			along.dist++;
			along.y++;
		}
		else if (left.find_first_of(input[along.y][along.x - 1]) != left.npos && right.find_first_of(input[along.y][along.x]) != right.npos){
			input[along.y][along.x] = 'a';
			along.dist++;
			along.x--;;
		}
		else if (up.find_first_of(input[along.y - 1][along.x]) != up.npos && down.find_first_of(input[along.y][along.x]) != down.npos){
			input[along.y][along.x] = 'a';
			along.dist++;
			along.y--;
		}
		else if (right.find_first_of(input[along.y][along.x + 1]) != right.npos && left.find_first_of(input[along.y][along.x]) != left.npos){
			input[along.y][along.x] = 'a';
			along.dist++;
			along.x++;
		}
		// std::cout << "Along moved to x: " << along.x << " y: " << along.y << std::endl;
		if (down.find_first_of(input[against.y + 1][against.x]) != down.npos && up.find_first_of(input[against.y][against.x]) != up.npos){
			input[against.y][against.x] = 'a';
			against.dist++;
			against.y++;
		}
		else if (left.find_first_of(input[against.y][against.x - 1]) != left.npos && right.find_first_of(input[against.y][against.x]) != right.npos){
			input[against.y][against.x] = 'a';
			against.dist++;
			against.x--;;
		}
		else if (up.find_first_of(input[against.y - 1][against.x]) != up.npos && down.find_first_of(input[against.y][against.x]) != down.npos){
			input[against.y][against.x] = 'a';
			against.dist++;
			against.y--;
		}
		else if (right.find_first_of(input[against.y][against.x + 1]) != right.npos && left.find_first_of(input[against.y][against.x]) != left.npos){
			input[against.y][against.x] = 'a';
			against.dist++;
			against.x++;
		}
		// std::cout << "Againts moved to x: " << against.x << " y: " << against.y << std::endl;
		// sleep(1);
	}
	input[along.y][along.x] = 'a';
	input[against.y][against.x] = 'a';
	// for (size_t i = 1; i < indexLine; i++)
	// 	for (size_t j = 1; j < input[i].length() - 1; j++)
	// 		if ((input[i][j + 1] == 'a' || input[i][j + 1] == 'i') && (input[i][j - 1] == 'a' || input[i][j - 1] == 'i') && (input[i + 1][j] == 'a' || input[i + 1][j] == 'i') && (input[i - 1][j] == 'a' || input[i - 1][j] == 'i')
	// 		&& (input[i][j] == 'a' ))
	// 			input[i][j] = 'i';
	// for (size_t i = 1; i < indexLine; i++){
	// 	for (size_t j = 1; j < input[i].length() - 1; j++){
	// 		if (input[i][j] == 'a'){
	// 			if (origin[i][j] == '|')
	// 				std::cout << "\e[0;42m" << origin[i][j] << "\e[0m";
	// 			else if (origin[i][j] == '-')
	// 				std::cout << "\e[0;42m" << origin[i][j] << "\e[0m";
	// 			else if (origin[i][j] == 'J')
	// 				std::cout << "\e[0;41m" << origin[i][j] << "\e[0m";
	// 			else if (origin[i][j] == 'L')
	// 				std::cout << "\e[0;41m" << origin[i][j] << "\e[0m";
	// 			else if (origin[i][j] == 'F')
	// 				std::cout << "\e[0;41m" << origin[i][j] << "\e[0m";
	// 			else if (origin[i][j] == '7')
	// 				std::cout << "\e[0;41m" << origin[i][j] << "\e[0m";
	// 		}
	// 		else if ((input[i][j + 1] == 'a' || input[i][j + 1] == 'i') && (input[i][j - 1] == 'a' || input[i][j - 1] == 'i') && (input[i + 1][j] == 'a' || input[i + 1][j] == 'i') && (input[i - 1][j] == 'a' || input[i - 1][j] == 'i'))
	// 			std::cout << "\e[0;46;30m" << origin[i][j] << "\e[0m";
	// 		else
	// 			std::cout << "\e[0;33m" << origin[i][j] << "\e[0m";
	// 	}
	// 	std::cout << std::endl;
	// }
	floodFill(1, 1, 0);
	for (size_t i = 1; i < indexLine; i++)
		for (size_t j = 1; j < input[i].length() - 1; j++)
			if (input[i][j] != 'a' && input[i][j] != '0' && input[i][j] != 'S')
				input[i][j] = '.';
	for (size_t i = 1; i < indexLine; i++){
		for (size_t j = 1; j < input[i].length() - 1; j++){
			if (input[i][j] == '.'){
				out++;
			}
		}
	}
	for (size_t i = 0; i < indexLine; i++){
		for (size_t j = 1; j < input[i].length() - 1; j++){
			if (input[i][j] == 'a'){
				if (origin[i][j] == '|')
					std::cout << "\e[0m" << "│" << "\e[0m";
				else if (origin[i][j] == '-')
					std::cout << "\e[0m" << "–" << "\e[0m";
				else if (origin[i][j] == 'J')
					std::cout << "\e[0m" << "╯" << "\e[0m";
				else if (origin[i][j] == 'L')
					std::cout << "\e[0m" << "╰" << "\e[0m";
				else if (origin[i][j] == 'F')
					std::cout << "\e[0m" << "╭" << "\e[0m";
				else if (origin[i][j] == '7')
					std::cout << "\e[0m" << "╮" << "\e[0m";
			}
			else if (input[i][j] == '.')
				std::cout << "\e[0;31m" << '.' << "\e[0m";
			else
				std::cout << "\e[0;31m" << input[i][j] << "\e[0m";
		}
		std::cout << std::endl;
	}


	std::cout << "Answer: " << out << std::endl;

}
