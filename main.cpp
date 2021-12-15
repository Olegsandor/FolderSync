#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "foldSync.h"
#include <chrono>
#include <thread>

using namespace std;


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
	cout << "if you like to continue, enter delay between syncronizations in minutes(or 0 to do it once or -1 to exit): ";
	int time;
	cin >> time;
	if (time == -1)
		return;
	if (!time){
		syncronizer.sync();
		return;
	}
	cout << "There is no way to stop the program except for ctrl + c for now" << endl;
	while (true) {
		syncronizer.sync();
		cout << "Folders synced" << endl;
		this_thread::sleep_for(chrono::minutes(time));
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
