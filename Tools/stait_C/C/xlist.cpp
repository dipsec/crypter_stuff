/***************************************************************************************************************\
*																												*
*							������ ��� ������ �� ���������������� ������� �������								*
*												(�����������)													*
*																												*
*		������ ������������ ��� ��������/����������/etc ������, ������ � ������ ������� ������ PE-������		*
*																												*
*	InitList, ShowListAll, DestroyListAll, AddElemDll, AddElemFunc, GetInfoAll, FindElem, SwapElem, BubbleSort	*
*																												*
\***************************************************************************************************************/



#include "xlist.h"



/***************************************************************************************************\
*	������� InitList
*	������������� ������ list_dll_node
*	����:
*		p	-	��������� �� ������ list_dll;
*	�����:
*		������������ ������ (������ ������);
\***************************************************************************************************/
void InitList(list_dll *p)
{
	p->pFirst = 0;	//������, ���� ��������� ) 
}
/***************************************************************************************************\
*	����� ����� InitList; 
\***************************************************************************************************/



/***************************************************************************************************\
*	������� WriteListAll
*	������ � ���� ���� ���������� ������� ������� (������ � ���� ������ �� ��������� � �������� 
*		������ PE-files dll & functions)
*	����:
*		p		-	��������� �� ������ list_dll (������ ��������� ��������, ����� 0);
*		file	-	��������� �� ������ FILE (� ���� ���� ������);
*		pgifle	-	��������� �� ������ GIFL (������ ������ ���� �����������);
*	�����:
*		������ � ���-����, ���� ��� �������=)!
\***************************************************************************************************/
void WriteListAll(list_dll *p, FILE *file, GIFL *pgifl)
{
	double pr_dll = 0;
	double pr_for_this_dll = 0;
	double pr_for_all_dll = 0;
	double pr_group_func = 0;
	list_dll_node *pldn_next = p->pFirst;	//pldn_next ������ ��������� �� ������ (������) ������ list_dll_node; 
	char szsng_line[] = "-----------------"; 
	char szdbl_line[] = "===================================";  
	char szInfo[] = "INFO FROM PE32-FILES (IMPORT TABLE)"; 
	char szTotal[] = "RESULT FROM LIST";
	int m_count[3] = {1, 1, 1};	//��������: [0] - ����� ���������� ��� � ������; [1] - ����� ���������� ����� � ���������� ���; [2] - ����� ���������� ����� �� ���� ������; 

	fprintf(file, "%s\n%s\n%s\n\n", szdbl_line, szInfo, szdbl_line);

	while(pldn_next)
	{
		list_func_node *plfn_next = pldn_next->pFirst;	//plfn_next ������ ��������� �� ������ (������) ������ list_func_node; 
		pr_dll = ((double)pldn_next->count * MAX_PER) / (double)pgifl->num_all_dll;	//��������� ���������� ����������� ��������� ���;
		pr_group_func = ((double)pldn_next->num_all_func * MAX_PER) / (double)pgifl->num_all_func;	//���������� ����������� ���-�� ����� ������� (�.�. ����������� ���-�� ������� (������� �� ����������) � ������ ��� � ���-�� ���� ������� �� ���� ���);     
		fprintf(file, "%s\n%s\n%d\n", szdbl_line, szdbl_line, m_count[0]);
		fprintf(file, "%s\n%d\n%d\n%d\n%3.5f%%\n%3.5f%%\n%s\n", pldn_next->pName, pldn_next->count, pldn_next->num_func, 
				pldn_next->num_all_func, pr_dll, pr_group_func, szdbl_line);	//� ���������� ��� ��� ���� � ����; 

		while(plfn_next)
		{
			pr_for_this_dll = ((double)plfn_next->count * MAX_PER) / (double)pldn_next->num_all_func;	//���������� ����������� ���-�� ����� ������� (������� ����������) � ������ ��� � ���-�� ���� ������� � ������ ���;
			pr_for_all_dll = ((double)plfn_next->count * MAX_PER) / (double)pgifl->num_all_func;	//���������� ����������� ���-�� ����� ����� (������� �� ����������) � ������ ��� � ���-�� ���� ����� �� ���� ���; 
			fprintf(file, "%d | %d\n", m_count[1], m_count[2]); 
			fprintf(file, "%s\n%d\n%3.5f%%\n%3.5f%%\n%s\n", plfn_next->pName, plfn_next->count, pr_for_this_dll, 
					pr_for_all_dll, szsng_line); 
			m_count[1]++;
			m_count[2]++;
			plfn_next = plfn_next->pNext;	//������� �� ��������� ������� ������; 
		}

		fprintf(file, "%s\n%s\n\n\n\n", szdbl_line, szdbl_line); 
		m_count[0]++;
		m_count[1] = 1;
		pldn_next = pldn_next->pNext;
	}
 
	fprintf(file, "%s\n%s\n%s\nnum_dll_in_list\t\t=\t%d\nnum_all_dll_in_list\t=\t%d\nnum_func_in_list\t=\t%d\nnum_all_func_in_list\t=\t%d\n%s\n", 
		szdbl_line, szTotal, szdbl_line, pgifl->num_dll, pgifl->num_all_dll, pgifl->num_func, pgifl->num_all_func, szdbl_line);
}
/***************************************************************************************************\
*	����� ����� WriteListAll; 
\***************************************************************************************************/



