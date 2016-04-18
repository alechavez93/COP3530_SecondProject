#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

//Charm for a centain Realm => C
int getMaxChanges(string C1, string C2);
int getMaxIncantation(string C);

int main() {

	//N -> number of realms    M -> number of magi   P -> power of magi
	int N, M, P;	string charm;
	vector<int> listOfMagi;


	//unordered map to save the whole input
	unordered_map<string, vector<int>> Realms;
	unordered_map < string, vector<int>>::iterator it;


	//Getting input
	cin >> N;
	for (int i = 0; i < N; i++) {

		cin >> charm; cin >> M;

		//Filling the vector with the magi's powers
		for (int j = 0; j < M; j++) {
			cin >> P;
			listOfMagi.push_back(P);
		}

		//Creating a Realm as a pair
		Realms.insert(make_pair(charm, listOfMagi));
		listOfMagi.clear();
	}



	//Check input was collected correctly
	for (it = Realms.begin(); it != Realms.end(); it++) {
		cout << "Charm: " << it->first << endl;

		for (int i = 0; i < it->second.size(); i++) {
			cout << it->second[i] << " ";
		}
		cout << endl << endl;
	}


	system("pause");
	return 0;
}