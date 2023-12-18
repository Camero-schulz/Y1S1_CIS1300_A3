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
#include "givenA3.h"
void topThree (int highestAmount[COUNTRIES], char countryNames [COUNTRIES][MAX_LENGTH_CNAME]);

// call function readFromFile to populate your arrays
void readFromFile (char fName [30], int country [COUNTRIES][MEDALCAT],
    char countryNames [COUNTRIES][MAX_LENGTH_CNAME]){

    int x = 0;

    // Opens file
    FILE * fPtr;
    fPtr = fopen(fName, "r");

    // Loops for # of lines
    while (!feof (fPtr)) {

        // Scans a line -- saves the country name and different medals earned for each country
        fscanf(fPtr, "%s %d %d %d", countryNames[x], &country[x][0], &country[x][1], &country[x][2]);

        x++;

    }

    fclose(fPtr); // closes file


}

// 1 - Display all country names read from file and the total number of medals won by each
void printFile (int country[COUNTRIES][MEDALCAT], char countryNames[COUNTRIES][MAX_LENGTH_CNAME]){

    printf("COUNTRY \t GOLD \t SILVER  BRONZE\n");
    for (int i = 0; i < COUNTRIES; i++) {

        printf("%12s \t %d \t %d \t %d\n", countryNames[i], country[i][0], country[i][1], country[i][2]);

    }
    printf("\n");
}

// 2 - Finds total number of medals won by each country
void findTotalPerCountry (int country [COUNTRIES] [MEDALCAT],
    int totalAllCountries [COUNTRIES]){

    int i;

    // Finds total amount of medals per country
    for (i = 0; i < COUNTRIES; i++){
        totalAllCountries[i] = country[i][0] + country[i][1] + country[i][2];

    }
}

// 3 - Finds total number of medals in each category (Gold, Silver, Bronze)
int findTotalPerMedal (int country [COUNTRIES][MEDALCAT],
    int totalAllMedals [MEDALCAT], int * whichMedal){

    int i;

    totalAllMedals[0] = 0;  // gold
    totalAllMedals[1] = 0;  // silver
    totalAllMedals[2] = 0;  // bronze

    // Adds all gold medals, adds all silver medals, and adds all bronze medals
    for (i = 0; i < COUNTRIES; i++){

        totalAllMedals[0] = totalAllMedals[0] + country[i][0];
        totalAllMedals[1] = totalAllMedals[1] + country[i][1];
        totalAllMedals[2] = totalAllMedals[2] + country[i][2];

    }

    int maxMedalValue = 0;

    // Finds which type of medal has the most amount of medals
    for (i = 0; i < MEDALCAT; i++){

        if (maxMedalValue < totalAllMedals[i]){
            maxMedalValue = totalAllMedals[i]; // determines the maximum value in totalAllMedals
            *whichMedal = i; // determines the index of the category with maximum medals
        }
    }

    return maxMedalValue; // Returns the maximum value in totalAllMedals

}

// 4 - Display horizontal histogram
void hHistogram (char countryNames [COUNTRIES][MAX_LENGTH_CNAME],
    int totalMedals[COUNTRIES]){

    int i = 0; // determines which country
    int star; // determines # of stars to print

    do{

        printf("%-10s: ", countryNames[i]); // prints name of country

        // prints 1 star for every 2 medals earned per country (rounds up)
        for (star = 0; star < totalMedals[i] / 2 + totalMedals[i] % 2; star++){
            printf("*");
        }
        printf("(%d)\n", totalMedals[i]); // prints number of medals

        i++;

    } while (i != COUNTRIES);
}

// 5 - Search for a country and return the total number of medals won by it
int searchCountry (char countryName [MAX_LENGTH_CNAME],
    char countryNames [COUNTRIES][MAX_LENGTH_CNAME],
    int totalAllCountries [COUNTRIES]){

    int i;

    printf("Enter a name of a country, we will return the total medals the country has won: ");

    fgets(countryName, MAX_LENGTH_CNAME, stdin);  // Gets user input
    countryName[strlen(countryName)-1] = '\0';    // Ends string and removes \n

    // Loops for # of countries available (15)
    for (i = 0; i < COUNTRIES; i++){

        // Compares user input with the country names to see if any matches
        if (strcmp(countryName, countryNames[i]) == 0){
            return totalAllCountries[i];  // Returns the # of medals the country has won
        }
    }

    return -1;  // returns -1 if the country does not exist
}

// 6 - Rank and display top three countries in order of total medals won
void rankTopThreeByTotal (int totalAllCountries [COUNTRIES],
    char countryNames [COUNTRIES][MAX_LENGTH_CNAME]){

    // Make a new array so data doesn't change for totalAllCountries
    int newTotalCountries[COUNTRIES];

    // new array will copy totalAllCountries
    for (int i = 0; i < COUNTRIES; i++){
        newTotalCountries[i] = totalAllCountries[i];
    }

    // Will find the top three countries with the most medals and print the results
    topThree(newTotalCountries, countryNames);
}

// 7 - Rank and display top three countries in order of total gold medals won
void rankTopThreeByMedal (int country [COUNTRIES][MEDALCAT],
    char countryNames [COUNTRIES][MAX_LENGTH_CNAME]){

    printf("Rank top three Based on Gold medals\n");

    // Make a new array so data doesn't change for country
    int countryGold[COUNTRIES];

    // new array will copy totalAllCountries
    for (int i = 0; i < COUNTRIES; i++){
        countryGold[i] = country[i][0];
    }

    // Will find the top three countries with the most gold medals and print the results
    topThree(countryGold, countryNames);

}

