//Felix Jackson
//CS 260
//5-15-2020

//Program 3

//"Table.h"

/*

	This program allows the client to make a table of websites. It uses 
a website struct that can contain the topic, url, summary, review, and rating of 
a website. There are functions to add a website to the table, retrieve an array 
of websites of a chosen topic, remove all websites with one-star reviews, display 
all websites with a chosen topic, and display all websites in the table.

*/


 
struct website
{
	website ();
	~website ();
	char * topic_name;
	char * url;
	char * summary;
	char * review;
	int rating;
};



struct node
{
	website site;
	node * next;
};



class Table
{
	public:
		//constructor. Pass it the size you want the hash table array
		//to be. Please have it be a prime number	
		Table (int array_size = 11);
		
		//Destructor	
		~Table ();

	
		//Adds a new website to the table with values that match the 
		//arguments passed to this function 
		//INPUT: arguments and the returned int from hash_function	
		int add_website (char topic_name [], char url [], char summary [],
			char review [], int rating);


		//puts the info of every website with a topic that matches the
		//topic_name argument into an array and returns the number of
		//matches found, which is also the length of the array	
		//INPUT: arguments and a returns in from the hash_function
		//OUTPUT: argument and an int return	
		int retrieve (char topic_name [], website * & matches);

	
		//Removes all websites in the table with one-star ratings and
		//returns the number of websites removed
		//OUTPUT: returns an int	
		int remove_one_star ();


		//Displays all websites in the table with a topic that matches
		//topic_name and returns the number of matches found
		//INPUT: arguments
		//OUTPUT: cout, int return	
		int display_by_topic (char topic_name []);

		
		//displays all websites in the table and returns how many there 
		//are
		//OUTPUT: cout, int return
		int display_all ();

	private:

		node * * hash_table;
		int size;	
	

		//calculates the index where the node should go using the keyword
		//INPUT: argument
		//OUTPUT: int return
		int hash_function (char keyword []);


		//removes all nodes in the hash table
		//INPUT: arguments	
		void remove_all (node * & current, int index);
	
		//counts and returns the number of matches found in a chain
		//INPUT: arguments
		//OUTPUT: int return	
		int count_matches (node * current, char topic_name []);
	
		//searches a chain for matches and copies each website match into
		//the "matches" array
		//INPUT: arguments
		//OUTPUT: website array argument 	
		void retrieve (node * current, char topic_name [], 
				website * & matches);

		//recursively removes every node in the hash table that contains
		//a website with a one star rating
		//INPUT: arguments
		//OUTPUT: int return
		int remove_one_star (node * & current, int index);

		//recursively searches a chain for matches and displays each of
		//them. returns the number of websites displayed
		//INPUT: arguments
		//OUTPUT: cout, int return
		int display_by_topic (node * current, char topic_name []);

		//recursively displays all the websites in the hash table and 
		//returns the number of websites displayed
		//INPUT: arguments
		//OUTPUT: cout, int return	
		int display_all (node * current, int index); 

};
