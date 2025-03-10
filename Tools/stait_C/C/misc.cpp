/***************************************************************************************************************\
*																												*
*									������ �� ���������������� �����������										*
*												(�����������)													*
*																												*
*					������� ���� ������ � ������ �������, ����������� ����� ������ (PE)							*
*																												*
*											StrToLower, FindPE													*
*																												*
\***************************************************************************************************************/



#include "misc.h"



/***************************************************************************************************\
*	����� StrToLower; 
*	������� ���� ������ � ������ �������;
*	����:
*		pStr	-	������, ������� ��� ��� � ���� ������������ )
*	�����:
*		(+) (��������� �� ���������� ������)
\***************************************************************************************************/
char *StrToLower(char *pStr)
{
	int len = strlen(pStr);
	
	for(int i = 0; i < len; i++)
		pStr[i] = tolower(pStr[i]);
	
	return pStr; 
}
/***************************************************************************************************\
*	����� ����� StrToLower; 	
\***************************************************************************************************/



/***************************************************************************************************\
*	����� FindPE; 
*	����������� ����� ������
*	����:
*		pszDir	-	���� � �����(!), ������ ������ ����� ������;
*		pszMask	-	����� ������;
*		fnFunc	-	��������� �� �������, ������� ����� ������� ��� ���������� ���������� ������� 
*						�����;
*	������:
*		1		-	���� ����� ���� �� ���������, ����� 0 (��������, ����� (������������) ����)
*	��������:
*		�� ������� ����������:
*			pszDir	- ���� ����� ����, ��������, �����: "C:\\Games", "C:", "C:\\xuita" etc;
*			pszMask	- ����� ����� ����, ��������, �����: "\\*.*"; 
*			fnFunc	- �������� ������� ������ ���� �����: 
*				BOOL WINAPI xMyFunc(char *pStr);
*				� �����, ���� ���� ��� ���������� ������; 
\***************************************************************************************************/
BOOL FindPE(char *pszDir, char *pszMask, LPVOID fnFunc)
{
	static int recurs_level = 0; 
	char szPath[MAX_LEN * 2];	//����� ����� �������� ������ ����;
	HANDLE hFindFile;
	WIN32_FIND_DATA wfd;
	LPTSTR part; 
	typedef LPVOID (WINAPI *func)(LPVOID);	//��� ��� ���� ������ ��� ��������� �����;	 
	func xFunc = (func)fnFunc;
	DWORD fp_len = strlen(pszDir) + 1 + strlen(pszMask) + 1 + 10;	//file path; 

	if((fp_len >= MAX_LEN) || (recurs_level > MAX_RECURS_LEVEL)) 
	{ 
		recurs_level--; 
	//	printf("\nskip dir: %s\n", pszDir); 
		return 0; 
	}
	
	strcpy(szPath, pszDir);   
	strcat(szPath, pszMask);	
	hFindFile = FindFirstFile(szPath, &wfd);	//�������� �����

	if(hFindFile != INVALID_HANDLE_VALUE)	//�������?
	{
		GetFullPathName(szPath, MAX_LEN, szPath, &part);	//��������� ������ ���� � ��� ���������� ����� (�����) � ��������� � ���� �� szPath; part - ��������� �� ��� �����/�����/�����;

		do
		{
			if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (wfd.cFileName[0] != '.'))	//��� "����������" �����?
			{
				++recurs_level; 
			//	printf("\nrecurs_level = %d\n", recurs_level); 
				strcpy(part, wfd.cFileName);	//�������� � ������ ���� ����� �� ��� ��������� �����
				FindPE(szPath, pszMask, (LPVOID)fnFunc);	//���������� ������� � ��� �����;
				recurs_level--; 
			}
			else	//����� �� ����� ����
			{
				char *pExt = (char*)&wfd.cFileName[strlen(wfd.cFileName) - 4];	//��������� �� ���������� ����� (���� ��� ������ ����)
				
				if(!stricmp(pExt, ".exe") || !stricmp(pExt, ".dll") || !stricmp(pExt, ".scr"))	//���� ��� ���� �� ������ ��� ����������, 
				{
					strcpy(part, wfd.cFileName);	//�� ������� � ������ ���� ����� �� ��� ���������� �����
					
					__try
					{
						xFunc((char*)szPath);	//������� ����� (� ������ ������ ����� ��������� ������� � PE-�����), ������� �� ���� � ���������� �����;
					}
					__except(EXCEPTION_EXECUTE_HANDLER)
					{
					}
				}
			}
		}while(FindNextFile(hFindFile, &wfd));	//���������� �����
		
		FindClose(hFindFile);	//��������� ������ �������� �����;
	}
	else return 0;	//���� ����� ����������, ������ 0
	 
	return 1;	//����� 1 )
}
/***************************************************************************************************\
*	����� ����� FindPE; 	
\***************************************************************************************************/
