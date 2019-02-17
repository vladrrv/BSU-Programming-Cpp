.586
.model flat 

public _task1

.data
min_length dd ?

.code 

_task1 proc 
	push ebp 
	mov ebp, esp 
	mov edi, [ebp+8] ;address
	mov ecx, [ebp+12] ;length
	mov ebx, ecx
	mov min_length, ecx
	
	mov al, ' '
	cld
	_loop :
		repne scasb
		sub ebx, ecx
		dec ebx
		cmp ebx, min_length
		jnl _skip
		mov min_length, ebx
		_skip :
		mov ebx, ecx
		cmp ecx, 0
		jg _loop
		
	mov eax, min_length
	
	_return :
	pop ebp
	ret  
_task1 endp  
end 