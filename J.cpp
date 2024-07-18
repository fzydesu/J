#include<iostream>
#include <string.h>
using namespace std;
// 1==J 2==D 3==T
int main()
{
    int setmode = 1;//1:调试模式 0:正常使用
    /*
    调试模式功能：
    连续对局
    无限掏
    输出玩家保守值
    */
    int movem[1000], turn = 0;
    int J = 0, D = 0, T = 0;
    int mjc = 0;
    int winc=0,totc=0;
    double a = 0.5, s = 0; // 越大对方越保守（0,1）
    srand(unsigned(time(0)));
    while (true)
    {
        turn++;
        char input;
        int toreturn = 1;
        if (turn > 2 && movem[turn - 1] == 1)
        {
            s += (1 - s) * 0.2;
        }
        else if (turn > 2 && movem[turn - 1] == 2)
        {
            s += (1 - s) * 0.3;
        }
        else if (turn > 2 && movem[turn - 1] == 3)
        {
            s -= (1 - s) * 0.3;
        }
        a = abs(s) * s + 0.5;
        if(setmode)
            cout << "a=" << a << endl;
        cout << "输入(JDT):";
        int pass = 0;
        while (!pass)
        {
            cin >> input;
            switch (input)
            {
            case 'J':
                movem[turn] = 1;
                pass = 1;
                break;
            case 'D':
                movem[turn] = 2;
                pass = 1;
                break;
            case 'T':
                movem[turn] = 3;
                if(J>0||setmode)
                    pass = 1;
                else
                    cout << "您的J数不足,请重新输入:";
                break;
            default:
                break;
            }
        }
        
        if (turn == 1)
        {
            toreturn = 1;
        }
        // special
        if (J == 0 && mjc != 0)
        {
            if (rand() % 1000 < a * 1000)
            { // baoshou
                toreturn = 1;
            }
            else
            { // jijin
                toreturn = 3;
            }
        }
        else if(J != 0 && mjc == 0)
        {
            if ((1 + J / 2) * rand() % 1000 < a * 1000)
            { // baoshou:J
                toreturn = 1;
            }
            else
            {
                toreturn = 2;
            }
        }
        else if(J==0&&mjc==0)
        {
            toreturn = 1;
        }
        else{
            if ((1+(J-mjc)/2)*rand() % 1000 < a * 1000)
            { // baoshou:J
                if ((1 + (J - mjc) / 2) * rand() % 1000 < a * 1000)
                { // baoshou:J
                    toreturn = 3;
                }
                else
                {
                    toreturn = 1;
                }
            }
            else
            {
                if ((1 + (J - mjc) / 2) * rand() % 1000 > a * 1000)
                { // baoshou:J
                    toreturn = 1;
                }
                else
                {
                    toreturn = 2;
                }
            }
        }
        switch (movem[turn])
        {
            case 1:
                J++;
                break;
            case 2:
                D++;
                break;
            case 3:
                J--;
                T++;
                break;
            default:
                break;
        }
        cout << "AI出的是:";
        switch (toreturn)
        {
            case 1:
                mjc++;
                cout << 'J' << endl;
                break;
            case 2:
                cout << 'D' << endl;
                break;
            case 3:
                mjc--;
                cout << 'T' << endl;
                break;
            default:
                break;
        }
        // panding
        if (toreturn == 1 && movem[turn] == 3)
        {
            cout << "你赢了\n";
            memset(movem,1,1000);
            turn = 0;
            J = 0, D = 0, T = 0;
            mjc = 0;
            a = 0.5; // 越大对方越保守（0,1）
            s = 0;
            totc++;
            srand(unsigned(time(0)));
            if (setmode)
                cout << "胜率:" << 1.0 * winc / totc << endl;
        }
        else if (toreturn == 3 && movem[turn] == 1)
        {
            cout << "你输了\n";
            memset(movem, 0, 1000);
            turn = 0;
            J = 0, D = 0, T = 0;
            mjc = 0;
            a = 0.5; // 越大对方越保守（0,1）
            s = 0;
            totc++;
            winc++;
            srand(unsigned(time(0)));
            if(setmode)
                cout << "胜率:" << 1.0 * winc / totc << endl;
        }
        if(turn==0&&!setmode)
            break;
    }
}
