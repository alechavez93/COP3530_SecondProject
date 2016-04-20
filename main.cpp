
#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<algorithm>
#include <functional>
#include <queue>
#include <stdexcept>
using namespace std;

//Struct for the edge
struct edge {
	string charm = "";
	int incantations = 0;
	int gems = 0;

	void initialize(string charm, int weight, int gems) {
		this->charm = charm;
		this->incantations = weight;
		this->gems = gems;
	}
	//operator overload for the priority queue
	bool operator <(const edge& rhs)const {
		return incantations > rhs.incantations;
	}

};


//Struct for the graph node
struct node {
	bool visited = false;
	int incantationsWeight = -1;
	int gemWeight = -1;
	vector<edge> connections;

	void clear() {
		visited = false;
		incantationsWeight = -1;
		connections.clear();
	}

};


//Realm => R
int getMinChanges (string R1, string R2);
vector<int> getMaxIncantation (vector<int> magicianPowers);
int getIndexOfCeiling(int number, vector<int> magicianPowers, vector<int> T, int iniIndex, int endIndex);
unordered_map<string, node> generateGraph(unordered_map<string, vector<int>> input);
vector<int> shortestPath (unordered_map<string, node>graph, string start, string finish);

int main () {

	//N -> number of realms    M -> number of magi   P -> power of magi
	int N, M, P;	string charm;
	//start node where to start, end node where to stop
	string start, end;

	vector<int> listOfMagi;
	vector<int> result;


	//unordered map to save the whole input
	unordered_map<string, vector<int>> Realms;
	unordered_map < string, vector<int>>::iterator it;

	//unordered map which will be the graph
	unordered_map<string, node> graph;


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


	cin >> start >> end;

	graph=generateGraph(Realms);
	cout << endl;
<<<<<<< HEAD
	result = shortestPath (graph, start, end);
	if (result[0] == -1)
	{
		cout << "IMPOSSIBLE" << endl;
	}
	else
	{
		// output the minimum of incantations and number of gems needed going to destination
		cout << result[0] << " " << result[1] << endl;
	}
=======
	cout << shortestPath (graph, start, end) << endl;
	cout << shortestPath (graph, end, start) << endl;


	//Check input was collected correctly
	for (it = Realms.begin(); it != Realms.end(); it++) {
		cout << "Charm: " << it->first << endl;
>>>>>>> d2525e8f4b408b09968b1e16d783d56c30d48cb2

	// cleaning the vector
	result.clear();
	result = shortestPath (graph, end, start);
	if (result[0] == -1)
	{
		cout << "IMPOSSIBLE" << endl;
	}
	else
	{
		// output the minimum of incantations and number of gems needed coming back from destination
		cout << result[0] << " " << result[1] << endl;
	}

<<<<<<< HEAD
	// //Check input was collected correctly
	// for (it = Realms.begin(); it != Realms.end(); it++) {
	// 	cout << "Charm: " << it->first << endl;
	//
	// 	for (int i = 0; i < it->second.size(); i++) {
	// 		cout << it->second[i] << " ";
	// 	}
	// 	cout << endl << endl;
	// }

	system("pause");
	return 0;
=======
>>>>>>> d2525e8f4b408b09968b1e16d783d56c30d48cb2

	system("pause");
	return 0;
}

//Gets the total changes that it needs to perform to get to a certain realm
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


//Gets the list with the maximum number of incantation per Realm that can be performed
//Each element in the result vector shows the power's cost up to position i
vector<int> getMaxIncantation (vector<int> magicianPowers)
{
	int length = 0;
	vector<int> T(magicianPowers.size());
	vector<int> R(magicianPowers.size());

	//Initizalize R values to -1
	for (int i = 0; i < (int)magicianPowers.size(); i++)
		R[i] = -1;

	for (int i = 1; i < (int)magicianPowers.size(); i++)
	{
		if(magicianPowers[i] > magicianPowers[T[length]])
		{
			T[++length] = i;
			R[i] = T[length-1];
		}
		else
		{
			if(magicianPowers[i] < magicianPowers[T[0]])
			{
				T[0] = i;
			}
			else
			{
				int index_ceiling = getIndexOfCeiling(magicianPowers[i]-1, magicianPowers, T, 0, length);

				//If element was not found (a.k.a. is not repeated) then we look up the ceiling
				if(magicianPowers[i] > magicianPowers[T[index_ceiling]])
				{
					//Find index of the ceiling of magicianPowers[i] in T[0:length+1] using Binary Search
					//index_ceiling = getIndexOfCeiling(magicianPowers[i], magicianPowers, T, length+1);
					index_ceiling = getIndexOfCeiling(magicianPowers[i], magicianPowers, T, 0, length);
					T[index_ceiling] = i;
					R[i] = T[index_ceiling-1];
				}
			}
		}
	}

	//Get increasing subsequence
	vector<int> maxSubsequence(length+1);
	int index = T[length];

	for(int i=length;i >= 0;i--)
	{
		maxSubsequence[i] = magicianPowers[index];
		index = R[index];
	}

	//Get vector with gems count per index
	vector<int> results(length+1);

	for(int i=0;i <= length;i++)
	{
		if(i == 0)
			results[i] = maxSubsequence[i];
		else
		  results[i] = results[i-1] + maxSubsequence[i];
	}

	return results;
}

//Number is not contained within the array of magicianPowers[T[i] because I already checked for this condition
//before I called this method.]
int getIndexOfCeiling(int number, vector<int> magicianPowers, vector<int> T, int iniIndex, int endIndex)
{
	if(iniIndex == endIndex)
		return T[iniIndex];

	if(iniIndex < endIndex)
	{
		int middleIndex = (iniIndex + endIndex)/2;

		if(magicianPowers[T[middleIndex]] < number)
			return getIndexOfCeiling(number, magicianPowers, T, middleIndex+1, endIndex);

		//magicianPowers[T[middleIndex]] > number
		return getIndexOfCeiling(number, magicianPowers, T, iniIndex, middleIndex-1);
	}

	return -1;
}

//Generates the weighted directed graph
unordered_map<string, node> generateGraph(unordered_map<string, vector<int>> input) {

	unordered_map<string, node> output;
	unordered_map < string, vector<int>>::iterator it, it2;
	vector<int> incantations;

	for (it = input.begin(); it != input.end(); it++) {
		//Compare every realm to all other realms to get the connections, and edge weights
		for (it2 = input.begin (); it2 != input.end (); it2++) {
			edge newEdge;
			if (it != it2) {
				//it is working!!!
				//placing the edges on the node
				int minChanges = getMinChanges (it->first, it2->first);
				incantations = getMaxIncantation (it->second);
				if (minChanges <= incantations.size()) {
					newEdge.initialize (it2->first, minChanges, incantations[minChanges-1]);
					output[it->first].connections.push_back (newEdge);
				}

			}
		}
		//output.insert(make_pair(it.first, newNode))
		//newNode.clear();
	}

	return output;
}


//find the least enchantments used, if gems are added to the nodes then it would work with gems as well
vector<int> shortestPath (unordered_map<string, node>graph, string start, string finish) {

	vector<int> result;

	priority_queue<edge>q;

	graph[start].visited = true;

	for (int i = 0; i < (int)graph[start].connections.size(); i++) {
		edge forEdge = graph[start].connections[i];
		graph[forEdge.charm].incantationsWeight=forEdge.incantations;
		graph[forEdge.charm].gemWeight = forEdge.gems;
		graph[forEdge.charm].visited = true;
		q.push (forEdge);
	}

	while (!q.empty()) {
		edge temp;
		temp = q.top ();
		q.pop ();

		for (int i = 0; i < (int)graph[temp.charm].connections.size (); i++) {
			edge forEdge = graph[temp.charm].connections[i];
			if (graph[forEdge.charm].visited ==false) {
				//add the weight of the forEdge to the one on the temporary edge
				graph[forEdge.charm].gemWeight = forEdge.gems+graph[temp.charm].gemWeight;
				graph[forEdge.charm].incantationsWeight=forEdge.incantations+graph[temp.charm].incantationsWeight;
				//visiting the node
				graph[forEdge.charm].visited = true;
				q.push (forEdge);
			}//if it is visited check if the distance is smaller from this node and update the distance
			else {
				if (forEdge.incantations+graph[temp.charm].incantationsWeight<graph[forEdge.charm].incantationsWeight) {
					graph[forEdge.charm].gemWeight = forEdge.gems;
					graph[forEdge.charm].incantationsWeight=forEdge.incantations;
				}
			}
		}

	}

	result.push_back(graph[finish].incantationsWeight);
	result.push_back(graph[finish].gemWeight);

	return result;
}
