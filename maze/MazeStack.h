#pragma once
#include <iostream>
#include <fstream>
#include "stack.h"
#include <Windows.h>

using namespace std;

class MazeStack

{
    int width; //미로의 너비
    int height; //미로의 높이
    char** map; //미로 맵

    stack stack;
    
public:
    MazeStack()
    {
        init(0, 0);
    }

    ~MazeStack()
    {
        reset();
    }

    void init(int w, int h) //map 이차원 배열을 동적으로 할당
    {
        map = new char* [h];
        for (int i = 0; i < h; i++)
            map[i] = new char[w];
    }

    void reset() //미로 맵 maze를 동적으로 해제

    {
        for (int i = 0; i < height; i++)
            delete[]map[i];
        delete[]map;

    }

    void load(const char* fname) //파일에서 미로 파일을 읽어옴

    {
        char temp;
        ifstream fin(fname);
        fin >> width >> height;

        init(width, height);
        

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                fin >> temp;
                map[i][j] = temp;

                if (map[i][j] == 'e')
                {
                    Location2D entry(i, j);
                    stack.push(new Node(i, j));
                }
                

            }
            cout << endl;
        }
        fin.close();
    }

    bool isValidLoc(int r, int c)
    {
        if (r < 0 || c < 0 || r >= height || c >= width) return false; //범위를 벗어나면 갈 수 없다
        else return map[r][c] == '0' || map[r][c] == 'x'; //비어있는 통로나 도착지점일 때만 true
    }

    void print() //현재 Maze를 화면에 출력
    {
        gotoxy(0, 5);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (map[i][j] == '0') //통로
                {
                    cout << "  ";
                }
                else if (map[i][j] == '1') //벽
                {
                    cout << "■";
                }
                else if (map[i][j] == '.') //지나온 길
                {
                    cout << "□";
                }
                else if (map[i][j] == 'e') //입구
                {
                    cout << "○";
                }
                else if (map[i][j] == 'x') //출구
                {
                    cout << "◎";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    void searchExit()
    {
        while (stack.isEmpty() == false)
        {
            Location2D* here = stack.peek();
            stack.pop();

            int r = here->row;
            int c = here->col;

            if (map[r][c] == 'x')
            {
                cout << " 출구를 찾았습니다\n";
                return;
            }
            else
            {
                map[r][c] = '.';
                if (isValidLoc(r - 1, c))
                {
                    stack.push(new Node(r - 1, c));
                }
                if (isValidLoc(r + 1, c))
                {
                    stack.push(new Node(r + 1, c));
                }
                if (isValidLoc(r, c - 1))
                {
                    stack.push(new Node(r, c - 1));
                }
                if (isValidLoc(r, c + 1))
                {
                    stack.push(new Node(r, c + 1));
                }
                print();
                Sleep(200);
            }
            
        }

    }
    void gotoxy(int x, int y)
    {
        COORD pos = { x,y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }
};
