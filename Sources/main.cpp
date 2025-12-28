#include <SDL3/SDL.h>
#include <iostream>

#include "DecisionTree.h"
#include "Graphics.h"

using namespace std;

int main(int argc, char* argv[]){
    DecisionTree tree;
    tree.BuildTree();

    Graphics graphics;
    if (!graphics.init("Decision Tree Editor - SDL3", 800, 600)){
        return -1;
    }

    Node* current = tree.getRoot();
    bool running = true;

    while (running && current){
        if (current->isleaf){
            cout << "Decision Finale : " << current->decision << endl;
            SDL_Delay(3000);
            break;
        }
        
        cout << current->question << endl;
        cout <<"Y = Oui | N = Non" << endl;

        SDL_Event event;
        while (SDL_WaitEvent(&event)){

            if (event.type == SDL_EVENT_QUIT){
                running = false;
                break;
            }

            if (event.type == SDL_EVENT_KEY_DOWN){
                if (event.key.keysym.sym == SDLK_y){
                    current = tree.next(current, true);
                    break;
                }
                if (event.key.keysym.sym == SDLK_n){
                    current = tree.next(current, false);
                    break;
                }
            }
        }
    }

    graphics.Quit();
    return 0;
}