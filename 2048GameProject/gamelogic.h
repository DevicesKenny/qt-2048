//游戏逻辑代码头文件
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <iostream>
#include <QSoundEffect>

#define ROW 4
#define COL 4

//控制上下左右移动的标志枚举类型
enum CMD
{
    CMD_UP,
    CMD_DOWN,
    CMD_LEFT,
    CMD_RIGHT,
};

//状态提示枚举类型
enum STAT
{
    STAT_WAIT,
    STAT_PROCESS,
    STAT_WIN,
    STAT_LOSE,
};

class GameLogic
{
public:
    GameLogic();
    bool createNum();                       //创建数字2,4,6,8
    void process(int cmd);                  //游戏过程
    int judge();                            //判定游戏输赢
    void initAll();                         //初始化游戏
    void calProb();                         //计算2,4,6,8出现的概率

    void moveUp();                          //上移
    void moveDown();                        //下移
    void moveLeft();                        //左移
    void moveRight();                       //右移

    bool getGameStart();                    //得到游戏开始状态，反馈
    void setGameStart(bool);                //设置游戏开始
    void setGradeUpCoefficient(float);      //设置分数加成的比例(即获取进度条的数值)
    int getData(int,int);                   //获取每个网格中的数据
    int getGrade();                         //游戏总分
    int getGradeBasic();                    //游戏基础得分
    int getGradeUp();                       //游戏加成得分
    int getStep();                          //游戏步数
    void voice_key();                       //游戏按键背景音

private:
    bool gameStart;                         //游戏开始
    int data[ROW][COL];                     //数据(数字)
    float grade;                            //总分
    int gradeBasic;                         //基础得分
    float gradeUp;                          //加成得分
    int step;                               //步数
    float gradeUpCoefficient;               //加成比例
    int prob2;                              //2出现的概率
    int prob4;                              //4出现的概率
    int prob8;                              //8出现的概率
    int prob16;                             //16出现的概率

};

#endif // GAMELOGIC_H
