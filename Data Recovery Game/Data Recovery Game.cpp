
#include <iostream>
#include <fstream>

const int MIN = 0;
const int MAX = 5;
const int RED = 31;
const int GREEN = 32;
const int BUFFER = 1024;

bool isLetter(char symbol);
bool isBlank(char symbol);
char* createDinamicChar(int n);
void freeDinamicChar(char*& str);
int* createDinamicInt(int n);
void freeDinamicInt(int*& num);
int strlenght(const char* str);
char* strcopy(const char* str);
int countLetters(const char* str);
int* countWords(const char* str, int& wordsCount);
bool corruptLetter(char& symbol,int& letters);
char invertAtPosition(char symbol, int n);
int randomInt(int min, int max);
bool yesOrNo();
void printColored(const char* str, const int* color);
void printColored(const char* str, const int* color,int start,int end);
bool isUnpritable(char symbol);
char* corruptText(const char* str, int* color,double randomiser);
void getInputData(char input[],char text[], std::ifstream& ifs, double randomiser);
void continueGameInputData(char corr[], int color[], std::ifstream& ifs, int errors);
void start(char input[], char text[], std::ifstream& ifs, double& randomiser, char corr[], int color[], int& errors, int words[], int& wordsCount);
void play(char input[], char text[], std::ifstream& ifs, double& randomiser, char corr[], int color[], int& errors, int words[], int& wordsCount);
void chosenWord(char input[], char text[], std::ifstream& ifs, double& randomiser, char corr[], int color[], int& errors, int words[], int& wordsCount,int wordNumber);
void chosenLetter(char input[], char text[], std::ifstream& ifs, double& randomiser, char corr[], int color[], int& errors, int words[], int& wordsCount, int wordNumber, int letterNumber);
void saveGame();
void exitGame();

