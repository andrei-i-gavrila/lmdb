//
// Created by Andrei Gavrila on 30.03.2017.
//

#include "movie.h"

Movie::Movie(const std::string& name, const int year, const std::string& genre, const std::string& trailer,
             int duration):
        _name(name), _year(year), _genre(genre), _trailer(trailer), _likes(0), _duration(duration) {}

Movie::Movie(const Movie& m): _name(m.getName()), _year(m.getYear()),
                              _genre(m.getGenre()), _trailer(m.getTrailer()), _likes(m.getLikes()) {}

const std::string& Movie::getName() const {
    return this->_name;
}

const int Movie::getYear() const {
    return this->_year;
}

const std::string& Movie::getGenre() const {
    return this->_genre;
}

void Movie::setGenre(const std::string& newGenre) {
    this->_genre = newGenre;
}

const std::string& Movie::getTrailer() const {
    return this->_trailer;
}

void Movie::setTrailer(const std::string& newTrailer) {
    this->_trailer = newTrailer;
}

const int Movie::getLikes() const {
    return this->_likes;
}

void Movie::setLikes(int newLikes) {
    this->_likes = newLikes;
}

void Movie::like() {
    this->_likes++;
}

std::ostream& operator <<(std::ostream& os, const Movie& movie) {
    return os << movie.toString();
}

//bool Movie::sameAs(const Movie& m) {
//    return this->getName() == m.getName() && this->getYear() == m.getYear();
//}

const std::string Movie::toString() const {
    return this->getName() + " (" + std::to_string(this->getYear()) + ") [" + this->getGenre() + "] Rating: "
           + std::to_string(this->getLikes()) + " Duration: " + std::to_string(this->getDuration()) + " minutes.";;
}


Movie::Movie(): _name(""), _year(0), _genre(""), _trailer(""), _likes(0), _duration(0) {}

Movie Movie::operator =(const Movie& other) {
    this->_name = other.getName();
    this->_year = other.getYear();
    this->_genre = other.getGenre();
    this->_trailer = other.getTrailer();
    this->_likes = other.getLikes();
    this->_duration = other.getDuration();
    return *this;
}

bool Movie::operator ==(const Movie& other) {
    return this->getName() == other.getName() &&
           this->getYear() == other.getYear();
}

const int Movie::getDuration() const {
    return this->_duration;
}

void Movie::setDuration(int newDuration) {
    this->_duration = newDuration;
}

bool Movie::operator <(int cmpDuration) {
    return this->_duration < cmpDuration;
}
