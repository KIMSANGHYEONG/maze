#include "MazeStack.h"
#include "MazeQueue.h"

int main (void)

{	
    MazeStack mazeStack; //�̷� Ž�� ���� ��ü ����
    MazeQueue mazeQueue; //�̷� Ž�� ť ��ü ����

    mazeStack.load("Maze.txt");
    mazeQueue.roadMap("Maze.txt");

 
    mazeStack.searchExit(); //�̷θ� Ž���� �ⱸ�� ã��
    //Sleep(5000);
    mazeQueue.queue_SearchExit(); //�̷θ� Ž���� �ⱸ�� ã��

}



