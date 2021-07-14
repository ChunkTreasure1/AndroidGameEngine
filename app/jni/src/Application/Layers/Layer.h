//
// Created by xXRag on 2021-07-05.
//

#ifndef TESTPROJECT_LAYER_H
#define TESTPROJECT_LAYER_H

#include <Application/Events/Event.h>
#include <Application/Timestep.h>
#include <Rendering/Renderer.h>

#include <Application/Events/ApplicationEvent.h>

class Layer
{
public:
    virtual ~Layer() {}

    virtual void OnAttach() {}
    virtual void OnDetach() {}

    virtual void OnEvent(Event& e) {}
    virtual void OnImGuiRender(Timestep ts) {}
};


#endif //TESTPROJECT_LAYER_H
