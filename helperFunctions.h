/*
    This file contains all the helper functions to assist with creating directories and searching 
    directories for specific files.

    There are five functions in this file:
        1.) getUniqueMovieYears()
        2.) createDirectory()
        3.) getLargestFile()
        4.) getSmallestFile()
        5.) getFileByName()
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Movie.h"
#include <regex.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#define PREFIX "movies"

/*  getUniqueMovieYears()
    Functionality: 
            This is a helper function for Option 2 in the Menu. The function fills the arr[] with every 
            Movie year data member stored in the linked list. Then it iterates through the arr[] to remove
            duplicates and only store unique values. It returns the newly created arr. 
    Parameters:
            1.) Head Movie node in the Linked List
            2.) Integer array with 'count' number of values
            3.) Count of Movies in Linked List
    Returns:
            Returns an array of integers which contains unique Movie release years from Linked List.
    Cited Sources:
            I utilized thw following resource to help with the implementation of removing duplicate values from an array:
            https://www.w3resource.com/c-programming-exercises/array/c-array-exercise-6.php
*/
int *getUniqueMovieYears(struct Movie *head, int *arr, int count)
{
    int i = 0;

    // Iterate through linked list and fill arr with Movie year values
    struct Movie *curr = head;
    while (curr != NULL)
    {
        arr[i] = curr->year;
        i++;
        curr = curr->next;
    }

    // Iterate though arr to get only unique values
    // Beginning of code used from sources cited
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count;)
        {
            if (arr[i] == arr[j])
            {
                for (int k = j; k < count; k++)
                {
                    arr[k] = arr[k + 1];
                }
                count--;
            }
            else
            {
                j++;
            }
        }
    }
    // End of sources cited

    return arr;
}

/*  createDirectory()
    Functionality: 
            This function creates a new directory using the mkdir() function. The random number to distinguish unique directories 
            is generated in this function. 
    Parameters:
            N/A
    Returns:
            Returns an int data type representing the random number to distinguish directories
*/
int createDirectory()
{
    //Generate random number
    int num;
    num = rand() % (99999) + 1;
    char str[12];
    sprintf(str, "%d", num);

    // Use strcat() to concatenate string
    char dirName1[100] = "ylijokic.movies.";
    strcat(dirName1, str);

    // Make directory with permission flags
    mkdir(dirName1, S_IRWXU | S_IRGRP | S_IXGRP);
    printf("Created directory with name %s\n", dirName1);
    return num;
}

/*  getLargestFile()
    Functionality: 
            This function opens the current directory and then iterates through all the directories, comparing
            file sizes to find the largest file.
    Parameters:
            1.) Takes in a pointer to a char to store the name of the directory
    Returns:
            Does not return anything, string is manipulated.
    Sources Cited:
            I utilized the following resources to assist with the implementation of parsing the data from each line:
            https://repl.it/@cs344/35statexamplec#main.c
*/
void getLargestFile(char *entryName)
{
    DIR *currDir = opendir(".");
    struct dirent *directory;
    struct stat directoryStat;
    int i = 0;
    char str[256];

    off_t largestFile;

    //Iterate through the currunt directory files
    while ((directory = readdir(currDir)) != NULL)
    {
        if (strncmp(PREFIX, directory->d_name, strlen(PREFIX)) == 0)
        {
            if (strcmp(directory->d_name, "movies_by_year") != 0)
            {
                // Use stat struct to compare file sizes
                stat(directory->d_name, &directoryStat);
                if (i == 0 || directoryStat.st_size > largestFile)
                {
                    largestFile = directoryStat.st_size;
                    memset(entryName, '\0', sizeof(str));
                    strcpy(entryName, directory->d_name);
                }
            }

            i++;
        }
    }
    closedir(currDir);
    printf("Now processing the chosen file named %s\n", entryName);
}

/*  getSmallestFile()
    Functionality: 
            This function opens the current directory and then iterates through all the directories, comparing
            file sizes to find the smallest file.
    Parameters:
            1.) Takes in a pointer to a char to store the name of the directory
    Returns:
            Does not return anything, manipulates string in place.
    Sources Cited:
            I utilized the following resources to assist with the implementation of parsing the data from each line:
            https://repl.it/@cs344/35statexamplec#main.c
*/
void getSmallestFile(char *entryName)
{
    // Open current directory. Define stat/dirent struct
    DIR *currDir = opendir(".");
    struct dirent *directory;
    struct stat directoryStat;
    int i = 0;
    char str[256];

    off_t smallestFile;

    //Iterate through the currunt directory files
    while ((directory = readdir(currDir)) != NULL)
    {
        if (strncmp(PREFIX, directory->d_name, strlen(PREFIX)) == 0)
        {
            // Use stat struct to compare file sizes
            stat(directory->d_name, &directoryStat);
            if (i == 0 || directoryStat.st_size < smallestFile)
            {
                smallestFile = directoryStat.st_size;
                memset(entryName, '\0', sizeof(str));
                strcpy(entryName, directory->d_name);
            }
            i++;
        }
    }
    closedir(currDir);
    printf("Now processing the chosen file named %s\n", entryName);
}

/*  getFileByName()
    Functionality: 
            This function opens the current directory and then iterates through all the directories, comparing
            file names to get the correct file. 
    Parameters:
            1.) Takes in a pointer to a char to store the name of the directory
    Returns:
            Does not return anything, manipulates string in place.
    Sources Cited:
            I utilized the following resources to assist with the implementation of parsing the data from each line:
            https://repl.it/@cs344/35statexamplec#main.c
*/
int getFileByName(char *entryName)
{
    printf("Enter the complete file name: ");
    scanf("%s", entryName);
    printf("\n");

    // Open current directory. Define dirent/stat struct
    DIR *currDir = opendir(".");
    struct dirent *directory;
    struct stat directoryStat;
    char str[256];

    //Iterate through the currunt directory files
    while ((directory = readdir(currDir)) != NULL)
    {
        // Use stat struct to compare directory names
        stat(directory->d_name, &directoryStat);
        if (strcmp(directory->d_name, entryName) == 0)
        {
            memset(entryName, '\0', sizeof(str));
            strcpy(entryName, directory->d_name);
            printf("Now processing the chosen file named %s \n", entryName);
            return 1;
        }
    }
    closedir(currDir);
    printf("The file %s was not found. Try again\n", entryName);
    return 0;
}