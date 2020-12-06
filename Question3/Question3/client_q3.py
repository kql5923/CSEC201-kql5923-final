


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
	sock.settimeout(10)
	try:
		sock.connect(("localhost",9999))
		send_str = "...".encode()
		sock.send(send_str)
		recieved = sock.recv(200).decode()
		print("[RECV]")
		print(recieved)

		send_str2 = ".....5555555555555".encode()
		sock.send(send_str2)
		recieved2 = sock.recv(200).decode()
		print("[RECV]")
		print(recieved2)

		recieved3 = sock.recv(200).decode()
		print("[RECV]")
		print(recieved3)

		send_str2 = "512".encode()
		sock.send(send_str2)
		recieved2 = sock.recv(200).decode()
		print("[RECV]")
		print(recieved2)

		



		
	except Exception as e:
		print("[!] Err")
		print(e)
main()