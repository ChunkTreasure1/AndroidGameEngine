//
// Created by xXRag on 2021-06-21.
//

#include <jni.h>
#include <string.h>
#include <android_native_app_glue.h>
#include "Application.h"

extern "C"
{
    void handle_cmd(android_app *pApp, int32_t cmd)
    {
        switch (cmd)
        {
            case APP_CMD_INIT_WINDOW:
                break;

            case APP_CMD_TERM_WINDOW:
                break;
        }
    }

    void android_main(struct android_app *pApp){
        Application app(pApp);

        if (app.Initialize())
        {
            app.Run();
        }
    }
}