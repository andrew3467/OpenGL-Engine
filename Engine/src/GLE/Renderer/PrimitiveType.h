//
// Created by Andrew Graser on 8/27/2024.
//

#ifndef OPENGL_ENGINE_PRIMITIVETYPE_H
#define OPENGL_ENGINE_PRIMITIVETYPE_H

namespace GLE {
    enum class PrimitiveType {
        //2D
        Quad = 0,

        //3D
        Cube = 1,
        Sphere = 2,
        Capsule = 3,
    };
}

#endif //OPENGL_ENGINE_PRIMITIVETYPE_H
