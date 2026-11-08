//
// Created by Agatha on 08.11.2026.
//

#include <print>
#include <box2d/box2d.h>
#include <box2d/collision.h>
#include "../../Starter/include/sensor.h"

void Sensor::Setup(b2BodyId body_id, b2Vec2 halfSize) {

    const b2Polygon pieds = b2MakeOffsetBox(halfSize.x, halfSize.y, {0,0}, b2Rot_identity);

    b2ShapeDef def = b2DefaultShapeDef();
    def.isSensor = true;
    def.enableSensorEvents = true;
    def.userData = this;

    b2CreatePolygonShape(body_id, &def, &pieds);
}


