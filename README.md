# 2D Platformer — Agatha Roman Garcia

* **CMake Version:** 4.3
* **Language:** C++23
* **Physics:** Box2D | **Graphics:** SFML

## Objective
Reach the finish line without touching the moving saw.  
To make the run a bit more forgiving, there is a **checkpoint** halfway through the level.

## KeyBoard
* **Menu:** Up / Down Arrows
* **Move:** Left / Right Arrows 
* **Jump:** Space *(includes coyote time)*
* **Reset Level:** `R`

## GamePad (Tested with Playstation Controller)
* **Move:** Left Joystick
* **Jump:**  (`X`)
* *(Note: Button mappings were configured using a PlayStation controller; layout may vary on Xbox or other third-party controllers.)*

## Easy Customization
Includes a `settings.h` header file where you can easily tweak parameters like jump force, gravity, scroll speed, window size, and movement speed.

## Installation & Build
```bash
git clone (https://github.com/Agatharogarci/Platformer_Agatha_Roman_Garcia.git)
cd Platformer_Agatha_Roman_Garcia
cmake -B build -S .
cmake --build build --config Release
