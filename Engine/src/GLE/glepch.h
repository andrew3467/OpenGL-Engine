//
// Created by Andrew Graser on 7/26/2024.
//

#ifndef OPENGL_ENGINE_GLEPCH_H
#define OPENGL_ENGINE_GLEPCH_H

#define ASSETS_FOLDER std::string("../../assets/")

//std
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <unordered_map>
#include <queue>
#include <future>
#include <ostream>
#include <fstream>

#include <cstdio>

#include "Core/Log.h"
#include <set>
#include <utility>

//Engine Types
#define GLE_BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

typedef uint64_t id_t;


#endif //OPENGL_ENGINE_GLEPCH_H
