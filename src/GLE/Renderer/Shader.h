//
// Created by Andrew Graser on 8/25/2024.
//

#ifndef OPENGL_ENGINE_SHADER_H
#define OPENGL_ENGINE_SHADER_H

namespace GLE {
    namespace glm {
        struct vec3 {
            float x, y, z;
        };
    }

    class Shader {
    public:
        Shader(const std::string &srcPath);
        ~Shader();



        void Bind() const;
        void Unbind() const;


        uint32_t GetUniformLoc(const char* name);
        void SetFloat3(const char* name, glm::vec3 v);




    private:
        uint32_t mRendererID;
        std::string mFileLoc;

        std::unordered_map<const char*, uint32_t> mUniforms;
    };
}

#endif //OPENGL_ENGINE_SHADER_H
