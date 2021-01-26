#include "start_menu.h"

#include <third_party/pitch_imgui/imgui.h>
#include <third_party/pitch_imgui/imgui_impl_glfw.h>
#include <third_party/pitch_imgui/imgui_impl_opengl3.h>

bool StartMenu::initialized = false;

StartMenu::StartMenu(Window& renderWindow)
#if DEBUG
    : ipAddress_("127.0.0.1")
    , portNumber_("49152")
    ,
#else
    :
#endif
      submitted_(false)
    , inMainMenu_(true)
    , inJoinMenu_(false)
    , inHostMenu_(false)
{
#if RELEASE
    memset(ipAddress_, 0, 16);
    memset(portNumber_, 0, 16);
#endif

    if(!initialized)
    {
        initImgui(renderWindow);
    }
}

void StartMenu::show()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if(inMainMenu_)
    {
        drawMainMenu();
    }

    if(inJoinMenu_)
    {
        drawJoinMenu();
    }

    if(inHostMenu_)
    {
        drawHostMenu();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool StartMenu::userHasSubmitted() const noexcept
{
    return submitted_;
}

std::string StartMenu::ipAddress() const noexcept
{
    return ipAddress_;
}

std::string StartMenu::portNumber() const noexcept
{
    return portNumber_;
}

void StartMenu::drawMainMenu()
{
    ImGui::Begin("Main Menu");

    if(ImGui::Button("Join Game"))
    {
        inMainMenu_ = false;
        inJoinMenu_ = true;
    }

    if(ImGui::Button("Host Game"))
    {
        inMainMenu_ = false;
        inHostMenu_ = true;
    }

    ImGui::End();
}

void StartMenu::drawJoinMenu()
{
    ImGui::Begin("Join Menu");
    ImGui::InputText("Ip Address:", ipAddress_, inputBufferSize);
    ImGui::InputText("Port Number", portNumber_, inputBufferSize);

    if(ImGui::Button("Submit"))
    {
        inJoinMenu_ = false;
        submitted_ = true;
    }

    if(ImGui::Button("Back"))
    {
        inJoinMenu_ = false;
        inMainMenu_ = true;
    }

    ImGui::End();
}

void StartMenu::drawHostMenu()
{
    ImGui::Begin("Host Menu");
    ImGui::Text("This option is not yet supported");

    if(ImGui::Button("Back"))
    {
        inHostMenu_ = false;
        inMainMenu_ = true;
    }

    ImGui::End();
}

//This should probably eventually be
//moved into another class like an
//ImGuiContext class
void StartMenu::initImgui(Window& renderWindow)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(renderWindow.glfwWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();

    initialized = true;
}
