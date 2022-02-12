#ifndef UIUtility
#define UIUtility

#include <imgui.h>
#include <imgui_internal.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

namespace UI
{
    static uint32_t s_contextId = 0;
    static uint32_t s_stackId = 0;

    class ScopedColor
    {
    public:
        ScopedColor(ImGuiCol_ color, const glm::vec4& newColor)
                : m_color(color)
        {
            auto& colors = ImGui::GetStyle().Colors;
            m_oldColor = colors[color];
            colors[color] = ImVec4{ newColor.x, newColor.y, newColor.z, newColor.w };
        }

        ~ScopedColor()
        {
            auto& colors = ImGui::GetStyle().Colors;
            colors[m_color] = m_oldColor;
        }

    private:
        ImVec4 m_oldColor;
        ImGuiCol_ m_color;
    };


    class ScopedStyleFloat
    {
    public:
        ScopedStyleFloat(ImGuiStyleVar_ var, float value)
        {
            ImGui::PushStyleVar(var, value);
        }

        ~ScopedStyleFloat()
        {
            ImGui::PopStyleVar();
        }
    };

    class ScopedStyleFloat2
    {
    public:
        ScopedStyleFloat2(ImGuiStyleVar_ var, const glm::vec2& value)
        {
            ImGui::PushStyleVar(var, { value.x, value.y });
        }

        ~ScopedStyleFloat2()
        {
            ImGui::PopStyleVar();
        }
    };

    static void PushId()
    {
        int id = s_contextId++;
        ImGui::PushID(id);
        s_stackId = 0;
    }

    static void PopId()
    {
        ImGui::PopID();
        s_contextId--;
    }

    static bool BeginProperties(const std::string& name = "", bool pushId = true)
    {
        if (pushId)
        {
            PushId();
        }

        return ImGui::BeginTable(name.c_str(), 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_Resizable);
    }

    static void EndProperties(bool popId = true)
    {
        ImGui::EndTable();
        if (popId)
        {
            PopId();
        }
    }

