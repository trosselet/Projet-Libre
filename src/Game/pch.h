#ifndef PCH_H
#define PCH_H

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS
#define FIXED_DT 0.01666666667f

#include <SFML/Graphics.hpp>

#include "Render/Texture.h"
#include "Render/Sprite.h"
#include "Render/RenderWindow.h"
#include "Resources.h"

#include <windows.h>
#include <iostream>
#include <fstream>

#include "Utils/Debug.h"
#include "Utils/Profiler.h"
#include "Inputs/Mouse.h"
#include "Inputs/Keyboard.h"

#endif