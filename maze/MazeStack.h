#pragma once
#include <iostream>
#include <fstream>
#include "stack.h"
#include <Windows.h>

using namespace std;

class MazeStack

{
    int width; //�̷��� �ʺ�
    int height; //�̷��� ����
    char** map; //�̷� ��

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

    void init(int w, int h) //map ������ �迭�� �������� �Ҵ�
    {
        map = new char* [h];
        for (int i = 0; i < h; i++)
            map[i] = new char[w];
    }

    void reset() //�̷� �� maze�� �������� ����

    {
        for (int i = 0; i < height; i++)
            delete[]map[i];
        delete[]map;

    }

    void load(const char* fname) //���Ͽ��� �̷� ������ �о��

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
        if (r < 0 || c < 0 || r >= height || c >= width) return false; //������ ����� �� �� ����
        else return map[r][c] == '0' || map[r][c] == 'x'; //����ִ� ��γ� ���������� ���� true
    }

    void print() //���� Maze�� ȭ�鿡 ���
    {
        gotoxy(0, 5);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (map[i][j] == '0') //���
                {
                    cout << "  ";
                }
                else if (map[i][j] == '1') //��
                {
                    cout << "��";
                }
                else if (map[i][j] == '.') //������ ��
                {
                    cout << "��";
                }
                else if (map[i][j] == 'e') //�Ա�
                {
                    cout << "��";
                }
                else if (map[i][j] == 'x') //�ⱸ
                {
                    cout << "��";
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
                cout << " �ⱸ�� ã�ҽ��ϴ�\n";
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
