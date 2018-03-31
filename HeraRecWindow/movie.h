#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <vector>

class Movie
{
public:
    Movie(std::string id,std::string title, std::vector<std::string> genres)
        :id(id),title(title),genres(genres){}
    void setID(std::string id);
    std::string ID();
    void setTitle(std::string title);
    std::string Title();
    void setGenres(std::vector<std::string> genres);
    std::vector<std::string> Genres();
    std::string GenreStr();
private:
    std::string id;
    std::string title;
    std::vector<std::string> genres;
};

#endif // MOVIE_H
