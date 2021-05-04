#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

char charnothing = ' ';
char charset = 'O';
char charset1 = '0';
const int howmanyrools = 10;
int mode = 10;
int choosenstuff = 0;
int cursorplace[2] = { 240, 240 };
int born[howmanyrools];
int stay[howmanyrools];
int neighbormodif[24];
int qoflife = 16800;
int mapsize[2] = { 480, 280 };
int screensize[2] = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
int consolesize[2] = { 0, 0 };
HANDLE h = NULL;
COORD zerocords = { 0, 0 };
CONSOLE_CURSOR_INFO cursorinfo;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
string* map;
string* secondmap;

int howmanyneighbors(int xc, int yc)
{
    int neighbors = 0;
    int times = 0;
    for (int x = -2; x <= 2; x++)
        for (int y = -2; y <= 2; y++)
            if (!(x == 0 && y == 0))
            {
                if ((xc + x >= 0 && xc + x < mapsize[1] && yc + y >= 0 && yc + y < mapsize[0]))
                    if (map[xc + x][yc + y] != charnothing) neighbors += neighbormodif[times];
                times++;
            }
    return neighbors;
}

void clear()
{
    if (true)
    {
        SetConsoleCursorPosition(h, zerocords);
        SetConsoleCursorInfo(h, &cursorinfo);
    }
    for (int i = 0; i < consolesize[1]; i++)
        for (int u = 0; u < consolesize[0]; u++)
            if (u < consolesize[0] - 7)
            {
                cout << "      ";
                u += 4;
            }
            else
                cout << " ";
}

