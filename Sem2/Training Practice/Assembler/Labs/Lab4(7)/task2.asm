.586
.model flat 

public _task2

.data
max_rep dd 1
mr_ind dd 0
.code 

_task2 proc 
	push ebp 
	mov ebp,esp 
	mov ebx, [ebp+8] ;address
	mov ecx, [ebp+12]  ;size
	dec ecx
	mov esi, 0
	mov edx, 0 ;repetitions counter
	_loop_out :
		mov al, byte ptr [ebx+esi]
		mov edi, esi
		inc edi
		cmp al, byte ptr [ebx+edi]
		jne _reset
		inc edx
		cmp esi, ecx
		jl _no_reset
		_reset :
		cmp edx, max_rep
		jle _not_max
		mov max_rep, edx
		mov mr_ind, esi
		_not_max :
		mov edx, 1
		_no_reset :
	inc esi
	cmp esi, ecx
	jl _loop_out
	
	mov al, byte ptr mr_ind
	inc al
	sub al, byte ptr max_rep
	
	mov ah, byte ptr max_rep
	
	_return :
	pop ebp
	ret  
_task2 endp  
end 