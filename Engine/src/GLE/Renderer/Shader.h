//
// Created by Andrew Graser on 8/25/2024.
//

#ifndef OPENGL_ENGINE_SHADER_H
#define OPENGL_ENGINE_SHADER_H

#include <glm/glm.hpp>
#include "Core/../glepch.h"
#include "Lights.h"


namespace GLE {
    class Shader {
    public:
        static std::shared_ptr<Shader> Create(const std::string& srcPath) {return std::make_shared<Shader>(srcPath);}
        static void Init();

        static std::shared_ptr<Shader> Get(const std::string& name);
        static std::unordered_map<std::string, std::shared_ptr<Shader>> GetShaders();

        [[nodiscard]] const std::string& GetName() const {return mName;}

        Shader(const std::string &srcPath);
        ~Shader();



        void Bind() const;
        void Unbind() const;


        uint32_t GetUniformLoc(const char* name);
        void SetFloat(const char* name, float v);
        void SetFloat2(const char* name, const glm::vec2& v);
        void SetFloat3(const char* name, const glm::vec3& v);
        void SetFloat4(const char* name, const glm::vec4& v);

        void SetInt(const char* name, int v);
        void SetInt2(const char* name, const glm::ivec2& v);
        void SetInt3(const char* name, const glm::ivec3& v);
        void SetInt4(const char* name, const glm::ivec4& v);

        void SetFloat4x4(const char* name, const glm::mat4& v);
        void SetFloat3x3(const char* name, const glm::mat3& v);

        void SetPointLight(std::string& name, const PointLight& light, const glm::vec3& position);


    private:
        uint32_t mRendererID;
        std::string mFileLoc;
        std::string mName;

        std::unordered_map<const char*, uint32_t> mUniforms;
    };
}

#endif //OPENGL_ENGINE_SHADER_H
