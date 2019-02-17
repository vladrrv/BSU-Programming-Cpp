.586
.model flat 

public _task1

.code 

_task1 proc 
	push ebp 
	mov ebp,esp 
	mov ebx, [ebp+8] ;num
	mov ecx, [ebp+12]  ;power
	
	mov eax, 1
	_loop_out :
		imul eax, ebx
	loop _loop_out
	
	_return :
	pop ebp
	ret  
_task1 endp  
end 