    static bool PropertyAxisColor(const std::string& text, glm::vec2& value, float resetValue = 0.f)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.f, 0.f });

        const ImVec2 buttonSize = { 22.f, 22.f };

        bool changed = false;

        {
            ScopedColor color{ ImGuiCol_Button, { 0.8f, 0.1f, 0.15f, 1.f } };
            ScopedColor colorh{ ImGuiCol_ButtonHovered, { 0.9f, 0.2f, 0.2f, 1.f } };
            ScopedColor colora{ ImGuiCol_ButtonActive, { 0.8f, 0.1f, 0.15f, 1.f } };

            std::string buttonId = "X##" + std::to_string(s_stackId++);
            if (ImGui::Button(buttonId.c_str(), buttonSize))
            {
                changed = true;
                value.x = resetValue;
            }

            ImGui::SameLine();

            std::string id = "##" + std::to_string(s_stackId++);
            if (ImGui::DragFloat(id.c_str(), &value.x, 0.1f))
            {
                changed = true;
            }
        }

        ImGui::PopItemWidth();
        ImGui::SameLine();

        {
            ScopedColor color{ ImGuiCol_Button, { 0.2f, 0.7f, 0.2f, 1.f } };
            ScopedColor colorh{ ImGuiCol_ButtonHovered, { 0.3f, 0.8f, 0.3f, 1.f } };
            ScopedColor colora{ ImGuiCol_ButtonActive, { 0.2f, 0.7f, 0.2f, 1.f } };

            std::string buttonId = "Y##" + std::to_string(s_stackId++);
            if (ImGui::Button(buttonId.c_str(), buttonSize))
            {
                changed = true;
                value.y = resetValue;
            }

            ImGui::SameLine();

            std::string id = "##" + std::to_string(s_stackId++);
            if (ImGui::DragFloat(id.c_str(), &value.y, 0.1f))
            {
                changed = true;
            }
        }

        ImGui::PopItemWidth();
        ImGui::PopStyleVar();

        return changed;
    }

    static bool Property(const std::string& text, bool& value)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(ImGui::GetColumnWidth());

        bool changed = false;

        const std::string id = "##" + std::to_string(s_stackId++);
        if (ImGui::Checkbox(id.c_str(), &value))
        {
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    static bool Property(const std::string& text, int32_t& value)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(ImGui::GetColumnWidth());

        bool changed = false;

        const std::string id = "##" + std::to_string(s_stackId);
        const int min = 0;

        if (ImGui::DragScalar(id.c_str(), ImGuiDataType_S32, &value, 1.f, &min))
        {
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    static bool Property(const std::string& text, uint32_t& value)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(ImGui::GetColumnWidth());

        bool changed = false;

        const std::string id = "##" + std::to_string(s_stackId);
        const int min = 0;

        if (ImGui::DragScalar(id.c_str(), ImGuiDataType_U32, &value, 1.f, &min))
        {
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    static bool Property(const std::string& text, float& value)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(ImGui::GetColumnWidth());

        bool changed = false;

        std::string id = "##" + std::to_string(s_stackId);
        if (ImGui::DragFloat(id.c_str(), &value))
        {
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    static bool Property(const std::string& text, glm::vec2& value)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(ImGui::GetColumnWidth());

        bool changed = false;

        const std::string id = "##" + std::to_string(s_stackId);
        if (ImGui::DragFloat2(id.c_str(), glm::value_ptr(value)))
        {
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    static bool Property(const std::string& text, glm::vec3& value)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(ImGui::GetColumnWidth());

        bool changed = false;

        std::string id = "##" + std::to_string(s_stackId);
        if (ImGui::DragFloat3(id.c_str(), glm::value_ptr(value)))
        {
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    static bool Property(const std::string& text, glm::vec4& value)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(ImGui::GetColumnWidth());

        bool changed = false;

        const std::string id = "##" + std::to_string(s_stackId);
        if (ImGui::DragFloat4(id.c_str(), glm::value_ptr(value)))
        {
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    static bool PropertyColor(const std::string& text, glm::vec3& value)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(ImGui::GetColumnWidth());

        bool changed = false;

        const std::string id = "##" + std::to_string(s_stackId);
        if (ImGui::ColorEdit3(id.c_str(), glm::value_ptr(value)))
        {
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    static bool PropertyColor(const std::string& text, glm::vec4& value)
    {
        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();
        ImGui::PushItemWidth(ImGui::GetColumnWidth());

        bool changed = false;

        const std::string id = "##" + std::to_string(s_stackId);
        if (ImGui::ColorEdit4(id.c_str(), glm::value_ptr(value)))
        {
            changed = true;
        }

        ImGui::PopItemWidth();

        return changed;
    }

    static bool Combo(const std::string& text, int& currentItem, const std::vector<const char*>& items)
    {
        bool changed = false;

        ImGui::TableNextColumn();
        ImGui::Text("%s", text.c_str());

        ImGui::TableNextColumn();

        ImGui::PushItemWidth(ImGui::GetColumnWidth());
        const std::string id = "##" + std::to_string(s_stackId++);
        if (ImGui::Combo(id.c_str(), &currentItem, items.data(), items.size()))
        {
            changed = true;
        }

        ImGui::PopItemWidth();
        return changed;
    }

    static void* DragDropTarget(const std::string& type)
    {
        void* data = nullptr;

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(type.c_str()))
            {
                data = payload->Data;
            }

            ImGui::EndDragDropTarget();
        }

        return data;
    }

    static void* DragDropTarget(std::initializer_list<std::string> types)
    {
        void* data = nullptr;

        if (ImGui::BeginDragDropTarget())
        {
            for (const auto& type : types)
            {
                if (const ImGuiPayload* pPayload = ImGui::AcceptDragDropPayload(type.c_str()))
                {
                    data = pPayload->Data;
                    break;
                }
            }

            ImGui::EndDragDropTarget();
        }

        return data;
    }
}

#endif