import time

path = '~/Documents/test.txt'

f = open(path)
start = time.time()
for i in range(1000):
	f.write(str(i)+"\n")
elapsed_time= time.time() -start
print ("elapsed_time:{0}".format(elapsed_time))
f.close()
