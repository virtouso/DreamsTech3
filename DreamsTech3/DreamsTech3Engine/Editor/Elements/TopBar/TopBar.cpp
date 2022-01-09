
#include "TopBar.h"
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"

void ShowFileBar();
void ShowSettings();
void ShowGameObjects();
void ShowComponents();


void TopBar::Show() {

    if (ImGui::BeginMainMenuBar())
    {
        
        ShowFileBar();
        
        ShowSettings();
        ShowGameObjects();
        ShowComponents();

        ImGui::EndMainMenuBar();
    }

}


void ShowFileBar() {
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New"))
        {
        }

        if (ImGui::MenuItem("Open"))
        {
            //Do something
        }
        if (ImGui::MenuItem("Save"))
        {
            //Do something
        }

        if (ImGui::MenuItem("Exit"))
        {
            exit(1);
        }

        ImGui::EndMenu();
    }
}
void ShowSettings()
{
    if (ImGui::BeginMenu("Settings"))
    {
        
        if (ImGui::MenuItem("General"))
        {
        }
        if (ImGui::MenuItem("Physics"))
        {
        }

        ImGui::EndMenu();
    }
}

void ShowGameObjects()
{
    if (ImGui::BeginMenu("Create"))
    {

        if (ImGui::MenuItem("Square"))
        {
        }
        if (ImGui::MenuItem("Circle"))
        {
        }
        if (ImGui::MenuItem("Triangle"))
        {
        }
        ImGui::EndMenu();
    }
}


void ShowComponents(){
    if (ImGui::BeginMenu("Components"))
    {

        if (ImGui::MenuItem("RigidBody"))
        {
        }
        if (ImGui::MenuItem("Collider"))
        {
        }
      

        if (ImGui::MenuItem("Audio Source"))
        {

        }
        if (ImGui::MenuItem("Particle"))
        {

        }
        if (ImGui::MenuItem("Trailer Renderer"))
        {

        }

        if (ImGui::MenuItem("Custom Script"))
        {
        }

        ImGui::EndMenu();
    }
}
