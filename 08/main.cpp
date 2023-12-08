#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <climits>

typedef struct s_node{
	std::string	name, left, right;
}				t_node;

long long	nnode = 0, out = 0;
t_node		nodes[1000];
int			follow[1000], nfollow = 0;
std::string	inst;

void	printData(){
	std::cout << inst << std::endl;
	for (size_t i = 0; i < nnode; i++){
		std::cout << nodes[i].name << " = ("
		<< nodes[i].left << ", "
		<< nodes[i].right << ")"
		<< std::endl;
	}
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	int	indexLine = 0;
	while (std::getline(in, line)){
		if (indexLine == 0)
			inst = line;
		else if (indexLine > 1){
			nodes[nnode].name = line.substr(0, 3);
			nodes[nnode].left = line.substr(7, 3);
			nodes[nnode].right = line.substr(12, 3);
			nnode++;
		}
		indexLine++;
	}
	// printData();
	for (int i = 0; i < nnode; i++){
		if (nodes[i].name[2] == 'A'){
			std::cout << i << ": " << nodes[i].name << " = ("
			<< nodes[i].left << ", "
			<< nodes[i].right << ")"
			<< std::endl << std::endl;
			follow[nfollow++] = i;
		}
	}

	while (1){
		for (size_t i = 0; i < inst.length(); i++){
			for (size_t fol = 0; fol < nfollow; fol++){
				if (inst[i] == 'L'){
					for (int l = 0; l < nnode; l++){
						if (nodes[l].name == nodes[follow[fol]].left){
							follow[fol] = l;

							break ;
						}
					}
				}
				else if (inst[i] == 'R'){
					for (int l = 0; l < nnode; l++){
						if (nodes[l].name == nodes[follow[fol]].right){
							follow[fol] = l;
							break ;
						}
					}
				}


			}
			out++;
			std::cout << nodes[follow[6]].name << std::endl;
				if (nodes[follow[6]].name[2] == 'Z')
					return (std::cout << "Answer: " << out, 0);

		}
	}


	std::cout << "Answer: " << out;
}
