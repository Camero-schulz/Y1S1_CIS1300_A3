/************************schulzCameronA3.c**************
Student Name: Cameron Schulz        Email Id: cschul03
Due Date: November 30 2022          Course Name: CIS 1300

I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:

1) I have read and understood the University policy on academic integrity. 2) I
have completed the Computing with Integrity Tutorial on Moodle; and 3) I have
achieved at least 80% in the Computing with Integrity Self Test.

I assert that this work is my own. I have appropriately acknowledged any and
all material that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for
this course.
********************************************************/

/*********************************************************
Compiling the program
The program should be compiled using the following flags: -std=c99 -Wall

compiling:
gcc -std=c99 -Wall schulzCameronA3.c schulzCameronA3Main.c

Running: ./a.out

OR
gcc -std=c99 -Wall schulzCameronA3.c schulzCameronA3Main.c -o assn3

Running the Program: ./assn3
*********************************************************/

// WHAT NEEDS DONE -- COMPILE PROPERLY -- COMAND-LINE ARGUMENTS

#include "givenA3.h"

void topThree (int highestAmount[COUNTRIES], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]);

void printFile (int country[COUNTRIES][MEDALCAT], char countryNames[COUNTRIES][MAX_LENGTH_CNAME]);

int findMedalVal (void);

int main (int argc, char * argv[]) {

    //declare all variables here
    int i; // used for different loops and indexing

    char fileWithMedals [30] = "commonWealth.txt"; // stores the filename of a sequential data file
    int country [COUNTRIES][MEDALCAT];  // stores the medals won by each country.
    char countryNames [COUNTRIES][MAX_LENGTH_CNAME]; // stores the country names

    int totalAllCountries [COUNTRIES]; // Finds total medals for each country

    int totalAllMedals[MEDALCAT]; // Finds total number of medals in each category (Gold/Silver/Bronze)
    int maxMedals;  // Stores the maximum value in totalAllMedals
    int whichMedal; //  Stores the index of the category with maximum medals
    char medalType[MEDALCAT][MAX_LENGTH_CNAME] = {"Gold", "Silver", "Bronze"}; // 0 = Gold, 1 = Silver, 2 = Bronze

    char countryName[MAX_LENGTH_CNAME]; // Holds spot for one country name
    int countryMedals; // Stores the amount of medals that one country has won

    int indexMedal; // gets metal type
    int indexOfCountries [COUNTRIES]; // gets the index value of an array of different countries

    int num;  // used for different loops and indexing

    int minOrMax; // 1 = min, 2 = max

    int choice; // used to pick menu options

    // call function readFromFile to populate your arrays
    //readFromFile (argv[1], country, countryNames);

    readFromFile (fileWithMedals, country, countryNames); // Reads given file


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

        printf ("\nEnter your choice: ");
        scanf ("%d", &choice);
        getchar();  // removes the \n after scanf so fgets does not read it -- used in menu 5

        switch (choice) {

            // Display all country names read from file and the total number of medals won by each
            case 1:
                printFile (country, countryNames);
                break;

            // Function 2 - Find total number of medals won by each country
            case 2:

                findTotalPerCountry (country, totalAllCountries);

                for (i = 0; i < COUNTRIES; i++){

                    // Displays the result
                    printf("Country %s = %d\n", countryNames[i], totalAllCountries[i]);
                }
                break;

            // Function 3 - Finds total number of medals in each category (Gold, Silver, Bronze)
            case 3:

                maxMedals = findTotalPerMedal (country ,totalAllMedals, &whichMedal);

                // displays the results
                for (i = 0; i < MEDALCAT; i++){

                    printf("Medal = %s, Total = %d\n", medalType[i], totalAllMedals[i]);
                }

                printf("Maximum number of medals = %d in category (%s)\n", maxMedals, medalType[whichMedal]);


                break;

            // Function 4 – Display horizontal histogram
            case 4:
                findTotalPerCountry (country, totalAllCountries); // to get totalAllCountries
                hHistogram (countryNames, totalAllCountries);
                break;

            // Function 5 – Search for a country and return the total number of medals won by it
            case 5:

                findTotalPerCountry (country, totalAllCountries); // to get totalAllCountries
                countryMedals = searchCountry (countryName, countryNames, totalAllCountries);

                if (countryMedals == -1){ // returns -1 if user input is not a country name
                    printf("Country name does not exists\n");
                }

                else{
                    printf("Found it -- %s has a total of %d medals\n", countryName, countryMedals);
                }

                break;

            // Function 6 – Rank and display top three countries in order of total medals won
            case 6:

                printf("Rank top three based on total number of medals\n");

                findTotalPerCountry (country, totalAllCountries); // to get totalAllCountries
                rankTopThreeByTotal (totalAllCountries, countryNames);

                break;

            // Function 7 – Rank and display top three countries in order of total gold medals won
            case 7:

                rankTopThreeByMedal (country, countryNames);
                break;

            // Function 8 – Find and display all countries that won no X medals, given X as either Gold, Silver or Bronze
            case 8:

                indexMedal = findMedalVal(); // determines medal type

                if (indexMedal == -1){ // findMedalVal returns -1 for an incorrect value
                    break;
                }

                num = findAllWithNoXMedals (country, indexMedal, indexOfCountries);

                // Prints country names of all countries that won no X medals
                for (i = 0; i < num; i++){
                    printf("%s\n", countryNames[indexOfCountries[i]]);
                }

                break;

            // Function 9 – Find and display all countries that won ONLY X medals, given X as either Gold, Silver or Bronze
            case 9:

                indexMedal = findMedalVal(); // determines medal type

                if (indexMedal == -1){ // findMedalVal returns -1 for an incorrect value
                    break;
                }

                num = findAllWithOnlyXMedals (country, indexMedal, indexOfCountries);

                printf("Number of countries with ONLY %s medals = %d\n", medalType[indexMedal-1], num);

                // Prints country names of all countries that only won X medals
                for (i = 0; i < num; i++){
                    printf("%s\n", countryNames[indexOfCountries[i]]);
                }

                break;

            // Function 10 – Find and display name of the country that has minimum or maximum length among all countries
            case 10:

                printf("Do you want min (enter 1) or max (enter 2)?: ");
                scanf("%d", &minOrMax);

                if (minOrMax != 1 && minOrMax != 2){  // user validation
                    printf("ERROR: Unkown value -- Please only enter 1 or 2");
                    break;
                }

                num = findCountryIndexWithMinOrMaxLength (minOrMax, countryNames);

                if (minOrMax == 1){ // for min
                    printf("The country name with minimum length = %s\n", countryNames[num]);
                }

                else{ // for max
                    printf("The country name with maximum length = %s\n", countryNames[num]);
                }

                break;

            // exits menu
            case 11:

                printf("Goodbye!\n");
                break;

            default: printf ("That is an invalid choice\n");

        }

    } while (choice != 11);


   return 0;
}
