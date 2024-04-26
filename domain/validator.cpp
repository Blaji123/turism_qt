//
// Created by Blajan David on 4/26/2024.
//
#include <vector>
#include <cassert>
#include "validator.h"
void OfertaValidator::validate(const Oferta &of) {
    std::vector<string> msg;
    if(of.getDenumire().empty())
        msg.emplace_back("Denumire cant be empty");
    if(of.getDestinatie().empty())
        msg.emplace_back("Destinatie cant be empty");
    if(of.getTip().empty())
        msg.emplace_back("Tip cant be empty");
    if(of.getPret() < 0)
        msg.emplace_back("Pret cant be negative");
    if(!msg.empty())
        throw ValidatorException(msg);
}

std::ostream& operator<<(std::ostream& out, const ValidatorException& ex) {
    for (const auto& msg : ex.msg) {
        out << msg<<" ";
    }
    return out;
}

void testValidator(){
    Oferta of{"","","",-1};
    try{
        OfertaValidator::validate(of);
    }catch (ValidatorException& e){
        string msg = e.what();
        std::stringstream sout;
        sout << e;
        auto mesaj = sout.str();
        assert(mesaj.find("negative")>=0);
        assert(mesaj.find("empty")>=0);
    }
}