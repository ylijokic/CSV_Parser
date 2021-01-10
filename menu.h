/*
    This file contains all the functionality that is related to displaying
    and implementing the Menu features for the program. This file utilizes the
    Movie.h file where the Movie struct is defined, as well as some external libraries. It
    also calls functions from functions.h file.

    There are seven functions in this file:
        1.) parseMoviesPerYear()
        2.) count()
        3.) createNewNode()
        4.) appendNode()
        5.) processCSVFile()
        6.) displaySubMenu()
        7.) displayMenu()
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#include "helperFunctions.h"
#include "Movie.h"

#define PREFIX "movies"

/*  parseMoviesPerYear()
    Functionality: 
            This function appends the randomly generated number onto directory name string. Then it iterates through
            the Linked List and either creates a new file (Year.txt) or appends data into a file that already exists.
    Parameters:
            1.) Head Movie node of the Linked List, random number generated for firectory name, cont of movies in Linked List
    Returns:
            Does not return anything. Creates new .txt files and appends data into files.
*/
void parseMoviesPerYear(struct Movie *head, int num, int count)
{
    // Store random number as string and use strcat() to create the full directory name
    char str[12];
    sprintf(str, "%d", num);
    char dirName1[100] = "ylijokic.movies.";
    strcat(dirName1, str);
    strcat(dirName1, "/");

    // Open directory
    DIR *currDir;
    currDir = opendir(dirName1);

    // Pointer to head Movie node
    struct Movie *curr = head;

    // Iterate throughout count of Linked List
    for (int i = 0; i < count; i++)
    {
        int newFile;
        //Iterate through the Linked List
        while (curr != NULL)
        {
            // String to store year.txt file for every year.
            char fullDirName[52];
            strcpy(fullDirName, dirName1);
            char s[52];
            sprintf(s, "%d", curr->year);
            char txt[12] = ".txt";

            // Use strcat() to concatenate strings
            strcat(s, txt);
            strcat(fullDirName, s);

            // Open file with appropriate flags and write title of Movie into .txt file
            if (curr->year != 0)
            {
                newFile = open(fullDirName, O_RDWR | O_CREAT | O_APPEND, 0640);
                if (newFile == -1)
                {
                    printf("Can't open the file!\n");
                    perror("error");
                }
                write(newFile, curr->title, strlen(curr->title));
                write(newFile, "\n", 1);
                close(newFile);
            }

            curr = curr->next;
        }
    }
    closedir(currDir);
    return;
}

