
// COS30008, problem set 1, 2024

#include "Matrix3x3.h"

#include <math.h>
#include <assert.h>
#include <sstream>

// Matrix multiplication
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept {
    Vector3D lResultRow1(
        row(0).dot(aOther.column(0)),
        row(0).dot(aOther.column(1)),
        row(0).dot(aOther.column(2))
    );

    Vector3D lResultRow2(
        row(1).dot(aOther.column(0)),
        row(1).dot(aOther.column(1)),
        row(1).dot(aOther.column(2))
    );

    Vector3D lResultRow3(
        row(2).dot(aOther.column(0)),
        row(2).dot(aOther.column(1)),
        row(2).dot(aOther.column(2))
    );

    return Matrix3x3(lResultRow1, lResultRow2, lResultRow3);
}

// Determinate of a matrix
float Matrix3x3::det() const noexcept {
    float lDet = row(0)[0] * (row(1)[1] * row(2)[2] - row(1)[2] * row(2)[1]) -
                 row(0)[1] * (row(1)[0] * row(2)[2] - row(1)[2] * row(2)[0]) +
                 row(0)[2] * (row(1)[0] * row(2)[1] - row(1)[1] * row(2)[0]);

    return lDet;
}

// The transpose of a matrix
Matrix3x3 Matrix3x3::transpose() const noexcept {
    return Matrix3x3(column(0), column(1), column(2));
}

// Checking if matrix is invertible
bool Matrix3x3::hasInverse() const noexcept {
    return (det() != 0) ? true : false;
}

// The inverse of a matrix
Matrix3x3 Matrix3x3::inverse() const noexcept{
    assert(det() != 0);

    Vector3D lResultRow1(
        row(1)[1] * row(2)[2] - row(1)[2] * row(2)[1],
        row(0)[2] * row(2)[1] - row(0)[1] * row(2)[2],
        row(0)[1] * row(1)[2] - row(0)[2] * row(1)[1]
    );

    Vector3D lResultRow2(
        row(1)[2] * row(2)[0] - row(1)[0] * row(2)[2],
        row(0)[0] * row(2)[2] - row(0)[2] * row(2)[0],
        row(0)[2] * row(1)[0] - row(0)[0] * row(1)[2]
    );

    Vector3D lResultRow3(
        row(1)[0] * row(2)[1] - row(1)[1] * row(2)[0],
        row(0)[1] * row(2)[0] - row(0)[0] * row(2)[1],
        row(0)[0] * row(1)[1] - row(0)[1] * row(1)[0]
    );

    return Matrix3x3(lResultRow1, lResultRow2, lResultRow3) * (1 / (det()));
}

std::ostream& operator<<(std::ostream& aOStream, const Matrix3x3& aMatrix) {
    return aOStream << "[" << aMatrix.row(0).toString()
                    << "," << aMatrix.row(1).toString()
                    << "," << aMatrix.row(2).toString() << "]";
}