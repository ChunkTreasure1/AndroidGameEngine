//
// Created by xXRag on 2021-07-04.
//

#include "Renderer.h"
#include <GLES3/gl3.h>
#include <android/log.h>
#include <glm/glm.hpp>

#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include "Buffers/VertexArray.h"
#include "Shaders/Shader.h"
#include "Texture2D/Texture2D.h"

#include "android/asset_manager.h"

struct QuadVertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    float TexIndex;
};

struct RendererStorage
{
    static const uint32_t MaxQuads = 20000;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;

    std::shared_ptr<VertexArray> QuadVertexArray;
    std::shared_ptr<VertexBuffer> QuadVertexBuffer;
    uint32_t QuadIndexCount = 0;

    QuadVertex* QuadVertexBufferBase = nullptr;
    QuadVertex* QuadVertexBufferPtr = nullptr;
    glm::vec4 QuadVertexPositions[4];

    std::shared_ptr<Shader> QuadShader;
    std::shared_ptr<Texture2D> WhiteTexture;
    std::shared_ptr<Texture2D>* TextureSlots { new std::shared_ptr<Texture2D>[5] };

    uint32_t TextureSlotIndex = 1; // 0 = white texture
};

static RendererStorage* s_pData;

void Renderer::Initialize()
{
    s_pData = new RendererStorage();

    /////Quad/////
    s_pData->QuadVertexArray = VertexArray::Create();

    s_pData->QuadVertexBuffer = VertexBuffer::Create(s_pData->MaxVertices * sizeof(QuadVertex));
    s_pData->QuadVertexBuffer->SetBufferLayout
            ({
                     { ElementType::Float3, "a_position" },
                     { ElementType::Float4, "a_color" },
                     { ElementType::Float2, "a_texCoord" },
                     { ElementType::Float, "a_texIndex" }
             });

    s_pData->QuadVertexArray->AddVertexBuffer(s_pData->QuadVertexBuffer);

    s_pData->QuadVertexBufferBase = new QuadVertex[s_pData->MaxVertices];
    uint32_t* pQuadIndices = new uint32_t[s_pData->MaxIndices];

    uint32_t offset = 0;
    for (uint32_t i = 0; i < s_pData->MaxIndices; i += 6)
    {
        pQuadIndices[i + 0] = offset + 0;
        pQuadIndices[i + 1] = offset + 1;
        pQuadIndices[i + 2] = offset + 2;

        pQuadIndices[i + 3] = offset + 2;
        pQuadIndices[i + 4] = offset + 3;
        pQuadIndices[i + 5] = offset + 0;

        offset += 4;
    }

    std::shared_ptr<IndexBuffer> quadIB = IndexBuffer::Create(pQuadIndices, s_pData->MaxIndices);
    s_pData->QuadVertexArray->SetIndexBuffer(quadIB);

    s_pData->QuadVertexPositions[0] = { -0.5f, -0.5f, 0.f, 1.f };
    s_pData->QuadVertexPositions[1] = { 0.5f, -0.5f, 0.f, 1.f };
    s_pData->QuadVertexPositions[2] = { 0.5f, 0.5f, 0.f, 1.f };
    s_pData->QuadVertexPositions[3] = { -0.5f, 0.5f, 0.f, 1.f };

    delete[] pQuadIndices;
    //////////////

    /////Texture/////
    s_pData->WhiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_pData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    int* samplers { new int[5] };
    for (int i = 0; i < 5; ++i)
    {
        samplers[i] = i;
    }

    s_pData->QuadShader = Shader::Create("shaders/quad_vert.glsl", "shaders/quad_frag.glsl");
    s_pData->QuadShader->Bind();
    s_pData->QuadShader->UploadIntArray("u_textures", samplers, 5);

    s_pData->TextureSlots[0] = s_pData->WhiteTexture;
    /////////////////

    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
}

void Renderer::Shutdown()
{
    delete s_pData;
}

void Renderer::Begin(const OrthographicCamera &camera)
{
    s_pData->QuadShader->Bind();
    s_pData->QuadShader->UploadMat4("u_viewProjection", camera.GetViewProjectionMatrix());

    ResetBatchData();
}

