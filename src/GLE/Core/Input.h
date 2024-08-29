//
// Created by Andrew Graser on 8/28/2024.
//

#ifndef OPENGL_ENGINE_INPUT_H
#define OPENGL_ENGINE_INPUT_H

namespace GLE {
    class Input {
    public:
        static bool GetKey(uint32_t keycode);
        static bool GetMouseButton(uint32_t mousecode);
    };
}

#endif //OPENGL_ENGINE_INPUT_H
