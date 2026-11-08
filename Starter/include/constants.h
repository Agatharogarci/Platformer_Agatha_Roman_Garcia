//
// Created by Agatha on 08.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_CONSTANTS_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_CONSTANTS_H

class Conversions {
    static constexpr float pixelsToMeters = 0.05f;


public:
    static float PhysicsToScreen(float meters) {
        return meters / pixelsToMeters;
    }
    static float ScreenToPhysics(float pixels) {
        return pixels * pixelsToMeters;
    }
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_CONSTANTS_H
