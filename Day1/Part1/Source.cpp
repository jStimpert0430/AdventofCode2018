#include <fstream>
#include <iostream>
using namespace std;

int main(){
	ifstream fs("input.txt");
	int sum = 0;
	int currentLine = 0;

	if(!fs){
		cout << "Could not read file\n";
		system("pause");
		exit(1);
	}

	while (fs >> currentLine) {
		cout << "Current Freq = " << sum << " | Next Freq Change: " << currentLine << endl;
		sum += currentLine;
	}

	fs.close();
	cout << endl <<"The total change in frequencey is " << sum << endl;
	system("pause");
	return 0;
}