/*  countList()
    Functionality: 
            Used to count the number of Movie nodes stored in Linked List.
    Parameters:
            1.) Head Movie node of the Linked List
    Returns:
            Returns int data type storing count of nodes in Linked List
*/
int countList(struct Movie *head)
{
    struct Movie *curr = head;
    int count = 0;
    // Iterate through every node and print all data members
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

/*  createNewNode()
    Functionality: 
            This function allocates memory for a new Movie node and then processes the char array 
            parameter using the strtok function. The strtok function reads the line up until the ","
            character and returns apointer to the substring. Then using the calloc and strcpy functions
            we can assign the data to the appropriate Movie data members. 
    Parameters:
            1.) array of char from each line parsed from the .csv file
    Returns:
            Returns a pointer to a newly created Movie struct
    Sources Cited:
            I utilized the following resources to assist with the implementation of parsing the data from each line:
            https://c-for-dummies.com/blog/?p=2355
            https://repl.it/@cs344/studentsc#main.c
*/
struct Movie *createNewNode(char *line)
{
    // Allocate memory
    struct Movie *new_node = malloc(sizeof(struct Movie));

    // Process data for Movie title
    char *title = strtok(line, ",");
    new_node->title = calloc(strlen(title) + 1, sizeof(char));
    strcpy(new_node->title, title);

    // Process data for Movie year
    char *data = strtok(NULL, ",");
    int year = atoi(data);
    new_node->year = year;

    // Process data for Movie languages
    data = strtok(NULL, ",");
    char *languages = &data[0];
    new_node->languages = calloc(strlen(languages) + 1, sizeof(char));
    strcpy(new_node->languages, languages);

    // Process data for Movie rating
    data = strtok(NULL, ",");
    float rating = atof(data);
    new_node->rating = rating;

    new_node->next = NULL;
    return new_node;
}

/*  appendNode()
    Functionality: 
            Used to add new Movie nodes to the end of the linked List.
    Parameters:
            1.) pointer to a pointer of the Head Movie struct
            2.) pointer to the Movie struct to be appended
    Returns:
            Does not return anything. Just appends a Movie node to the Linked List by accessing
            the next data member from the Movie struct object.
*/
void appendNode(struct Movie **head_ref, struct Movie *new_node)
{
    // Iterate through linked list until last node
    struct Movie *p = *head_ref;

    while (p->next != NULL)
    {
        // Set next pointer to the node you want to append
        p = p->next;
    }

    p->next = new_node;
    return;
}

/*  processCSVFile()
    Functionality: 
            Used to read through each line of the .csv file and create Movie nodes stored in a Linked List
    Parameters:
            1.) pointer to string of csvfile to parse
    Returns:
            Returns the head node of the newly created linked list
*/
struct Movie *processCSVFile(char *csvFile)
{
    char line[1000];
    int count = 0;
    FILE *buffer_stream;
    struct Movie *head = NULL;

    /*Open the .csv file with fopen method */
    buffer_stream = fopen(csvFile, "r");
    if (buffer_stream == NULL)
    {
        printf("Unable to open file '%s'\n", csvFile);
        exit(1);
    }

    // /*Process .csv file information*/
    while (fgets(line, 1000, buffer_stream))
    {
        // For every line of the .csv file call the createNewNode() function
        struct Movie *temp = createNewNode(line);

        // Create Head Node
        if (head == NULL)
        {
            head = temp;
            count++;
        }
        // Append all other nodes to the Head
        else
        {
            appendNode(&head, temp);
            count++;
        }
    }
    // Close file
    fclose(buffer_stream);

    return head;
}

/*  displaySubMenu()
    Functionality: 
            Displays the Sub Menu to the user. The submenu prompts the user
            for an integer input 1-3. Depending on the input, the program will either call one of the
            functions or it will exit.
    Parameters: 
            N/A
    Returns:
            Does not return anything. Calls other functions or exits program.
*/
void displaySubMenu()
{
    int option;
    int flag;
    int num;
    int count;
    char csvFile[256];
    struct Movie *head = NULL;

    printf("\nWhich file do you want to process?\n");
    printf("Enter 1 to pick the largest file\n");
    printf("Enter 2 to pick the smallest file\n");
    printf("Enter 3 to specify the name of a file\n");
    printf("\nEnter a choice from 1 to 3: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        getLargestFile(csvFile);
        head = processCSVFile(csvFile);
        count = countList(head);
        num = createDirectory();
        parseMoviesPerYear(head, num, count);
        break;
    case 2:
        getSmallestFile(csvFile);
        head = processCSVFile(csvFile);
        count = countList(head);
        num = createDirectory();
        parseMoviesPerYear(head, num, count);
        break;
    case 3:
        flag = getFileByName(csvFile);
        if (flag == 1)
        {
            head = processCSVFile(csvFile);
            count = countList(head);
            num = createDirectory();
            parseMoviesPerYear(head, num, count);
        }
        break;
    // Default displayed with improper input.
    default:
        printf("Please enter a valid option 1 thru 3!\n");
        break;
    }
}

/*  displayMenu()
    Functionality: 
            Displays the Menu to the user. The Menu continuously runs a loop which prompts the user
            for an integer input 1-2. Depending on the input, the program will either call the sub menu or it will exit.
    Parameters: 
            N/A
    Returns:
            Does not return anything. Calls other functions or exits program.
*/
void displayMenu()
{
    int option;
    // Continuously run while true
    while (1)
    {
        // Menu prompt
        printf("\n1. Select file to process\n");
        printf("2. Exit the program\n");
        printf("\nEnter a choice 1 or 2: ");
        scanf("%d", &option);

        printf("\n");
        // Switch statement with options
        switch (option)
        {
        case 1:
            displaySubMenu();
            break;
        case 2:
            exit(0);
            break;

        // Default displayed with improper input.
        default:
            printf("Please enter a valid option 1 or 2!\n");
            break;
        }
    }
}