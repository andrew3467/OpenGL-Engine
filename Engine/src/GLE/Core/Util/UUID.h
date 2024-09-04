//
// Created by Andrew Graser on 8/28/2024.
//

#ifndef OPENGL_ENGINE_UUID_H
#define OPENGL_ENGINE_UUID_H

namespace GLE {
    class UUID {
    public:
        UUID();
        UUID(uint64_t uuid);
        UUID(const UUID&) = default;

        operator uint64_t() const {return mUUID;}

    private:
        uint64_t mUUID;
    };
}

namespace std {
    template<>
    struct hash<GLE::UUID> {
        std::size_t operator()(const GLE::UUID& uuid) const {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}

#endif //OPENGL_ENGINE_UUID_H
