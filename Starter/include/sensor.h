//
// Created by Agatha on 08.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_SENSOR_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_SENSOR_H

class Sensor {

public:
    void Setup(b2BodyId body_id, b2Vec2 halfSize);
    bool HasTouched = false;
};

#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_SENSOR_H
