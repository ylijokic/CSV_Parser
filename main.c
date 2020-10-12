#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Movie.h"
#include "menu.h"

struct Movie *createNewNode(char *line)
{
    struct Movie *new_node = malloc(sizeof(struct Movie));

    char *title = strtok(line, ",");
    new_node->title = calloc(strlen(title) + 1, sizeof(char));
    strcpy(new_node->title, title);

    // printf("\tTitle: %s\n", title);

    char *data = strtok(NULL, ",");
    int year = atoi(data);
    new_node->year = year;

    // printf("\tYear: %d", year);

    data = strtok(NULL, ",");
    char *languages = &data[0];
    new_node->languages = calloc(strlen(languages) + 1, sizeof(char));
    strcpy(new_node->languages, languages);
    // // printf("\tLanguages: %s", languages);

    data = strtok(NULL, ",");
    float rating = atof(data);
    new_node->rating = rating;
    // // printf("\tRating: %.1f\n", rating);

    new_node->next = NULL;
    return new_node;
}

void printList(struct Movie *head)
{
    struct Movie *curr = head;

    while (curr != NULL)
    {
        printf("Title: %s", curr->title);
        printf("  Year: %d\n", curr->year);
        printf("  Languages: %s", curr->languages);
        printf("  Rating: %.1f\n", curr->rating);
        printf("---------------------------------------------\n");
        curr = curr->next;
    }
}

void appendNode(struct Movie **head_ref, struct Movie *new_node)
{
    struct Movie *p = *head_ref;

    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = new_node;
    return;
}

int main(int argc, char *argv[])
{
    if (argc < 2) 
    {
        printf("Please provide the name of the CSV file!\n");
        return EXIT_FAILURE;
    }
    char *csv_file = argv[1];

    char line[80];
    int count = 0;
    FILE *buffer_stream;
    struct Movie *head = NULL;
    struct Movie *tail = NULL;

    /*Open the .csv file with fopen method */
    buffer_stream = fopen(csv_file, "r");
    if (buffer_stream == NULL) 
    {
        printf("Unable to open file '%s'\n", csv_file);
        exit(1);
    }

    /*Process .csv file information*/
    while (fgets(line, 80, buffer_stream))
    {
        struct Movie *temp = createNewNode(line);

        if (head == NULL)
        {
            head = temp;
            tail = temp;
            count++;
            // printf("HEAD->%s\n", head->title);
            // printf("HEAD->%s\n", tail->title);
        }
        else
        {
            appendNode(&head, temp);
            count++;
        }
    }
    fclose(buffer_stream);

    printList(head);

    printf("Processed file %s and parsed data for %d movies\n\n", csv_file, count-1);
    displayMenu(head, count);

    return EXIT_SUCCESS;
}