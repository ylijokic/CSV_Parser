/*
    This file contains the information for the Movie Struct object.
    The Movie struct contains all information related to individual movies, 
    as well as a pointer to a Movie struct. This pointer data member allows 
    for the implementation of a linked list data structure.

    Data Members:
        title: (char array) ->      movie title
        year: (int) ->              year movie was released
        languages: (char array) ->  languages movie was released in
        rating: (float) ->          movie rating
        next: (pointer to Movie) -> stores location of next Movie struct in Linked List
*/

#ifndef MOVIE_H
#define MOVIE_H

// Movie Struct with data members
struct Movie
{
    /* data */
    char *title;
    int year;
    char *languages;
    float rating;
    struct Movie *next;
};

#endif