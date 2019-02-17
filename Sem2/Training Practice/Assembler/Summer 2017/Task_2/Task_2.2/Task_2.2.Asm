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
words1 dd 128 dup(0)
words2 dd 128 dup(0)
w1counter dd 0
w2counter dd 0
request_str db "Enter string: ", 0
result_caption db 10,13,"Result: ", 0
buf db 256 dup(0)
buf2 db 256 dup(0)
.code

;SHITCODE - NEED TO REWRITE ->
Parse proc str_addr:dword, w1_addr:dword, w2_addr:dword
	mov esi, str_addr
	mov eax, 0
	mov edx, 0 ;length of cur.word
	mov ecx, 1 ;isdigit flag
	lbl_loop :
		mov al, byte ptr [esi]
		cmp al, ' '
		je lbl_endofword
		cmp al, 0
		je lbl_endofstr
		cmp ecx, 0
		je lbl_cont
		cmp al, '0'
		jl lbl_notdigit
		cmp al, '9'
		jle lbl_isdigit
		
		lbl_notdigit :
		mov ecx, 0
		mov edi, w2_addr
		mov [edi], esi
		sub [edi], edx
		add w2_addr, 4
		inc w2counter
		jmp lbl_cont
		
		lbl_isdigit :
		inc edx
		cmp edx, 1
		jg lbl_cont
		push esi
		jmp lbl_cont
		
		lbl_endofword :
		cmp ecx, 0
		je lbl_res
		mov edi, w1_addr
		pop [edi]
		add w1_addr, 4
		inc w1counter
		lbl_res :
		mov edx, 0
		mov byte ptr [esi], 0
		mov ecx, 1
		lbl_cont :
		inc esi
		jmp lbl_loop
	lbl_endofstr :
	cmp ecx, 0
	je lbl_ret
	mov edi, w1_addr
	pop [edi]
	add w1_addr, 4
	inc w1counter
	lbl_ret :
	ret
Parse endp

Merge proc str_addr:dword, w1_addr:dword, w2_addr:dword
	cld
	cmp w1counter, 0
	je lbl_next
	mov edi, str_addr
	lea ebx, words1
	lbl_loop_1 :
		mov esi, [ebx]
		invoke StrLen, esi
		mov ecx, eax
		rep movsb
		mov byte ptr [edi], ' '
		inc edi
		add ebx, 4
		dec w1counter
		jnz lbl_loop_1
	lbl_next :
	cmp w2counter, 0
	je lbl_done
	lea ebx, words2
	lbl_loop_2 :
		mov esi, [ebx]
		invoke StrLen, esi
		mov ecx, eax
		rep movsb
		mov byte ptr [edi], ' '
		inc edi
		add ebx, 4
		dec w2counter
		jnz lbl_loop_2
	lbl_done :
	dec edi
	mov byte ptr [edi], 0
	lbl_ret :
	ret
Merge endp

mainCRTStartup proc
	invoke StdOut, addr request_str
	invoke StdIn, addr buf, 256
	invoke StrLen, addr buf
	mov ecx, eax
	lea esi, buf
	lea edi, buf2
	cld
	rep movsb
	invoke Parse, addr buf2, addr words1, addr words2
	invoke Merge, addr buf, words1, words2
	invoke StdOut, addr result_caption
	invoke StdOut, addr buf
	invoke StdIn, addr buf, 256
	invoke ExitProcess, 0
mainCRTStartup endp

end 