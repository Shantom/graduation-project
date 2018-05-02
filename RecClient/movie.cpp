#include "movie.h"


void Movie::setID(std::string id)
{
    this->id=id;
}

std::string Movie::ID() const
{
    return this->id;
}

void Movie::setTitle(std::string title)
{
    this->title=title;
}

std::string Movie::Title() const
{
    return this->title;
}

void Movie::setGenres(std::vector<std::string> genres)
{
    this->genres=genres;
}

std::vector<std::string> Movie::Genres() const
{
    return this->genres;
}

std::string Movie::GenreStr()
{
    std::string genreStr;
    for(int i=0;i<genres.size();i++)
    {
        if(i!=0)
            genreStr.append(",");
        genreStr.append(genres[i]);
    }
    return genreStr;
}
