//
// Created by apgra on 10/1/2024.
//

#ifndef GLE_ASSETBROWSERWINDOW_H
#define GLE_ASSETBROWSERWINDOW_H

#include "EditorWindow.h"


namespace GLE {
    class AssetBrowserWindow : public EditorWindow
    {
    public:
        AssetBrowserWindow();
        ~AssetBrowserWindow() override;

        void ImGuiRender() override;
    };
}


#endif //GLE_ASSETBROWSERWINDOW_H
