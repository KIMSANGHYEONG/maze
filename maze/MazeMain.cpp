#include "MazeStack.h"
#include "MazeQueue.h"

int main (void)

{	
    MazeStack mazeStack; //미로 탐색 스택 객체 생성
    MazeQueue mazeQueue; //미로 탐색 큐 객체 생성

    mazeStack.load("Maze.txt");
    mazeQueue.roadMap("Maze.txt");

 
    mazeStack.searchExit(); //미로를 탐색해 출구를 찾음
    //Sleep(5000);
    mazeQueue.queue_SearchExit(); //미로를 탐색해 출구를 찾음

}



