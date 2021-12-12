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

	//��ġ ���� ��ü ����
	LinkedQueue locQueue;


public:

	MazeQueue() { init(0, 0); }
	~MazeQueue() {
		reset();
	}

	void init(int w, int h) //map ������ �迭�� �������� �Ҵ�
	{
		map = new char* [h];
		for (int i = 0; i < h; i++)
			map[i] = new char[w];
	}

	void reset() //������ �迭 �������� ����
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

	//�̷� ȭ�鿡 ���
	void printMap() {
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (map[i][j] == '0') //��
				{
					cout << "  ";
				}
				else if (map[i][j] == '1') //��
				{
					cout << "��";
				}
				else if (map[i][j] == 'e') //�Ա�
				{
					cout << "�� ";
				}
				else if (map[i][j] == 'x') //�ⱸ
				{
					cout << "�� ";
				}
				else if (map[i][j] == '.') //������ ��
				{
					cout << "��";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	// ���Ḯ��Ʈ ť�� ������ �̷� ã��(�ʺ� �켱 Ž��).


	void queue_SearchExit()
	{
		int count = 0;
		while (locQueue.isEmpty() == false) //ť�� ������� �ʴ� ����
		{
			printMap();
			while (true)
			{
				system("cls");

				locQueue.display();

				Location2D* here = locQueue.peek(); //ť�� ��� front ��ü ����
				locQueue.dequeue(); //ť ��� ��ü ����

				count++;
				int r = here->row;
				int c = here->col;

				printf("Now Position: (%d,%d) \n", r, c); //��� front ��ü�� ��ġ�� ������ġ

				if (map[r][c] == 'x') { //�ⱸ�̸� ����
					while (locQueue.isEmpty() == false)
						locQueue.dequeue();
					system("cls");
					printf("Ž�� �Ϸ�\n");
					printf("dequeue %d�� \n", count);
					printf("[ �̷� ��� ]\n");
					printMap();
					printf("\n�ⱸ�� ã�ҽ��ϴ�\n");
					DebugBreak();
				}
				else if (map[r][c] != '.') //������ ���� �ƴϸ�
				{
					map[r][c] = '.'; //������ ��� ǥ��
					//�� �� �ִ� ���̸� ť�� ����
					if (isValidLoc(r - 1, c)) locQueue.enqueue(new Node(r - 1, c));
					if (isValidLoc(r + 1, c)) locQueue.enqueue(new Node(r + 1, c));
					if (isValidLoc(r, c - 1)) locQueue.enqueue(new Node(r, c - 1));
					if (isValidLoc(r, c + 1)) locQueue.enqueue(new Node(r, c + 1));
					printMap();
					Sleep(200);
				}
			}
		}
		printf("�̷� Ž�� ����\n");
	}

};