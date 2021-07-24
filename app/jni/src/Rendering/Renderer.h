//
// Created by xXRag on 2021-07-04.
//

#ifndef TESTPROJECT_RENDERER_H
#define TESTPROJECT_RENDERER_H


#include <cstdint>
#include "Camera/OrthographicCamera.h"
#include "Texture2D/Texture2D.h"

class Renderer
{
public:
    static void Initialize();
    static void Shutdown();

    static void Begin(const OrthographicCamera& camera);
    static void End();
    static void Flush();

    static void DrawQuad(const glm::mat4& tm, const glm::vec4& color);
    static void DrawQuad(const glm::mat4& tm, const std::shared_ptr<Texture2D>& texture, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& pos, const glm::vec2& scale, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& pos, const std::shared_ptr<Texture2D>& texture, const glm::vec4& color);

    static void Render();
    static void Clear();

    static std::shared_ptr<Texture2D> GetWhiteTexture();

private:
    static void StartNewBatch();
    static void ResetBatchData();
};


#endif //TESTPROJECT_RENDERER_H
