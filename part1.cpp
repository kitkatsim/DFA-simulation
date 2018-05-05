#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int findsize(char* p, vector<string> &state);

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
	
	/*
	//print transitions
	for(int i = 0; i < deltas.size(); i++){
		cout << deltas[i] << "\n";
	}*/
	
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
	}
	*/
	string test(argv[2]);
	int final_state_index = 0;
	
	//simulate the actual dfa, find which state it stops in
	for (int i=0; i<test.length(); ++i)
	{
		bool valid = false;
		//find which symbol it is, and give the index of alphabets
		int index_alpha;
		for(int j = 0; j < alphabet.size(); j++){
			if(test.at(i) == (alphabet[j])[0]){
				//printf("hit!\n");
				index_alpha = j;
				valid = true;
			}
			
		}
		if(!valid){
			//invalid string, contains symbol outside of the dfa
			printf("No\n");
			return 0;
		}
		final_state_index = transition[final_state_index][index_alpha];
		
	}
	//printf("final index is %d!\n",final_state_index);
	bool x = false;
	//printf("accept size %d!\n",accept_size);
	for(int i = 0; i < accept_size; i++){
		
		//find the accepting states
		if(state[final_state_index] == accept[i]){
			x = true;
		}
	}
	if(x){
		printf("Yes\n");
	}else{
		printf("No\n");
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