// for functions 6 and 7 -- ranks top three of any value
void topThree (int highestAmount[COUNTRIES],
    char countryNames [COUNTRIES][MAX_LENGTH_CNAME]){

    int i; // used to index all countries
    int x = 0; // used to index the top 3 medal counts
    int pickedVal; // saves the index of the highest value used

    int topThreeVal[3] = {0, 0, 0}; // will hold 3 of the most medals earned
    char highestCountry[3][MAX_LENGTH_CNAME]; // will hold the country names of those who have the most medals

    do{
        for (i = 0; i < COUNTRIES; i++){ // loops for # of countries

            // Determines the highest value out of the array
            if (topThreeVal[x] < highestAmount[i]){
                topThreeVal[x] = highestAmount[i];

                // saves the country with the most medals
                strcpy(highestCountry[x], countryNames[i]);

                pickedVal = i; // saves the index of the highest value used

            }
        }
        highestAmount[pickedVal] = 0; // set to 0 so value cannot be picked again

        x++;

    } while (x != 3); // Runs for a total of 3 times for the top 3 countries


    // PRINTS RESULTS
    for (i = 0; i < 3; i++){
        printf("%s (%d)\n", highestCountry[i], topThreeVal[i]);
    }
}

// finds the value for indexMedal
int findMedalVal (void){

    int indexMedal;

    printf("Which medal would you like to look for? -- ");
    printf("Type 1 for Gold, 2 for Silver, 3 for Bronze: ");
    scanf("%d", &indexMedal); // user input

    if (indexMedal >= 1 && indexMedal <= 3){ // validates input
        return indexMedal;
    }

    else{
        printf("ERROR: Unkown value - please only enter 1, 2 or 3");
        return -1; // returns -1 if user does not type 1, 2 or 3
    }

}

// 8 - Returns the total number of countries with no medal of a specific category, where category =
// indexMedal (1 for Gold, 2 for Silver, 3 for Bronze)
// Stores the indices of countries that do not have indexMedal in an array called indexOfCountries.
int findAllWithNoXMedals (int country [COUNTRIES][MEDALCAT],
    int indexMedal, int indexOfCountries [COUNTRIES]){

    int i;
    int x = 0; // Counts up by # of countries that do not have indexMedal

    for (i = 0; i < COUNTRIES; i++){

        // Finds the countries that have no indexMedal
        if (country[i][indexMedal-1] == 0){

            // Saves the indicies of countries that do not have indexMedal
            indexOfCountries[x] = i;

            x++;

        }
    }

    return x;
}

// 9 - Returns the total number of countries that have ONLY won medals of a specific category, where
// category = indexMedal (1 for Gold, 2 for Silver, 3 for Bronze).
// Stores the indices of such countries in an array called indexOfCountries
int findAllWithOnlyXMedals (int country [COUNTRIES][MEDALCAT], int indexMedal, int indexOfCountries [COUNTRIES]){

    int x = 1;  // for do-while. Determines which category of medal-type we're on
    int j = 0;  // used for the two times we call function findAllWithNoXMedals

    // finds all values in the text file that are equal to 0 and are not under indexMedal
    int indexOfCountriesNew[2][COUNTRIES];

    int output[2];  // sums # of values that = 0


    do {  // Determines which category of medal-type we're on

        if (indexMedal != x){   //if indexMedal is not the same as x -- will cycle twice

          // Passes values to function to find countries that have no metals under
          // each category
          output[j] = findAllWithNoXMedals(country, x, indexOfCountriesNew[j]);

          j++;

        }

        x++;

    } while (x != 4);


    int i;
    int t = 0;  // sums the total number of countries that have ONLY won medals of a specific category

    // two for loops will go through every single value of both indexOfCountriesNew values
    // to see if two of the same indexs are both 0 in the file
    for (i = 0; i < output[1]; i++){
        for (j = 0; j < output[0]; j++){

            // checks if the two types of medals, other than indexMedal, are both equal to zero
            if (indexOfCountriesNew[0][j] == indexOfCountriesNew[1][i]){

                if (country [i][indexMedal] != 0){ // checks if the index value for type indexMedal is not zero

                    indexOfCountries[t] = indexOfCountriesNew[0][j]; // grabs the index of the remaining countries

                    t++;  // sums the total number of countries that have ONLY won medals of a specific category

                }
            }
        }
    }
    return t;

}

// 10 - Returns the index of the countryName that has min or max length.
int findCountryIndexWithMinOrMaxLength (int minOrMax,
    char countryNames [COUNTRIES][MAX_LENGTH_CNAME]){

    int i;
    int indexVal; // stores index value of country name

    if (minOrMax == 1){ // for min
        int x = 9999;

        for (i = 0; i < COUNTRIES; i++){  // loops for # of countries

            int len = strlen(countryNames[i]);

            // Determines smallest length
            if (len < x){
                x = len;
                indexVal = i; // Saves the index value of country with smallest length
            }
        }
    }

    else if (minOrMax == 2){ // for max
        int x = 0;

        for (i = 0; i < COUNTRIES; i++){  // loops for # of countries

            int len = strlen(countryNames[i]);

            // Determines largest length
            if (len > x){
                x = len;
                indexVal = i; // Saves the index value of country with largest length
            }
        }
    }

    return indexVal;  // returns index of countryName
}
