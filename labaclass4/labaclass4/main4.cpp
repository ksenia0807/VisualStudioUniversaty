/**************************************************************************
*                      �  �  �  �      �  �  �                            *
*-------------------------------------------------------------------------*
*                                                                         *
* Project Name  : labaclass                                               *
* Project Type  : Win32 Console application                               *
* File Name     : main.cpp                                                *
* Language      : Visual C++           MS VS 2019                         *
* Programmer(s) : �������� �.�.                                           *
* Modified By   : �������� �.�.                                           *
* Created       : 28 / 04 / 2023                                          *
* Last Revision : 02 / 06 / 2023                                          *
* Comment(s)    : ������������ ������                                     *
*                                                                         *
*                                                                         *
***************************************************************************/

#pragma once                  
#include <windows.h>
#include <conio.h>
#include <iostream>    
#include <vector>
using namespace std;           // ������������ ���� std
#include "class4.h"

bool Collision(Chandelier* inputChandelier, Man* inputMan, vector<int> GetLoc);
//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*   � � � � � � � � � �   � � � � � � � � � �  �  � � � � � � � � �   */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

HDC hdc;// ������� �������� ����������
		// �������� ���������� �� ���� ��� ���������,
		// ���������� �������� ���������� �� ����� ����������
		// � ���� ����������� ����������� ���������

/*---------------------------------------------------------------------*/
/*               � � � � � � � � �    � � � � � � �                    */
/*---------------------------------------------------------------------*/
HWND GetConcolWindow(); //��������� �� ���������� ����

/***********************************************************************/
/*               � � � � � � � �    � � � � � � � � �                  */
/***********************************************************************/
int main()
{
	//���������� � ������������� ����������
	int x0 = 500;	//��������� ���������� �����/������
	int y0 = 200;
	int x1 = 225;	//��������� ���������� ��������
	int y1 = 350;
	int x2 = 750;	//��������� ���������� �������������
	int y2 = 450;

	//������� ���������� ����������� ����
	HWND hwnd = GetConcolWindow();
	system("color F0");

	//���� ���������� ����������
	if (hwnd != NULL)
	{
		//������� �������� ���������� ��� ����������� ����
		hdc = GetWindowDC(hwnd);

		//���� �������� ���������� - ����� ��������
		if (hdc != 0)
		{
			//===================================================================
			//	� � � � �    � � � � � � � 	

			//������������� �����
			Chandelier AChandelier(x0, y0);
			LChand ALChand(x0, y0);
			RChand ARChand(x0, y0);
			NoChand ANoChand(x0, y0);
			ChandDop AChandDop(x0, y0);

			//������������� ������������� ��������
			Man AMan(x1, y1);
			Man1 AMan1(x1 + 200, y1);
			SwitchOff ASwitchOff(x2, y2);
			SwitchOn ASwitchOn(x2 + 100, y2);
			ManDop AManDop(x1 + 300, y1);

			Chandelier* BufChandelier[5];  //������ �����
			BufChandelier[0] = &AChandelier;
			BufChandelier[1] = &ALChand;
			BufChandelier[2] = &ARChand;
			BufChandelier[3] = &ANoChand;
			BufChandelier[4] = &AChandDop;

			Man* BufObjects[5];    //������ ������������� ��������
			BufObjects[0] = &AMan;
			BufObjects[1] = &AMan1;
			BufObjects[2] = &ASwitchOff;
			BufObjects[3] = &ASwitchOn;
			BufObjects[4] = &AManDop;

			int MatrCollision[5][5] = { {1,3,3,0,0}, 
										{2,3,3,3,2}, 
										{0,1,2,3,4}, 
										{0,1,2,3,4},
										{4,4,4,4,0} };  //������� ���������
			
			vector<int> Stop = AChandelier.Loc();  //������, ������� ���������� ������� ������

			Chandelier* CurChandelier = BufChandelier[0]; //�������������� ��������� �� ������� ������� � ��������
			Man* CurObj = BufObjects[0];

			Man* pointerMan = &AMan; //�������������� ��������� �� ������� ������� � ������
			Man* pointerMan1 = &AMan1; //�������������� ��������� �� ������� ������� � ������
			Man* pointerManDop = &AManDop; //�������������� ��������� �� ������� ������� � ������
			Man* SwOff = &ASwitchOff;  //�������������� ��������� �� ������� ������� � ���������������
			Man* SwOn = &ASwitchOn;        //�������������� ��������� �� ������� ������� � ���������������
			int flag = 0;  //���� ��� ����������� �������� �� ������ ��� ���
			while (1)
			{
				if (KEY_DOWN(VK_ESCAPE))   //����� �� ����� �� Esc
					break;

				
				//�������� ������� � ����
				
				if (flag == 0)
				{
					CurChandelier->Off();
					CurChandelier->Show();
				}
				else if (flag == 1)
				{
					
					CurChandelier->Show();
					CurChandelier->On();
				}
				pointerMan->Show();
				pointerMan1->Show();
				pointerManDop->Show();
				SwOff->Show();
				SwOn->Show();
				CurChandelier->Drag(50, Stop);  //����������� ������

				
				//��������� ������������ � �������
				for (int i = 0; i < 5; i++)  //���� �� ��������
				{
					bool res = Collision(CurChandelier, BufObjects[i], Stop);  //�������� �� ������������

					if ((res == true) && (i != 2) && (i != 3))  //������������� ������ �� �������� ��������������
					{
						int icol = CurChandelier->id;
						int irow = BufObjects[i]->idm;

						int IndCurChandelier = MatrCollision[irow][icol];
						CurChandelier = BufChandelier[IndCurChandelier];
						
						break;
						//CurChandelier->Show();
					}//end if
					if ((res == true) && ((i == 2) || (i == 3)))  //������������� ������ �������������
					{
						if (i == 2)
						{
							CurChandelier->Off();  //��������� ������
							flag = 0;
						}
						if (i == 3)
						{
							CurChandelier->On();   //������� ������
							flag = 1;
						}
					}//end if
				}//end for 
				Sleep(50);
			}//end whil		

			while (1)
				if (KEY_DOWN(48))  //����� 0 ����� �� ���������
					break;

			//===================================================================
		}//end if
	}//end if
	return 0;
}//end main()

/*---------------------------------------------------------------------*/
/*               � � � � � � � � � �   � � � � � � �                   */
/*---------------------------------------------------------------------*/
bool Collision(Chandelier* inputChandelier, Man* inputMan, vector<int> GetLoc)  //�������� �� ������������ ��������
{
	if ((inputChandelier->GetX() < inputMan->GetX() + 50) && (inputChandelier->GetX() > inputMan->GetX() -
		50) && (inputChandelier->GetY() < inputMan->GetY() + 55) && (inputChandelier->GetY() > inputMan->GetY() - 55))
	{
		inputChandelier->Hide(); //������ �����
		inputChandelier->SetX(500);
		inputChandelier->SetY(200);
		return true;
	}//end if
	else
	{
		return false;
	}//end else
}//end Collision()
/*----------------------------------------------------------------------*/
/*  ������� ���������� ����  */
/*---------------------------*/
HWND GetConcolWindow()
{
	char str[128];
	//char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//����� ������ Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // �������� ��������� ����
	SetConsoleTitle(title);						// ���������� ����� ��������� ����
	Sleep(100);									// ���� ����� ��������� ���� (100 ��);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// ���������� ���������� ����
	SetConsoleTitle((LPWSTR)str);				//���������� ������� ���������

	return hwnd;//������� ���������� ����
}//end GetConcolWindow()

/**********************  End Of main.cpp File ********************/

