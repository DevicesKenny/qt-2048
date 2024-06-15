//游戏逻辑代码相关实现
#include "gamelogic.h"
#include "ui_mainwindow.h"

#include <random>
#include <iostream>
#include <vector>
#include <QDebug>
#include <QFile>
using namespace std;

GameLogic::GameLogic()
{
    initAll();
}

void GameLogic::initAll()
{
    //为空时，初始化为0，方便后续移动，遍历使用
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            data[i][j] = 0;
        }
    }
    gameStart = false;
    grade = 0;
    gradeBasic = 0;
    gradeUp = 0;
    step = 0;
    gradeUpCoefficient = 0;

    prob2 = 0;
    prob4 = 0;
    prob8 = 0;
    prob16 = 0;
}

void GameLogic::calProb()
{
    qDebug() << "gradeUpCoefficient:" << gradeUpCoefficient ;
    if(gradeUpCoefficient < 0.6) // 0->0.6
    {
        prob2 = 80-gradeUpCoefficient*100*0.5; // 80%->50%
        prob4 = 100;                           // 20%->50%
        prob8 = 0, prob16 = 0;                 // 0
        qDebug() << "2:" << prob2 << " 4:" << prob4 << " 8:" << prob8 << " 16:" << prob16 ;
    }
    else if(gradeUpCoefficient < 0.8) // 0.6->0.8
    {
        prob2 = 80-gradeUpCoefficient*100*0.5; // 50%->40%
        prob4 = 50+prob2;                      // 50%
        prob8 = 100;                           // 0->10%
        prob16 = 0;                            // 0
        qDebug() << "2:" << prob2 << " 4:" << prob4 << " 8:" << prob8 << " 16:" << prob16 ;
    }
    else if(gradeUpCoefficient <= 1.0)// 0.8->1.0
    {
        prob2 = 40;                                    // 40%
        prob4 = -10+gradeUpCoefficient*100*0.5+prob2;  // 30%->40%
        prob8 = -10+gradeUpCoefficient*100*0.25+prob4; // 10%->15%
        prob16 = 100;                                  // 0->5%
        qDebug() << "2:" << prob2 << " 4:" << prob4 << " 8:" << prob8 << " 16:" << prob16 ;
    }
}

bool GameLogic::createNum()
{
    vector<int> indexSpace;
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            if(!data[i][j])
            {
                indexSpace.push_back(i*4+j);
            }
        }
    }
    if(!indexSpace.empty())
    {
        int randNum = rand()%100;
        int randPlace = rand()%indexSpace.size();
        int chooseNum = -1;

        calProb();
        //qDebug() << "randNum:" << randNum;
        //qDebug() << "2:" << prob2 << " 4:" << prob4 << " 8:" << prob8 << " 16:" << prob16 ;
        if     (randNum < prob2)
            chooseNum = 2;
        else if(randNum < prob4)
            chooseNum = 4;
        else if(randNum < prob8)
            chooseNum = 8;
        else if(randNum < prob16)
            chooseNum = 16;
        //设置游戏初始化的最初开始的坐标(x,y)
        int x = indexSpace[randPlace]/4;
        int y = indexSpace[randPlace]%4;
        //qDebug("---------- %d %d----------",x,y);
        data[x][y] = chooseNum;
        gradeUp += 2*chooseNum*gradeUpCoefficient;
        grade = gradeBasic + gradeUp;
        return true;
    }
    else
    {
        return false;
    }
}

void GameLogic::process(int cmd)
{
    switch(cmd)
    {
    case CMD_UP:
        moveUp();
        break;
    case CMD_DOWN:
        moveDown();
        break;
    case CMD_LEFT:
        moveLeft();
        break;
    case CMD_RIGHT:
        moveRight();
        break;
    }
    //随机创建两个数字并添加
    createNum();
    createNum();
    step++;
}

void GameLogic::voice_key()
{
    //添加按键背景音乐
    QSoundEffect *voice_key = new QSoundEffect();
    voice_key->setSource(QUrl::fromLocalFile(":/keyTone.wav"));
    voice_key->setVolume(1.0);
    voice_key->play();
}

