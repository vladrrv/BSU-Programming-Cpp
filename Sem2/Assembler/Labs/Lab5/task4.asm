.586
.model flat 

public _task4

.data
sz dd ?
max_rep dd 1
mr_ind dd 0
.code 

_task4 proc 
	push ebp 
	mov ebp,esp 
	mov ebx, [ebp+8] ;address
	mov ecx, [ebp+12]  ;size
	mov sz, ecx
	
	mov esi, 0
	_loop_out :
		mov eax, [ebx+esi*4]
		mov edx, 0 ;repetitions counter
		mov edi, 0
		cmp_loop :
			cmp eax, [ebx+edi*4]
			jne cont_
			inc edx
			cont_ :
		inc edi
		cmp edi, sz
		jl cmp_loop
		
		cmp edx, max_rep
		jle _skip
		mov max_rep, edx
		mov mr_ind, esi
		_skip :
		
	inc esi
	cmp esi, sz
	jl _loop_out
	
	cmp max_rep, 1
	jg _found
	mov eax, -1
	jmp _return
	
	_found :
	mov eax, mr_ind
	
	_return :
	pop ebp
	ret  
_task4 endp  
end 