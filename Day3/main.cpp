#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
int fabric[1000][1000] = {0};

struct Claim
{
	int ID;
	int startX;
	int startY;
	int width;
	int height;
	int overlaps;
};

vector<Claim> GetClaims();
void MapClaim(Claim);
void CheckClaim(Claim);

int main(){
	vector<Claim> claims;
	claims = GetClaims();
	system("pause");
}



vector<Claim> GetClaims(){
	int overLapping = 0;
	vector<Claim> dataIn;
	ifstream fs("input.txt");
	string currentStringIn;
	while(getline(fs, currentStringIn)){
		int id, x, y, w, h;
		sscanf(currentStringIn.c_str(), "#%d @ %d,%d: %dx%d", &id, &x, &y, &w, &h);
		Claim currentClaim = {id, x, y, w, h, 0};
		dataIn.push_back(currentClaim);
		MapClaim(currentClaim);

	}
	fs.close();
	fs.clear();
	for(int i = 0; i < 1000; i++){
		for(int j = 0; j < 1000; j++){
			if(fabric[i][j] == 2){
				overLapping++;
			}
			else{}
		}
	}
	cout<<"Total overlaps = "<<overLapping<<endl<<endl;
	for(vector<Claim>::iterator it = dataIn.begin(); it != dataIn.end(); ++it){
		CheckClaim(*it);
	}

	return dataIn;
}


void MapClaim(Claim myClaim){
	for(int i = myClaim.startX; i < myClaim.startX + myClaim.width; i++){
		for(int j = myClaim.startY; j < myClaim.startY + myClaim.height; j++){
			if(fabric[i][j] == 0){
				fabric[i][j] = 1;
			}
			else if( fabric[i][j] == 1){
				fabric[i][j] = 2;
			}
		}
	}	
}

void CheckClaim(Claim myClaim){
	for(int i = myClaim.startX; i < myClaim.startX + myClaim.width; i++){
		for(int j = myClaim.startY; j < myClaim.startY + myClaim.height; j++){
			if(fabric[i][j] == 2){
				myClaim.overlaps++;
			}
		}
	}
	if(myClaim.overlaps == 0){
		cout<<"The Claim without any overlaps: "<<myClaim.ID<<endl<<endl;
	}
}