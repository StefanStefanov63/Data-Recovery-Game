/**
*
* Solution to course project # 12
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Stefan Stefanov
* @idnumber 3MI0600574
* @compiler VS
*
* <file with all code for the project>
*
*/
#include <iostream>
#include <fstream>

const int MIN = 0;
const int MAX = 5;
const int BUFFER = 1024;
const int FAILVALUE = -10;

enum Color
{
	WHITE = 0,
	RED = 1,
	GREEN = 2
};

struct CurrentGame
{
	char input[BUFFER] /*= "C:\Users\Admin\Desktop\input.txt"*/;
	char text[BUFFER] = "The quick brown fox jumped over the lazy dog.\0";
	std::ifstream ifs;
	std::ofstream ofs;
	double randomiser = FAILVALUE;
	Color* color = nullptr;
	int* words = nullptr;
	int errors = 0;
	int wordsCount = 0;
	char* corr = nullptr;
};

bool isLetter(char symbol);
bool isBlank(char symbol);
bool isUnpritable(char symbol);

char* createDinamicChar(int n);
void freeDinamicChar(char*& str);
Color* createDinamicColor(int n);
int* createDinamicInt(int n);
void freeDinamicInt(int*& num);
void freeDinamicColor(Color*& color);
void freeCurentGame(CurrentGame& game);

int strlenght(const char* str);
char* strcopy(const char* str);

int countLetters(const char* str);
int* countWords(const char* str, int& wordsCount);

char* corruptText(const char* str, Color* color,double randomiser);
bool corruptLetter(char& symbol,int& letters);
char invertAtPosition(char symbol, int n);
bool isPartOfWordCorr(const Color* color, int start, int end);
int calculateStartAndEndOfWord(const int* wordsIndexes, int wordNumber, int& start, int& end);
void changeCharTo(char sym);

int randomInt(int min, int max);
bool yesOrNo();

void printColored(const char* str, const Color* color);
void printColored(const char* str, const Color* color,int start,int end);


void getInputData(CurrentGame& game);
void extractSaveGame(CurrentGame& game);
void saveGame(CurrentGame& game);
void exitGame();
bool isSaveFileCompatable(const CurrentGame& game);

void start(CurrentGame& game);
void play(CurrentGame& game);
void chosenWord(CurrentGame& game, int wordNumber);
void chosenLetter(CurrentGame& game, int wordNumber, int letterNumber);

