#ifndef START_MENU_H
#define START_MENU_H

#include <string>

#include <graphics/window.h>

class StartMenu
{
public:
    StartMenu(Window& renderWindow); //<Note: Once the ImguiContext is factored out the window won't be necessary here

    void show();

    bool userHasSubmitted() const noexcept;

    std::string ipAddress() const noexcept;
    std::string portNumber() const noexcept;

private:
    void drawMainMenu();
    void drawJoinMenu();
    void drawHostMenu();

private:
    static void initImgui(Window& renderWindow);
    static bool initialized;
    static constexpr auto inputBufferSize = 16;

private:
    char ipAddress_[inputBufferSize];
    char portNumber_[inputBufferSize];
    bool submitted_;
    bool inMainMenu_;
    bool inJoinMenu_;
    bool inHostMenu_;
};

#endif //START_MENU_H
