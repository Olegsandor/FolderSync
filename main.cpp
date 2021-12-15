#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "foldSync.h"

using namespace std;

#include <filesystem>

using namespace filesystem;


void readPathsFromFile(string cfgPath, vector<std::string>& paths)
{
	ifstream file(cfgPath);
	if (file.fail())
		throw invalid_argument("Can't find the file named \"" + cfgPath + "\"");
	for (string i; getline(file, i); paths.push_back(i));
	file.close();
}

void foldersSync(string cfgPath) {
	vector<string> foldPaths;
	int stillWanted = 1;
	foldSync syncronizer;
	while (stillWanted) 
	{
		try {
			stillWanted = 0;
			readPathsFromFile(cfgPath, foldPaths);
		}
		catch (invalid_argument err) 
		{
			cout << err.what() << endl
				<< "would you like to choose anoter?(y/n)" << endl;
			char i;
			for (i = ' '; i != 'y' && i != 'n'; cin >> i);
			if (i == 'y') {
				cout << "Enter a new file name: ";
				cin >> cfgPath;
				stillWanted = 1;
				continue;
			}
			else return;
		}
		try {
			syncronizer = foldPaths;
		}
		catch (invalid_argument err)
		{
			cout << err.what() << endl
			<< "would you like to choose anoter file?(y/n)" << endl;
			char i;
			for (i = ' '; i != 'y' && i != 'n'; cin >> i);
			if (i == 'y') {
				cout << "Enter a new file name: ";
				cin >> cfgPath;
				stillWanted = 1;
			}
			else return;
		}
	}
	cout << "The programm will syncronize folders from a file \"" << cfgPath << "\"" << endl;
	for (auto i : foldPaths)
		cout << i << endl;
	cout << "Would you like to continue?(y/n)" << endl;
	char i;
	for (i = ' '; i != 'y' && i != 'n'; cin >> i);
	stillWanted = (i == 'y') ? 1 : 0;
	while (stillWanted) {
		syncronizer.sync();
		cout << "Do you want to syncronize them once more?(y/n)" << endl;
		char i;
		for (i = ' '; i != 'y' && i != 'n'; cin >> i);
		stillWanted = (i == 'y') ? 1 : 0;
	}
}

int main(int argc, char *argv[])
{
	string cfgPath = "folders.cfg";
	if (argc != 1)
		cfgPath = argv[1];
	foldersSync(cfgPath);
	return 0;
}
