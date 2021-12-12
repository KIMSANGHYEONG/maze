#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "Link.h"
using namespace std;

class MazeQueue
{
	char** map = NULL;
	int width;
	int height;


	char** queueMap = NULL;

	//위치 스택 객체 생성
	LinkedQueue locQueue;


public:

	MazeQueue() { init(0, 0); }
	~MazeQueue() {
		reset();
	}

	void init(int w, int h) //map 이차원 배열을 동적으로 할당
	{
		map = new char* [h];
		for (int i = 0; i < h; i++)
			map[i] = new char[w];
	}

	void reset() //이차원 배열 동적으로 해제
	{
		for (int i = 0; i < height; i++)
			delete[]map[i];
		delete[]map;
	}

	bool isValidLoc(int r, int c)
	{
		if (r < 0 || c < 0 || r >= height || c >= width) return false;
		else return map[r][c] == '0' || map[r][c] == 'x';
	}

	void roadMap(const char* filename)
	{
		char temp;
		ifstream fin(filename);
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
					locQueue.enqueue(new Node(i, j));
				}

			}
			cout << endl;
		}
		fin.close();
	}

	//미로 화면에 출력
	void printMap() {
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (map[i][j] == '0') //길
				{
					cout << "  ";
				}
				else if (map[i][j] == '1') //벽
				{
					cout << "■";
				}
				else if (map[i][j] == 'e') //입구
				{
					cout << "★ ";
				}
				else if (map[i][j] == 'x') //출구
				{
					cout << "☆ ";
				}
				else if (map[i][j] == '.') //지나온 길
				{
					cout << "＊";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	// 연결리스트 큐로 구현한 미로 찾기(너비 우선 탐색).


	void queue_SearchExit()
	{
		int count = 0;
		while (locQueue.isEmpty() == false) //큐가 비어있지 않는 동안
		{
			printMap();
			while (true)
			{
				system("cls");

				locQueue.display();

				Location2D* here = locQueue.peek(); //큐의 상단 front 객체 복사
				locQueue.dequeue(); //큐 상단 객체 삭제

				count++;
				int r = here->row;
				int c = here->col;

				printf("Now Position: (%d,%d) \n", r, c); //상단 front 객체의 위치가 현재위치

				if (map[r][c] == 'x') { //출구이면 성공
					while (locQueue.isEmpty() == false)
						locQueue.dequeue();
					system("cls");
					printf("탐색 완료\n");
					printf("dequeue %d번 \n", count);
					printf("[ 미로 결과 ]\n");
					printMap();
					printf("\n출구를 찾았습니다\n");
					DebugBreak();
				}
				else if (map[r][c] != '.') //지나온 길이 아니면
				{
					map[r][c] = '.'; //지나온 길로 표시
					//갈 수 있는 길이면 큐에 삽입
					if (isValidLoc(r - 1, c)) locQueue.enqueue(new Node(r - 1, c));
					if (isValidLoc(r + 1, c)) locQueue.enqueue(new Node(r + 1, c));
					if (isValidLoc(r, c - 1)) locQueue.enqueue(new Node(r, c - 1));
					if (isValidLoc(r, c + 1)) locQueue.enqueue(new Node(r, c + 1));
					printMap();
					Sleep(200);
				}
			}
		}
		printf("미로 탐색 실패\n");
	}

};