/***************************************************************************************************\
*	����� DestroyListAll
*	������������ ������, ����� ���������� ��� ������� �������; 
*	����:
*		p	-	��������� �� ������ list_dll;
*	�����:
*		(+)
\***************************************************************************************************/
void DestroyListAll(list_dll *p)
{
	list_dll_node *pldn_next = p->pFirst;	//�������� ������ ������ list_dll_node;

	while(p->pFirst)
	{
		pldn_next = p->pFirst;	//��������� ����� ������� �������� � ������ - ��� �� � ����� �������;
		p->pFirst = p->pFirst->pNext;	//������ ������ ������ ������� ������; 
		list_func_node *plfn_next = pldn_next->pFirst;	//�������� ������ ������ list_func_node;
		
		while(pldn_next->pFirst)
		{
			plfn_next = pldn_next->pFirst; //etc 
			pldn_next->pFirst = pldn_next->pFirst->pNext;
			free(plfn_next->pName);	//����������� ������� ������, ���������� ��� ������;
			free(plfn_next);	//� ����� ��������� ��� ������� ������;
		}

		free(pldn_next->pName);	//etc 
		free(pldn_next);
	}
}
/***************************************************************************************************\
*	����� ����� DestroyListAll; 
\***************************************************************************************************/



/***************************************************************************************************\
*	����� AddElemDll
*	 ���������� ���������� �������� (������ � ����� ��������� ���) � ������ 
*	(���� �� ����� ������� � ������ ����, ����� ������ ��������� �������� ����� ��������)
*	����:
*		p			-	��������� �� ������ ��������� list_dll;
*		pszDllName	-	��������� �� ��� ���. "��� ���" �� � ����� �������� � ������. 
*	�����:
*		1			-	���� �������� ����� �������, ����� 0 (������� ��� ���� � ������); 		
*	�������:
*		������� �� ������ ���������, ���� �� ������ ��� ��� � ��� � ������. ��� ����� �� ���������� 
*		����� � ������ �� ����� ��� (pszDllName). ��� ������ ������ ���� ��� � ������ ��������, 
*		��� ��� � ������ ����� ��� �������� ������ � ����� ����. ����� ������� ��������  � 
*		���������� ����;
\***************************************************************************************************/
BOOL AddElemDll(list_dll *p, char *pszDllName)
{ 	
	int fld;
	list_dll_node *pldn;
	list_dll_node *pldn_next = FindElemDll(p, pszDllName, &fld);	//������� ��������, ���� �� ������� ��� � ������

	if(!fld)	//������� �� ��� ������? 
	{
		int len = strlen(pszDllName);	//������� ����� ������
		pldn = (list_dll_node*)malloc(sizeof(list_dll_node));	//������� ������ ��� ������ �������� ������;
		pldn->pName = (char*)malloc(sizeof(char) * len + 1);	//������� ������ ��� ������, ����� ������� ������� ������ �������� � pName; 
		strcpy(pldn->pName, pszDllName);	//��������� ������;
//		pldn->pDllName[len] = 0;
		pldn->count = 1;	//����������������� ���������� ������ ��������; 
		pldn->num_func = 0;
		pldn->num_all_func = 0; 
		pldn->pFirst = 0;

		if(!p->pFirst)	//���� ������ ������
		{
			p->pFirst = pldn;
			pldn->pNext = 0;
		}
		else	//���� ������ �������� ��� ���� �� ���� �������, ����� ������� ����� ������� � ����� ������; 
		{
			pldn_next->pNext = pldn;
			pldn->pNext = 0; 
		}

		return 1; 
	}
	else
		pldn_next->count++;

	return 0;
}
/***************************************************************************************************\
*	����� ����� AddElemDll; 
\***************************************************************************************************/