int main()
{
	std::srand(std::time(0));
	CurrentGame game = {};
	start(game);
	freeCurentGame(game);
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

Color* createDinamicColor(int n)
{
	Color* color = new Color[n] {WHITE};
	return color;
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

void freeDinamicColor(Color*& color)
{
	delete[] color;
	color = nullptr;
}

void freeCurentGame(CurrentGame& game)
{
	freeDinamicChar(game.corr);
	freeDinamicColor(game.color);
	freeDinamicInt(game.words);
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
	if (str == nullptr)
		return nullptr;

	wordsCount = 0;
	int lenght = strlenght(str);
	
	if (!isBlank(str[0]))
		wordsCount++;
	for (int i = 1; str[i]; i++)
	{
		if (isBlank(str[i - 1]) && !isBlank(str[i]))
		{
			wordsCount++;
		}
	}

	int* wordIndexes = createDinamicInt(2*wordsCount),n=0;
	if (!isBlank(str[0]))
	{
		wordIndexes[n] = 0;
		n++;
	}
	for (int i = 1; i<lenght; i++)
	{
		if (isBlank(str[i-1]) && !isBlank(str[i]))
		{
			wordIndexes[n] = i;
			n++;
		}
		if((!isBlank(str[i]) && isBlank(str[i+1])))
		{
			wordIndexes[n] = i;
			n++;
		}
	}
	
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

void printColored(const char* str, const Color* color)
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

void printColored(const char* str, const Color* color, int start, int end)
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

char* corruptText(const char* str, Color* color, double randomiser)
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

void getInputData(CurrentGame& game)
{
	system("cls");

	std::cout << "The absolute/relative path to a text file (.txt)(type 0 to exit game):\n";
	while (true)
	{
		std::cin.getline(game.input, BUFFER);
		if (game.input[0] == '0')
			exitGame();
		game.ifs.open(game.input);

		if (!game.ifs.is_open())
			std::cout << "Error! The entered path didn't open!\n";
		else 
		{
			game.ifs.getline(game.text, BUFFER);
			game.color = createDinamicColor(strlenght(game.text));
			game.words = countWords(game.text, game.wordsCount);
			game.ifs.close();
			break;
		}
	}

	std::cout << "Real number (between 0 and 1) - to what degree the text is corrupted(type -1 to exit game):\n";
	while (true)
	{
		std::cin >> game.randomiser;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			game.randomiser = FAILVALUE;
		}
		if (game.randomiser == -1)
			exitGame();
		else if (game.randomiser < 0 || game.randomiser > 1)
			std::cout << "Input must be a real number between 0 and 1\n";
		else
		{
			game.corr = corruptText(game.text, game.color, game.randomiser);
			break;
		}
	}
}

void extractSaveGame(CurrentGame& game)
{
	system("cls");

	std::cout << "The absolute/relative path to a text file (.txt)(type 0 to exit game):\n";
	while (true)
	{
		std::cin.getline(game.input, BUFFER);
		if (game.input[0] == '0')
			exitGame();
		game.ifs.open(game.input);

		if (!game.ifs.is_open())
			std::cout << "Error! The entered path didn't open!\n";
		else
		{
			game.ifs.getline(game.text, BUFFER);
			game.corr = strcopy(game.text);
			int lenght = strlenght(game.text);
			game.ifs.getline(game.corr, lenght + 1);
			game.color = createDinamicColor(lenght);
			game.words = countWords(game.text, game.wordsCount);
			for (int i = 0; game.text[i]; i++)
			{
				int temp;
				game.ifs >> temp; 
				if (temp == WHITE)
					game.color[i] = WHITE;
				else if (temp == RED)
					game.color[i] = RED;
				else if (temp == GREEN)
					game.color[i] = GREEN;
			}
			game.ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			game.ifs >> game.errors;
			game.ifs.close();
			if (!isPartOfWordCorr(game.color, 0, lenght) || lenght != strlenght(game.corr) || !isSaveFileCompatable(game))
			{
				std::cout << "Error! Unsuported file format!\n";
				exitGame();
			}
			break;
		}
	}
}

void start(CurrentGame& game)
{
	std::cout << "[0]Start base Game!\n";
	std::cout << "[1]Start new Game!\n";
	std::cout << "[2]Continue Game?\n";
	std::cout << "[3]Exit\n";

	while (true) 
	{
		int n;
		std::cin >> n;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			n = FAILVALUE;
		}
		if (n < 0 || n>3)
			std::cout << "input must be an integer 0, 1, 2 or 3\n";
		else if (n == 0)
		{
			game.randomiser = 0.5;
			game.color = createDinamicColor(strlenght(game.text));
			game.words = countWords(game.text, game.wordsCount);
			game.corr = corruptText(game.text, game.color, game.randomiser);
			break;
		}
		else if (n == 1)
		{
			std::cin.ignore();
			getInputData(game);
			break;
		}
		else if (n == 2)
		{
			std::cin.ignore();
			extractSaveGame(game);
			break;
		}
	}
	play(game);
}

void play(CurrentGame& game)
{
	while (true)
	{
		system("cls");

		if (!isPartOfWordCorr(game.color, 0, strlenght(game.text)))
		{
			printColored(game.corr, game.color);
			std::cout << "\nCongratulations you recovered the data to its original state with " << game.errors << " errors!";
			exitGame();
		}

		printColored(game.corr, game.color);
		std::cout << "\n[0]To exit without saving";
		std::cout << "\n[-1]To exit and save";
		std::cout << "\nEnter the number of the word you wish to inspect:\n";
		while (true)
		{
			int n;
			std::cin >> n;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Input must be an integer\n";
				n = FAILVALUE;
			}
			else if (n == 0)
				exitGame();
			else if(n == -1)
				saveGame(game);
			else if (n < -1 || n > game.wordsCount)
				std::cout << "Input must be an integer -1 or above and must not exede the number of words\n";
			else if(!isPartOfWordCorr(game.color, game.words[2 * (n - 1)], game.words[2 * (n - 1) + 1]))
				std::cout << "The word must be corrupted\n";
			else
			{
				chosenWord(game, n);
				break;
			}
		}
	}
}

void chosenWord(CurrentGame& game, int wordNumber)
{
	while (true)
	{
		system("cls");

		int wordIndex = wordNumber - 1,
			wordStart = game.words[2 * wordIndex],
			wordEnd = game.words[2 * wordIndex + 1],
			wordLenght = wordEnd - wordStart + 1,
			charIndex = game.words[2 * wordIndex] - 1;

		if (!isPartOfWordCorr(game.color, wordStart, wordEnd))
			break;

		printColored(game.corr, game.color);
		std::cout << "\nSelected word is: ";
		printColored(game.corr, game.color, wordStart,wordEnd);

		std::cout << "\n[-1] To exit without saving\n";
		std::cout << "[-2] To exit and save\n";
		std::cout << "Enter the number of the character in this word you wish to inspect (0 to cancel):\n";

		while (true)
		{
			int n;
			std::cin >> n;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Input must be an integer\n";
				n = FAILVALUE;
			}
			else if (n == 0)
				return;
			else if (n == -1)
				exitGame();
			else if (n == -2)
				saveGame(game);
			else if (n < -2 || n > wordLenght)
				std::cout << "Input must be a positive integer less then word lenght\n";
			else if (game.color[charIndex + n] != RED)
				std::cout << "The letter MUST be corrupted\n";
			else
			{
				chosenLetter(game, wordNumber, n);
				break;
			}
		}
	}
}