void Renderer::End()
{
    uint32_t dataSize = (uint8_t*)s_pData->QuadVertexBufferPtr - (uint8_t*)s_pData->QuadVertexBufferBase;
    s_pData->QuadVertexBuffer->SetData(s_pData->QuadVertexBufferBase, dataSize);

    Flush();
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::StartNewBatch()
{
    End();
    ResetBatchData();
}

void Renderer::ResetBatchData()
{
    s_pData->QuadIndexCount = 0;
    s_pData->QuadVertexBufferPtr = s_pData->QuadVertexBufferBase;
    s_pData->TextureSlotIndex = 1;
}

void Renderer::Flush()
{
    //Bind textures
    for (uint32_t i = 0; i < s_pData->TextureSlotIndex; ++i)
    {
        s_pData->TextureSlots[i]->Bind();
    }

    s_pData->QuadVertexArray->Bind();
    glDrawElements(GL_TRIANGLES, s_pData->QuadIndexCount, GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawQuad(const glm::mat4 &tm, const glm::vec4 &color)
{
    if (s_pData->QuadIndexCount >= RendererStorage::MaxIndices)
    {
        StartNewBatch();
    }

    const float texIndex = 0.f; // white texture

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[0];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 0.f, 0.f };
    s_pData->QuadVertexBufferPtr->TexIndex = texIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[1];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 1.f, 0.f };
    s_pData->QuadVertexBufferPtr->TexIndex = texIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[2];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 1.f, 1.f };
    s_pData->QuadVertexBufferPtr->TexIndex = texIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[3];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 0.f, 1.f };
    s_pData->QuadVertexBufferPtr->TexIndex = texIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadIndexCount += 6;
}

void Renderer::DrawQuad(const glm::mat4 &tm, const std::shared_ptr<Texture2D> &texture, const glm::vec4 &color)
{
    if (s_pData->QuadIndexCount >= RendererStorage::MaxIndices)
    {
        StartNewBatch();
    }

    float textureIndex = 0.f;
    for (uint32_t i = 0; i < s_pData->TextureSlotIndex; ++i)
    {
        if (*s_pData->TextureSlots[i].get() == *texture.get())
        {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.f)
    {
        textureIndex = (float)s_pData->TextureSlotIndex;
        s_pData->TextureSlots[s_pData->TextureSlotIndex] = texture;
        s_pData->TextureSlotIndex++;
    }

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[0];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 0.f, 0.f };
    s_pData->QuadVertexBufferPtr->TexIndex = textureIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[1];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 1.f, 0.f };
    s_pData->QuadVertexBufferPtr->TexIndex = textureIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[2];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 1.f, 1.f };
    s_pData->QuadVertexBufferPtr->TexIndex = textureIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[3];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 0.f, 1.f };
    s_pData->QuadVertexBufferPtr->TexIndex = textureIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadIndexCount += 6;
}

void Renderer::DrawQuad(const glm::vec3 &pos, const glm::vec2 &scale, const glm::vec4 &color)
{
    if (s_pData->QuadIndexCount >= RendererStorage::MaxIndices)
    {
        StartNewBatch();
    }

    const float texIndex = 0.f; // white texture

    glm::mat4 tm = glm::translate(glm::mat4(1.f), pos)
            * glm::scale(glm::mat4(1.f), { scale.x, scale.y, 1.f });

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[0];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 0.f, 0.f };
    s_pData->QuadVertexBufferPtr->TexIndex = texIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[1];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 1.f, 0.f };
    s_pData->QuadVertexBufferPtr->TexIndex = texIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[2];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 1.f, 1.f };
    s_pData->QuadVertexBufferPtr->TexIndex = texIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[3];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 0.f, 1.f };
    s_pData->QuadVertexBufferPtr->TexIndex = texIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadIndexCount += 6;
}

void Renderer::DrawQuad(const glm::vec3 &pos, const std::shared_ptr<Texture2D> &texture, const glm::vec4 &color)
{
    if (s_pData->QuadIndexCount >= RendererStorage::MaxIndices)
    {
        StartNewBatch();
    }

    float textureIndex = 0.f;
    for (uint32_t i = 0; i < s_pData->TextureSlotIndex; ++i)
    {
        if (*s_pData->TextureSlots[i].get() == *texture.get())
        {
            textureIndex = (float)i;
            break;
        }
    }

    glm::mat4 tm = glm::translate(glm::mat4(1.f), pos);

    if (textureIndex == 0.f)
    {
        textureIndex = (float)s_pData->TextureSlotIndex;
        s_pData->TextureSlots[s_pData->TextureSlotIndex] = texture;
        s_pData->TextureSlotIndex++;
    }

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[0];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 0.f, 0.f };
    s_pData->QuadVertexBufferPtr->TexIndex = textureIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[1];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 1.f, 0.f };
    s_pData->QuadVertexBufferPtr->TexIndex = textureIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[2];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 1.f, 1.f };
    s_pData->QuadVertexBufferPtr->TexIndex = textureIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadVertexBufferPtr->Position = tm * s_pData->QuadVertexPositions[3];
    s_pData->QuadVertexBufferPtr->Color = color;
    s_pData->QuadVertexBufferPtr->TexCoord = { 0.f, 1.f };
    s_pData->QuadVertexBufferPtr->TexIndex = textureIndex;
    s_pData->QuadVertexBufferPtr++;

    s_pData->QuadIndexCount += 6;
}

void Renderer::Render()
{
    s_pData->QuadShader->Bind();
    s_pData->QuadVertexArray->Bind();

    glDrawElements(GL_TRIANGLES, s_pData->QuadVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT,nullptr);
}