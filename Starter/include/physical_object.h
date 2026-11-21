//
// Created by Agatha on 08.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_PHYSICAL_OBJECT_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_PHYSICAL_OBJECT_H
#include <box2d/id.h>
#include <box2d/math_functions.h>
#include <box2d/types.h>

class PhysicalObject {
    b2BodyId body_ = b2_nullBodyId;


public:
    PhysicalObject() = default;
    ~PhysicalObject();

    PhysicalObject(const PhysicalObject&) = delete;
    PhysicalObject& operator=(const PhysicalObject&) = delete;

    // Déplacement autorisé
    PhysicalObject(PhysicalObject&& other) noexcept;
    PhysicalObject& operator=(PhysicalObject&& other) noexcept;


    void Setup(b2WorldId world, b2BodyType type, b2Vec2 position, b2Vec2 halfSize, bool fixedRotation = true);
    void SetupCircle(b2WorldId world, b2BodyType type, b2Vec2 position, b2Vec2 halfSize, bool fixedRotation = true);
    void Destroy();

    b2Vec2 GetPosition() const;
    b2Vec2 GetVelocity() const;
    void SetVelocity(b2Vec2 vel);
    void SetGravityScale(float scale);
    b2BodyId GetBodyId() const { return body_; }
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_PHYSICAL_OBJECT_H
