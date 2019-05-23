#include "SSERedef.h"
#ifdef SSEOP 

void Vector2f::Equal(const Vector3f &p) { x = p.x; y = p.y; }
void Vector2f::Equal(const Vector4f &p) { x = p.x; y = p.y; }
void Vector2f::operator=(const Vector3f &p) { this->Equal(p); }
void Vector2f::operator=(const Vector4f &p) { this->Equal(p); }
Vector2f::Vector2f(const Vector3f &p) { this->Equal(p); }
Vector2f::Vector2f(const Vector4f &p) { this->Equal(p); }

void Vector3f::Equal(const Vector2f &p) { dat = p.dat; }
void Vector3f::Equal(const Vector4f &p) { x = p.x; y = p.y; z = p.z; }
void Vector3f::operator=(const Vector2f& p) { this->Equal(p); }
void Vector3f::operator=(const Vector4f &p) { this->Equal(p); }
Vector3f::Vector3f(const Vector2f& p) { this->Equal(p); }
Vector3f::Vector3f(const Vector4f &p) { this->Equal(p); }



void Vector4f::Equal(const Vector3f &p) { dat = p.dat; }
void Vector4f::Equal(const Vector2f &p) { dat = p.dat; }
void Vector4f::operator=(const Vector3f &p) { this->Equal(p); }
void Vector4f::operator=(const Vector2f &p) { this->Equal(p); }

Vector4f::Vector4f(const Vector3f &p) { this->Equal(p); }
Vector4f::Vector4f(const Vector2f &p) { this->Equal(p); }

#endif