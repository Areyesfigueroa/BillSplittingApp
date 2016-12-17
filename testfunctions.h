#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include <string>
#include <QtSql>
#include <QDir>
#include <QJsonDocument>

class TestFunctions
{
public:
    TestFunctions();

    static void TestFunction()
    {
        QString pathToDB = getAppPath() + "BillSplittingApp/Database/GroupRecords.db";
        QSqlDatabase localDB = QSqlDatabase::addDatabase("QSQLITE");
        localDB.setDatabaseName(pathToDB);

        if(localDB.open()){
            QSqlQuery queryResult = localDB.exec("SELECT * FROM Groups");
            queryResult.next();
            QString path = getAppPath() +"/BillSplittingApp/" + queryResult.value(3).toString();
            path = path.replace("/", "\\");
            QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(stringFromFile(path).toStdString()));

            if(!doc.isNull()){
                QJsonObject jsonObj = doc.object();
                QJsonArray arr = jsonObj["people"].toArray();
                for(int i= 0; i < arr.count(); i++ )
                    qDebug() << arr[i].toObject()["bill"].toInt();
            }
            else
                qDebug() << "not formatted properly";
        }
    }


    static QString getAppPath()
    {
        std::string pathToAppFolder = QDir::currentPath().toStdString();
        size_t index = pathToAppFolder.find_last_of('/');
        pathToAppFolder.erase(pathToAppFolder.begin()+(++index), pathToAppFolder.end());
        return QString::fromStdString(pathToAppFolder);
    }

    static QString stringFromFile(QString path)
    {

            QString fileString;
            QFile xmlFile;

            xmlFile.setFileName(path);
            if(xmlFile.open(QIODevice::ReadOnly)) {
                     QTextStream textStream(&xmlFile);
                     fileString = textStream.readAll();
            }

            xmlFile.close();
            return fileString;

    }

};

#endif // TESTFUNCTIONS_H
