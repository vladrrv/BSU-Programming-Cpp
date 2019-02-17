.386 
.model flat, stdcall
option casemap:none
include \masm32\include\kernel32.inc
include \masm32\include\masm32.inc
include \masm32\include\user32.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\masm32.lib
includelib \masm32\lib\user32.lib

.data
ret_addr dd 0
rows dd 32 dup(0) ; array of matrix row addresses
mem_chunk db 4096 dup(0) ; memory allocation for 'text' matrix
matrix db 1024 dup(0) ; memory allocation for byte matrix
request_n db "Enter n: ", 0
request_matrix db 10,13,"Enter matrix: ",10,13,0
result_caption db 10,13,"Result: ", 0
result dd 0
n dd 0
buf db 256 dup(0)
.code

parse_row proc par1:dword, par2:dword, par3:dword
	mov esi, par1 ;row address
	;mov ecx, par2 ;row index
	mov edi, par3 ;matrix address
	mov eax, 0
	mov ebx, 0 ;length of cur.word
	
	lbl_loop :
		xor eax, eax
		mov al, byte ptr [esi]
		cmp al, ' '
		je lbl_skip
		cmp al, 0
		je lbl_return
		
		inc ebx
		cmp ebx, 1
		jg lbl_cont
		
		invoke atol, esi
		mov ecx, par2
		imul ecx, n
		mov byte ptr [edi+ecx], al
		inc edi
		jmp lbl_cont
		
		lbl_skip :
		mov ebx, 0
		lbl_cont :
		inc esi
		jmp lbl_loop
		
	lbl_return :
	mov eax, [ebp+16]
	ret
parse_row endp  

input_rows proc 
	invoke StdOut, addr request_n
	invoke StdIn, addr buf, 256
	invoke atol, addr buf 
	mov n, eax
	invoke StdOut, addr request_matrix
	lea esi, mem_chunk
	mov edi, 0
	mov ecx, n
	lbl_loop :
		push ecx
		invoke StdIn, esi, 256
		mov rows[edi*4], esi
		inc edi
		invoke StrLen, esi
		add esi, eax
		inc esi
		pop ecx
	loop lbl_loop
	lbl_return :
	lea eax, rows
	ret  
input_rows endp


mainCRTStartup proc
	invoke input_rows
	mov ecx, 0
	lbl_parse_loop :
		push ecx
		mov eax, rows[ecx*4]
		invoke parse_row, eax, ecx, addr matrix
		pop ecx
		inc ecx
		cmp ecx, n
		jl lbl_parse_loop
		
	mov edx, 1
	mov esi, 0
	lbl_loop_i :
		mov edi, 0
		lbl_loop_j :
			cmp esi, edi
			jle lbl_skip_higher
			mov ecx, n
			imul ecx, esi
			mov eax, 0
			mov al, byte ptr matrix[ecx+edi]
			imul edx, eax
			lbl_skip_higher :
			inc edi
			cmp edi, n
			jl lbl_loop_j
		inc esi
		cmp esi, n
		jl lbl_loop_i
	mov result, edx
	invoke StdOut, addr result_caption
	invoke ltoa, result, addr buf
	invoke StdOut, addr buf
	invoke StdIn, addr buf, 256
	invoke ExitProcess, 0
mainCRTStartup endp
end 