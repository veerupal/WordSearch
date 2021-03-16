//Including all the necessary header files
#include <bits/stdc++.h> 
using namespace std; 

//Total alaphates that contain in dictionary are either character a-z or A-Z or ' or - 
//Considering all the letters as small letter, 26+2=28
const int ALPHABET_SIZE = 28; 

// trie node 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 

	// isEndOfWord is true if the node represents 
	// end of a word 
	bool isEndOfWord;

	//Stores the frequency of word ending at the node;
	int freq; 

	//Store the start and end word number counting from that leaf.
	int a,b;
}; 

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = new TrieNode; 

	pNode->isEndOfWord = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 
	return pNode; 
} 

// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string key, int freq,int n) 
{ 
	struct TrieNode *pCrawl = root; 	//Setting temporary pointer variable of TrieNode type
	//Repeat for every character of word key
	for (int i = 0; i < key.length(); i++) 
	{ 
		int index;
		
		//index 0-25 for letters, 26 for ' and 27 for -
		if(key[i]>='a' && key[i]<='z')
			index=key[i]-'a';
		else if(key[i]=='\'')
			index=26;
		else
			index=27;
			
		//Check if leaf exists if no then make a node
		if (!pCrawl->children[index])
		{ 
			pCrawl->children[index] = getNode(); 
			pCrawl->children[index]->a=n;
		}
		//Assiging next node to pCrawl
		pCrawl->b=n;
		pCrawl = pCrawl->children[index]; 
		pCrawl->b=n;
	} 

	// mark last node as leaf 
	pCrawl->isEndOfWord = true;

	//Store the frequency
	pCrawl->freq=freq; 
} 

// Search for the nth word
void search(struct TrieNode *root, int n,string st="") 
{ 
	struct TrieNode *pCrawl = root; 

	//Check if the word nth word is found
	if(root->isEndOfWord && root->a==n)
	{
		cout<<st<<"\n";
		return;
	}
	
	//Search for next leaf for the nth word
	for (int i = 0; i < 28; i++) 
	{ 
		//Check if the letter node is present
		if (pCrawl->children[i]) 
		{
			//If letter node present, check weather word number falls in between minimum and maximum word index
			//If word index a and b doesn't contain n, then skip the leaf node
			if(!((pCrawl->children[i]->a)<=n && (pCrawl->children[i]->b)>=n))
				continue;
			
			//If exists in between, add the letter to word and search unless word is found
			char x;
			if(i<26)
				x=(i+'a');
			else if(i==26)
				x='\'';
			else
				x='-';
			search(root->children[i],n,st+x);
		} 
	}
} 


/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main(int argc, char** argv) {

	//Variable to read file
	ifstream fin;
	
	//Opening the dictionary
	fin.open("EnglishDictionary.csv");
	string line, word;
	int freq,n=0;
	
	//Creating root node for the dictionary
	struct TrieNode *root = getNode(); 

	//Read file till the end of file
	while(getline(fin,line,'\n'))
	{
		stringstream s(line);
		getline(s,word,',');
		s>>freq;
		
		//Changing uppercase letters to lowercase
		for(int j=0;word[j];j++)
		{
			if(word[j]>=65 && word[j]<92)
				word[j]=word[j]^32;
		}
			
		insert(root,word,freq,n);
		n++;
		word="";
	}
	fin.close();
	for(int i=2;i<argc;i++)
	{
		stringstream s(argv[i]);
		int a;
		s>>a;
		search(root,a);
	}
	return 0;
}