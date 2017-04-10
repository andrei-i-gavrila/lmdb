//
// Created by Andrei Gavrila on 30.03.2017.
//

#ifndef LMDB_MOVIE_H
#define LMDB_MOVIE_H

#include <string>
#include <ostream>
#include <functional>

class Movie {
private:
    std::string _name;
    int _year;
    std::string _genre;
    std::string _trailer;
    int _likes;
    int _duration;
public:
    Movie();
    
    Movie(const std::string& name, const int year, const std::string& genre, const std::string& trailer, int duration);
    
    Movie(const Movie& m);
    
    Movie operator =(const Movie& other);
    
    /// @brief Compares the unique identifiers name and year
    /// @param other The comparee
    /// @return true or false
    bool operator ==(const Movie& other);
    
    
    ~Movie() = default;
    
    const std::string& getName() const;
    
    const int getYear() const;
    
    const std::string& getGenre() const;
    
    void setGenre(const std::string& newGenre);
    
    const std::string& getTrailer() const;
    
    void setTrailer(const std::string& newTrailer);
    
    const int getLikes() const;
    
    void setLikes(int newLikes);
    
    void like();
    
    const int getDuration() const;
    
    void setDuration(int newDuration);
    
    /// @brief Compares the duration
    /// @param cmpDuration The comparee
    /// @return
    bool operator <(int cmpDuration);


//    bool sameAs(const Movie& m);
    
    /// @brief Puts the movie in a stream
    /// @param os The output stream
    /// @param movie The movie
    /// @return the stream
    friend std::ostream& operator <<(std::ostream& os, const Movie& movie);
    
    /// @brief Returns a string representation
    /// @return
    const std::string toString() const;
};

#endif //LMDB_MOVIE_H
