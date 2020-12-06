


import socket


ip = ""
port = 0

def init():
	ip = input("[str>] IP? ")
	port = input("[int>] port?")

def main():
	print("------------------------------------------")
	print("[Client for cpp server]")
	init()
	print("[Connecting to server...]")
	sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	sock.settimeout(3)
	try:
		sock.connect((ip,port))
	except Exception as e:
		print("[!] Err")
		print(e)
main()