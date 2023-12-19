#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <climits>

typedef struct s_rule{
	std::string	param, dest;
	int			tresh, more;
}				t_rule;

typedef struct s_flow{
	std::string name;
	t_rule		rules[4];
	int			nRule = 0;
}				t_flow;

typedef struct s_part{
	int data[4];
}				t_part;

long long	nFlow = 0, nPart = 0, out = 0;
t_flow		works[1000];
t_part		parts[1000];

void	printData(){
	for (size_t d = 0; d < nFlow; d++){
		std::cout << works[d].name << std::endl;
		for (size_t j = 0; j < works[d].nRule; j++){
			if (works[d].rules[j].param[0] == 'f')
				std::cout << works[d].rules[j].dest << std::endl;
			else {
				std::cout << works[d].rules[j].param;
				if (works[d].rules[j].more)
					std::cout << " > ";
				else
					std::cout << " < ";
				std::cout << works[d].rules[j].tresh << " : "
				<< works[d].rules[j].dest << std::endl;
			}
		}
		std::cout << std::endl;
	}
	for (size_t d = 0; d < nPart; d++){
		std::cout << d << ": " << "x=" << parts[d].data[0]
		<< "," << "m=" << parts[d].data[1]
		<< "," << "a=" << parts[d].data[2]
		<< "," << "s=" << parts[d].data[3] << std::endl;
	}
}

t_flow findFlow(std::string name){
	for (size_t d = 0; d < nFlow; d++)
		if (works[d].name == name)
			return (works[d]);
	return (works[0]);
}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	long long num = 0, emptyLine = 0;
	while (std::getline(in, line)){
		if (emptyLine == 0){
			int	at = line.find_first_of("{");
			works[nFlow].name = line.substr(0, at);
			at = line.find_first_of("<>");
			while (at != line.npos){
				if (line[at - 1] == 'x')
					works[nFlow].rules[works[nFlow].nRule].param = "x";
				else if (line[at - 1] == 'm')
					works[nFlow].rules[works[nFlow].nRule].param = "m";
				else if (line[at - 1] == 'a')
					works[nFlow].rules[works[nFlow].nRule].param = "a";
				else if (line[at - 1] == 's')
					works[nFlow].rules[works[nFlow].nRule].param = "s";
				if (line[at] == '<')
					works[nFlow].rules[works[nFlow].nRule].more = 0;
				else if (line[at] == '>')
					works[nFlow].rules[works[nFlow].nRule].more = 1;
				works[nFlow].rules[works[nFlow].nRule].tresh = atoi(line.substr(at + 1).c_str());
				int dt = line.find_first_of(":"), ct = line.find_first_of(",");
				works[nFlow].rules[works[nFlow].nRule].dest = line.substr(dt + 1, ct - dt - 1);
				works[nFlow].nRule++;
				for (size_t i = 0; i <= ct; i++)
					line[i] = ' ';
				// std::cout << line << std::endl;
				at = line.find_first_of("<>");
			}
			int	destAt = line.find_first_not_of(" ");
			if (destAt != line.npos){
				works[nFlow].rules[works[nFlow].nRule].param = "f";
				works[nFlow].rules[works[nFlow].nRule].dest = line.substr(destAt, line.length() - 1 - destAt);
				works[nFlow].nRule++;
			}
			nFlow++;
		}
		else if (emptyLine){
			int	at = line.find_first_of("="), nElem = 0;
			while (at != line.npos){
				if (nElem == 0)
					parts[nPart].data[nElem++] = atoi(line.substr(at + 1).c_str());
				else if (nElem == 1)
					parts[nPart].data[nElem++] = atoi(line.substr(at + 1).c_str());
				else if (nElem == 2)
					parts[nPart].data[nElem++] = atoi(line.substr(at + 1).c_str());
				else if (nElem == 3)
					parts[nPart].data[nElem++] = atoi(line.substr(at + 1).c_str());
				for (size_t i = 0; i <= at; i++)
					line[i] = ' ';
				at = line.find_first_of("=");
			}
			nPart++;
		}
		if (line.length() == 0)
			emptyLine = 1;
	}
	printData();
	for (size_t d = 0; d < nPart; d++){
		std::string xmas("xmas"), currFlow("in");
		int rule = 0;
		// std::cout << "Start:\n" << currFlow << std::endl;
		while (1){
			// std::cout << findFlow(currFlow).rules[0].more << std::endl;
			if (findFlow(currFlow).rules[rule].param[0] == 'f'){
				currFlow = findFlow(currFlow).rules[rule].dest;
				rule = 0;
			}
			if (currFlow == "A"){
				std::cout << "Part " << d << " was accepted!!!\n";
				out += parts[d].data[0];
				out += parts[d].data[1];
				out += parts[d].data[2];
				out += parts[d].data[3];
				break ;
			} else if (currFlow == "R"){
				std::cout << "Part " << d << " was rejected!!!\n";
				break ;
			}
			if (!findFlow(currFlow).rules[rule].more){
			std::cout << currFlow << std::endl;

			std::cout << parts[d].data[xmas.find_first_of(findFlow(currFlow).rules[0].param)] << " against " << findFlow(currFlow).rules[rule].tresh << std::endl;

				if (parts[d].data[xmas.find_first_of(findFlow(currFlow).rules[rule].param)] < findFlow(currFlow).rules[rule].tresh){
					currFlow = findFlow(currFlow).rules[rule].dest;
					rule = 0;
				} else
					rule++;
			} else {
			std::cout << currFlow << std::endl;

			std::cout << parts[d].data[xmas.find_first_of(findFlow(currFlow).rules[0].param)] << " against " << findFlow(currFlow).rules[rule].tresh << std::endl;

				if (parts[d].data[xmas.find_first_of(findFlow(currFlow).rules[rule].param)] > findFlow(currFlow).rules[rule].tresh){
					currFlow = findFlow(currFlow).rules[rule].dest;
					rule = 0;
				} else
					rule++;
			}


		}
	}
	std::cout << "Answer: " << out << std::endl;
}

