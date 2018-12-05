#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

	int highestNum = 0;
	int highestNumVal = 0;
	int highestGuardID = 0;

struct Shift
{
	int sleepTimeMinutes;
	int WakeTimeMinutes;
};

struct Guard{
	int id;
	int totalTimeSlept;
	vector<Shift> shifts;
	int minutes[60];
	int sleepTimeMinutes;
	int WakeTimeMinutes;
};

struct guard_functor
{
    bool operator()(pair<const int&, const Guard&> x, pair<const int&, const Guard&> y) const
    {
        return x.second.sleepTimeMinutes < y.second.sleepTimeMinutes; 
    }
};

vector<string> GetInputSorted();
void createShiftFromString(string, map<int, Guard>& guards, int& currentGuardID);

int main(){
	vector<string> dataIn = GetInputSorted();
	map<int, Guard> guards;
	int currentGuardID = 0;
	for(vector<string>::iterator it = dataIn.begin(); it != dataIn.end(); ++it){
		createShiftFromString(*it, guards, currentGuardID);
	}


	for(map<int, Guard>::iterator it = guards.begin(); it != guards.end(); ++it){
		Guard thisGuard = it->second;
		for(int i = 0; i < 60; i++){
			thisGuard.totalTimeSlept += thisGuard.minutes[i];
		}
		cout<<endl<<thisGuard.id<<"| Total Time slept: "<<thisGuard.totalTimeSlept<<endl;
		int count = 0;
		for(int i = 0; i < 60; i++){
			cout<<" | minute ("<<i<<"): "<<thisGuard.minutes[i];
			if(count > 9){
				cout<<endl;
				count = 0;
				
			}
			count++;
		}
		cout<<endl;
	}
	system("pause");
	return 0;
}

vector<string> GetInputSorted(){
	vector<string> dataIn;
	ifstream fs("input.txt");
	string currentStringIn;
	while(getline(fs, currentStringIn)){
		dataIn.push_back(currentStringIn);
	}
	fs.close();
	fs.clear();
	sort(dataIn.begin(), dataIn.end());
	return dataIn;
}

void createShiftFromString(string inString, map<int, Guard>& guards, int& currentGuardID){
	int year, month, day, minute, hour, id;
	char command[50];
	sscanf(inString.c_str(), "[%d-%d-%d %d:%d] %[^\n] ", &year, &month, &day, &hour, &minute, command);
	string commandStr = command;

	if(commandStr.find("wakes") != string::npos){
		guards[currentGuardID].shifts.back().WakeTimeMinutes = minute;
		for(int i = guards[currentGuardID].shifts.back().sleepTimeMinutes; i < guards[currentGuardID].shifts.back().WakeTimeMinutes; i++){
			guards[currentGuardID].minutes[i] += 1;
		}
	}

	else if(commandStr.find("falls") != string::npos){
		guards[currentGuardID].shifts.back().sleepTimeMinutes = minute;
	}

	else if(commandStr.find('#') != string::npos){
		auto id = stoi(commandStr.substr(commandStr.find('#') + 1, commandStr.find(' ') - 1));
		bool newID = true;
		for(map<int, Guard>::iterator it = guards.begin(); it != guards.end(); ++it){
			Guard currentCheck = it->second;
			if(currentCheck.id == id){
				newID = false;
				currentGuardID = id;
			}
		}
		if(newID == true){
			Guard newGuard = {id, 0};
			guards.insert(make_pair(id, newGuard));
			currentGuardID = id;
		}
		Shift newShift = { 0, 0};
		guards[currentGuardID].shifts.push_back(newShift);
	}
}
