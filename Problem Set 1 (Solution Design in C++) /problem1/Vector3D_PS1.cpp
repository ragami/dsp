
// COS30008, problem set 1, 2024

#include "Vector3D.h"
#include <sstream>

using namespace std;

string Vector3D::toString() const noexcept
{
    stringstream lVectorString;
    lVectorString << "[" << round(x() * 10000.0f) / 10000.0f << ","
                  << round(y() * 10000.0f) / 10000.0f << ","
                  << round(w() * 10000.0f) / 10000.0f << "]";
    return lVectorString.str();
}
