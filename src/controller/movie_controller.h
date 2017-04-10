//
// Created by Andrei Gavrila on 30.03.2017.
//

#ifndef LMDB_MOVIE_CONTROLLER_H
#define LMDB_MOVIE_CONTROLLER_H


#include "../domain/movie.h"
#include "../database/database.h"

class MovieController {
private:
    Database<Movie>* db;
    Vector<std::pair<std::string, int>> watchlist;
    int currentWatch;
    Vector<Movie>* currentSelection;
    int currentSelectionId;
public:
    
    MovieController();
    
    MovieController(MovieController& mc);
    
    MovieController& operator =(MovieController& other);
    
    ~MovieController();
    
    /// @brief Constructs and adds a movie to the repository. If it is found, then it is updated
    /// @param name
    /// @param year
    /// @param genre
    /// @param trailer
    /// @param duration
    /// @return True if it added, false if it updated an existing one
    bool
    addMovie(const std::string& name, int year, const std::string& genre, const std::string& trailer, int duration);
    
    /// @brief Removes a matching movie from the database
    /// @param name
    /// @param year
    /// @return
    bool removeMovie(const std::string& name, int year);
    
    Database<Movie>& getAll();
    
    /// @brief Adds the current movie to the watchlist
    /// @return
    bool addToWatchlist();
    
    /// @brief Returns the current watchlist
    /// @return
    Vector<std::pair<std::string, int>>& getWatchlist();
    
    
    /// @brief Removes the movie with the given attrs from the watchlist
    /// @param name
    /// @param year
    /// @param like Likes the movie if this starts with y
    /// @return
    bool removeFromWatchlist(const std::string& name, int year, const std::string& like);
    
    void likeMovie();
    
    /// @brief Starts a new selection based on the query
    /// @param query
    void newSelection(const std::string& query);
    
    /// @brief Returns the current selected element
    /// @return
    Movie& getCurrentFromSelection();
    
    /// @brief Returns true if there is an ongoing selection
    /// @return
    bool selectionStarted();
    
    
    /// @brief Stops the current selection
    /// @return
    bool stopSelection();
    
    
    /// @brief Starts chrome for the trailer of the current selected element
    void watchTrailer();
    
    /// @brief Goes to the next element
    void nextMovie();
    
    /// @brief Filters all movies with duration less than given
    /// @param duration
    /// @return
    Vector<Movie>* durationLessthan(int duration);
};


#endif //LMDB_MOVIE_CONTROLLER_H
