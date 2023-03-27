#pragma once
#include "Window.h"
namespace UIFW {
    class ExternalWindow : public Window
    {

    protected:

        void UpdateRECT();

    public:

        //constructors / initiallizers
        ExternalWindow(const wstring& name);
        ExternalWindow(wstring&& name);
        bool Init(const wstring& name);
        bool Init(wstring&& name);

        //info retrivers
        POINT GetMousePos();
        bool Exists();
        RECT GetRECT() override;

        //manipulators
        void Reposition(int x, int y) override;
        void Move(int DX, int DY) override;
        void Resize(int width, int height) override;
        void Destroy() override;

    };

}