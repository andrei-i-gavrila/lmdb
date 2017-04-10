#include <string>
#include "src/ui/adminconsole.h"
#include "src/ui/console.h"


int main() {
    MovieController* mc = new MovieController();
    mc->addMovie("Star wars Rogue One", 2016, "sci-fi", "https://www.youtube.com/watch?v=frdj1zb9sMY", 100);
    mc->addMovie("sjsjs", 2222, "asd", "asd", 200);
    mc->addMovie("sdafa", 2222, "foo", "asd", 120);
    mc->addMovie("aosdas", 2222, "foo", "asd", 80);
    mc->addMovie("lkkkk", 2222, "asd", "asd", 10);
    mc->addMovie("Jurassic park", 1993, "sci-fi", "https://www.youtube.com/watch?v=PJlmYh27MHg", 210);
    mc->addMovie("Ghost in the shell", 2017, "sci-fi",
                 "http://www.imdb.com/video/imdb/vi273004057?playlistId=tt1219827&ref_=tt_ov_vi", 210);
    mc->addMovie("Doctor who S10", 2017, "sci-fi", "https://youtu.be/PbJqNa0_Oz0", 180);
    mc->addMovie("Interstellar", 2014, "sci-fi", "https://youtu.be/0vxOhd4qlnA", 100);
    
    
    Console c(*mc);
    c.run();
    delete mc;
}