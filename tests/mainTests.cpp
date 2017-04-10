//
// Created by Andrei Gavrila on 31.03.2017.
//
#include <assert.h>
#include "../src/domain/movie.h"
#include "../src/utils/vector.h"
#include <vector>

void testMovie() {
    Movie m;
    assert(m.getName() == "");
    assert(m.getYear() == 0);
    assert(m.getGenre() == "");
    assert(m.getLikes() == 0);
    assert(m.getTrailer() == "");
    
    auto* mo = new Movie("hii", 2016, "comedy", "trailer", 0);
    
    assert(mo->getName() == "hii");
    assert(mo->getYear() == 2016);
    assert(mo->getGenre() == "comedy");
    assert(mo->getLikes() == 0);
    assert(mo->getTrailer() == "trailer");
    
    mo->like();
    assert(mo->getLikes() == 1);
    
    auto* mo1 = new Movie("hii", 2015, "comedy", "", 0);
    assert(!(*mo == *mo1));
    
    auto* mo2 = new Movie("hii", 2016, "com", "", 0);
    assert((*mo == *mo2));
    
    mo2->setTrailer("trailer");
    mo2->setLikes(1);
    mo2->setGenre("comedy");
//    std::cout << *mo2;
    assert(mo2->toString() == "hii (2016) [comedy] Rating: 1 Duration: 0 minutes.");
    assert(*mo == *mo2);
    
    delete mo;
    delete mo1;
    delete mo2;
    
    
    Movie mov("haha", 0, "heee", "heee", 0);
    mov.setLikes(1337);
    auto m2 = mov;
    
    assert(m2 == mov);
}

void testVector() {
    Vector<int> vint;
    int a = 2;
    vint.push_back(a);
    vint[0] = 3;
    assert(a == 2);
    
    a = 4;
    assert(vint[0] != 4);
}

int main() {
    testMovie();
    testVector();
}
