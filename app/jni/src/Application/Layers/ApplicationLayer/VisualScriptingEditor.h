//
// Created by Emilia on 2021-07-25.
//

#ifndef TESTPROJECT_VISUALSCRIPTINGEDITOR_H
#define TESTPROJECT_VISUALSCRIPTINGEDITOR_H



class VisualScriptingEditor
{
public:
    VisualScriptingEditor();
    ~VisualScriptingEditor();

    void OnEvent(Event& e);

private:
    bool OnImGuiUpdate(ImGuiUpdateEvent& e);
    bool OnUpdate(AppUpdateEvent& e);

private:
    bool m_isOpen;
};



#endif //TESTPROJECT_VISUALSCRIPTINGEDITOR_H
