
// COS30008, problem set 1, 2024

#include "Polygon.h"

float Polygon::getSignedArea() const noexcept {
    float lResult = 0.0f;

    for (size_t i = 0; i < fNumberOfVertices; i++) {
        size_t j = (i + 1) % fNumberOfVertices;
        lResult += fVertices[i].x() * fVertices[j].y();
        lResult -= fVertices[i].y() * fVertices[j].x();
    }

    return lResult / 2.0f;
}

Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept {
    Polygon lResult = *this;

    for (int i = 0; i < fNumberOfVertices; i++) {
        Vector3D lTransformedVertex = Vector3D(aMatrix * fVertices[i]);

        lResult.fVertices[i] = static_cast<Vector2D>(lTransformedVertex);
    }

    return lResult;
}
