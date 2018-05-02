#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <vector>

class Movie
{
public:
    Movie(std::string id,std::string title, std::vector<std::string> genres)
        :id(id),title(title),genres(genres){}
    Movie(){}
    void setID(std::string id);
    std::string ID() const;
    void setTitle(std::string title);
    std::string Title() const;
    void setGenres(std::vector<std::string> genres);
    std::vector<std::string> Genres() const;
    std::string GenreStr();
private:
    std::string id;
    std::string title;
    std::vector<std::string> genres;
};

#endif // MOVIE_H
