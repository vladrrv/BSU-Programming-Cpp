.586
.model flat, stdcall

public parse

.data
.code 

parse proc str_addr:dword, len:dword, w_addr:dword
	mov esi, str_addr ;address
	mov ecx, len ;length
	mov edi, w_addr ;address of words array
	mov eax, 0
	mov edx, 0 ;length of cur.word
	
	lbl_loop :
		mov al, byte ptr [esi]
		cmp al, '_'
		je lbl_isletter
		cmp al, '0'
		jl lbl_skip
		cmp al, '9'
		jle lbl_isletter
		cmp al, 'A'
		jl lbl_skip
		cmp al, 'Z'
		jle lbl_isletter
		cmp al, 'a'
		jl lbl_skip
		cmp al, 'z'
		jg lbl_skip
		lbl_isletter :
		inc edx
		cmp edx, 1
		jg lbl_cont
		mov [edi], esi
		add edi, 4
		jmp lbl_cont
		
		lbl_skip :
		mov edx, 0
		mov byte ptr [esi], 0
		lbl_cont :
		inc esi
		loop lbl_loop
		
	mov eax, [ebp+16]
	
	lbl_return :
	ret  
parse endp

end 