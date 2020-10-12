#ifndef MOVIE_H
#define MOVIE_H

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