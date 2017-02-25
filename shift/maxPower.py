# -*- coding: utf-8 -*-
"""
Created on Fri Feb 24 21:38:25 2017

@author: Joseph
"""

digits = {'1':2, '2':5,'3':5, '4':4, '5':5, '6':6, '7':3, '8':7, '9':5, '0':6}
 #volts
maxPower = .1 #watts
inputVoltage = 5 #volts
#resistor = input("enter resistor value")
maxSegments = 21
forwardCurrent = 

mostPower = maxSegments * 


'''
for k,v in digits.items():
   print("digit:%d number of segments:%d"%(k,v) )
timesNum = []
for num in range(1,13):
    for i in range(0,60):
        timesNum.append(100*num + i)
times = []   
for num in timesNum:
    times.append(str(num))
 
maxSegments = 0           
for time in times:
    maxS = 0
    for num in time:
        maxS += digits[num]
    if maxS > maxSegments :
        maxSegments = maxS
        print(time)
print(maxSegments)
'''