/***************************************************************************************************\
*	����� AddElemFunc
*	 ���������� ���������� �������� (������ � ����� ��������� �����) � ������ 
*	(���� �� ����� ������� � ������ ����, ����� ������ ��������� �������� ����� ��������)
*	����:
*		p	-	��������� �� ������ list_dll;
*		pszDllName	-	��������� �� ������ - ��� ���;
*		pszFuncName	-	��������� �� ������ - ��� �����;
*	�����:
*		1			-	���� �������� ����� �������, ����� 0 (������� ��� ���� � ������);
*	�������:
*		������� �� ���� �������-���, � ������� ���������� ��������� �� ������ ������ 
*		list_func_node (���, ��� �������� ������ �� ������ �����, ������������� ������ ���); � ��� 
*		����� ���������� �� ����� pszDllName. ��� ������ ������ ���� ��� � ������ ��������. 
*		����� �� ���������, ���� �� ������ ����� � ���� ������ list_func_node. ���� �� ����� 
*		pszFuncName.
\***************************************************************************************************/
BOOL AddElemFunc(list_dll *p, char *pszDllName, char *pszFuncName)
{
	int fld;
	int flf;
	list_func_node *plfn;
	list_dll_node *pldn_next = FindElemDll(p, pszDllName, &fld);	//�����  �������� (���), ������� �� ���� ����������� ������ ��� ����� (���������); 
	list_func_node *plfn_next = FindElemFunc(pldn_next, pszFuncName, &flf);	//����� �������� (�����) � ��������� (��-������ ���������=)) ��� (�������);

	if(fld)	//etc
	{
		pldn_next->num_all_func++; 
		 
		if(!flf)
		{
			int len = strlen(pszFuncName);
			plfn = (list_func_node *)malloc(sizeof(list_func_node));
			plfn->pName = (char*)malloc(sizeof(char) * len + 1); 
			strcpy(plfn->pName, pszFuncName);
			plfn->count = 1;
			pldn_next->num_func++;

			if(!pldn_next->pFirst)
			{
				pldn_next->pFirst = plfn;
				plfn->pNext = 0;
			}
			else
			{
				plfn_next->pNext = plfn;
				plfn->pNext = 0; 
			}

			return 1; 
		}
		else
			plfn_next->count++;
	}
	else
	{
	} 

	return 0; 
}
/***************************************************************************************************\
*	����� ����� AddElemFunc; 
\***************************************************************************************************/



/***************************************************************************************************\
*	������ ������� FindElem
*	����� �������� � ����� (list_dll_node ��� list_func_node)
*	����:
*		p		-	��������� �� ������ ��������� B, � ������� ���������� ��������� �� ������ 
*						A; ��� ����� ����� )
*		pszName	-	��� (��������� �� ������), �� �������� ����� ���� �����;
*		fl		-	���� �������� ����� ����������, � ������� �� ������ ���������� 0 - ���� ������� 
*						����������� � ������, � 1 - ���� ������� ������;
*	�����:
*		��������� �� ������� ��������� A. ���� ������� ��� ������, ����� ��������� ����� 
*			��������� ����� ����� �������� � ������. ���� �� ������� �� ��� ������, ����� 
*			��������� ����� ��������� ����� ������� �������� � ������ (����� ������) - ��� ���� ����� 
*			� ����� �������� ����� �������; 
*		fl;		
*	�������:
*		������ � ����� � ��� ������ ������0 )
\***************************************************************************************************/
template <class A, class B>
A *FindElem(B *p, char *pszName, int *fl)
{
	A *pl_next = p->pFirst;	//etc
	*fl = 0;

	while(pl_next) 
	{
		if(strcmp(pl_next->pName, pszName) == 0)	//����� �� �����; 
		{
			*fl = 1;
			break;
		}

		if(!pl_next->pNext)
			break;

		pl_next = pl_next->pNext;
	}

	return pl_next;
}
/***************************************************************************************************\
*	����� ������� ����� FindElem;  
\***************************************************************************************************/



