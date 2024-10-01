//
// Created by Andrew Graser on 8/25/2024.
//

#ifdef GLE_PLATFORM_GLFW

#include "Renderer/Shader.h"

#include <glm/gtc/type_ptr.hpp>
#include "Glad/glad.h"


namespace GLE {
    //region Shader Load
    static GLenum ShaderTypeFromString(const std::string &type) {
        if(type == "vertex") return GL_VERTEX_SHADER;
        if(type == "fragment") return GL_FRAGMENT_SHADER;

        GLE_ASSERT(false, "ERROR: Unknown shader type: {0}", type);
        return 0;
    }

    static const char* ShaderTypeToString(GLenum type) {
        if(type == GL_VERTEX_SHADER) return "vertex";
        if(type == GL_FRAGMENT_SHADER) return "fragment";

        GLE_ASSERT(false, "ERROR: Unknown shader type: {0}", type);
        return "";
    }

    /// returns: non positive integer if compilation fails
    uint32_t CompileShader(GLuint type, const char* src) {
        GLuint id = glCreateShader(type);
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        //Error handling
        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if(!success) {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            GLE_ERROR(errorLog.data());

            glDeleteShader(id);
            return -1;
        }

        return id;
    }

    std::string LoadSource(const std::string &path) {
        std::ifstream file(path, std::ios::in | std::ios::binary);
        std::string result;

        if(file) {
            file.seekg(0, std::ios::end);
            size_t size = file.tellg();
            if(size != -1) {
                result.resize(size);
                file.seekg(0, std::ios::beg);
                file.read(&result[0], size);

            } else{
                GLE_ERROR("ERROR: Failed to read shader file at: {0}");
            }

        } else {
            GLE_ERROR("ERROR: Failed to open shader file at: {0}", path);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> PreProcess(const std::string &source) {
        std::unordered_map<GLenum, std::string> result;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while(pos != std::string::npos) {
            size_t eol = source.find_first_of("\r\n", pos);
            GLE_ASSERT(eol != std::string::npos, "Syntax Error!");

            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            GLE_ASSERT(nextLinePos != std::string::npos, "Syntax Error!");

            result[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }

        return result;
    }

    std::vector<uint32_t> CreateShaders(const std::string &srcPath) {
        std::string src = LoadSource(srcPath);
        auto shaderSources = PreProcess(src);

        std::vector<uint32_t> shaders;

        for(auto shader : shaderSources) {
            GLenum type = shader.first;
            const char* src = shader.second.c_str();

            uint32_t id = glCreateShader(type);
            glShaderSource(id, 1, &src, nullptr);
            glCompileShader(id);

            GLint success = 0;
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);

            if(!success) {
                GLint maxLength = 0;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
                std::vector<GLchar> errorLog(maxLength);
                glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

                GLE_ERROR("Failed to compile {0} shader!\n{1}", ShaderTypeToString(type), errorLog.data());
            }

            shaders.push_back(id);
        }

        return shaders;
    }

    void CleanupShaders(const std::vector<uint32_t>& shaders, GLuint program) {
        for(auto &shader : shaders) {
            glDetachShader(program, shader);
            glDeleteShader(shader);
        }
    }

    int CreateShaderProgram(const std::string &srcpath) {
        auto shaders = CreateShaders(srcpath);

        GLE_ASSERT(!shaders.empty(), "ERROR: Shader program provided no compiled shaders!\nCheck file path and error log!");

        GLuint id = glCreateProgram();

        for(auto &shader : shaders) {
            glAttachShader(id, shader);
        }

        glLinkProgram(id);

        GLint isLinked = 0;
        glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(id);
        }

        CleanupShaders(shaders, id);

        return id;
    }
    //endregion


    Shader::Shader(const std::string &srcPath) : mFileLoc(srcPath) {
        mRendererID = CreateShaderProgram(srcPath);

        auto baseFileName = srcPath.substr(srcPath.find_last_of("\\/") + 1);
        int const p = baseFileName.find_last_of('.');
        mName = baseFileName.substr(0, p);
    }

    Shader::~Shader() {

    }

    void Shader::Bind() const {
        glUseProgram(mRendererID);
    }

    void Shader::Unbind() const {
        glUseProgram(0);
    }

    uint32_t Shader::GetUniformLoc(const std::string& name) {
        if(!mUniforms.contains(name)) {
            mUniforms[name] = glGetUniformLocation(mRendererID, name.c_str());
        }

        return mUniforms[name];
    }




#pragma region Uniforms

    void Shader::SetBool(const std::string& name, bool value) {
        glUniform1i(GetUniformLoc(name), value);
    }


    void Shader::SetFloat(const std::string& name, float v) {
        glUniform1f(GetUniformLoc(name), v);
    }

    void Shader::SetFloat2(const std::string& name, const glm::vec2 &v) {
        glUniform2f(GetUniformLoc(name), v.x, v.y);
    }

    void Shader::SetFloat3(const std::string& name, const glm::vec3& v) {
        glUniform3f(GetUniformLoc(name), v.x, v.y, v.z);
    }

    void Shader::SetFloat4(const std::string& name, const glm::vec4 &v) {
        glUniform4f(GetUniformLoc(name), v.x, v.y, v.z, v.w);
    }

    void Shader::SetInt(const std::string& name, int v) {
        glUniform1i(GetUniformLoc(name), v);
    }

    void Shader::SetInt2(const std::string& name, const glm::ivec2 &v) {
        glUniform2i(GetUniformLoc(name), v.x, v.y);
    }

    void Shader::SetInt3(const std::string& name, const glm::ivec3 &v) {
        glUniform3i(GetUniformLoc(name), v.x, v.y, v.z);
    }

    void Shader::SetInt4(const std::string& name, const glm::ivec4 &v) {
        glUniform4i(GetUniformLoc(name), v.x, v.y, v.z, v.w);
    }

    void Shader::SetFloat4x4(const std::string& name, const glm::mat4 &v) {
        glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE, glm::value_ptr(v));
    }

    void Shader::SetFloat3x3(const std::string& name, const glm::mat3 &v) {
        glUniformMatrix3fv(GetUniformLoc(name), 1, GL_FALSE, glm::value_ptr(v));
    }

    void Shader::SetPointLight(std::string& name, const PointLight &light, const glm::vec3& position) {
        SetFloat3(name + ".Position", position);
        SetFloat3(name + ".Color", light.Ambient);
    }

#pragma endregion
}



#endif
