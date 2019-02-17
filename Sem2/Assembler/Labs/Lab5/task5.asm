.586
.model flat 

public _task5

.data
sz dd ?
min_sum dd 90
ms_ind dd 0
.code 

_task5 proc 
	push ebp 
	mov ebp,esp 
	mov ebx, [ebp+8] ;address
	mov ecx, [ebp+12]  ;size
	mov sz, ecx
	
	mov esi, 0
	_loop_out :
		mov eax, [ebx+esi*4]
		mov ecx, 0 ;digit sum
		push ebx
		dig_loop :
			mov ebx, 10
			cdq
			idiv ebx
			add ecx, edx
			cont_ :
		cmp eax, 0
		jg dig_loop
		pop ebx
		
		cmp ecx, min_sum
		jge _skip
		mov min_sum, ecx
		mov ms_ind, esi
		_skip :
		
	inc esi
	cmp esi, sz
	jl _loop_out
	
	mov eax, ms_ind
	
	_return :
	pop ebp
	ret  
_task5 endp  
end 