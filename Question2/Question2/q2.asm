.586	; 586 processor 
.model flat,stdcall
.stack 4096
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
ExitProcess PROTO, dwExitCode:DWORD

.data
	; variables

.code
	main PROC c
	; assembily instructions

	INVOKE Exitprocess, 0 
	main endp

end