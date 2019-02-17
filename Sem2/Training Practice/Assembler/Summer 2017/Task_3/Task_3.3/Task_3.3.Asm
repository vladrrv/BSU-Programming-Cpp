.386
.model flat, stdcall
option casemap:none
include \masm32\include\windows.inc
include \masm32\include\masm32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\masm32.lib
includelib \masm32\lib\kernel32.lib


.data
header db "Enter dx step (dx > 0): ",10,13,0
res_caption db "Integral of (x^2+sinx) = ",0
nline db 10,13,0
buf db 256 dup(0)
two dq 2.0
ten dq 10.0

.code

F_x proc x:qword
    fld x
	fmul st,st
	fld x
	fsin
	fadd
	ret
F_x endp

FInt proc left_x:qword, right_x:qword
	fld right_x
	fsub left_x
	invoke F_x, left_x
	invoke F_x, right_x
	fadd
	fdiv two
	fmul
	ret
FInt endp

Calc proc eps:qword, res:ptr qword
local pi2:qword
local x1:qword
local x2:qword
	fldpi
	fmul two
	fstp pi2
	fldz
	fst x1
	fstp x2
	mov edi, [res]
	lbl_loop:
		fld x2
		fcom pi2
		fstsw ax
		sahf
		jnc lbl_done
		fst x1
		fadd eps
		fstp x2
		invoke FInt, x1, x2
		fadd qword ptr [edi]
		fstp qword ptr [edi]
		jmp lbl_loop
	lbl_done:
	fstp st

	ret
Calc endp


mainCRTStartup proc
local eps:qword
local res:qword
	finit
	fldz
	fstp res
	invoke StdOut, addr header
	invoke StdIn, addr buf, 256
	invoke StrToFloat, addr buf, addr eps

	invoke Calc, eps, addr res
	invoke FloatToStr, res, addr buf
	
	invoke StdOut, addr res_caption
	invoke StdOut, addr buf

	lbl_return:
	invoke StdIn, addr buf, 256
	invoke ExitProcess, 0
mainCRTStartup endp

end 