//
// Created by Agatha on 08.11.2026.
//
#include "../../Starter/include/physical_object.h"

#include <box2d/box2d.h>


PhysicalObject::~PhysicalObject() {
    if (b2Body_IsValid(body_)) {
        b2DestroyBody(body_);
        body_ = b2_nullBodyId;
    }
}


void PhysicalObject::Setup(b2WorldId world, b2BodyType type, b2Vec2 position, b2Vec2 halfSize, bool fixedRotation) {
    b2BodyDef def = b2DefaultBodyDef();
    def.type = type;
    def.position = position;
    def.fixedRotation = true; // Empêche le personnage ou la plateforme de pivoter/tomber sur le côté

    body_ = b2CreateBody(world, &def);

    // Forme rectangulaire invisible
    b2Polygon square = b2MakeBox(halfSize.x, halfSize.y);

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 1.0f;
    shape_def.material.friction = 0.2f;
    shape_def.material.restitution = 0.0f;
    shape_def.enableSensorEvents = true;

    b2CreatePolygonShape(body_, &shape_def, &square);
}

void PhysicalObject::SetupCircle(b2WorldId world, b2BodyType type, b2Vec2 position, b2Vec2 halfSize,
    bool fixedRotation) {
    b2BodyDef def = b2DefaultBodyDef();
    def.type = type;
    def.position = position;
    def.fixedRotation = true;

    body_ = b2CreateBody(world, &def);

    b2Circle circle = {{0.0f, 0.0f}, halfSize.x};


    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 1.0f;
    shape_def.material.friction = 0.2f;
    shape_def.material.restitution = 0.0f;
    shape_def.enableSensorEvents = true;

    b2CreateCircleShape(body_, &shape_def, &circle);

}

b2Vec2 PhysicalObject::GetPosition() const {
    if (b2Body_IsValid(body_)) {
        return b2Body_GetPosition(body_);
    }
    return {0.0f, 0.0f};
}

b2Vec2 PhysicalObject::GetVelocity() const {
    if (b2Body_IsValid(body_)) {
        return b2Body_GetLinearVelocity(body_);
    }
    return {0.0f, 0.0f};
}

void PhysicalObject::SetVelocity(b2Vec2 vel) {
    if (b2Body_IsValid(body_)) {
        b2Body_SetLinearVelocity(body_, vel);
    }
}
void PhysicalObject::SetGravityScale(float scale) {
    if (b2Body_IsValid(body_)) {
        b2Body_SetGravityScale(body_, scale);
    }
}