int main()
{
	std::srand(std::time(0));
	/*char text[] = "The quick brown fox jumped over the lazy dog. ";
	
	std::cout << text;
	double randomiser = 0.5,k=10;
	while (k>0)
	{
		int* color = createDinamicInt(strlenght(text));
		char* corr = corruptText(text, color,randomiser);
		std::cout << "\n";
		printColored(corr, color);
		freeDinamicInt(color);
		freeDinamicChar(corr);
		k--;

	}*/
	//C:\Users\Admin\Desktop\input.txt
	char input[BUFFER],text[BUFFER]="8cats ar bad f";
	std::ifstream ifs;
	double randomiser = -1;
	int* color = nullptr,* words = nullptr,errors=0,wordsCount=0;
	char* corr = nullptr;
	start(input, text, ifs, randomiser, corr, color, errors, words, wordsCount);
	//

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

bool isBlank(char symbol)
{
	bool condition = symbol == ' ' || symbol == '\t' || symbol == '\0' || symbol == '\n';
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

int* createDinamicInt(int n)
{
	int* num = new int[n] {0};
	return num;
}

void freeDinamicInt(int*& num)
{
	delete[] num;
	num = nullptr;
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

int* countWords(const char* str,int& wordsCount)
{
	wordsCount = 0; int k = 0;
	if (!isBlank(str[0]))
		wordsCount++;
	for (int i = 1; str[i]; i++)
	{
		if (isBlank(str[i - 1]) && !isBlank(str[i]))
		{
			wordsCount++;
		}
	}
	int* wordIndexes = createDinamicInt(wordsCount+1),n=1;
	for (int i = 1; str[i]; i++)
	{
		if (isBlank(str[i-1]) && !isBlank(str[i]))
		{
			wordIndexes[n] == i;
			n++;
		}
	}
	wordIndexes[n] = str[k];
	
	return wordIndexes;
}

bool corruptLetter(char& symbol, int& letters)
{
	int rand = randomInt(MIN, MAX);
	char temp = invertAtPosition(symbol, rand);
	if (temp != symbol)
	{
		symbol = temp;
		letters--;
		return true;
	}
	return false;
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

void printColored(const char* str, const int* color)
{
	for (int i = 0; str[i]; i++)
	{
		if (color[i] == RED)
		{ 
			std::cout << "\x1b[1;31m" << str[i]<< "\x1b[1;37m";
		}
		else if (color[i] == GREEN)
		{
			std::cout << "\x1b[1;32m" << str[i]<< "\x1b[1;37m";
		}
		else
			std::cout << str[i];
	}
}

void printColored(const char* str, const int* color, int start, int end)
{
	if (start > end)
		return;
	for (int i = start; i<=end; i++)
	{
		if (color[i] == RED)
		{
			std::cout << "\x1b[1;31m" << str[i] << "\x1b[1;37m";
		}
		else if (color[i] == GREEN)
		{
			std::cout << "\x1b[1;32m" << str[i] << "\x1b[1;37m";
		}
		else
			std::cout << str[i];
	}
}

bool isUnpritable(char symbol)
{
	return ((symbol >= 0 && symbol <= 31) || symbol == 127);
}

char* corruptText(const char* str, int* color, double randomiser)
{
	char* corr = strcopy(str);
	int letters = countLetters(str) * randomiser;

	while (letters > 0)
	{
		for (int i = 0; corr[i]; i++)
		{
			if (isLetter(corr[i]) && (corr[i] == str[i]) )
			{
				if (yesOrNo())
				{
					if (corruptLetter(corr[i], letters))
						color[i] = RED;
				}
			}
			if (letters == 0)
				break;
		}
	}
	return corr;
}

void getInputData(char input[],char text[], std::ifstream& ifs, double randomiser)
{
	//C:\Users\Admin\Desktop\input.txt
	std::cout << "The absolute/relative path to a text file (.txt):\n";
	std::cin.getline(input, BUFFER);
	ifs>> input;
	if (!ifs.is_open()) {
		std::cout << "Error!" << std::endl;
		return;
	}

	while (!ifs.eof())
	{
		ifs.getline(text, BUFFER);
	}

	ifs.close();
	std::cout << "Real number (between 0 and 1) - to what degrer the text is corrupted:\n";
	std::cin >> randomiser;
	while (randomiser < 0 || randomiser>1)
	{
		std::cout << "Input must be a real number between 0 and 1\n";
		std::cin >> randomiser;
	}
}

void continueGameInputData(char corr[], int color[], std::ifstream& ifs, int errors)
{
	if (!ifs.is_open()) {
		std::cout << "Error!" << std::endl;
		return;
	}

	while (!ifs.eof()) {
		ifs.getline(corr, BUFFER);
		for (int i = 0; ifs.peek() != '\n'; i++)
		{
			ifs >> color[i];
		}
		ifs >> errors;
	}

	ifs.close();
}

void start(char input[], char text[], std::ifstream& ifs, double &randomiser, char corr[], int color[], int& errors,int words[], int& wordsCount)
{
	int n;
	std::cout << "[1]Start new Game!\n";
	std::cout << "[2]Continue Game?\n";
	std::cout << "[3]Exit\n";
	std::cin >> n;
	while (n < 1 || n>3)
	{
		std::cout << "input must be an integer 1, 2 or 3\n";
		std::cin >> n;
	}
	switch (n)
	{
	case 1:
	{
		getInputData(input, text, ifs, randomiser);
		color = createDinamicInt(strlenght(text));
		words = countWords(text, wordsCount);
		corr = corruptText(text, color, randomiser);
		break;
	}
	case 2:
	{
		getInputData(input, text, ifs, randomiser);
		corr = strcopy(text);
		color = createDinamicInt(strlenght(text));
		words = countWords(text, wordsCount);
		continueGameInputData(corr, color, ifs, errors);
		break;
	}
	case 3:
		return ;
	}
	play(input, text, ifs, randomiser, corr, color, errors, words, wordsCount);
}

void play(char input[], char text[], std::ifstream& ifs, double& randomiser, char corr[], int color[], int& errors, int words[], int& wordsCount)
{
	while (true)
	{
		printColored(text, color);
		std::cout << "[0]To exit without saving\n";
		std::cout << "[-1]To exit and save\n";
		std::cout << "Enter the number of the word you wish to inspect\n";
		int n = 0;
		std::cin >> n;
		while (n < -1 && n <= wordsCount)
		{
			std::cout << "Input must be an integer -1 or above and must not exede the number of words\n";
			std::cin >> n;
		}
		if (n == 0)
			exitGame();
		else if (n == -1)
			saveGame();
		else
			chosenWord(input, text, ifs, randomiser, corr, color, errors, words, wordsCount, n);
	}
}

void chosenWord(char input[], char text[], std::ifstream& ifs, double& randomiser, char corr[], int color[], int& errors, int words[], int& wordsCount, int wordNumber)
{
	while (true)
	{
		int wordStart = 0, wordEnd = 0, n = 0,wordLenght;
		if (isBlank(text[0]))
		{
			wordStart = words[wordNumber - 1] + 1;
		}
		else
		{
			wordStart = words[wordNumber - 1];
		}
			wordEnd = words[wordNumber ];
		printColored(text, color);
		std::cout << "\nSelected word is: ";
		printColored(text, color);
		std::cout << "[-1]To exit without saving\n";
		std::cout << "[-2]To exit and save\n";
		std::cout << "Enter the number of the character in this word you wish to inspect (0 to cancel):\n";
		int n = 0;
		std::cin >> n;
		while (n < -2 && n <= wordsCount)
		{
			std::cout << "Input must be an integer -1 or above and must not exede the number of letters\n";
			std::cin >> n;
		}
		if (n == -1)
			exitGame();
		else if (n == -2)
			saveGame();
		else
			chosenLetter(input, text, ifs, randomiser, corr, color, errors, words, wordsCount, n);
	}
}

void chosenLetter(char input[], char text[], std::ifstream& ifs, double& randomiser, char corr[], int color[], int& errors, int words[], int& wordsCount, int wordNumber, int letterNumber)
{
}

void saveGame()
{
}
