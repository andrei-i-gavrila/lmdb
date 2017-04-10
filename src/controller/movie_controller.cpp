//
// Created by Andrei Gavrila on 30.03.2017.
//

#include <iostream>
#include "movie_controller.h"

MovieController::MovieController() {
    this->db = new Database<Movie>();
    this->watchlist = Vector<std::pair<std::string, int>>();
    this->currentSelection = new Vector<Movie>();
    
}

MovieController::MovieController(MovieController& mc) {
    this->db = new Database<Movie>(*(mc.db));
    this->watchlist = Vector<std::pair<std::string, int>>(mc.watchlist);
    this->currentSelection = new Vector<Movie>(*mc.currentSelection);
    
}

MovieController::~MovieController() {
    std::cout << "1";
    delete this->db;
    delete this->currentSelection;
}

bool MovieController::addMovie(const std::string& name, int year, const std::string& genre, const std::string& trailer,
                               int duration) {
    
    Movie m(name, year, genre, trailer, duration);
    
    int id = this->db->find(m);
    if (id != -1) {
        (*this->db)[id].setGenre(genre);
        (*this->db)[id].setTrailer(trailer);
        (*this->db)[id].setDuration(duration);
        
        return false;
    }
    
    this->db->add(m);
    return true;
}

Database<Movie>& MovieController::getAll() {
    return *this->db;
}

MovieController& MovieController::operator =(MovieController& other) {
    this->db = other.db;
    return *this;
}

bool MovieController::removeMovie(const std::string& name, int year) {
    Movie m(name, year, "", "", 0);
    int id = this->db->find(m);
    if (id == -1) {
        return false;
    }
    this->db->remove(m);
    
    return true;
}

Vector<Movie>* MovieController::durationLessthan(int duration) {
    return this->db->getAll().filter(std::function<bool(Movie&)>([duration](Movie& m) {
        return m < duration;
    }));
}

void MovieController::newSelection(const std::string& query) {
    auto t = this->db->getAll().filter(std::function<bool(Movie&)>([&query](Movie& m) {
        return query.empty() || m.getGenre() == query;
    }));
    this->currentSelection = t;
    this->currentSelectionId = 0;
}

Movie& MovieController::getCurrentFromSelection() {
    return (*this->currentSelection)[this->currentSelectionId];
}

void MovieController::watchTrailer() {
    system(("google-chrome " + this->getCurrentFromSelection().getTrailer()).c_str());
}

void MovieController::nextMovie() {
    this->currentSelectionId++;
}

void MovieController::likeMovie() {
    this->getCurrentFromSelection().like();
}

bool MovieController::removeFromWatchlist(const std::string& name, int year, const std::string& like) {
    auto p = std::make_pair(name, year);
    
    int wid = this->watchlist.findFirstId(p);
    
    if (wid == -1) {
        return false;
    }
    
    if (like[0] == 'y' || like[0] == 'Y') {
        (*this->db)[wid].like();
    }
    
    this->watchlist.remove(wid);
    return true;
}

Vector<std::pair<std::string, int>>& MovieController::getWatchlist() {
    return this->watchlist;
}

bool MovieController::addToWatchlist() {
    auto m = this->getCurrentFromSelection();
    auto p = std::make_pair(m.getName(), m.getYear());
    
    int wid = this->watchlist.findFirstId(p);
    
    if (wid != -1) {
        return false;
    }
    this->watchlist.push_back(p);
    return true;
}

bool MovieController::stopSelection() {
    if (!this->selectionStarted()) {
        return false;
    }
    delete this->currentSelection;
    this->currentSelection = new Vector<Movie>();
    return true;
}

bool MovieController::selectionStarted() {
    return this->currentSelection->size() != 0;
}
