.386
.model flat, stdcall
option casemap:none
include \masm32\include\masm32.inc
includelib \masm32\lib\masm32.lib

public Task_34

.data
header db "x = ",0
res_caption db "f(x) = ",0
nline db 10,13,0
buf db 256 dup(0)
two dq 2.0
ten dq 10.0

.code

PowInt proc x:qword
	fld x
	fld1
	fscale
	fstp st(1)
	ret
PowInt endp

PowFloat proc x:qword
    fld x
	f2xm1
	fld1
	fadd
	ret
PowFloat endp

F10PowX proc x:qword, y:ptr qword
local x_int:qword
local x_dec:qword
	mov ebx, 0 ;sign
	mov edi, [y]
	fld x
	fldz
	fcomp x
	fstsw ax
	sahf
	jc lbl_greater0
	mov ebx, 1
	fabs
	lbl_greater0:
	fld ten
	fyl2x
	fld st
	frndint
	fst x_int
	fsub
	fstp x_dec
	invoke PowInt, x_int
	invoke PowFloat, x_dec
	fmul
	cmp ebx, 0
	je lbl_noreverse
	fld1
	fdiv st, st(1)
	lbl_noreverse:
	fstp qword ptr [edi]
	fstp st
	ret
F10PowX endp


Task_34 proc
local res:qword
local x:qword
	finit
	invoke StdOut, addr header
	invoke StdIn, addr buf, 256
	invoke StrToFloat, addr buf, addr x

	invoke F10PowX, x, addr res
	invoke FloatToStr, res, addr buf

	invoke StdOut, addr res_caption
	invoke StdOut, addr buf

	lbl_return:
	ret
Task_34 endp

end 