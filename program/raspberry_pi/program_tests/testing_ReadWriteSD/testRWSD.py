import time

path = 'test.txt'

f = open(path, mode='w')
start = time.time()
for i in range(1000):
	f.write(str(i)+"\n")
elapsed_time= time.time() -start
print ("elapsed_time:{0}".format(elapsed_time))
f.close()
