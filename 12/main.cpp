#include <iostream>
#include <fstream>
#include <sstream>

typedef struct s_entry{
	std::string	rec;
	int			groups[50], nGroups = 0, group = 0, amount = 0, permutation = 1;
}				t_entry;

t_entry		data[5000];
long long	out = 0, nEntry = 0;

void	printData(){
	for (size_t i = 0; i < nEntry; i++){
		std::cout << data[i].rec << " ";
		for (size_t j = 0; j < data[i].nGroups; j++)
			std::cout << data[i].groups[j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void permute(std::string a, int e, int l){
	// std::cout << a << std::endl;
	// std::string copy(a);
	// int	hashAt = copy.find_first_of("#"), correct = 1, pos = 0;
	// while (hashAt != copy.npos){
	// 	int n = 0;
	// 	for (size_t i = hashAt; copy[i] == '#'; i++){
	// 		copy[i] = ' ';
	// 		n++;
	// 	}
	// 	// std::cout << n << " comparing to " << data[e].groups[pos] << std::endl;
	// 	if (n != data[e].groups[pos]){
	// 		correct = 0;
	// 		break ;
	// 	}
	// 	pos++;
	// 	hashAt = copy.find_first_of("#");
	// }
	// if (correct && pos == data[e].nGroups && copy.find_first_of('?') == copy.npos){
	// 	std::cout << a << " is correct!!" << std::endl;
	// 	out++;
	// }
	std::cout << a << " Amount: " << data[e].amount << " Till amount: " << data[e].groups[data[e].group] << std::endl;
	if (l == a.length())
		return ;
	if (a[l] == '?')
	{
		if (data[e].amount < data[e].groups[data[e].group]){
			data[e].amount++;
			permute(a.replace(l, 1, "#"), e, l + 1);
		}
		else if (data[e].amount == data[e].groups[data[e].group]){
			data[e].group++;
			data[e].amount = 0;
			permute(a.replace(l + 1, 1, "."), e, l + 1);

		}
		permute(a.replace(l, 1, "."), e, l + 1);

	}
	else if (a[l] == '#'){
		if (data[e].amount < data[e].groups[data[e].group]){
			data[e].amount++;
			permute(a, e, l + 1);
		}
		else if (data[e].amount == data[e].groups[data[e].group]){
			data[e].group++;
			data[e].amount = 0;
			permute(a.replace(l + 1, 1, "."), e, l + 1);

		}
	}
	else if (a[l] == '.'){
		if (data[e].amount == data[e].groups[data[e].group]){
			data[e].group++;
			data[e].amount = 0;
			permute(a, e, l + 1);
		}
		else {

		}
	}

}

int main(void){
	std::fstream in;
	in.open("input.txt", std::ios::in);
	std::string	line;
	while (std::getline(in, line)){
		int spaceAt = line.find_first_of(" ");
		if (spaceAt != line.npos)
			data[nEntry].rec = line.substr(0, spaceAt);
		int	numAt = line.find_first_of("0123456789");
		while (numAt != line.npos){
			std::string numS = line.substr(numAt);
			int num = atoll(numS.c_str());
			data[nEntry].groups[data[nEntry].nGroups++] = num;
			for (size_t i = numAt; isdigit(line[i]); i++){
				line[i] = ' ';
			}
			numAt = line.find_first_of("0123456789");
		}
		nEntry++;
	}
	for (size_t i = 0; i < nEntry; i++){
		std::cout << "\n" << i + 1 << ": " << std::endl;
		// std::string copy(data[i].rec);
		// data[i].rec.append("?");
		// data[i].rec.append(copy);
		// data[i].rec.append("?");
		// data[i].rec.append(copy);
		// data[i].rec.append("?");
		// data[i].rec.append(copy);
		// data[i].rec.append("?");
		// data[i].rec.append(copy);
		// for (int g = 0; g < 5 * data[i].nGroups; g++)
		// 	data[i].groups[g] = data[i].groups[g % data[i].nGroups];
		// data[i].nGroups = data[i].nGroups * 5;
		// std::cout << data[i].rec << std::endl;
		// for (size_t j = 0; j < data[i].nGroups; j++)
		// 	std::cout << data[i].groups[j] << " ";
		permute(data[i].rec, i, 0);
	}
	// printData();
	std::cout << "Answer: " << out << std::endl;
}
