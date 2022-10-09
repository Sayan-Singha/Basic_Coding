#!/usr/bin/python

import socket as sc
import os, sys
import base64
import threading
from termcolor import colored
from datetime import datetime
from time import sleep




def comm(target, ip):

	global term_words
	def Send(message):
		target.send(message.encode('utf-8'))

	def Recv():
		data = ""		
		while True:
			try:																	# tries to receive 1024 bytes of data from target
				data = data + target.recv(1024).decode('utf-8')							# decodes the utf-8 encoded as sent by the Send() function				
				#print(('\r'+str(ip[0]) + '> ' + data).rjust(50,' '))
				#print('\r\t',end='')
				print('\r',end='')
				print((data + ' <[' + str(ip[0]) + ']').rjust(50,' '))
				print('\n[You]> ',end='')
				for word in term_words:					
					if data.lower().find(word) >= 0:
						#Send("Bye. Take care!")
						quit()
				data=""
			except ValueError:														# ValueError signifies that the data to be received is larger than 1024 bytes
				continue															# goes back to the loop iteration and adds the remaining data from the execution of try block

	if os.name == 'nt':
		print("[+] Connection established from target " + ip[0] + "\n")
	else:
		print(colored("[+] Connection established from target " + ip[0] + "\n", "green"))

	recv_thread = threading.Thread(target=Recv)
	recv_thread.start()
	while True:
		message = input("\n[You]> ")
		Send(message)
		for word in term_words:					
			if message.lower().find(word) >= 0:
				quit()


#"""
if len(sys.argv) != 3:  
	print ("Correct usage: script <IP address> <Port number>") 
	exit()  

connect_ip = sys.argv[1]
conn_port = int(sys.argv[2])
#"""
term_words = ['tata','bye','goodbye']

#connect_ip = '192.168.0.103'
#conn_port = 54321

sock = sc.socket(sc.AF_INET, sc.SOCK_STREAM)
sock.setsockopt(sc.SOL_SOCKET, sc.SO_REUSEADDR, 1)

sock.bind((connect_ip, conn_port))
sock.listen(5)
print('[!] Waiting for incoming connections on port ' + str(conn_port) + '...\n')
while True:
	try:
		target, ip = sock.accept()
		comm(target,ip)
	except Exception as e:
		print(e)
sock.close()

