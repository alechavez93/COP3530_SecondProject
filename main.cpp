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
	int weight = 0;

	void initialize(string charm, int weight) {
		this->charm = charm;
		this->weight = weight;
	}
	//operator overload for the priority queue
	bool operator <(const edge& rhs)const {
		return weight > rhs.weight;
	}

};


//Struct for the graph node
struct node {
	bool visited = false;
	int minWeight = -1;
	vector<edge> connections;

	void clear() {
		visited = false;
		minWeight = -1;
		connections.clear();
	}

};



//Realm => R
int getMinChanges (string R1, string R2);
vector<int> getMaxIncantation (vector<int> magicianPowers);
int getIndexOfCeiling(int number, vector<int> magicianPowers, vector<int> T, int size);
unordered_map<string, node> generateGraph(unordered_map<string, vector<int>> input);
int shortestPath (unordered_map<string, node>graph, string start, string finish);

int main () {
	//N -> number of realms    M -> number of magi   P -> power of magi
	int N, M, P;	string charm;
	//start node where to start, end node where to stop
	string start, end;

	vector<int> listOfMagi;


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
	cout << shortestPath (graph, start, end) << endl;
	cout << shortestPath (graph, end, start) << endl;

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

	/*

	int length = 0;
	cin >> length;

	vector<int> arr(length);
	for(int i=0;i<length;i++)
		cin >> arr[i];

	vector<int> maxSub = getMaxIncantation(arr);

	cout << "The max subarray is: " << endl;
	for(int i=0;i<maxSub.size();i++)
		cout << maxSub[i] << " ";
	cout << " End" << endl;

	system("pause");

	return 0;
	*/
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
				int index_ceiling = getIndexOfCeiling(magicianPowers[i]-1, magicianPowers, T, length+1);
				if(magicianPowers[i] != magicianPowers[T[index_ceiling]])
				{
					//Find index of the ceiling of magicianPowers[i] in T[0:length+1] using Binary Search
					index_ceiling = getIndexOfCeiling(magicianPowers[i], magicianPowers, T, length+1);
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

/*
//Works for non-repeated values
//https://www.youtube.com/watch?v=S9oUiVYEq7E
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
				//Find index of the ceiling of magicianPowers[i] in T[0:length+1] using Binary Search
				int index_ceiling = getIndexOfCeiling(magicianPowers[i], magicianPowers, T, length+1);
				T[index_ceiling] = i;
				R[i] = T[index_ceiling-1];
			}
		}
	}

	//Get increasing subsequence
	vector<int> results(length+1);
	int index = T[length];

	for(int i=length;i >= 0;i--)
	{
		results[i] = magicianPowers[index];
		index = R[index];
	}

	return results;
}
*/

int getIndexOfCeiling(int number, vector<int> magicianPowers, vector<int> T, int size)
{
	if(magicianPowers.size() == 0 || T.size() == 0)
		throw invalid_argument("Array cannot be empty.");

	for(int i=0;i<size;i++)
	{
		if(magicianPowers[T[i]] > number)
			return i;
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
					newEdge.initialize (it2->first, minChanges);
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
int shortestPath (unordered_map<string, node>graph, string start, string finish) {
	priority_queue<edge>q;

	graph[start].visited = true;

	for (int i = 0; i < (int)graph[start].connections.size(); i++) {
		edge forEdge = graph[start].connections[i];
		graph[forEdge.charm].minWeight = forEdge.weight;
		graph[forEdge.charm].visited = true;
		q.push (forEdge);
	}

	/*testing the priority queue, it works!!!!
	while(!q.empty()){
		cout <<"charm-->" <<q.top ().charm << "weight "<<q.top().weight<< endl;
		q.pop ();
	}*/

	while (!q.empty()) {
		edge temp;
		temp = q.top ();
		q.pop ();

		for (int i = 0; i < (int)graph[temp.charm].connections.size (); i++) {
			edge forEdge = graph[temp.charm].connections[i];
			//if u r mind blown by these next lines u should, this is really weird, checking if the node to add is already visited
			if (graph[forEdge.charm].visited ==false) {
				//add the weight of the forEdge to the one on the temporary edge
				graph[forEdge.charm].minWeight = forEdge.weight+graph[temp.charm].minWeight;
				//visiting the node
				graph[forEdge.charm].visited = true;
				q.push (forEdge);
			}//if it is visited check if the distance is smaller from this node and update the distance
			else {
				if (forEdge.weight+graph[temp.charm].minWeight<graph[forEdge.charm].minWeight) {
					graph[forEdge.charm].minWeight = forEdge.weight;
				}
			}
		}

	}


	return graph[finish].minWeight;
}
