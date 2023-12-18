#include "givenA3.h"

int main (int argc, char * argv[]) {

   //declare all variables here

    int country [COUNTRIES][MEDALCAT];

    char countryNames [COUNTRIES][MAX_LENGTH_CNAME];

    int choice;

    // call function readFromFile to populate your arrays
    // readFromFile (argv[1], country, countryNames);

    do {
        printf ("\nHere is the menu \n\n");
        printf ("1. Display all country names read from file and the total number of medals won by each\n");
        printf ("2.    Function 2 - Find total number of medals won by each country\n");
        printf ("3.    Function 3 - Finds total number of medals in each category (Gold, Silver, Bronze)\n");
        printf ("4.    Function 4 – Display horizontal histogram\n");
        printf ("5.    Function 5 – Search for a country and return the total number of medals won by it\n");
        printf ("6.    Function 6 – Rank and display top three countries in order of total medals won\n");
        printf ("7.    Function 7 – Rank and display top three countries in order of total gold medals won\n");
        printf ("8.    Function 8 – Find and display all countries that won no X medals, given X as either Gold, Silver or Bronze\n");
        printf ("9.    Function 9 – Find and display all countries that won ONLY X medals, given X as either Gold, Silver or Bronze\n");
        printf ("10.   Function 10 – Find and display name of the country that has minimum or maximum length among all countries read in option 1\n");

        printf ("11.    Exit\n");

        printf ("Enter your choice: ");
        scanf ("%d", &choice);

        switch (choice) {
            case 1:

                // write code to display all country names read from file and the total number of medals won by each
                break;
            case 2:

                // write code to call Function 2 - Find total number of medals won by each country
                break;

                // write all other cases

            default: printf ("That is an invalid choice\n");

        }

    } while (choice != 11);


   return 0;
}
