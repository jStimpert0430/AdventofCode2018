#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void SearchStringForDuplicatesAndIncrement(std::string inString, int &refTwiceCount, int &refThriceCount);
bool CompareStringsForSimilarID(string inStringA, string inStringB);
vector<string> getInput();
void Day2Part1();
void Day2Part2();


int main(){
	cout<<"Day 2 Part 1\n-----------------\n";
	Day2Part1();
	cout<<"Day 2 Part 2\n-----------------\n";
	Day2Part2();
	system("pause");
	return 0;
}

void Day2Part1(){
	int twiceCount = 0;
	int thriceCount = 0;
	vector<string> dataIn = getInput();

	for(std::vector<std::string>::iterator it = dataIn.begin(); it != dataIn.end(); ++it)
		SearchStringForDuplicatesAndIncrement(*it, twiceCount, thriceCount);
	
	cout<<"Total double counts found: "<<twiceCount<<endl;
	cout<<"Total triple counts found: "<<thriceCount<<endl;
	cout<<"Checksum: " <<twiceCount * thriceCount<<endl<<endl;
};

void Day2Part2(){
	vector<string> dataIn = getInput();
	bool matchFound;
	cout<<"Searching ID's for match...\n";
	for(vector<string>::iterator it = dataIn.begin(); it != dataIn.end(); ++it){
		string compareString = *it;
		for(vector<string>::iterator it2 = dataIn.begin(); it2 != dataIn.end(); ++it2){
			matchFound = CompareStringsForSimilarID(compareString, *it2);
			if(matchFound)
				break;
		}
		if(matchFound)
			break;
	}
}

vector<string> getInput(){
	vector<string> dataIn;
	ifstream fs("input.txt");
	string currentStringIn;
	while(fs >> currentStringIn)
		dataIn.push_back(currentStringIn);
	fs.close();
	fs.clear();
	return dataIn;
}


void SearchStringForDuplicatesAndIncrement(std::string inString, int &refTwiceCount, int &refThriceCount){
	bool stringHasTwice = false;
	bool stringHasThrice = false;
	for(int i = 0; i < inString.length(); i++){
		int letterCount = 0;
		for(int j = 0; j < inString.length(); j++){
			if(inString[j] == inString[i])
				letterCount++;
		}
		if(letterCount == 2 && !stringHasTwice){
			stringHasTwice = true;
			refTwiceCount++;
		}
		else if(letterCount == 3 && !stringHasThrice){
			stringHasThrice = true;
			refThriceCount++;
		}
	}

}

bool CompareStringsForSimilarID(string inStringA, string inStringB){
	vector<char> stringDifferences;
	vector<char> stringSimalarities;
	for(int i = 0; i < inStringA.length(); i++){
		if(inStringA[i] != inStringB[i]){
			stringDifferences.push_back(inStringA[i]);
		}
		else
		{
			stringSimalarities.push_back(inStringA[i]);
		}
	}

	if(stringDifferences.size() == 1){
		cout<<"Match found!: IDA = "<<inStringA<<" IDB = "<< inStringB<< " | ID difference: "<< stringDifferences.size()<<" characters"<<endl;
		cout<<"The matching letters found in these strings are: ";
		for(vector<char>::iterator it = stringSimalarities.begin(); it != stringSimalarities.end(); ++it)
			cout<<*it;
		cout<<endl;
		return true;
	}
	else{
		return false;
	}
}