.586
.model flat, stdcall

public IntToHex

.data
.code 

IntToHex proc num:dword, buf:ptr dword
	mov eax, num 
	mov edi, buf
	mov ecx, 0 ;hex length
	lbl_loop :
		mov ebx, 15
		and ebx, eax
		cmp ebx, 10
		jl lbl_decimal
		sub ebx, 10
		add ebx, 'A'
		jmp lbl_put_digit
		lbl_decimal :
		add ebx, '0'
		lbl_put_digit :
		;mov byte ptr [edi], bl
		push ebx
		inc ecx
		;inc edi
		shr eax, 4
		cmp eax, 0
		jg lbl_loop
	
	
	lbl_loop_reverse :
		pop ebx
		mov byte ptr [edi], bl
		inc edi
	loop lbl_loop_reverse
	
	mov byte ptr [edi], 0
	
	lbl_return :
	ret  
IntToHex endp

end 