.586
.model flat 

public _task1

.data
sz dd ?
i dd ?
greater dd 0
smaller dd 0
.code 

_task1 proc 
	push ebp 
	mov ebp,esp 
	mov ebx, [ebp+8] ;address
	mov ecx, [ebp+12]  ;size
	mov sz, ecx
	
	mov esi, 0
	_loop_out :
		mov eax, [ebx+esi*4]
		
		mov greater, 0
		mov smaller, 0
		
		mov edi, 0
		cmp_loop :
			mov edx, [ebx+edi*4]
			cmp edx, eax
			je cont_
			jl sm_
			inc greater
			jmp cont_
			sm_ :
			inc smaller
			cont_ :
		inc edi
		cmp edi, ecx
		jl cmp_loop
		
		mov eax, greater
		cmp eax, smaller
		jne _skip
		add eax, smaller
		inc eax
		cmp eax, sz
		je _found
		_skip :
		
	inc esi
	cmp esi, ecx
	jl _loop_out
	
	_not_found :
	mov eax, -1
	jmp _return
	
	_found :
	mov eax, esi
	
	_return :
	pop ebp
	ret  
_task1 endp  
end 