int main()
{
    srand(time(NULL));
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);   
    GetConsoleCursorInfo(h, &cursorinfo);
    cursorinfo.bVisible = false;

    for (int i = 0; i < howmanyrools; i++)
    {
        born[i] = -1;
        stay[i] = -1;
    }

    born[0] = 3;

    stay[0] = 2;
    stay[1] = 3;

    for (int i = 0; i < 24; i++)
        neighbormodif[i] = 0;

    neighbormodif[6] = 1;
    neighbormodif[7] = 1;
    neighbormodif[8] = 1;
    neighbormodif[11] = 1;
    neighbormodif[12] = 1;
    neighbormodif[15] = 1;
    neighbormodif[16] = 1;
    neighbormodif[17] = 1;

    /*
     0  1  2  3  4
     5  6  7  8  9
    10 11  X 12 13
    14 15 16 17 18
    19 20 21 22 23
    */

    map = new string[mapsize[1]];
    secondmap = new string[mapsize[1]];
    for (int i = 0; i < mapsize[1]; i++)
    {
        for (int u = 0; u < mapsize[0]; u++)
        {
            map[i] += charnothing;
        }
    }

    if (false)
        for (int i = 0; i < qoflife; i++)
        {
            int cordx = rand() % mapsize[0];
            int cordy = rand() % mapsize[1];
            map[cordy][cordx] = charset;
        }
    while (false) for (int i = 0; i < 255; i++) if (GetAsyncKeyState(i)) cout << i << endl;
    clock_t timer;
    timer = clock();
    float cdlife = 0;
    float cdcontrol = 0;
    float cdmenu = 0;
    float firsttime = 200;
    float secondtime = 200;
    float thirdtime = 200;
    int choosen = 0;
    bool somethinghappens = true;
    bool stopit = false;
    bool choosed = false;
    bool pause = false;
    string mainstuff[6];
    mainstuff[0] = "Resume";
    mainstuff[1] = "Random generation";
    mainstuff[2] = "Clear map";
    mainstuff[3] = "Settings";
    mainstuff[4] = "Author";
    mainstuff[5] = "Quit";
    while (!stopit)
    {
        GetConsoleScreenBufferInfo(h, &consoleInfo);
        if (consolesize[0] != consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1)
            somethinghappens = true;
        if (consolesize[1] != consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top)
            somethinghappens = true;
        consolesize[0] = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
        consolesize[1] = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top;
        if (mode == 0)
        {
            float timesgone = clock() - timer;
            if (cdlife < firsttime) cdlife += timesgone;
            if (cdcontrol < secondtime) cdcontrol += timesgone;
            timer = clock();
            for (int i = 0; i < mapsize[1]; i++)
                secondmap[i] = map[i];
            if (cdcontrol >= secondtime)
            {
                cdcontrol = 0;
                if (GetAsyncKeyState(27))
                    mode = 1; 
                if (GetAsyncKeyState(32))
                    pause = !pause;
                if (GetAsyncKeyState(81)) {
                    secondmap[cursorplace[1]][cursorplace[0]] = charnothing; somethinghappens = true;
                }
                if (GetAsyncKeyState(69)) {
                    secondmap[cursorplace[1]][cursorplace[0]] = charset; somethinghappens = true;
                }
                if (GetAsyncKeyState(87) && cursorplace[1] > 0) {
                    cursorplace[1]--; somethinghappens = true;
                }
                if (GetAsyncKeyState(83) && cursorplace[1] < mapsize[1] - 1) {
                    cursorplace[1]++; somethinghappens = true;
                }
                if (GetAsyncKeyState(65) && cursorplace[0] > 0) {
                    cursorplace[0]--; somethinghappens = true;
                }
                if (GetAsyncKeyState(68) && cursorplace[0] < mapsize[0] - 1) {
                    cursorplace[0]++; somethinghappens = true;
                }
                if (GetAsyncKeyState(16) && GetAsyncKeyState(87) && cursorplace[1] > 10) {
                    cursorplace[1] -= 10; somethinghappens = true;
                }
                if (GetAsyncKeyState(16) && GetAsyncKeyState(83) && cursorplace[1] < mapsize[1] - 11) {
                    cursorplace[1] += 10; somethinghappens = true;
                }
                if (GetAsyncKeyState(16) && GetAsyncKeyState(65) && cursorplace[0] > 10) {
                    cursorplace[0] -= 10; somethinghappens = true;
                }
                if (GetAsyncKeyState(16) && GetAsyncKeyState(68) && cursorplace[0] < mapsize[0] - 11) {
                    cursorplace[0] += 10; somethinghappens = true;
                }
            }
            if (cdlife >= firsttime)
            {
                if (!pause)
                {
                    cdlife = 0;
                    for (int i = 0; i < mapsize[1]; i++)
                        for (int u = 0; u < mapsize[0]; u++)
                        {
                            bool da = false;
                            int neighbors = howmanyneighbors(i, u);
                            if (map[i][u] == charset)
                            {
                                for (int h = 0; h < howmanyrools; h++)
                                    if (neighbors == stay[h])
                                        da = true;

                                if (!da)
                                {
                                    secondmap[i][u] = charnothing; somethinghappens = true;
                                }
                            }
                            else
                            {
                                if (map[i][u] == charset1)
                                {
                                    for (int h = 0; h < howmanyrools; h++)
                                        if (neighbors == stay[h])
                                            da = true;

                                    if (!da)
                                    {
                                        secondmap[i][u] = charnothing; somethinghappens = true;
                                    }
                                }
                                else
                                {
                                    for (int h = 0; h < howmanyrools; h++)
                                        if (neighbors == born[h])
                                            da = true;
                                    if (da)
                                    {
                                        if ((i + u) % 2 == 0)
                                        {
                                            secondmap[i][u] = charset1; somethinghappens = true;
                                        }
                                        else
                                        {
                                            secondmap[i][u] = charset; somethinghappens = true;
                                        }
                                    }
                                }
                            }
                        }
                }
            }
            for (int i = 0; i < mapsize[1]; i++)
                map[i] = secondmap[i];
            if (somethinghappens)
                {
                    somethinghappens = false;
                    if (true)
                    {
                        SetConsoleCursorPosition(h, zerocords);
                        SetConsoleCursorInfo(h, &cursorinfo);
                    }
                    if (true)
                    {
                        string* viewmap;
                        viewmap = new string[consolesize[1] - 1];
                        int center[2];

                        center[0] = cursorplace[0];
                        center[1] = cursorplace[1];
                        if (cursorplace[0] < (consolesize[0]) / 2)
                            center[0] = (consolesize[0]) / 2;
                        else
                            if (cursorplace[0] > mapsize[0] - ((consolesize[0]) / 2))
                                center[0] = mapsize[0] - (consolesize[0]) / 2;

                        if (cursorplace[1] < (consolesize[1]) / 2)
                            center[1] = (consolesize[1]) / 2;
                        else
                            if (cursorplace[1] > mapsize[1] - ((consolesize[1]) / 2))
                                center[1] = mapsize[1] - (consolesize[1]) / 2;

                        int needit[2] = { center[0] - (consolesize[0]) / 2, center[1] - (consolesize[1]) / 2 };

                        for (int i = needit[1]; i < needit[1] + consolesize[1] - 1; i++)
                            for (int u = needit[0]; u < needit[0] + consolesize[0]; u++)
                            {
                                viewmap[i - needit[1]] = viewmap[i - needit[1]] + map[i][u];
                            }
                        for (int i = 0; i < consolesize[1] - 1; i++)
                        {
                            cout << viewmap[i];
                        }
                    }
                    if (true)
                    {
                        COORD curscords;
                        if (cursorplace[0] > int(consolesize[0] / 2))
                            if (cursorplace[0] < mapsize[0] - (consolesize[0]) / 2)
                                curscords.X = int(consolesize[0] / 2);
                            else
                                curscords.X = cursorplace[0] - (mapsize[0] - (consolesize[0]) / 2) + (consolesize[0]) / 2;
                        else
                            curscords.X = cursorplace[0];

                        if (cursorplace[1] > int(consolesize[1] / 2))
                            if (cursorplace[1] < mapsize[1] - (consolesize[1]) / 2)
                                curscords.Y = int(consolesize[1] / 2);
                            else
                                curscords.Y = cursorplace[1] - (mapsize[1] - (consolesize[1]) / 2) + (consolesize[1]) / 2;
                        else
                            curscords.Y = cursorplace[01];

                        SetConsoleCursorPosition(h, curscords);
                        cout << "X";
                        SetConsoleCursorInfo(h, &cursorinfo);
                    }
                }
            if (mode == 1)
            {
                clear();
                somethinghappens = true;
                cdmenu = thirdtime + 1;
            }
        }
        if (mode == 1)
        {
            float timesgone = clock() - timer;
            if (cdmenu <= thirdtime) cdmenu += timesgone;
            timer = clock();
            if (somethinghappens == true && mode == 1)
            {
                somethinghappens = false;
                if (true)
                {
                    SetConsoleCursorPosition(h, zerocords);
                    SetConsoleCursorInfo(h, &cursorinfo);
                }
                for (int i = 0; i < 6; i++)
                {
                    if (choosen == i)
                        cout << mainstuff[i] << "<<<" << endl;
                    else
                        cout << mainstuff[i] << "   " << endl;
                }
            }
            if (cdmenu >= thirdtime && mode == 1)
            {
                cdmenu = 0;
                if (GetAsyncKeyState(32)) {
                    if (choosen == 0)
                    {
                        mode = 0; somethinghappens = true;
                    }
                    if (choosen == 1)
                    {
                        mode = 2; somethinghappens = true;
                        clear();
                    }
                    if (choosen == 2)
                    {
                        mode = 3; somethinghappens = true;
                        clear();
                    }
                    if (choosen == 3)
                    {
                        mode = 4; somethinghappens = true;
                        clear();
                    }
                    if (choosen == 4)
                    {
                        mode = 5; somethinghappens = true;
                    }
                    if (choosen == 5)
                    {
                        stopit = true;
                    }
                }
                if (GetAsyncKeyState(27)) {
                    mode = 0; somethinghappens = true;
                }
                if (GetAsyncKeyState(87) && choosen > 0) {
                    choosen--; somethinghappens = true;
                }
                if (GetAsyncKeyState(83) && choosen < 5) {
                    choosen++; somethinghappens = true;
                }
            }      
        }
        if (mode == 2)
        {
            mode = 1;
            for (int u = 0; u < mapsize[1]; u++)
            {
                map[u] = "";
            }
            for (int i = 0; i < mapsize[1]; i++)
            {
                for (int u = 0; u < mapsize[0]; u++)
                {
                    map[i] += charnothing;
                }
            }
            for (int i = 0; i < qoflife; i++)
            {
                int cordx = rand() % mapsize[0];
                int cordy = rand() % mapsize[1];
                map[cordy][cordx] = charset;
            }
            for (int i = 0; i < mapsize[1]; i++)
                secondmap[i] = map[i];
        }
        if (mode == 3)
        {
            mode = 1;
            for (int u = 0; u < mapsize[1]; u++)
            {
                map[u] = "";
            }
            for (int i = 0; i < mapsize[1]; i++)
            {
                for (int u = 0; u < mapsize[0]; u++)
                {
                    map[i] += charnothing;
                }
            }
            for (int i = 0; i < mapsize[1]; i++)
                secondmap[i] = map[i];
        }
        if (mode == 4)
        {
            float timesgone = clock() - timer;
            if (cdmenu <= thirdtime) cdmenu += timesgone;
            timer = clock();
            if (somethinghappens == true && mode == 4)
            {
                somethinghappens = false;
                if (true)
                {
                    SetConsoleCursorPosition(h, zerocords);
                    SetConsoleCursorInfo(h, &cursorinfo);
                }
                cout << "Press escape to return\nThe weight of a cell determines the number of neighbors that this cell gives, if there is life in it\n";
                cout << "Choose a cell using WASD and set the weight of that\n\n\t ";
                for (int i = 0; i < 25; i++)
                {
                    if (choosen == i)
                    {
                        if (choosed)
                        {
                            cout << "X";
                        }
                        else cout << "x";
                    }
                    else cout << " ";
                    if (i < 12) cout << neighbormodif[i];
                    else
                        if (i > 12) cout << neighbormodif[i - 1];
                        else
                            cout << "O";
                    if (choosen == i)
                    {
                        if (choosed)
                        {
                            cout << "X  \t";
                        }
                        else cout << "x  \t";
                    }
                    else cout << "  \t";
                    if (i % 5 == 4) cout << "                          \n\t ";
                }
                cout << "\nRules for interaction of cells\nIf you don't know what is it, so, whar are you doing here?....\n\nBorn \t";
                for (int i = 0; i < howmanyrools; i++)
                {
                    if (i == 5) cout << "                   \n\t";
                    if (choosen - 25 == i)
                    {
                        if (choosed)
                        {
                            cout << "X";
                        }
                        else cout << "x";
                    }
                    else
                        cout << " ";
                    cout << born[i];
                    if (choosen - 25 == i)
                    {
                        if (choosed)
                        {
                            cout << "X ";
                        }
                        else cout << "x ";
                    }
                    else
                        cout << "  ";
                    cout << "\t";
                }
                cout << "\nStay \t";
                for (int i = 0; i < howmanyrools; i++)
                {
                    if (i == 5) cout << "                           \n\t";
                    if (choosen - 35 == i)
                    {
                        if (choosed)
                        {
                            cout << "X";
                        }
                        else cout << "x";
                    }
                    else
                        cout << " ";
                    cout << stay[i];
                    if (choosen - 35 == i)
                    {
                        if (choosed)
                        {
                            cout << "X ";
                        }
                        else cout << "x ";
                    }
                    else
                        cout << "  ";
                    cout << "\t";
                }
            }
            if (cdmenu >= thirdtime && mode == 4)
            {
                cdmenu = 0;
                if (GetAsyncKeyState(32)) {
                    choosed = !choosed; somethinghappens = true;
                }
                if (GetAsyncKeyState(27)) {
                    mode = 1; somethinghappens = true; choosen = 1; choosed = false;
                    clear();
                }
                if (choosed == false)
                {
                    if (GetAsyncKeyState(87) && choosen > 4) {
                        somethinghappens = true; choosen -= 5;
                    }
                    if (GetAsyncKeyState(83) && choosen < 41) {
                        somethinghappens = true; choosen += 5;
                    }
                    if (GetAsyncKeyState(65) && choosen >= 0 && choosen % 5 > 0) {
                        somethinghappens = true; choosen--;
                    }
                    if (GetAsyncKeyState(68) && choosen < 45 && choosen % 5 < 4) {
                        somethinghappens = true; choosen++;
                    }
                }
                else
                {
                    if (GetAsyncKeyState(87)) 
                    {
                        if (choosen < 12)
                        {
                            if (neighbormodif[choosen] < 99) neighbormodif[choosen]++; somethinghappens = true;
                        }
                        else
                            if (choosen > 12)
                            {
                                if (choosen >= 25)
                                {
                                    if (choosen >= 35)
                                    {
                                        if (stay[choosen - 35] < 99) stay[choosen - 35]++; somethinghappens = true;
                                    }
                                    else
                                        if (born[choosen - 25] < 99) born[choosen - 25]++; somethinghappens = true;
                                }
                                else
                                    if (neighbormodif[choosen - 1] < 99) neighbormodif[choosen - 1]++; somethinghappens = true;
                            }
                    }
                    if (GetAsyncKeyState(83)) 
                    {
                        if (choosen < 12)
                        {
                            if (neighbormodif[choosen] > -99) neighbormodif[choosen]--; somethinghappens = true;
                        }
                        else
                            if (choosen > 12)
                            {
                                if (choosen >= 25)
                                {
                                    if (choosen >= 35)
                                    {
                                        if (stay[choosen - 35] > -99) stay[choosen - 35]--; somethinghappens = true;
                                    }
                                    else
                                        if (born[choosen - 25] > -99) born[choosen - 25]--; somethinghappens = true;
                                }
                                else
                                    if (neighbormodif[choosen - 1] > -99) neighbormodif[choosen - 1]--; somethinghappens = true;
                            }
                    }
                }
            }
        }
        if (mode == 5)
        {
            float timesgone = clock() - timer;
            if (cdmenu <= thirdtime) cdmenu += timesgone;
            timer = clock();
            if (somethinghappens)
            {
                somethinghappens = false;
                clear();
                if (true)
                {
                    SetConsoleCursorPosition(h, zerocords);
                    SetConsoleCursorInfo(h, &cursorinfo);
                }
                cout << "Press space to return to menu\n\nThis programm created by Den from Crimea, that's all. I surprised by your wish to know author of this programm. \nAre you don't have anything to do? Close it and go to do something useful.";
            }
            if (GetAsyncKeyState(32) && cdmenu >= thirdtime)
            {
                cdmenu = 0;
                mode = 1; somethinghappens = true;
                clear();
            }
        }

        if (mode == 10)
        {
            float timesgone = clock() - timer;
            if (cdmenu <= thirdtime) cdmenu += timesgone;
            timer = clock();
            if (somethinghappens)
            {
                somethinghappens = false;
                if (true)
                {
                    SetConsoleCursorPosition(h, zerocords);
                    SetConsoleCursorInfo(h, &cursorinfo);
                }
                cout << "\tHello! Wellcome to programm to creating of cellular automata.\n\n";
                cout << " W        \t Shift - up speed\t Escape - menu         \t Q - delete life\n";
                cout << "ASD - move\t Space - pause   \t Space - choose in menu\t E - born life\n\n\t\t\tPress space to start";
            }
            if (GetAsyncKeyState(32) && cdmenu >= thirdtime)
            {
                cdmenu = 0;
                mode = 0; somethinghappens = true;
                clear();
            }
        }
    }
    CloseHandle(h);
}