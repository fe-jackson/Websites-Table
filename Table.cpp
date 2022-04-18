//Felix Jackson
//CS 260
//5-15-2020

//Program 3

//"Table.cpp"

/*

	This program allows the client to make a table of websites. It uses 
a website struct that can contain the topic, url, summary, review, and rating of 
a website. There are functions to add a website to the table, retrieve an array 
of websites of a chosen topic, remove all websites with one-star reviews, display 
all websites with a chosen topic, and display all websites in the table.

*/


#include "Table.h"
#include <iostream>
#include <cstring>
using namespace std;




//website constructor
website::website()
{
	topic_name = NULL;
	url = NULL;
	summary = NULL;
	review = NULL;
	rating = 0;
}





//website destructor
website::~website ()
{
	if (topic_name)
	{
		delete topic_name;
	}

	if (url)
	{
		delete url;
	}

	if (summary)
	{
		delete summary;
	}

	if (review)
	{
		delete review;
	}
}





//Table constructor
//INPUT: int argument
Table::Table (int array_size)
{
	size = array_size;
	hash_table = new node * [size];

	node * * current = hash_table;
	
	for (int k = 0; k < size; ++k)
	{
		*current = NULL;
		++current;
	}
}





//Table destructor
Table::~Table ()
{
	if (hash_table)
	{
		remove_all (hash_table [0], 0);
		delete [] hash_table;
		hash_table = NULL;
	}
}





//removes all the nodes in the hash table. pass hash_table[0] as current and 0 as
//index
//INPUT: arguments 
void Table::remove_all (node * & current, int index)
{
	if (!current)
	{
		++index;
		if (index == size)
		{
			return;
		}
		
		remove_all (hash_table [index], index);
	}

	if (current)
	{
		node * temp = current -> next;
		delete current;
		current = temp;
	}

	remove_all (current, index);
}






//calculates the index where the node should go using the keyword
//INPUT: argument
//OUTPUT: int return
int Table::hash_function (char keyword [])
{
	int length = strlen (keyword);
	int sum = 0;
	
	for (int k = 0; k < length; ++k)
	{
		sum += keyword[k];
	}

	sum %= size;
	
	return sum;
}





//Adds a new website to the table with values that match the 
//arguments passed to this function 
//INPUT: arguments and the returned int from hash_function	
int Table::add_website (char topic_name [], char url [], char summary [],
	char review [], int rating)
{
	if (!hash_table)
	{
		return 0;
	}	


	int index = hash_function (topic_name);

	node * temp = hash_table[index];
	website * temp2 = NULL;

	hash_table [index] =  new node;
	hash_table [index] -> next = temp;
	temp2 = &hash_table[index]->site;

	temp2->topic_name = new char [strlen(topic_name) + 1];
	strcpy (temp2->topic_name, topic_name);

	temp2->url = new char [strlen (url) + 1];
	strcpy (temp2->url, url);

	temp2->summary = new char [strlen (summary) + 1];
	strcpy (temp2->summary, summary);

	temp2->review = new char [strlen (review) + 1];
	strcpy (temp2->review, review);

	if (rating >= 1 && rating <=5)
	{
		temp2->rating = rating;
	}
	
	if (rating < 1)
	{
		temp2->rating = 1;
	}

	if (rating > 5)
	{
		temp2->rating = 5;
	}

	return 1;
}






 
//puts the info of every website with a topic that matches the
//topic_name argument into an array and returns the number of
//matches found, which is also the length of the array	
//INPUT: arguments and a returns in from the hash_function
//OUTPUT: argument and an int return	
int Table::retrieve (char topic_name [], website * & matches)
{
	if (!hash_table)
	{
		return 0;
	}

	int index = hash_function (topic_name);
	int num = count_matches (hash_table [index], topic_name);
	website * matches_current_index = NULL;

	if (matches)
	{
		delete matches;
	}

	matches = new website [num];

	matches_current_index = matches;	
	
	retrieve (hash_table [index], topic_name, matches_current_index);
	
	return num;
}





 	
//counts and returns the number of matches found in a chain
//INPUT: arguments
//OUTPUT: int return	
int Table::count_matches (node * current, char topic_name [])
{
	if (!current)
	{
		return 0;
	}

	int sum = 0;
	
	if (strcmp (current->site.topic_name, topic_name) == 0)
	{
		return sum += 1 + count_matches (current->next, topic_name);
	}

	return sum += count_matches (current->next, topic_name);
}






	
//searches a chain for matches and copies each website match into
//the "matches" array
//INPUT: arguments
//OUTPUT: website array argument 	
void Table::retrieve (node * current, char topic_name [], website * & matches)
{
	if (!current)
	{
		return;
	}

	if (strcmp (current->site.topic_name, topic_name) == 0)
	{
		website * temp = &current->site;
	
		matches->topic_name = new char [strlen (temp->topic_name) 
			+ 1];
		strcpy (matches->topic_name, temp->topic_name);

		matches->url = new char [strlen (temp->url) + 1];
		strcpy (matches->url, temp->url);
		
		matches->summary = new char [strlen (temp->summary) + 1];
		strcpy (matches->summary, temp->summary);
		
		matches->review = new char [strlen (temp->review) + 1];
		strcpy (matches -> review, temp->review);
		
		matches->rating = temp->rating;
	
		retrieve (current->next, topic_name, ++matches);	
	}

	retrieve(current->next, topic_name, matches);	
}






