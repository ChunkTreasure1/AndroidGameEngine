//
// Created by Emilia on 2021-07-25.
//

#ifndef TESTPROJECT_VISUALSCRIPTINGEDITOR_H
#define TESTPROJECT_VISUALSCRIPTINGEDITOR_H

#include <VisualScripting/CodeGraph.h>
#include "../../Events/ApplicationEvent.h"

class VisualScriptingEditor
{
public:
    VisualScriptingEditor();
    ~VisualScriptingEditor();

    void OnEvent(Event& e);
    void OpenGraph(std::shared_ptr<CodeGraph>& graph);
    bool& GetIsOpen() { return m_isOpen; }

private:
    bool OnImGuiUpdate(ImGuiUpdateEvent& e);
    bool OnUpdate(AppUpdateEvent& e);

    void UpdateNodeWindow();
    void UpdateToolsWindow();

    //Pop-ups
    void UpdateCreateVariable();

    void RemoveNode(uint32_t id);
    void RemoveLink(uint32_t id);

    void DrawNode(std::shared_ptr<Node>& node);
    void DrawInput(InputAttribute& attr, std::shared_ptr<Node>& node, bool isProperties = false);
    void DrawOutput(OutputAttribute& attr, std::shared_ptr<Node>& node, bool isProperties = false);

private:
    bool m_isOpen;
    std::shared_ptr<CodeGraph> m_currentlyOpenGraph;
    std::shared_ptr<Variable> m_variableToCreate = nullptr;
};



#endif //TESTPROJECT_VISUALSCRIPTINGEDITOR_H
