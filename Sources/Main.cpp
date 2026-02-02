/**
 * Main.cpp
 * Application entry point and main game loop
 * 
 * Initializes the window, renderer, editor, and layout, then runs the
 * main update/render loop until the user closes the application.
 */

#include <iostream>
#include "Core/Window.h"
#include "Graphics/Renderer.h"
#include "Core/Input.h"
#include "Editor/Editor.h"
#include "Editor/Layout.h"

int main(int argc, char* argv[]) {
    // Initialize window and  graphics
    Core::Window window("Larry - Decision Tree Editor", 1280, 720);
    if (!window.Initialize()) {
        return 1;
    }

    // Create renderer wrapper
    Graphics::Renderer renderer(window.GetRenderer());
    
    // Create editor and layout (UI + Editor composition)
    Editor::Editor editor;
    Editor::Layout layout(&editor, 1280, 720, window.GetNativeWindow());

    // Main game loop
    bool quit = false;
    while (!quit) {
        // PHASE 1: Input - Capture previous frame state before processing events
        Core::Input::Update();

        // PHASE 2: Event Processing - Process SDL events and update current state
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            } else if (e.type == SDL_EVENT_TEXT_INPUT) {
                // Forward text input to layout for text editing widgets
                layout.ProcessTextInput(e.text.text);
            }
            Core::Input::ProcessEvent(e);
        }

        // PHASE 3: Update - Update UI and editor logic
        // UI gets priority; if it captures input, editor won't process it
        bool uiHandled = layout.Update(0.016f); 
        editor.Update(0.016f, uiHandled);

        // PHASE 4: Render - Clear, draw, and present
        window.Clear(30, 30, 30, 255); // Dark gray background
        
        layout.Draw(renderer); // Layout draws both editor and UI

        window.Present();
    }

    return 0;
}