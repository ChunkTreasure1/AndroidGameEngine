package com.engine.test;

import android.content.res.AssetManager;
import android.os.Bundle;

import org.libsdl.app.SDLActivity;

public class GameActivity extends SDLActivity
{
    private static native void Load(AssetManager mgr);
    private AssetManager m_manager;

    @Override
    protected void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);

        m_manager = getResources().getAssets();
        Load(m_manager);
    }
}
