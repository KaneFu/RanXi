#!/usr/bin/python

import datetime
import pandas as pd
import pymongo
import sys
import pytz
from babel.util import UTC

def GetFutureMinData(instrumentid):   
    fPdData = []
    client = pymongo.MongoClient("192.168.10.252",27017)
    db_name = 'FutureData'
    db = client[db_name]
    global collection_useraction
    collection_useraction = db['bar']
    df_1min = []

    datas = collection_useraction.find({"instrumentID":instrumentid,"type":"1min","startTime":{'$gte':datetime.datetime(2017, 4, 15, 1, 0),'$lt':datetime.datetime(2017, 4, 30, 23, 0)}})
    lastTime = datas[0]['startTime'].replace(tzinfo=UTC)

    for data in datas:
       data['startTime']=data['startTime'].replace(tzinfo=UTC)
       data['endTime']=data['endTime'].replace(tzinfo=UTC)
       if data['startTime'] == data['endTime']:
           continue
       timeDiff = lastTime - data['startTime']
       while timeDiff > datetime.timedelta(minutes=1) and timeDiff < datetime.timedelta(minutes=15):
           lastTime = lastTime - datetime.timedelta(minutes=1)
           print str(data['c']) + "," +  str(lastTime)
           fPdData.append(str(data['c']) + "," +  str(lastTime))
           timeDiff = lastTime - data['startTime']
       fPdData.append(str(data['c']) + "," +  str(data['startTime']))
       lastTime = data['startTime']

    fPdData.reverse()
    if fPdData:
        with open(instrumentid + ".data", "w") as outputFile:
            for data in fPdData:
                outputFile.write(str(data) + "\n")
       
if __name__ == '__main__':  
    GetFutureMinData("ru1709")    
    GetFutureMinData("ru1705")    
    GetFutureMinData("rb1710")    
    GetFutureMinData("rb1705")    
