#include <iostream>
#include "Core/Window.h"
#include "Graphics/Renderer.h"
#include "Core/Input.h"
#include "Editor/Editor.h"
#include "Editor/Layout.h" // Include Layout

int main(int argc, char* argv[]) {
    Core::Window window("Larry - Decision Tree Editor", 1280, 720);
    if (!window.Initialize()) {
        return 1;
    }

    Graphics::Renderer renderer(window.GetRenderer());
    Editor::Editor editor;
    Editor::Layout layout(&editor, 1280, 720, window.GetNativeWindow()); // Initialize Layout

    bool quit = false;
    while (!quit) {
        // 1. Update Input Internal State (Snapshot previous frame)
        Core::Input::Update();

        // 2. Process System Events (Updates current state in SDL internals)
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            } else if (e.type == SDL_EVENT_TEXT_INPUT) {
                layout.ProcessTextInput(e.text.text);
            }
            Core::Input::ProcessEvent(e);
        }


        bool uiHandled = layout.Update(0.016f); 
        editor.Update(0.016f, uiHandled); // Keep editor updating but respect UI

        // 4. Render
        window.Clear(30, 30, 30, 255); // Dark background
        
        layout.Draw(renderer); // Layout draws Editor + UI

        window.Present();
    }

    return 0;
}