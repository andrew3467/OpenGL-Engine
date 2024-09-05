//
// Created by Andrew Graser on 9/4/2024.
//


#pragma once

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

#include "GLE/Core/Log.h"
#include <set>


//Engine Types
#define GLE_BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)
