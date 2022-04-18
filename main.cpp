//Felix Jackson
//CS 260
//5-16-2020

//Project 3

//"main.cpp"


/*
	This program allows a user to create and manage 
a table of websites and their information. They can keep
track of each website's topic, url, summary, review,
and rating. This program loads websites from an external 
file. It allows the user to add a new website an it's 
info to the table, remove all websites with one-star
ratings, display all websites of a chosen topic, and
display all websites in the table.

*/


#include "Table.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


int load_table (Table & my_table);
void add (Table & my_table);


int main ()
{
	Table my_table;

	int count = 0;
	
	char selection = 'a';
	char topic [51];

	website * matches = NULL;
	website * current = NULL;
	
	count = load_table (my_table);
	
	if (!count)
	{
		cout << "\n\nError loading data.\n\n";
	}
	else
	{
		cout << "\n\nLoaded " << count << " websites onto the table.\n\n";
	}



	do 
	{
		do 
		{
			cout << "\n\nMAIN MENU:\nSelect from the following options"
				<< "\n\n1\tAdd a website to the table"
				<< "\n\n2\tRemove all websites in the table that "
				<< "only have one-star ratings"
				<< "\n\n3\tDisplay all websites of a certain topic"
				<< "\n\n4\tDisplay all websites in the table"
				<< "\n\n5\tExit program\n\n";
			cin >> selection;
			cin.ignore (100, '\n');
			
			if (selection < '1' || selection > '5')
			{
				cout << "\n\nInvalid selection. Try again.\n\n";
			}
	
		} while (selection < '1' || selection > '5');
	
	
		if (selection == '1')
		{
			add (my_table);
		}

		if (selection == '2')
		{
			count = my_table.remove_one_star ();
			cout << "\n\nRemoved the " << count << " website(s) with "
				<< "one-star reviews from the table.\n\n";
		}

		if (selection == '3')
		{
			cout << "\n\nOkay. What is the topic of the websites you "
				<< "wish to dispay?\n\n";
			cin.get (topic, 51, '\n');
			cin.ignore (100, '\n');

			//DISPLAY USING TABLE'S DISPLAY FUNCTION
			count = my_table.display_by_topic (topic);
			
			cout << "\n\n" << count << " websites found and displayed."
				<< "\n\n";

			//DISPLAY USING TABLE'S RETRIEVE FUNCTION
			/*	
			count = my_table.retrieve (topic, matches);

			current = matches;

			cout << "\n\n" << count << " websites found.\n\n";
	
			for (int k = 0; k < count; ++k)
			{
				cout << "\n\n\tWebsite topic - " 
					<< current->topic_name
					<< "\n\tWebsite URL - " << current->url
					<< "\n\tWebsite summary - " 
					<< current->summary
					<< "\n\tWebsite review - " 
					<< current->review
					<< "\n\tWebsite rating - "
					<< current->rating << " out of 5 stars."
					<< "\n\n";
				++current;
			}			
			current = NULL;		
			*/	
		}

		
		if (selection == '4')
		{
			count = my_table.display_all ();
			cout << "\n\n" << count << " websites displayed.\n\n";	
		}

	
	} while (selection != '5');	



	cout << "\n\nGoodbye.\n\n";


	return 0;
}






int load_table (Table & my_table)
{
	char topic [51];
	char url [101];
	char summary [251];
	char review [251];
	int rating = 0;

	int count = 0;

	ifstream file_in;

	file_in.open ("websites.txt");

	if (!file_in)
	{
		cout << "\n\nFailed to load data from file.\n\n";	
		return 0;
	}

	for (count = 0; file_in && !file_in.eof (); ++count)
	{
		file_in.get (topic, 51, '\n');
		file_in.ignore (100, '\n');
		
		if (file_in && !file_in.eof ())
		{
			file_in.get (url, 101, '\n');
			file_in.ignore (100, '\n');
		}

		if (file_in && !file_in.eof ())
		{
			file_in.get (summary, 251, '\n');
			file_in.ignore (100, '\n');
		}

		if (file_in && !file_in.eof ())
		{
			file_in.get (review, 251, '\n');
			file_in.ignore (100, '\n');
		}

		if (file_in && !file_in.eof ())
		{
			file_in >> rating;
			file_in.ignore (100, '\n');
		}

		if (file_in && !file_in.eof ())
		{
			if (!my_table.add_website (topic, url, summary, review, 
				rating))
			{	
				cout << "\n\nERROR: No table to add to\n\n";
			}
		}

	}

	--count;
	
	return count;
}



void add (Table & my_table)
{
	char topic [51];
	char url [101];
	char summary [251];
	char review [251];
	int rating = 0;
	char get_rating = 'a';
	char selection [4];
	
	int added = 0;
	
	do
	{
		cout << "\n\nWhat is the topic of the website? (50 characters max"
			<< "\n\n";

		cin.get (topic, 51, '\n');
		cin.ignore (100, '\n');

		cout << "\nWhat is the URL of the website?\n\n";
		
		cin.get (url, 101, '\n');
		cin.ignore (100, '\n');

		cout << "\nWhat is a summary of the website? (250 characters max)"
			<< "\n\n";
		
		cin.get (summary, 251, '\n');
		cin.ignore (250, '\n');
	
		cout << "\nPlease write a review of the website. (250 characters "
			<< "max) \n\n";
		
		cin.get (review, 251, '\n');
		cin.ignore (100, '\n');

		do
		{
			cout << "\n\nPlease rate the website out of 5 stars. "
				<< "(examples: '1' or '2' or '5')\n\n";
			cin >> get_rating;
			cin.ignore (100, '\n');
			
			if (get_rating > '5' || get_rating < '1')
			{
				cout << "\nInvalid input. Try again.";
			}

		} while (get_rating > '5' || get_rating < '1');

		do
		{
			cout << "\n\n\tWebsite topic - " << topic
				<< "\n\tWebsite URL - " << url
				<< "\n\tWebsite summary - " << summary
				<< "\n\tWebsite review - " << review
				<< "\n\tWebsite rating - " << get_rating 
				<< " out of 5 stars.\n\n"
				<< "Is this infomation correct? Type 'yes' or "
				<< "'no'.\n\n";
			
			cin.get (selection, 4, '\n');
			cin.ignore (100, '\n');
	
			if (strcmp (selection, "no") != 0 && 
				strcmp (selection, "yes") != 0)
			{
				cout << "\n\nInvalid input. Try again.";
			}
	
		} while (strcmp (selection, "no") != 0 &&
			strcmp (selection, "yes") != 0);
 
					
	} while (strcmp (selection, "no") == 0);	
	
	if (get_rating == '1')
	{
		rating = 1;
	}

	if (get_rating == '2')
	{
		rating = 2;
	}

	if (get_rating == '3')
	{
		rating = 3;
	}

	if (get_rating == '4')
	{
		rating = 4;
	}
	
	if (get_rating == '5')
	{
		rating = 5;
	}

	added = my_table.add_website (topic, url, summary, review, rating);

	if (added)
	{
		cout << "\n\nWebsite added to table.\n\n";
	}
	else
	{
		cout << "\n\nTable not available\n\n";
	}
}
