#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <utility>

#include <vector>
#include <map>
#include <set>
#include <list>

using namespace std;

// #################################################################################################################
// ##												Part 1 and 2												####
// #################################################################################################################

int main(int argc, char *argv[]) {

	// Vector of strings, and set of unique strings
	vector<string> tokens;
	set <string> unique;

	// Grab things 1 line at a time
	string next_line;

	// Read in the first argument (text file)
	ifstream in(argv[1]);

	// While it's reading in the file
	while (getline(in, next_line)) {

		// String stream
		istringstream iss(next_line);

		// Assign the lines as tokens
		string token;
		while (iss >> token) {

			// Ignore if punctuation - otheswise append
			string nopunct = "";
			for(auto &c : token) {
				if (isalpha(c)) {
					nopunct +=c;
				}
			}

			// Add No punct to the vector
			tokens.push_back(nopunct);

			// And then to the set
			unique.insert(nopunct);
			// cout << token<<endl;
		}
	}

	// Print out the total number of words and unique words
	cout << "Number of words "<<tokens.size()<<endl;
	cout << "Number of unique words "<<unique.size()<<endl;

	// Write the content to a vector text file
	string filename = argv[1];
	ofstream vectorfile(filename+"_vector.txt");

	// Iterate through all strings and add to the file
	for (int i = 0; i < tokens.size(); i++) {
		vectorfile << " " << tokens[i] << endl;
	}

	// Write the content to a set text file
	ofstream setfile(filename+"_set.txt");

	// Iterator through our unique strings and print out
	for (set<string>::iterator it=unique.begin(); it!=unique.end(); ++it) {
		// cout << ' ' << *it;
		setfile << " " << *it << endl;
	}

	// End line
	cout << endl;

	// #################################################################################################################
	// ##												 Part 3														####
	// #################################################################################################################


	// Define our map of strings
	map<string, string> wordmap;
	string last="";

	// Loop through the vector
	for (int i = 0; i < tokens.size(); ++i) {

		// Assign the key as the token
		wordmap[last] = tokens[i];
		last = tokens[i];

	}

	// Write the content to a set text file
	ofstream mapfile(filename+"_map.txt");

	// Print everything out and assign to new file
	// NOTE: (I'm confused - don't we WANT duplicates???)
	for (auto const &pair: wordmap) {
		// cout <<  pair.first << ", " << pair.second << endl;
		mapfile << pair.first << ", " << pair.second << endl;
	}

	// #################################################################################################################
	// ##												 Part 4														####
	// #################################################################################################################

	// For the terminal...
	cout << "Here is my Nephi speech/poem/sermon: " << endl;


	// Generating similar text
	string state = "";

	// Loop through the entire map
	for(int i = 0; i < 100; i++){
		cout << wordmap[state] << " ";
		state = wordmap[state];
	}
	cout << endl << endl;

	// #################################################################################################################
	// ##												 Part 5														####
	// #################################################################################################################

	// For reference
	cout << "Here is my updated Nephi poem/speech/sermon: " << endl;

	// Define a different map
	map<string, vector<string>> wordmap_all;
	string state_all = "";

	// Loop through the vector
	for(int i = 0; i < tokens.size(); ++i) {

		// Append next word to vector of words
		wordmap_all[state_all].push_back(tokens[i]);

		// Reassign the state
		state_all = tokens[i];
	}


	// Initialize the random generator and string
	srand(time(NULL));
	string state_rand = "";

	// Do 100 words
	for (int i = 0; i < 100; i++) {

		// Pick a random index from the wordmap
		int ind = rand() % wordmap_all[state_rand].size();

		// Loop through the associative words
		cout << wordmap_all[state_rand][ind] << " ";
		state_rand = wordmap_all[state_rand][ind];
	}
	cout << endl << endl;

	// #################################################################################################################
	// ##												 Part 6														####
	// #################################################################################################################

	// Debugging
	cout << "Here is my final, contextual Nephi sermon: " << endl;

	// Define our new map, and now list
	map<list<string>, vector<string>> wordmap_context;
	list<string> state_context;
	int M = 2;

	// Loop through (M) times
	for (int i = 0; i < M; i++) {
		state_context.push_back("");
	}

	// Loop through our token vector
	for (int i = 0; i < tokens.size(); ++i) {

		// Push back token on our vector, and then our list
		wordmap_context[state_context].push_back(tokens[i]);
		state_context.push_back(tokens[i]);
		state_context.pop_front();
	}

	// Generate a new sermon
	state_context.clear();
	for (int i = 0; i < M; i++) {
		state_context.push_back("");
	}

	// We'll do 100 words
	for (int i = 0; i < 100; i++) {

		// Identify a random string
		int ind = rand() % wordmap_context[state_context].size();

		// Output the token, add, pop
		cout << wordmap_context[state_context][ind]<<" ";
		state_context.push_back(wordmap_context[state_context][ind]);
		state_context.pop_front();
	}

	cout << endl << endl;

	// #################################################################################################################
	// ##																											####
	// ##												 Part 7														####
	// ##		Context: I have a blog - so I copy and posted 12+ posts from my blog into a word document 			####
	// ##		and downloaded as a .txt file. I'm going to see if I can recreate my own voice using the file.		####
	// ##																											####
	// #################################################################################################################



	// First create a vector of strings, and a set of unique strings
	vector<string> blog_tokens;
	set <string> blog_unique;

	// Grab things 1 line at a time
	string next_blog_line;

	// Read in the first argument (text file)
	ifstream blog("Blog.txt");

	// While it's reading in the file
	while (getline(blog, next_blog_line)) {

		// String stream
		istringstream iss(next_blog_line);

		// Assign the lines as tokens
		string tokens;
		while (iss >> tokens) {

			// Ignore if punctuation - otheswise append
			string nopuncts = "";
			for(auto &c : tokens) {
				if (isalpha(c)) {
					nopuncts +=c;
				}
			}

			// Add No punct to the vector
			blog_tokens.push_back(nopuncts);

			// And then to the set
			blog_unique.insert(nopuncts);
			// cout << token<<endl;
		}
	}

	// Print out the total number of words and unique words
	cout << "Number of words "<< blog_tokens.size() <<endl;
	cout << "Number of unique words "<< blog_unique.size() <<endl;

	// Write the content to a vector text file
	string blog_filename = "Blog.txt";
	ofstream blog_vectorfile(blog_filename+"_vector.txt");

	// Iterate through all strings and add to the file
	for (int i = 0; i < blog_tokens.size(); i++) {
		blog_vectorfile << " " << blog_tokens[i] << endl;
	}

	// Write the content to a set text file
	ofstream blog_setfile(blog_filename+"_set.txt");

	// Iterator through our unique strings and print out
	for (set<string>::iterator it=unique.begin(); it!=unique.end(); ++it) {
		// cout << ' ' << *it;
		blog_setfile << " " << *it << endl;
	}

	// End line
	cout << endl;

	// Define our new blog map, and now list
	map<list<string>, vector<string>> blogmap;
	list<string> state_blog;

	// Loop through (M) times
	for (int i = 0; i < M; i++) {
		state_blog.push_back("");
	}

	// Loop through our token vector
	for (int i = 0; i < blog_tokens.size(); ++i) {

		// Push back token on our vector, and then our list
		blogmap[state_blog].push_back(blog_tokens[i]);
		state_blog.push_back(blog_tokens[i]);
		state_blog.pop_front();
	}

	// Generate a new 100 word blog post using my own language
	state_blog.clear();
	for (int i = 0; i < M; i++) {
		state_blog.push_back("");
	}

	// Debugging
	cout << "Here is my NLP blog post: " << endl;

	// Generate (100)
	for (int i = 0; i < 100; i++) {

		// Identify a random string
		int ind = rand() % blogmap[state_blog].size();

		// Output the token, add, pop
		cout << blogmap[state_blog][ind]<<" ";
		state_blog.push_back(blogmap[state_blog][ind]);
		state_blog.pop_front();
	}

	cout << endl << endl;

	// Return
	return 0;
}
