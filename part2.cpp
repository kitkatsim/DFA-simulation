/**

Algorithm for BFS is taken from www.geeksforgeeks.org

**/

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include<bits/stdc++.h>
#include <list>
using namespace std;

int findsize(char* p, vector<string> &state);

vector <int> visited_state;

class Graph
	{
		int V;    // No. of vertices
	 
		// Pointer to an array containing adjacency
		// lists
		list<int> *adj;   
	public:
		Graph(int V);  // Constructor
	 
		// function to add an edge to graph
		void addEdge(int v, int w); 
	 
		// prints BFS traversal from a given source s
		void BFS(int s);  
	};
	 
	Graph::Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
	}
	 
	void Graph::addEdge(int v, int w)
	{
		adj[v].push_back(w); // Add w to v’s list.
	}
	 
	void Graph::BFS(int s)
	{
		// Mark all the vertices as not visited
		bool *visited = new bool[V];
		for(int i = 0; i < V; i++)
			visited[i] = false;
	 
		// Create a queue for BFS
		list<int> queue;
	 
		// Mark the current node as visited and enqueue it
		visited[s] = true;
		queue.push_back(s);
	 
		// 'i' will be used to get all adjacent
		// vertices of a vertex
		list<int>::iterator i;
	 
		while(!queue.empty())
		{
			// Dequeue a vertex from queue and print it
			s = queue.front();
			visited_state.push_back(s);
			queue.pop_front();
	 
			// Get all adjacent vertices of the dequeued
			// vertex s. If a adjacent has not been visited, 
			// then mark it visited and enqueue it
			for (i = adj[s].begin(); i != adj[s].end(); ++i)
			{
				if (!visited[*i])
				{
					visited[*i] = true;
					queue.push_back(*i);
				}
			}
		}
	}

