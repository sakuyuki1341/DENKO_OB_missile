import time
import math
import pigpio
import MadgwickAHRS


"""-----センサ用i2c初期化-----"""
MPU_WHO_AM_I =		0x75	# Read Only
MPU_PWR_MGMT_1 =	0x6B	# Read and Write
MPU_ADDRESS =		0x68
MPU_REGISTER =		0x3B	# Read Only

BYTE = 14	# データが格納されているbyte数

# ライブラリ初期化
pi = pigpio.pi()
# i2c通信開始
sensor = pi.i2c_open(1, MPU_ADDRESS)
# MPUの動作モード設定
pi.i2c_write_byte(1, MPU_PWR_MGMT_1)
pi.i2c_write_byte(1, 0x00)
"""------------------------"""


"""-----Madgwick初期化------"""
q = MadgwickAHRS.MadgwickAHRS()
"""------------------------"""


with open('log.txt', mode='w') as f:
	while (True):
		start = time.time()

		pi.i2c_write_byte(1, MPU_REGISTER)

		(b, d) = pi.i2c_read_i2c_block_data(sensor, MPU_REGISTER, BYTE)

		axRaw = d[0] << 8 | d[1]
		ayRaw = d[2] << 8 | d[3]
		azRaw = d[4] << 8 | d[5]
		Temperature = d[6] << 8 | d[7]
		gxRaw = d[8] << 8 | d[9]
		gyRaw = d[10] << 8 | d[11]
		gzRaw = d[12] << 8 | d[13]

		acc_x = axRaw / 16384.0
		acc_y = ayRaw / 16384.0
		acc_z = azRaw / 16384.0

		gyro_x = gxRaw / 131.0
		gyro_y = gyRaw / 131.0
		gyro_z = gzRaw / 131.0

		q.MadgwickAHRSupdateIMU(
			gx = gyro_x*math.pi/180.0,
			gy = gyro_y*math.pi/180.0,
			gz = gyro_z*math.pi/180.0,
			ax = acc_x,
			ay = acc_y,
			az = acc_z
		)

		print("-"*10)
		print(u"Roll")
		print(q.GetRoll())
		print(u"Pitch")
		print(q.GetPitch())
		print(u"Yaw")
		print(q.GetYaw())
		print('\n')

		while time.time() == start:
			pass
		dotime = time.time() - start
		q.sampleFreq = 1/dotime

#		print('{0:04.3f}, {1:04.3f}, {2:04.3f}, {3:04.3f}, {4:04.3f}, {5:04.3f}'.format(acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z))
		logline = str(dotime) + ', ' + str(gyro_x) + ', ' + str(gyro_y) + ', ' + str(gyro_z) + ', ' + str(acc_x) + ', ' + str(acc_y) + ', ' + str(acc_z)
		f.write(logline)
