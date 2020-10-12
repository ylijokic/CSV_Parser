#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Movie.h"
#include <regex.h>

void displayMoviesPerYear(struct Movie *head)
{
    int year;
    int count = 0;
    printf("Enter the year for which you want to see movies: ");
    scanf("%d", &year);
    printf("\n");

    struct Movie *curr = head;
    while (curr != NULL)
    {
        if (curr->year == year)
        {
            printf("%s\n", curr->title);
            count++;
        }
        curr = curr->next;
    }
    if (count == 0)
    {
        printf("No data about movies released in the year %d\n", year);
    }
    return;
}

int *getUniqueMovieYears(struct Movie *head, int *arr, int count)
{
    int i = 0;
    struct Movie *curr = head;
    while (curr != NULL)
    {
        arr[i] = curr->year;
        i++;
        curr = curr->next;
    }

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

    return arr;
}

void displayRatingsPerYear(struct Movie *head, int count)
{
    float max = 1.0;
    struct Movie *curr = head;
    struct Movie *p = curr;
    int arr[count];
    int *years = getUniqueMovieYears(head, arr, count);

    for (int i = 0; i < count; i++)
    {
        while (curr != NULL)
        {
            if (curr->year == years[i])
            {
                if (curr->rating > max)
                {
                    max = curr->rating;
                    p = curr;
                }
            }
            curr = curr->next;
        }
        max = 1.0;
        if (p->year != 0)
        {
            printf("%d %.1f %s\n", p->year, p->rating, p->title);
        }
        curr = head;
        p = curr;
    }

    return;
}

void displayMoviesPerLanguage(struct Movie *head)
{
    char language[10];
    int status;
    regex_t reg;
    printf("Enter the language for which you want to see movies: ");
    scanf("%s", language);
    printf("\n");
    struct Movie *p = head;

    status = regcomp(&reg, language, 0);
    if (status)
    {
        printf("Error with regular expression!");
    }

    while (p != NULL)
    {
        status = regexec(&reg, p->languages, 0, NULL, 0);
        // status = strcmp(language, p->languages);
        if (status == 0)
        {
            printf("%d %s\n", p->year, p->title);
        }
        p = p->next;
    }

    return;
}

void displayMenu(struct Movie *head, int count)
{
    int option;
    while (1)
    {
        printf("\n1. Show movies released in the specified year\n");
        printf("2. Show the highest rated movie for each year\n");
        printf("3. Show the title and year of release of all movies in a specific language\n");
        printf("4. Exit the program\n\n");
        printf("\nEnter a choice from 1 to 4: ");
        scanf("%d", &option);

        printf("\n");
        switch (option)
        {
        case 1:
            /* code */
            displayMoviesPerYear(head);
            break;
        case 2:
            displayRatingsPerYear(head, count);
            break;
        case 3:
            displayMoviesPerLanguage(head);
            break;
        case 4:
            exit(0);
            break;

        default:
            printf("Please enter a valid option 1 thru 4!\n");
            break;
        }
    }
}

#endif