void chosenLetter(CurrentGame& game, int wordNumber, int letterNumber)
{
	int curentErrors = game.errors;
	while (true)
	{
		system("cls");

		int wordIndex = wordNumber - 1,
			wordStart = game.words[2 * wordIndex],
			wordEnd = game.words[2 * wordIndex + 1],
			wordLenght = wordEnd - wordStart + 1,
			charIndex = game.words[2 * wordIndex] + letterNumber - 1;
		char letter = game.corr[charIndex];

		if (game.color[charIndex] == GREEN)
			break;

		if (curentErrors != game.errors)
			std::cout << "Your last guess was an error!\nCount : " << game.errors << " \n";

		printColored(game.corr, game.color);
		std::cout << "\nSelected word is: ";
		printColored(game.corr, game.color, wordStart, wordEnd);
		std::cout << "\nSelected char is:";
		for (int i = 0; i < letterNumber; i++)
			std::cout << " ";
		std::cout << "^\n";

		std::cout << "\nChoose what to change the selected character to:\n";
		changeCharTo(letter);

		while (true)
		{
			int n;

			std::cin >> n;

			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Input must be an integer\n";
				n = FAILVALUE;
			}
			else if (n == 0)
				return;
			else if (n == -1)
				exitGame();
			else if (n == -2)
				saveGame(game);
			else if (n < -2 || n > 6)
				std::cout << "Input must be an integer -1 or above and must not exede the number of options\n";
			else
			{
				char k=  invertAtPosition(letter, n - 1);
				if (k == game.text[charIndex])
				{
					game.corr[charIndex] = k;
					game.color[charIndex] = GREEN;
					std::cout << "Input must be an integer -1 or above and must not exede the number of options\n";
				}
				else
					game.errors++;
				break;
			}
		}
	}
}

bool isPartOfWordCorr(const Color* color, int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		if (color[i] == RED)
			return true;
	}
	return false;
}

int calculateStartAndEndOfWord(const int* wordsIndexes, int wordIndex, int& start, int& end)
{
	start = wordsIndexes[2 * wordIndex];
	end = wordsIndexes[2 * wordIndex + 1];;
	return  end - start + 1;
}

void changeCharTo(char sym)
{
	std::cout << "[0] Cancel\n";
	for (int i = 0; i < 6; i++)
	{
		std::cout << "[" << i + 1 << "] " << invertAtPosition(sym, i) << "\n";
	}
	std::cout << "Your choice:\n";
}

void saveGame(CurrentGame& game)
{
	game.ofs.open(game.input, std::ios::out);
	if (game.ofs.is_open()) 
	{
		game.ofs << game.text << '\n';
		game.ofs << game.corr << '\n';
		for (int i = 0; game.text[i]; i++)
		{
			game.ofs << game.color[i] << ' ';
		}
		game.ofs << '\n';
		game.ofs << game.errors;
		game.ofs.close();
		std::cout << "Game saved!\n";
		exitGame();
	}
	else
	{
		std::cout << "Error! The path didn't open! Couldn't save!\n";
	}
}

void exitGame()
{
	std::cout << "\nThanks for playing!";
	exit(0);
}

bool isSaveFileCompatable(const CurrentGame& game)
{
	for (int i = 0; game.text[i]; i++)
	{	
		if (game.color[i] == RED)
		{
			bool reversable = false;
			for (int j = 0; j < 6; j++)
			{
				if (game.text[i] == invertAtPosition(game.corr[i], j))
					reversable = true;
			}
			if (!reversable)
				return false;
		}

		else if ((game.text[i] == game.corr[i]) && (game.color[i] == RED))
			return false;
		else if (isBlank(game.text[i]) && !isBlank(game.corr[i]))
			return false;
		else if (!isBlank(game.text[i]) && isBlank(game.corr[i]))
			return false;
		else if (isBlank(game.text[i]) && (game.color[i] == RED))
			return false;
		else if (!isLetter(game.text[i]) && (game.color[i] == RED))
			return false;
		else if ((game.text[i] != game.corr[i]) && (game.color[i] != RED))
			return false;
		else if (game.color[i] < 0 || game.color[i] > 2)
			return false;
		else if (game.errors < 0)
			return false;
	}
	return true;
}
