#include <iostream>		
#include <vector>		// For weblog and pages
#include <string>		// For string
#include <fstream>		// For ifstream
#include <cstddef>		// For size_t
#include <iomanip>		// For setpresision
#include <windows.h>	// For color
using namespace std;


class Bag {
public:
	void loadWeblog();				// This member function loads data into weblog vector
	void loadPages();				// This member function loads data into pages vector
	void openFile(int);				// This member function opens weblog file nad pages file
	void display();					// This member function display the IP and pages
	class ErrorOpeningFile {};		// This class uses to catch error
private:
	vector<string> weblog;
	vector<string> pages;
	ifstream inputFile;

};


void Bag::openFile(int a) {
	if (a == 1) {												// This function uses parameter a to decide which file to open
		inputFile.open("weblog.txt");							// It use try, catch, and throw to open file.
		try {
			if (!inputFile)
				throw ErrorOpeningFile();
			else
				cout << "Open weblog.txt Success" << endl;
		}
		catch (Bag::ErrorOpeningFile) {
			cout << "Error Opening File..." << endl;
		}
	}
	else {
		inputFile.open("weblog_visitedpages_unique.txt");

		try {
			if (!inputFile)
				throw ErrorOpeningFile();
			else
				cout << "Open weblog_visitedpages_unique.txt Success" << endl;
		}
		catch (Bag::ErrorOpeningFile) {
			cout << "Error Opening File..." << endl;
		}
	}
}


void Bag::loadWeblog() {
	int count = 0;
	for (string x;;) {									// This is an infinite loop to load 
		getline(inputFile, x);							// data into the weblog vector
		weblog.push_back(x);
		count++;
		if (count > 2)									// Use count to compare two datas next
			if (weblog[(count)-1] == weblog[(count)-2])	// to each other in a vector. If they are the
				break;									// same exit the infinite loop
	}
	inputFile.close();

}

void Bag::loadPages() {
	int count = 0;										// This function functions exactly the 
	for (string x;;) {									// same as the loadWeblog funtion
		getline(inputFile, x);
		pages.push_back(x);
		count++;
		if (count > 2)
			if (pages[(count)-1] == pages[(count)-2])
				break;
	}
	inputFile.close();
}

void Bag::display() {
	vector<string> showIP;
	vector<string> uniqueIP;
	string tempIP;

	for (int count = 0; count < weblog.size(); count++) {			//This is a double loop. The first loop sets "b" 
		string b = weblog[count];									//variable to vector weblog and then find the charaters
		size_t found = b.find_first_of("0123456789. ");				//"0123456789." The second loop save the charater found into  
		for (int count = 0; count < b.size(); count++) {			//tempIP variable. It is terminated when a "space" is met.
			tempIP.push_back(b[found]);
			found = b.find_first_of("0123456789. ", found + 1);
			if (b[found] == ' ')
				break;
		}
		showIP.push_back(tempIP);
		tempIP.clear();
	}

	for (int count = 0; count < showIP.size() - 1; count++) {		//This loop compare 2 showIP vector next to each other
		if (showIP[count] != showIP[(count)+1])						// in order to  find unique IP
			uniqueIP.push_back(showIP[count]);
	}

	for (int count = 0; count < pages.size() - 1; count++) {	//This loop append a "space" to the end of
		pages[count].append(" ");								// each vector in order to compare the entry
	}															// between weblog and pages.

	for (string x : uniqueIP) {													//This is a triple loop. The first loop
		cout << endl << setw(15) << left << x << "  ";							//print out the unique IP. The second loop
		for (int index = 0; index < weblog.size(); index++) {					//compare the IP to the weblog. The third
			size_t found = weblog[index].find(x);								//loop compare the entry and print out
			if (found != std::string::npos)										//the index page number.
				for (int index1 = 0; index1 < pages.size() - 3; index1++) {
					size_t found1 = weblog[index].find(pages[index1]);
					if (found1 != std::string::npos)
						cout << index1 << "  ";
				}
		}
	}
}

int main() {
	Bag bag1;
	int a = 0;

	bag1.openFile(1);
	bag1.loadWeblog();
	bag1.openFile(0);
	bag1.loadPages();
	bag1.display();


	system("PAUSE");
	return 0;
}

