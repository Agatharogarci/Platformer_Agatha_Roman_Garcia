//
// Created by Agatha on 08.11.2026.
//

#ifndef PLATFORMER_AGATHA_ROMAN_GARCIA_PHYSICAL_OBJECT_H
#define PLATFORMER_AGATHA_ROMAN_GARCIA_PHYSICAL_OBJECT_H

class physical_object {
    b2BodyId body_ = b2_nullBodyId;
    public:
    physical_object() = default;
    ~physical_object();
};
#endif //PLATFORMER_AGATHA_ROMAN_GARCIA_PHYSICAL_OBJECT_H
