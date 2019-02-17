.586
.model flat 

public _task3

.data
sz dd ?
i dd ?
sum dd 0
min_dif dd 2147483647
min_index dd ?
.code 

_task3 proc 
	push ebp 
	mov ebp,esp 
	mov ebx, [ebp+8] ;address
	mov ecx, [ebp+12]  ;size
	mov sz, ecx
	
	
	mov esi, 0
	mov eax, 0
	_loop_acc :
		add eax, [ebx+esi*4]
	inc esi
	cmp esi, sz
	jl _loop_acc
	
	mov sum, eax
	
	mov esi, 0
	_loop_out :
		mov eax, [ebx+esi*4]
		imul eax, sz
		cmp eax, sum
		je _found
		jl less_
		sub eax, sum
		jmp cont_
		less_ :
		mov edx, sum
		sub edx,  eax
		mov eax, edx
		cont_ :
		
		cmp eax, min_dif
		jge _skip
		mov min_index, esi
		mov min_dif, eax
		_skip :
		
	inc esi
	cmp esi, sz
	jl _loop_out
	
	_found :
	mov eax, min_index
	
	_return :
	pop ebp
	ret  
_task3 endp  
end 