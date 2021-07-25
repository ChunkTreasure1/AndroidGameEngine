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

private:
    bool OnImGuiUpdate(ImGuiUpdateEvent& e);
    bool OnUpdate(AppUpdateEvent& e);

    void UpdateNodeWindow();

private:
    bool m_isOpen;
    std::shared_ptr<CodeGraph> m_currentlyOpenGraph;
};



#endif //TESTPROJECT_VISUALSCRIPTINGEDITOR_H
