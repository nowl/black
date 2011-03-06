#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>

template<int N, class T>
class matrix
{
};

typedef class matrix<4, float> matrix4f;

template<int N, class T>
class vect
{
};

typedef class vect<4, float> vect4f;
typedef class vect<2, float> vect2f;

template<>
class vect<4, float>
{
public:
    vect(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    float x, y, z, w;
};

template<>
class vect<2, float>
{
public:
    vect(float x, float y) : x(x), y(y) {}

    float x, y;
};

template<>
class matrix<4, float>
{
public:
    matrix(float mat[4][4])
    {
        aa = mat[0][0];
        ab = mat[0][1];
        ac = mat[0][2];
        ad = mat[0][3];
        ba = mat[1][0];
        bb = mat[1][1];
        bc = mat[1][2];
        bd = mat[1][3];
        ca = mat[2][0];
        cb = mat[2][1];
        cc = mat[2][2];
        cd = mat[2][3];
        da = mat[3][0];
        db = mat[3][1];
        dc = mat[3][2];
        dd = mat[3][3];
    }

    vect4f operator*(const vect4f& v)
    {
        return vect4f(v.x*aa+v.y*ab+v.z*ac+v.w*ad,
                      v.x*ba+v.y*bb+v.z*bc+v.w*bd,
                      v.x*ca+v.y*cb+v.z*cc+v.w*cd,
                      v.x*da+v.y*db+v.z*dc+v.w*dd);
    }

    float aa, ab, ac, ad, ba, bb, bc, bd, ca, cb, cc, cd, da, db, dc, dd;
};

std::ostream& operator<<(std::ostream &out, vect2f &v);
std::ostream& operator<<(std::ostream &out, vect4f &v);
std::ostream& operator<<(std::ostream &out, matrix4f &m);

#endif // __VECTOR_H__
