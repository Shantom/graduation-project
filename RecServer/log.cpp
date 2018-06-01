#include "log.h"

Log::Log(QObject *parent) : QObject(parent)
{

}

void Log::log_new(QString source)
{
    emit writeLogs(source+QString("\n\t新用户接入\n"));
}

void Log::log_query(QString source, QString user, bool isDebug, QString errStr)
{
    QString info=source;
    info+=QString(" 新查询\n\t用户ID:");
    info+=user;
    if(isDebug)
        info+=QString("\n\t(测试用集)");
    info+=QString("\n\t错误信息：");
    info+=errStr;
    info+=QString("\n");
    emit writeLogs(info);
}

void Log::log_login(QString source, QString user, int id, QString pwd)
{
    QString info = source;
    if(id)
    {
        info+=QString(" 新登录\n\t用户ID:%1").arg(id);
        info+=QString("\n\t密码:\n")+pwd;
        info+=QString("\n");
    }
    else
    {
        info+=QString(" 新登录\n\t用户名不存在或密码不正确\n\t");
        info+=QString("Name/ID:")+user;
        info+=QString("\n\t密码:\n")+pwd;
        info+=QString("\n");
    }
    emit writeLogs(info);
}

void Log::log_signup(QString source, QString user, int id, QString pwd)
{
    QString info = source;
    if(id)
    {
        info+=QString(" 新注册\n\t用户名:")+user;
        info+=QString("\n\tID:%1").arg(id);
        info+=QString("\n\t密码:\n")+pwd;
        info+=QString("\n");
    }
    else
    {
        info+=QString(" 新注册\n\t用户名存在\n\t");
        info+=QString("Name/ID:")+user;
        info+=QString("\n");
    }
    emit writeLogs(info);
}

void Log::log_rating(QString source, QString userID, QString movieID, double rating)
{
    QString info = source;
    info+=QString(" 新评分\n\t用户ID:%1\n\t").arg(userID);
    info+=QString("电影ID:%1\n\t").arg(movieID);
    info+=QString("评分:%1\n").arg(rating);
    emit writeLogs(info);
}
