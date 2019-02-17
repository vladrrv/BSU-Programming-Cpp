.386
.model flat, stdcall
option casemap:none
include \masm32\include\masm32.inc
includelib \masm32\lib\masm32.lib

public Task_32

.data
hline db  "+--------------------+-----------------+",10,13,0
header db "| Precision (digits) | Iteration count |",10,13,0
nline db 10,13,0
divider1 db "|          ", 0
divider2 db "         |       ", 0
buf db 256 dup(0)
k_acc dq 0
two dq 2.0
ten dq 10.0
four dq 4.0

.code 


Fk proc k:qword
    fld k
	fmul st,st
	fmul four
	fld1
	fsubp
	fmul k
	fld1
	fdiv st, st(1)
	fstp st(1)
	ret
Fk endp


EvaluateLn2 proc eps:qword, sum:ptr qword
local ln2r:qword
	mov edx, 0 ;iteration count
	;2ln2-1
	fldln2
	fmul two
	fld1
	fsubp st(1), st
	fstp ln2r

	fld eps
	fdiv ten
	fstp eps

	mov edi, [sum]
	lbl_loop:
		fld1
		fadd k_acc
		fstp k_acc
		invoke Fk, k_acc
		inc edx
		fadd qword ptr [edi]
		fstp qword ptr [edi]
		fld ln2r
		fsub qword ptr [edi]
		fabs
		fcomp eps
		fstsw ax
		sahf
		jnc lbl_loop

	ret
EvaluateLn2 endp


Task_32 proc
local iter_count:dword
local eps:qword
local res:qword
	mov iter_count, 0
	finit
	invoke StdOut, addr hline
	invoke StdOut, addr header
	invoke StdOut, addr hline
	fldz
	fstp res
	mov ebx, 0
	fld1
	fstp eps
	lbl_loop_stat:
		inc ebx
		fld eps
		fdiv ten
		fstp eps
		invoke EvaluateLn2, eps, addr res
		add iter_count, edx
		invoke StdOut, addr divider1
		;invoke FloatToStr, qword ptr res, addr buf
		invoke ltoa, ebx, addr buf
		invoke StdOut, addr buf
		invoke StdOut, addr divider2
		invoke ltoa, iter_count, addr buf
		invoke StdOut, addr buf
		invoke StdOut, addr nline
		cmp ebx, 11
		jl lbl_loop_stat
	invoke StdOut, addr hline

	lbl_return:
	ret
Task_32 endp

end 