int main(int argc, char *argv[]){
	
	std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "No\n";
        return -1;
    }
	//not enough argument/too many arguments
	if(argc != 3){
		printf("No\n");
		return 0;
	}
    std::string haystack,states,input_alphabet,start_state,accept_states,delta;	//declaration
	
	//parse the needed lines
    while (std::getline(file, haystack))
    {
    	//find states:
         if (haystack.find("states:") != std::string::npos && haystack.find("accept_states:") == std::string::npos){    
        	size_t pos = 0;
			while ((pos = haystack.find("#")) != std::string::npos) {
				states = haystack.substr(0, pos);
				haystack.erase(0, pos + 1);
			}
			if(states.size() <= 0){
				states = haystack;
			}
        	//printf("Condition 1:\n%s\n",states.c_str()); 
        }
        if(haystack.find("input_alphabet:") != std::string::npos){
        	size_t pos = 0;

			while ((pos = haystack.find("#")) != std::string::npos) {
				input_alphabet = haystack.substr(0, pos);
				haystack.erase(0, pos + 1);
			}
			if(input_alphabet.size() <= 0){
				input_alphabet = haystack;
			}
        	//printf("Condition 2:\n%s\n",input_alphabet.c_str());
        }
        if(haystack.find("start_state:") != std::string::npos){
			size_t pos = 0;
			
			while ((pos = haystack.find("#")) != std::string::npos) {
				//to split the part after #, ignore anything after #
				start_state = haystack.substr(0, pos);
				haystack.erase(0, pos + 1);
			}
			if(start_state.size() <= 0){
				start_state = haystack;
			}
        	//printf("Condition 3:\n%s\n",start_state.c_str());
        }
        if(haystack.find("accept_states:") != std::string::npos){
			size_t pos = 0;
			
			while ((pos = haystack.find("#")) != std::string::npos) {
				accept_states = haystack.substr(0, pos);
				haystack.erase(0, pos + 1);
			}
			if(accept_states.size() <= 0){
				accept_states = haystack;
			}
        	//printf("Condition 4:\n%s\n",accept_states.c_str());
        }
        if(haystack.find("delta:") != std::string::npos){
        	size_t pos = 0;

			while ((pos = haystack.find("#")) != std::string::npos) {
				delta = haystack.substr(0, pos);
				haystack.erase(0, pos + 1);
			}
			if(delta.size() <= 0){
				delta = haystack;
			}
        	//printf("Condition 5:\n%s\n",delta.c_str());
        }
    }
	
	//parse the lines into a usable data
    char* p;
	vector <string> state,alphabet,start,accept,deltas;	//declaration
    p = strtok (const_cast<char*>(states.c_str())," .");
	int state_count = findsize(p,state);
	//printf("number of state is %d\n",state_count);
	
	p = strtok (const_cast<char*>(input_alphabet.c_str())," .");
	int alphabet_size = findsize(p,alphabet);
	
	p = strtok (const_cast<char*>(start_state.c_str())," .");
	findsize(p,start);
	
	p = strtok (const_cast<char*>(accept_states.c_str())," .");
	int accept_size = findsize(p,accept);

	p = strtok (const_cast<char*>(delta.c_str())," ,.->;");
	findsize(p,deltas);
	
	if(deltas.size()/3 != (alphabet_size*state_count)){
		//transitions number invalid
		printf("No\n");
		//printf("transition number:%d, alphabet*state:%d\n",deltas.size()/3,(alphabet_size*state_count));
		return 0;
	}
	
	
	
	//create an inverse accepting states (to create negate dfa)
	
	
	
	
	
	int transition[state_count][alphabet_size];	//dfa table
	
	//loop for total number of transitions
	for(int i = 0; i<deltas.size();i=i+3){
		//find index of state that match what's on delta
		int index_state, index_alpha;
		for(int j = 0; j < state.size();j++){
			if(deltas[i] == state[j]){
				index_state = j;
				//printf("hit!\n");
			}
		}
		//find index of alphabet
		for(int j = 0; j < alphabet.size();j++){
			if(deltas[i+1] == alphabet[j]){
				index_alpha = j;
			}
		}
		//find which state it leads to
		for(int j = 0; j < state.size();j++){
			if(deltas[i+2] == state[j]){
				transition[index_state][index_alpha] = j;
				//printf("hit!\n");
			}
		}
		
	}
	/*
	for(int i = 0; i<state_count;i++){
		for(int j = 0; j < alphabet_size; j++){
			printf("%d ",transition[i][j]);
		}
		printf("\n");
	}*/
	
	/** 
		
		Phase 2
		
	**/
	
	std::ifstream file2(argv[2]);
    if (!file2.is_open())
    {
        std::cerr << "No\n";
        return -1;
    }
	//not enough argument/too many arguments
	
    std::string haystack2,states2,input_alphabet2,start_state2,accept_states2,delta2;	//declaration
	
	//parse the needed lines
    while (std::getline(file2, haystack2))
    {
    	//find states:
         if (haystack2.find("states:") != std::string::npos && haystack2.find("accept_states:") == std::string::npos){    
        	size_t pos = 0;
			while ((pos = haystack.find("#")) != std::string::npos) {
				states2 = haystack2.substr(0, pos);
				haystack2.erase(0, pos + 1);
			}
			if(states2.size() <= 0){
				states2 = haystack2;
			}
        	//printf("Condition 1:\n%s\n",states.c_str()); 
        }
        if(haystack2.find("input_alphabet:") != std::string::npos){
        	size_t pos = 0;

			while ((pos = haystack2.find("#")) != std::string::npos) {
				input_alphabet2 = haystack2.substr(0, pos);
				haystack2.erase(0, pos + 1);
			}
			if(input_alphabet2.size() <= 0){
				input_alphabet2 = haystack2;
			}
        	//printf("Condition 2:\n%s\n",input_alphabet.c_str());
        }
        if(haystack2.find("start_state:") != std::string::npos){
			size_t pos = 0;
			
			while ((pos = haystack2.find("#")) != std::string::npos) {
				//to split the part after #, ignore anything after #
				start_state2 = haystack2.substr(0, pos);
				haystack2.erase(0, pos + 1);
			}
			if(start_state2.size() <= 0){
				start_state2 = haystack2;
			}
        	//printf("Condition 3:\n%s\n",start_state.c_str());
        }
        if(haystack2.find("accept_states:") != std::string::npos){
			size_t pos = 0;
			
			while ((pos = haystack2.find("#")) != std::string::npos) {
				accept_states2 = haystack2.substr(0, pos);
				haystack2.erase(0, pos + 1);
			}
			if(accept_states2.size() <= 0){
				accept_states2 = haystack2;
			}
        	//printf("Condition 4:\n%s\n",accept_states.c_str());
        }
        if(haystack2.find("delta:") != std::string::npos){
        	size_t pos = 0;

			while ((pos = haystack2.find("#")) != std::string::npos) {
				delta2 = haystack2.substr(0, pos);
				haystack2.erase(0, pos + 1);
			}
			if(delta2.size() <= 0){
				delta2 = haystack2;
			}
        	//printf("Condition 5:\n%s\n",delta.c_str());
        }
    }
	
	//parse the lines into a usable data
    char* p2;
	vector <string> state2,alphabet2,start2,accept2,deltas2;	//declaration
    p2 = strtok (const_cast<char*>(states2.c_str())," .");
	int state_count2 = findsize(p2,state2);
	//printf("number of state is %d\n",state_count);
	
	p2 = strtok (const_cast<char*>(input_alphabet2.c_str())," .");
	int alphabet_size2 = findsize(p2,alphabet2);
	
	p2 = strtok (const_cast<char*>(start_state2.c_str())," .");
	findsize(p2,start2);
	
	p2 = strtok (const_cast<char*>(accept_states2.c_str())," .");
	int accept_size2 = findsize(p2,accept2);

	p2 = strtok (const_cast<char*>(delta2.c_str())," ,.->;");
	findsize(p2,deltas2);
	
	if(deltas2.size()/3 != (alphabet_size2*state_count2)){
		//transitions number invalid
		printf("No\n");
		//printf("transition number:%d, alphabet*state:%d\n",deltas.size()/3,(alphabet_size*state_count));
		return 0;
	}
	
	
	int transition2[state_count2][alphabet_size2];	//dfa table
	
	//loop for total number of transitions
	for(int i = 0; i<deltas2.size();i=i+3){
		//find index of state that match what's on delta
		int index_state2, index_alpha2;
		for(int j = 0; j < state2.size();j++){
			if(deltas2[i] == state2[j]){
				index_state2 = j;
				//printf("hit!\n");
			}
		}
		//find index of alphabet
		for(int j = 0; j < alphabet2.size();j++){
			if(deltas2[i+1] == alphabet2[j]){
				index_alpha2 = j;
			}
		}
		//find which state it leads to
		for(int j = 0; j < state2.size();j++){
			if(deltas2[i+2] == state2[j]){
				transition2[index_state2][index_alpha2] = j;
				//printf("hit!\n");
			}
		}
		
	}
	
	
	/*
	for(int i = 0; i<state_count2;i++){
		for(int j = 0; j < alphabet_size2; j++){
			printf("%d ",transition2[i][j]);
		}
		printf("\n");
	}*/
	
	
	vector <string> inverse_accept1;
	for(int i = 0; i < state.size(); i++){
		bool x = true;
		for(int j = 0; j < accept.size(); j++){
			if(state[i] == accept[j]){
				x = false;
			}
		}
		if(x){
			inverse_accept1.push_back(state[i]);
			//cout << state[i] << "\n";
		}
	}
	
	
	vector <string> inverse_accept2;
	//create an inverse accepting states (to create negate dfa)
	for(int i = 0; i < state2.size(); i++){
		bool x = true;
		for(int j = 0; j < accept2.size(); j++){
			if(state2[i] == accept2[j]){
				x = false;
			}
		}
		if(x){
			inverse_accept2.push_back(state2[i]);
			//cout << state2[i] << "\n";
		}
	}
	
	
	
		
	if(alphabet_size != alphabet_size2){
		//reject if different symbols
		printf("No\n");
		return 0;
	}
	
	
	//this table is the intersection of 2 DFA transition table
	
	pair<int, int> new_transition[state_count*state_count2][alphabet_size]; 
	int index_lul = 0;
	for(int i=0; i<(state_count*state_count2); i++){ 
		
		for(int j = 0; j < alphabet_size; j++){			
			new_transition[i][j] = make_pair(transition2[index_lul][j%state_count2],transition[i%state_count][j%state_count]);
			//printf("%d,%d  %d,%d | ",index_lul,j%state_count2,i%state_count,j%state_count);
		}
		if(((i+1)%state_count) == 0 && i !=0){
			//printf("i =%d hit!\n",i);	
			index_lul++;
		}
		//printf("\n");
	}
	/*
	printf("---------\n");
	for(int i=0; i<(state_count*state_count2); i++){
		for(int j = 0; j < alphabet_size; j++){
			printf("%d,%d ",new_transition[i][j].first,new_transition[i][j].second);
		}
		printf("\n");
	}
	*/
	
	//an edited transition for easier travesal between states
	
	int edited_transition[state_count*state_count2][alphabet_size];
	
	for(int i=0; i<(state_count*state_count2); i++){
		for(int j = 0; j < alphabet_size; j++){
			edited_transition[i][j] = state_count*new_transition[i][j].first + new_transition[i][j].second;
		}
	}
	
	/*printf("---------\n");
	for(int i=0; i<(state_count*state_count2); i++){
		for(int j = 0; j < alphabet_size; j++){
			printf("%d ",edited_transition[i][j]);
		}
		printf("\n");
	}*/
	
	
	
	
	//Conduct BFS to search for reachable states, 
	//the reachable states can later be compared with accepted states 
	
	Graph g(state_count*state_count2);
	for(int i = 0; i < state_count*state_count2; i++){
		for(int j = 0; j < alphabet_size; j++){
			g.addEdge(i,edited_transition[i][j]);
		}
	}
	//start traverse from starting state
	g.BFS(0);
	
	
	/*
	while(!visited_state.empty()){
		int output = visited_state.back();
		visited_state.pop_back();
		cout << output << "\n";
	}*/
	
	//M2 intersect NEG M1
	pair<string, string> new_accepted1[accept_size*inverse_accept1.size()];
	//M1 intersect NEG M2
	pair<string, string> new_accepted2[accept_size*inverse_accept2.size()];
	
	//M2 intersect NEG M1
	
	int state_index = 0;
	for(int i = 0; i < accept_size; i++){
		for(int j = 0; j < inverse_accept1.size();j++){
			new_accepted1[state_index] = make_pair(accept[i],inverse_accept1[j]);
			//cout<< accept[i] << " " << inverse_accept1[j] << "\n";
			state_index++;
		}
	}
	//M1 intersect NEG M2
	int state_index2 = 0;
	for(int i = 0; i < accept_size; i++){
		for(int j = 0; j < inverse_accept2.size();j++){
			new_accepted1[state_index2] = make_pair(accept[i],inverse_accept2[j]);
			//cout<< accept[i] << " " << inverse_accept2[j] << "\n";
			state_index++;
		}
	}
	bool final = false;
	bool final2 = false;
	
	//check if the traversed state are accepted
	for(int i = 0; i < visited_state.size(); i++){
		for(int j = 0; j < accept_size*inverse_accept1.size(); j++){
			int x,y;
			int k = visited_state[i];
			x = k/state_count;
			y = k%state_count;
			int l = new_transition[x][y].first;
			int m = new_transition[x][y].second;
			//printf("%d %d \n",l,m);
			//printf("1%s 2%s 3%s 4%s \n",state[l].c_str(),new_accepted1[j].first.c_str(),state[m].c_str(),new_accepted1[j].second.c_str());
			
			if(state[l] == new_accepted1[j].first && state[m] == new_accepted1[j].second){
				
				final = true;
			}
		}
	}
	/*
	for(int i = 0; i < visited_state.size(); i++){
		for(int j = 0; j < accept_size*inverse_accept2.size(); j++){
			int x,y;
			int k = visited_state[i];
			x = k/state_count;
			y = k%state_count;
			int l = new_transition[x][y].first;
			int m = new_transition[x][y].second;
			//printf("%d %d \n",l,m);
			//printf("1%s 2%s 3%s 4%s \n",state[l].c_str(),new_accepted2[j].first.c_str(),state[m].c_str(),new_accepted2[j].second.c_str());
			
			if(state[l] == new_accepted1[j].first && state[m] == new_accepted1[j].second){
				
				final2 = true;
			}
		}
	}*/
	
	if(final == true){
		printf("Yes\n");
		return 0;
	}
	
	if((final != true)){
		printf("No, M1 is not equal to M2\n");
		return 0;
	}

	

}

int findsize(char* p,vector<string> &state){
	int i = 0;
	while (p != NULL)
  	{	
		std::string str(p);
		
		if(str.find(":") == std::string::npos){
			i++;
			state.push_back(str);	//tokenize and save it onto vector
		}
    	p = strtok (NULL, " ,.->;");
  	}
	return i;
}


