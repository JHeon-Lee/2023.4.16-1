// 2023.4.16,1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"

void InitTable(int* table); // 전방선언 
void ShowTable(int* table);
void HideTable(int* table);
void UserSelect(int* userTable, int* comTable);
void ComSelect(int* userTable, int* comTable);
int CheckBingo(int* table);

int main()
{
    // 랜덤 초기화
    srand(time(NULL));
    rand();

    //테이블 배열과 빙고 변수 선언
    int nUserTable[25];
    int nUserBingo = 0;
    int nComTable[25];
    int nComBingo = 0;

    //게임 진행 변수 선언
    bool isPlaying = true;
    bool isMyTurn = true;

    // 게임 진행
    while (isPlaying)
    {
        // 게임 플레이
        InitTable(nUserTable);
        InitTable(nComTable);

        while (true)
        {
            system("cls");

            //nUserBingo < 3 && nComBingo < 3
            
            // 빙고 확인
            nUserBingo = CheckBingo(nUserTable);
            nComBingo = CheckBingo(nComTable);

            // 테이블 확인
            HideTable(nComTable);
            cout << "컴퓨터 빙고 : " << nComBingo << endl << endl;
            ShowTable(nUserTable);
            cout << "유저 빙고 : " << nUserBingo << endl;

            if (nUserBingo >= 3 && nComBingo >= 3)
            {
                cout << "빙고 동시 달성!! 비겼습니다." << endl;
                break;
            }
            else if (nUserBingo >= 3)
            {
                cout << "유저 빙고 달성!! 이겼습니다." << endl;
                break;
            }
            else if (nComBingo >= 3)
            {
                cout << "컴퓨터 빙고 달성!! 졌습니다." << endl;
                break;
            }

            // 번호 선택
            if (isMyTurn)
            {
                UserSelect(nUserTable, nComTable);
                isMyTurn = false;
            }
            else
            {
                ComSelect(nUserTable, nComTable);
                isMyTurn = true;
            }
        }

        // 게임 종료 선택
        cout << "0. 게임종료, 1. 새 게임 : ";
        cin >> isPlaying;
    }

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

void InitTable(int* table)
{
    for (int i = 0; i < 25; i++)
    {
        table[i] = i + 1;
    }

    int nSrc;
    int nDest;
    int nTemp;

    for (int i = 0; i < 250; i++)
    {
        nSrc = rand() % 25;
        nDest = rand() % 25;

        nTemp = table[nSrc];
        table[nSrc] = table[nDest];
        table[nDest] = nTemp;
    }
}

void ShowTable(int* table)
{
    cout << "=========================================" << endl;
    for (int i = 0; i < 25; i++)
    {
        cout << "|  " << table[i] << "\t|";

        if (i % 5 == 4)
        {
            cout << endl;
            cout << "=========================================" << endl;
        }
    }
}

void HideTable(int* table)
{
    cout << "=========================================" << endl;
    for (int i = 0; i < 25; i++)
    {
        if(table[i] == 0)
            cout << "|  0\t|";
        else
            cout << "|  ?\t|";

        if (i % 5 == 4)
        {
            cout << endl;
            cout << "=========================================" << endl;
        }
    }
}

void UserSelect(int* userTable, int* comTable)
{
    int nSelect;

    cout << "선택 (1 ~ 25) : ";
    cin >> nSelect; // 문자를 넣으면 버그가 생겨서 예외처리가 필요하지만 지금 굳이 만들 필요는 없고
                    // API로 넘어가면 필요없음

    // 테이블 전체를 검사
    for (int i = 0; i < 25; i++)
    {
        if (nSelect == userTable[i])
        {
            // 0 => 테이블에서 이미 선택된 숫자를 의미
            userTable[i] = 0;

            // 컴퓨터 테이블도 똑같은 숫자를 처리
            for (int j = 0; j < 25; j++)
            {
                if (nSelect == comTable[j])
                {
                    comTable[j] = 0;
                    break;
                }
            }
            break;
        }

        // 선택한 숫자를 찾지 못한 경우
        if (i == 24)
        {
            cout << "제대로 선택해라!!" << endl;
            Sleep(1000);
        }
    }
}

/*
    컴퓨터의 AI 향상
    우선순위 Table 만들기
    [3] [0] [0] [0] [3]    [3] [0] [0] [0] [4]
    [0] [3] [0] [3] [0]    [0] [3] [0] [3] [1]
    [0] [0] [4] [0] [0] -> [1] [1] [5] [1] [X]
    [0] [3] [0] [3] [0]    [0] [3] [0] [3] [1]
    [3] [0] [0] [0] [3]    [3] [0] [0] [0] [4]
*/

void ComSelect(int* userTable, int* comTable)
{
    int nIndex = 0;
    int nSelect;

    cout << "컴퓨터 선택 중";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << "." << endl;

    while (true) // 이전에 선택된 적이 없는 칸(배열의 Index)을 선택한다.
    {
        nIndex = rand() % 25;
        nSelect = comTable[nIndex];
        
        if (nSelect != 0) // 숫자가 남은 칸을 찾았으면
        {
            for (int i = 0; i < 25; i++) // 유저 테이블에서 선택된 숫자를 처리하고
            {
                if (nSelect == userTable[i])
                {
                    userTable[i] = 0;
                    break;
                }
            }

            comTable[nIndex] = 0; // 컴퓨터 테이블에서도 선택된 숫자를 처리한다.
            break;
        }
    }

    cout << "컴퓨터 선택 : " << nSelect << endl;
    Sleep(2000);
}

int CheckBingo(int* table)
{
    int nBingo = 0;

    // 가로 검사 5
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[i * 5 + j] == 0) // 한칸씩 선택 유무 확인
            {
                if (j == 4) // 제일 마지막칸까지 선택이 되어있는 경우라면
                {
                    nBingo++;
                }
            }
            else
                break;
        }
    }

    // 세로 검사 5
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (table[j * 5 + i] == 0) // 한칸씩 선택 유무 확인
            {
                if (j == 4) // 제일 마지막칸까지 선택이 되어있는 경우라면
                {
                    nBingo++;
                }
            }
            else
                break;
        }
    }

    // 왼쪽 사선
    for (int i = 0; i < 5; i++)
    {
        if (table[i * 5 + i] == 0)
        {
            if (i == 4) // 제일 마지막칸까지 선택이 되어있는 경우라면
            {
                nBingo++;
            }
        }
        else
            break;
    }

    // 오른쪽 사선
    for (int i = 0; i < 5; i++)
    {
        if (table[(i + 1) * 4] == 0)
        {
            if (i == 4) // 제일 마지막칸까지 선택이 되어있는 경우라면
            {
                nBingo++;
            }
        }
        else
            break;
    }
    return nBingo;
}
