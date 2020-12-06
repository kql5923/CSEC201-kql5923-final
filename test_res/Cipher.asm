.586
.model flat, stdcall
.stack 2096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib

ExitProcess PROTO, dwExitCode: DWORD
extern scanf:NEAR
extern malloc:NEAR
extern printf:NEAR

.data
	format_s BYTE "%s", 0
	format_sn BYTE "%s", 0Ah, 0
	msg BYTE "Enter a word: ", 0
	; Do not declare any other variables here

.code

	caesar_cipher:
	


	main PROC c
		push ebp
		mov ebp, esp
		sub esp, 20

		;printf("Enter a word: ")
		push offset msg
		call printf
		add esp, 4

		;scanf("%s", plaintext)
		lea eax, [ebp-20]
		push eax
		push offset format_s 
		call scanf
		add esp, 8

		;caesar_cipher(plaintext)		
		lea eax, [ebp-20]
		push eax
		call caesar_cipher
		add esp, 4

		push eax
		push offset format_sn
		call printf  
		add esp, 8

		add esp, 20
		pop ebp
		INVOKE ExitProcess, 0
	main endp

end