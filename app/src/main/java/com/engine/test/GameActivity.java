package com.engine.test;

import android.content.res.AssetManager;
import android.os.Bundle;

import org.libsdl.app.SDLActivity;

public class GameActivity extends SDLActivity
{
    private static native void Load(AssetManager mgr);
    private static native void SetFilesFolder(String str);

    private AssetManager m_manager;
    private String m_fileDir;

    @Override
    protected void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);

        m_fileDir = getFilesDir().getAbsolutePath();
        SetFilesFolder(m_fileDir);

        m_manager = getResources().getAssets();
        Load(m_manager);
    }
}
