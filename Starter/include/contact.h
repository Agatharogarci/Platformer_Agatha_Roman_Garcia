//
// Created by Agatha on 10.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_CONTACT_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_CONTACT_H
#include <print>
#include <box2d/types.h>
#include <box2d/box2d.h>

#include "sensor.h"


void SensorContact(b2WorldId worldId){

    const b2SensorEvents sensors = b2World_GetSensorEvents(worldId);

    for (int i = 0; i < sensors.beginCount; ++i) {

        std::println(" Sensor Touched");

        const b2SensorBeginTouchEvent &e = sensors.beginEvents[i];

        auto *a = static_cast<Sensor*>(b2Shape_GetUserData(e.sensorShapeId));
        auto *b = static_cast<Sensor*>(b2Shape_GetUserData(e.visitorShapeId));

        if (a) {
            a->HasTouched = true;
        }

        if (b) {

            b->HasTouched = true;
        }
    }
    for (int i = 0; i < sensors.endCount; ++i) {

        std::println("Sensor not touched");

        const b2SensorEndTouchEvent &e = sensors.endEvents[i];

        auto *a = static_cast<Sensor*>(b2Shape_GetUserData(e.sensorShapeId));
        auto *b = static_cast<Sensor*>(b2Shape_GetUserData(e.visitorShapeId));

        if (a) {
            a->HasTouched = false;
        }

        if (b) {

            b->HasTouched = false;
        }
    }
}
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_CONTACT_H
