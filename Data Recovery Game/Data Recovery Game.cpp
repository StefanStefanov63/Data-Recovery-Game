
#include <iostream>
#include <bitset>
bool isLetter(char symbol);
char* createDinamicChar(int n);
void freeDinamicChar(char*& str);
int strlenght(const char* str);
char* strcopy(const char* str);
int countLetters(const char* str);
void corruptLetter(char& symbol,int& letters);
char invertAtPosition(char symbol, int n);
int randomInt(int min, int max);
bool yesOrNo();
bool isUnpritable(char symbol);
char* corruptText(const char* str, double percatge);
const int MIN = 0;
const int MAX = 5;

int main()
{
	std::srand(std::time(0));
	char text[] = "The quick brown fox jumped over the lazy dog. ";
	std::cout << text;
	double randomiser = 0.5,k=100;
	while (k>0)
	{
		char* corr = corruptText(text, randomiser);
		std::cout <<  '\n' << corr;
		freeDinamicChar(corr);
		k--;

	}
	/*std::cout << std::bitset<8>('{') << "\n";
	std::cout << std::bitset<8> (invertAtPosition('o',0))<< " "<< invertAtPosition('o', 0) << "\n";
	std::cout << std::bitset<8>(invertAtPosition('o', 1)) << " " << invertAtPosition('o', 1) << "\n";
	std::cout << std::bitset<8>(invertAtPosition('o', 2)) << " " << invertAtPosition('o', 2) << "\n";
	std::cout << std::bitset<8>(invertAtPosition('o', 3)) << " " << invertAtPosition('o', 3) << "\n";
	std::cout << std::bitset<8>(invertAtPosition('o', 4)) << " " << invertAtPosition('o', 4) << "\n";
	std::cout << std::bitset<8>(invertAtPosition('o', 5)) << " " << invertAtPosition('o', 5) << "\n";*/
}

bool isLetter(char symbol)
{
	bool condition = (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
	return condition;
}

char* createDinamicChar(int n)
{
	char* str = new char[n+1] {};
	str[n] = '\0';
	return str;
}

void freeDinamicChar(char*& str)
{
	delete[] str;
	str = nullptr;
}

int strlenght(const char* str)
{
	int lenght = 0;
	while (str[lenght])
		lenght++;

	return lenght;
}

char* strcopy(const char* str)
{
	int lenght = strlen(str);
	char* copy = createDinamicChar(lenght);
	for (int i = 0; str[i]; i++)
			copy[i] = str[i];
	
	return copy;
}

int countLetters(const char* str)
{
	int letters = 0;
	while (*str)
	{
		if (isLetter(*str))
			letters++;
		str++;
	}
	return letters;
}

void corruptLetter(char& symbol, int& letters)
{
	int rand = randomInt(MIN, MAX);
	char temp = invertAtPosition(symbol, rand);
	if (temp != symbol)
	{
		symbol = temp;
		letters--;
	}
}
char invertAtPosition(char symbol, int n)
{
	char temp = symbol ^(1 << n);

	//when temp is 01111111 or 127 for instance it is not pritable
	//whus we return the original

	if(isUnpritable(temp))
		return symbol;
	else
		return temp;
}

int randomInt(int min, int max)
{
	int rand = min + std::rand() % (max - min + 1);
	return rand;
}

bool yesOrNo()
{
	return std::rand() % 2;
}

bool isUnpritable(char symbol)
{
	return ((symbol >= 0 && symbol <= 31) || symbol == 127);
}


char* corruptText(const char* str, double percatge)
{
	char* corr = strcopy(str);
	int letters = countLetters(str) * percatge;

	while (letters > 0)
	{
		for (int i = 0; corr[i]; i++)
		{
			if (isLetter(corr[i]) && (corr[i] == str[i]) )
			{
				if (yesOrNo())
					corruptLetter(corr[i],letters);
			}
			if (letters == 0)
				break;
		}
	}
	return corr;
}
