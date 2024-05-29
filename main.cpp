#include <QApplication>

#include "repository/AgentieRepo.h"
#include "repository/Wishlist.h"
#include "service/AgentieService.h"
#include "domain/validator.h"
#include "ui/GUI.h"

void runAllTests(){
    testWishlist();
    testeRepo();
    testeService();
    testValidator();
}

int main(int argc, char *argv[]) {
    runAllTests();
    QApplication app(argc, argv);
    AgentieRepoFile repo{"oferte.txt"};
    Wishlist wishlist{repo};
    AgentieService service{repo, wishlist};

    GUI gui{service, wishlist};
    return QApplication::exec();
}

//int main() {
//    runAllTests();
//    AgentieRepoFile repo{"oferte.txt"};
//    Wishlist wishlist{repo};
//    AgentieService service{repo, wishlist};
//    Console console{service};
//    console.start();
//}
