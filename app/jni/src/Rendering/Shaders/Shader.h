//
// Created by xXRag on 2021-07-04.
//

#ifndef TESTPROJECT_SHADER_H
#define TESTPROJECT_SHADER_H

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& vPath, const std::string& fPath, bool isCode);

    void GenerateShader(const char* vCode, const char* fCode);

    void Bind();
    void UploadBool(const std::string& name, bool value) const;
    void UploadInt(const std::string& name, int value) const;
    void UploadIntArray(const std::string& name, int* value, uint32_t count) const;
    void UploadFloat(const std::string& name, float value) const;
    void UploadFloat4(const std::string& name, const glm::vec4& value) const;
    void UploadMat4(const std::string& name, const glm::mat4& value) const;

public:
    static std::shared_ptr<Shader> Create(const std::string& vPath, const std::string& fPath, bool isCode = false);

private:
    uint32_t m_id;
};


#endif //TESTPROJECT_SHADER_H
