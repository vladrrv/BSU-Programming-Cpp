.586
.model flat 

public _task2

.data
.code 

_task2 proc 
	push ebp 
	mov ebp, esp 
	mov edi, [ebp+8] ;string address
	mov ecx, [ebp+12] ;string length
	inc ecx
	mov ebx, ecx
	mov esi, [ebp+16] ;word address
	;mov ecx, [ebp+20] ;word length
	
	mov al, ' '
	cld
	_loop :
		repne scasb ; scan for whitespace
		sub ebx, ecx
		dec ebx
		cmp ebx, [ebp+20] ; compare with word length
		jne _skip
		sub edi, [ebp+20]
		dec edi
		push ecx
		mov ecx, ebx
		repe cmpsb
		jecxz _found
		add edi, ecx
		inc edi
		mov esi, [ebp+16]
		pop ecx
		_skip :
		mov ebx, ecx
		cmp ecx, 0
		jg _loop
	
	_notfound :
	mov eax, 0
	jmp _return
	
	_found :
	pop ecx
	mov eax, 1
	_return :
	pop ebp
	ret  
_task2 endp  
end 