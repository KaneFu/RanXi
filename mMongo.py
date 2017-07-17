#!/usr/bin/python

import datetime
import pandas as pd
import pymongo
import sys
import pytz
from babel.util import UTC
import datetime
import numpy as np
import os

client = pymongo.MongoClient("192.168.10.252",27017)
db_name = 'FutureData'
db = client[db_name]
# global collection
tick_col = db['tick']
instrument_col = db['Instruments']
traday_col = db['TradingDate']
df_1min = []

start = datetime.datetime(2016,1,1)
end = datetime.datetime(2016,1,10)


tradays = traday_col.find({"date":{'$gte':start,'$lte':end}})
dayIdx = []
for day in tradays:
	dayIdx.append(day['date'])
dayIdx = pd.Index(dayIdx).date

instruments = instrument_col.find({})
instruments_list = []
for instrument in instruments:
	instruments_list.append(instrument['instrumentID'])

for day in dayIdx:
	dayStr = day.strftime('%Y%m%d')
	if not os.path.exists('data/'+dayStr):
		os.mkdir('data/'+dayStr)
	for instru in instruments_list:
		askP = []
		askV = []
		bidP = []
		bidV = []
		c = []
		i = []
		t = []
		v = []
		startTime = datetime.datetime.combine(day,datetime.time(0,0,0))
		endTime = datetime.datetime.combine(day,datetime.time(23,59,59))
		ticks = tick_col.find({"instrumentID":instru,"t":{'$gte':startTime,'$lte':endTime}})
		
		if ticks.count()>0:
			for tick in ticks:
				askP.append(tick['askP'])
				askV.append(tick['askV'])
				bidP.append(tick['bidP'])
				bidV.append(tick['bidV'])
				c.append(tick['c'])
				i.append(tick['i'])
				v.append(tick['v'])
				t.append(tick['t'])
			instru_df = pd.DataFrame({"t":t,"c":c,"v":v,"i":i,"askP":askP,"askV":askV,"bidP":bidP,"bidV":bidV}).set_index('t')
			instru_df.to_csv('data/'+dayStr+'/'+instru+'.csv')





# datas = tick_col.find({"instrumentID":'bu0',"startTime":{'$gte':start,'$lt':end}})
