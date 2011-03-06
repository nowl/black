#include "Black.h"

std::ostream& operator<<(std::ostream &out, vect2f &v)
{ out << "<" << v.x << "," << v.y; return out; }

std::ostream& operator<<(std::ostream &out, vect4f &v)
{ out << "<" << v.x << "," << v.y << "," << v.z << "," << v.w << ">"; return out; }

std::ostream& operator<<(std::ostream &out, matrix4f &m)
{
    out << "<" << m.aa << "," << m.ab << "," << m.ac << "," << m.ad << ">" << std::endl;
    out << "<" << m.ba << "," << m.bb << "," << m.bc << "," << m.bd << ">" << std::endl;
    out << "<" << m.ca << "," << m.cb << "," << m.cc << "," << m.cd << ">" << std::endl;
    out << "<" << m.da << "," << m.db << "," << m.dc << "," << m.dd << ">" << std::endl;
    return out;
}