//Removes all websites in the table with one-star ratings and
//returns the number of websites removed
//OUTPUT: returns an int	
int Table::remove_one_star ()
{
	if (!hash_table)
	{
		return 0;
	}

	return remove_one_star (hash_table [0], 0);
}






	
//recursively removes every node in the hash table that contains
//a website with a one star rating
//INPUT: arguments
//OUTPUT: int return
int Table::remove_one_star (node * & current, int index)
{
	int count = 0;

	if (!current)
	{
		++index;
		if (index == size)
		{
			return 0;
		}

		return count += remove_one_star (hash_table[index], index);
	}

	if (current->site.rating == 1)
	{
		node * temp = current -> next;
		delete current;
		current = temp;
		
		return count += 1 + remove_one_star (current, index);
	}

	return count += remove_one_star (current->next, index);
}







//Displays all websites in the table with a topic that matches
//topic_name and returns the number of matches found
//INPUT: arguments
//OUTPUT: cout, int return	
int Table::display_by_topic (char topic_name [])
{
	if (!hash_table)
	{
		return 0;
	}

	int index = hash_function (topic_name);
	int num = 0;
	cout << "\n\nWebsites with " << topic_name << " as a topic:\n\n";

	num = display_by_topic (hash_table [index], topic_name);

	if (!num)
	{
		cout << "None found.\n\n";
	}

	return num;
}







//recursively searches a chain for matches and displays each of
//them. returns the number of websites displayed
//INPUT: arguments
//OUTPUT: cout, int return
int Table::display_by_topic (node * current, char topic_name [])
{
	if (!current)
	{
		return 0;
	}

	int count = 0;

	if (strcmp (current->site.topic_name, topic_name) == 0)
	{
		website * temp = &current->site;
	
		cout << "\n\nWebsite URL - " << temp -> url
			<< "\nWebsite summary - " << temp -> summary
			<< "\nWebsite review - " << temp -> review
			<< "\nWebsite rating - " << temp -> rating << " stars\n\n";
		
		return count += 1 + display_by_topic (current->next, topic_name);
	}

	return count += display_by_topic (current->next, topic_name);
}







//displays all websites in the table and returns how many there are
//OUTPUT: cout, int return
int Table::display_all ()
{
	if (!hash_table)
	{
		return 0;
	}

	return display_all (hash_table [0], 0);
}






	
//recursively displays all the websites in the hash table and 
//returns the number of websites displayed
//INPUT: arguments
//OUTPUT: cout, int return	
int Table::display_all (node * current, int index)
{
	int count = 0;
	
	if (!current)
	{
		++index;
		if (index == size)
		{
			return 0;
		}
		
		return count += display_all (hash_table [index], index);
	}
	
	website * temp = &current->site;
	
	cout << "\n\nWebsite Topic - " << temp->topic_name
		<< "\nURL - " << temp -> url
		<< "\nSummary - " << temp -> summary
		<< "\nReview - " << temp -> review
		<< "\nRating - " << temp->rating << " stars out of 5\n\n";

	return count += 1 + display_all (current->next, index);
}




 
