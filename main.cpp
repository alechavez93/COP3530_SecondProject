#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>

#include<algorithm>


using namespace std;

//Realm => R
int getMinChanges (string R1, string R2);
int getMaxIncantation (string R);

int main () {

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


int getMinChanges (string R1, string R2) {
	vector<vector<int>> ar;
	int rows = R1.size () + 1;
	ar.resize (rows);
	for (int i = 0; i < rows; i++) {
		ar[i].resize (R2.size () + 1);
	}

	for (int i = 0; i <= R1.size (); i++) {
		for (int j = 0; j <= R2.size(); j++) {

			if (i==0) {
				ar[i][j] = j;
			}
			else {
				if (j==0) {
					ar[i][j] = i;
				}
				else {
					if (R1[i-1]==R2[j-1]) {
						ar[i][j] = ar[i - 1][j - 1];
					}
					else {
						ar[i][j] = 1 + min (min (ar[i][j - 1], ar[i - 1][j]), ar[i - 1][j - 1]);
					}
				}
			}


		}

	
	}


	return ar[R1.size ()][R2.size ()];

}
