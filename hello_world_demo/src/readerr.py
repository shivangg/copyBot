import httplib2

http = httplib2.Http()




while True:

	f = http.request("http://192.168.43.205/niyantra/newfolder/leapxdata.txt")

	# with http.request("http://192.168.43.205/niyantra/newfolder/data.txt") as f:
	lineArr=f[1].split('\r\n')
	print lineArr

	string = ""
	for x in lineArr:
		string += str(x) + "\n"

	# print(string)

	text_file = open("youbotJoint.txt", "w")
	text_file.write("%s" % str(string))
text_file.close()