/***************************************************************************************************\
*	������ ����� SwapElem; 
*	������������ ������� ��������� (� ������ (list_dll_node ��� list_func_node)) (��� ����������� 
		����������);
*	����:
*		p		-	��������� �� ������ ��������� B, � ������� ���������� ��������� �� ������ A;
*		pPrev	-	"����������" ������� � ������ �������� A; 
*		pCur	-	"�������";
*		pNext	-	"���������";
*	�����:
*		��������� �� ����� ������� ������� (��� ��� ��������� ������������ �������� � ����������� 
*			��������� ����� �����); 
\***************************************************************************************************/
template <class A, class B>
A *SwapElem(B *p, A *pPrev, A *pCur, A *pNext)
{
	if(!pPrev)	//���� ������� ������� - ������ ������;
		p->pFirst = pNext;
	else	//���� ������� ������� - �����, ����� ������ (�.0.)
		pPrev->pNext = pNext;
	
	pCur->pNext = pNext->pNext; 
	pNext->pNext = pCur;

	return pNext;

}
/***************************************************************************************************\
*	����� ������� ����� SwapElem;  
\***************************************************************************************************/



/***************************************************************************************************\
*	������ ����� BubbleSort;  
*	����������� ���������� (������ (list_dll_node or list_func_node))
*	����:
*		p	-	��������� �� ������ ��������� A, � ������� ���������� ��������� �� ������ B; 
*	�����:
*		�����, ������� ����� ���� ������������ � ������;
*	�������:
*		���������� �������������� ����� ��������� �������� ����� count (����� ���������� �������� 
*		� ������);
*		������� - ������������ ������� ��������� ��� ������ ��������� ���� �������; 
*		���������� � ������� ��������; 
\***************************************************************************************************/
template <class A, class B>
DWORD BubbleSort(A *p)	//	������0��� ���������� ); 
{
	B *pldn_next;
	B *pldn_prev;
	int fl = 0;
	int count = 0;

	while(1)
	{
		pldn_next = p->pFirst; 
		pldn_prev = 0;

		while(pldn_next->pNext)
		{
			if(pldn_next->count < pldn_next->pNext->count)
			{
				pldn_next = SwapElem<B, A>(p, pldn_prev, pldn_next, pldn_next->pNext);
				fl = 1;
				count++;
			}

			pldn_prev = pldn_next;
			pldn_next = pldn_next->pNext; 
		}

		if(!fl)
			break;
		else
			fl = 0;
	}

	return count;
}
/***************************************************************************************************\
*	����� ������� ����� BubbleSort;  
\***************************************************************************************************/



/***************************************************************************************************\
*	����� BubbleSortAll; 
*	 �����, ���������� ������� ����������� ���������� ��� ���� ������� (����������� ��� ������);
*	����:
*		p	-	��������� �� ������ ��������� list_dll; (�����������, p - ������ ��������� 
*					�������� ��������); 
*	�����:
*		�����, ������� ����� ���� ������������ �� ���� �������;
\***************************************************************************************************/
DWORD BubbleSortAll(list_dll *p)
{
	int count = 0;
	list_dll_node *pldn_next;

	if(!p->pFirst)	//���� ������ ������
		return count;

	count += BubbleSortDll(p);	//������� ����������� ������ list_dll_node;
	pldn_next = p->pFirst;

	while(pldn_next)
	{
		count += BubbleSortFunc(pldn_next);	//� ����� ������ ������ list_func_node; 
		pldn_next = pldn_next->pNext; 
	} 

	return count;
}
/***************************************************************************************************\
*	����� ����� BubbleSortAll;   
\***************************************************************************************************/
 


/***************************************************************************************************\
*	����� GetInfoAll; 
*	��������� ������ ���� �� ������ list_dll_node; 
*	����:
*		p		-	��������� �� list_dll;
*		pgifl	-	��������� �� ������ GIFL. ������ ������ ������ ���� ���������� (��� �������� 
*						������ ���� �������������������);
*	�����:
*		��������� �� ���������� ������. �������� ��������� ���������.
\***************************************************************************************************/
GIFL *GetInfoAll(list_dll *p, GIFL *pgifl)
{
	list_dll_node *pldn_next = p->pFirst;	//etc 

	while(pldn_next)
	{
		pgifl->num_dll++;	//������� ���������� ��� (�� ���� ��� ����������); 
		pgifl->num_func += pldn_next->num_func;	//������� ���������� ������� (etc) �� ���� dll; 
		pgifl->num_all_dll += pldn_next->count; //������� ��� ��� (� ������������);
		pgifl->num_all_func += pldn_next->num_all_func;	//������� ��� ������ (� ������������) �� ���� ���; 
		pldn_next = pldn_next->pNext;
	}

	return pgifl;
}
/***************************************************************************************************\
*	����� ����� GetInfoAll;   
\***************************************************************************************************/
 
