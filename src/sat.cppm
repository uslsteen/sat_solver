module;
#include <iostream>

export module sat;

export class SAT {
public:
    SAT() = default;
    ~SAT() = default;
    //
    void print(std::ostream& os) const {
        os << "(\n";
        os <<  "    v\n";
        os << ")";
    }

};