#include "Snake-Game/MenuManager.h"

MenuManager::MenuManager() {
    initializeMenu();
    
    modesName.push_back("Start Game");
    modesName.push_back("Settings");
    modesName.push_back("Edit Map");
    modesName.push_back("Exit");
}

void MenuManager::initializeMenu() {
    getmaxyx(stdscr, maxHeight, maxWidth);
}

void MenuManager::showMenu() {

    if (MENU_WINDOW_HEIGHT > maxHeight || MENU_WINDOW_WIDTH > maxWidth) {

        move((maxHeight-2)/2,(maxWidth-5)/2);
        printw("Window size should be bigger than %d X %d", MENU_WINDOW_HEIGHT, MENU_WINDOW_WIDTH);
        endwin();
        exit(1);
    }

    refresh();

    int offsety = (maxHeight - MENU_WINDOW_HEIGHT) / 2;
    int offsetx = (maxWidth - MENU_WINDOW_WIDTH) / 2;
    menuWindow = newwin(MENU_WINDOW_HEIGHT, MENU_WINDOW_WIDTH, offsety, offsetx);

    wborder(menuWindow, '|', '|', '-', '-', '+', '+', '+', '+');

    int c, highlight = 0;
    
    printMenu(highlight);

    while(1) {
        c = getch();
        switch(c) {       
            case KEY_UP:
                if(highlight == 0)
                    highlight = modesName.size() - 1;
                else
                    --highlight;
                break;                                                                                  
            case KEY_DOWN:                                                                                  
                if(highlight == modesName.size() - 1)                                                              
                    highlight = 0;                                                               
                else                                                                                   
                    ++highlight;                                                                    
                break;                                                                                  
            case '\n':                                                                                 
                startMode(highlight);   
                return;                                                  
                break;                                                                                  
            default:
                return;                                                                                
        }
        printMenu(highlight);           
    }
}
void MenuManager::printMenu(int needTobeHighligted) {
    refresh();
    for(int i=0; i< modesName.size(); i++) {

        if(i == needTobeHighligted) {
            wattron(menuWindow, A_REVERSE);
            mvwprintw(menuWindow, i+2, 1, "> %s", modesName[i].c_str());
            wattroff(menuWindow, A_REVERSE);
        } else {
            mvwprintw(menuWindow, i+2, 1, "  %s", modesName[i].c_str());
        }
    }
    wrefresh(menuWindow);
}

void MenuManager::startMode(int mode) {
    switch (mode)
    {
        case MODE_START_GAME:
            destroyMenu();
            GlobalStateManager().startGame();
            endwin();
            break;
        case MODE_SETTING:
            break;
        case MODE_EDIT_MAP:
            break;
        case MODE_EXIT:
            delwin(menuWindow);
            endwin();
            exit(1);
            break;
        
        default:
            break;
    }
}

void MenuManager::destroyMenu() {
    wclear(menuWindow);
    wrefresh(menuWindow);
    delwin(menuWindow);
}