void GameLogic::moveUp()
{
    for(int j=0; j<COL; j++)
    {
        //取出所有非零元素
        int t[10] = {0};
        int cnt = 0;
        for(int i=0; i<ROW; i++)
            if(data[i][j])
                t[cnt++] = data[i][j];

        for(int k=0; k<cnt-1; k++)
        {
            if(t[k]==t[k+1])
            {
                gradeBasic += t[k];
                t[k] *= 2;
                t[k+1] = 0;
            }
        }
        //将合并后的非零元素填入data中
        int n = 0;
        for(int k=0; k<cnt; k++)
        {
            if(t[k])
                data[n++][j] = t[k];
        }
        //尾部补零
        for(; n<ROW; n++)
        {
            data[n][j] = 0;
        }
    }
    voice_key();
}

void GameLogic::moveDown()
{
    for(int j=0; j<COL; j++)
    {
        int t[10];
        int cnt = 0;

        for(int i=ROW-1; i>=0; i--)
            if(data[i][j])
                t[cnt++] = data[i][j];

        for(int k=0; k<cnt-1; k++)
        {
            if(t[k]==t[k+1])
            {
                gradeBasic += t[k];
                t[k] *= 2;
                t[k+1] = 0;
            }
        }

        int n = ROW-1;
        for(int k=0; k<cnt; k++)
        {
            if(t[k])    data[n--][j] = t[k];
        }

        for(; n>=0; n--)
        {
            data[n][j] = 0;
        }
    }
    voice_key();
}

void GameLogic::moveLeft()
{
    for(int i=0; i<ROW; i++)
    {
        int t[10];
        int cnt = 0;
        for(int j=0; j<COL; j++)
            if(data[i][j])    t[cnt++] = data[i][j];

        for(int k=0; k<cnt-1; k++)
        {
            if(t[k]==t[k+1])
            {
                gradeBasic += t[k];
                t[k] *= 2;
                t[k+1] = 0;
            }
        }

        int n = 0;
        for(int k=0; k<cnt; k++)
        {
            if(t[k])    data[i][n++] = t[k];
        }

        for(; n<COL; n++)
        {
            data[i][n] = 0;
        }
    }
    voice_key();
}

void GameLogic::moveRight()
{
    for(int i=0; i<ROW; i++)
    {
        int t[10];
        int cnt = 0;
        for(int j=COL-1; j>=0; j--)
            if(data[i][j])    t[cnt++] = data[i][j];

        for(int k=0; k<cnt-1; k++)
        {
            if(t[k]==t[k+1])
            {
                gradeBasic += t[k];
                t[k] *= 2;
                t[k+1] = 0;
            }
        }

        int n = COL-1;
        for(int k=0; k<cnt; k++)
        {
            if(t[k])    data[i][n--] = t[k];
        }

        for(; n>=0; n--)
        {
            data[i][n] = 0;
        }
    }
    voice_key();
}

int GameLogic::judge()
{
    //赢得游戏
    for (int i=0; i<ROW; i++)
    {
        for (int j=0; j<COL; j++)
        {
            if (data[i][j] == 2048)
            {
                return STAT_WIN;
            }
        }
    }
    //横向检查
    for (int i=0; i<ROW; i++)
    {
        for (int j=0; j<COL-1; j++)
        {
            if (!data[i][j] || (data[i][j] == data[i][j+1]))
            {
                return STAT_PROCESS;
            }
        }
    }
    //纵向检查
    for (int j=0; j<COL; j++)
    {
        for (int i=0; i<ROW-1; i++)
        {
            if (!data[i][j] || (data[i][j] == data[i+1][j]))
            {
                return STAT_PROCESS;
            }
        }
    }
    //不符合上述两种状况，游戏结束
    return STAT_LOSE;
}

bool GameLogic::getGameStart()
{
    return gameStart;
}

void GameLogic::setGameStart(bool flag)
{
    gameStart = flag;
}

void GameLogic::setGradeUpCoefficient(float i)
{
    gradeUpCoefficient = i;
}

int GameLogic::getData(int i, int j)
{
    return data[i][j];
}

int GameLogic::getGrade()
{
    return grade;
}

int GameLogic::getGradeBasic()
{
    return gradeBasic;
}

int GameLogic::getGradeUp()
{
    return gradeUp;
}

int GameLogic::getStep()
{
    return step;
}
