#!/usr/bin/env python

from random import randint

days_month = [None, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

NUM_DATES = randint(2000, 4000)

dates = []
for i in xrange(NUM_DATES):
    month, year = randint(1, 12), randint(2005, 2010)
    day = randint(1, days_month[month])
    dates.append((year * 100 + month) * 100 + day)
    
dates.sort()

for d in dates:
    print "%02d/%02d/%04d" % (d % 100, (d // 100) % 100, d // 10000)
