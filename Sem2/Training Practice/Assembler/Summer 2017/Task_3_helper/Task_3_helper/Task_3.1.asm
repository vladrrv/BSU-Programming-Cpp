.386
.model flat, stdcall
option casemap:none
include \masm32\include\masm32.inc
includelib \masm32\lib\masm32.lib

public Task_31

.data
request_abc db 10,13,"Enter a, b, c: ",10,13,0
request_eps db 10,13,"Enter precision (epsilon): ",10,13,0
nline db 10,13,0
result_capt db 10,13,"Root on [-a, b] segment: ", 0
noroot_capt db 10,13,"No roots on [-a, b] segment!", 0
dif_sign db 10,13,"Different signs",10,13,0
same_sign db 10,13,"Same signs",10,13,0
buf db 256 dup(0)

a_coef dq ?
b_coef dq ?
c_coef dq ?
two dq 2.0

.code 


Fx proc x:qword ;  x^3+ax^2+bx+c
    fld x
    fadd a_coef
    fmul x
    fadd b_coef
	fmul x
	fadd c_coef
	ret
Fx endp


CheckSign proc left_x:qword, right_x:qword
    invoke Fx, left_x
    invoke Fx, right_x
	fmul
	fldz
	fcompp
	fstsw ax
	sahf
	jnc lbl_l_diff
	mov eax, 1
	jmp lbl_fin
	lbl_l_diff :
	mov eax, 0
	lbl_fin :
	ret
CheckSign endp


RootSearch proc left_end:qword, right_end:qword, eps:qword, root:ptr qword
	mov edi, [root]
	lbl_loop :
		invoke Fx, left_end
		fldz
		fcompp
		fstsw ax
		sahf
		jz lbl_root_l

		invoke Fx, right_end
		fldz
		fcompp
		fstsw ax
		sahf
		jz lbl_root_r

		lbl_checkends:
		invoke CheckSign, left_end, right_end
		cmp eax, 0
		je lbl_proceed
		fld left_end
		fcom right_end
		fstsw ax
		sahf
		jnc lbl_noroot
		fadd eps
		fstp left_end
		jmp lbl_checkends

		lbl_proceed:
		fld right_end
		fld left_end
		fsub
		fld eps
		fcomp
		fstsw ax
		sahf
		jnc lbl_endsearch

		fld two
		fdiv
		fld left_end
		fadd
		fstp qword ptr [edi]
		
		invoke CheckSign, left_end, qword ptr [edi]
		cmp eax, 0
		je lbl_dif
		fld qword ptr [edi]
		fstp left_end
		jmp lbl_cont
		lbl_dif:
		fld qword ptr [edi]
		fstp right_end
		lbl_cont:
		jmp lbl_loop

	lbl_root_l :
	fld left_end
	fstp qword ptr [edi]
	ret

	lbl_root_r :
	fld right_end
	fstp qword ptr [edi]

	lbl_endsearch:
	ret
	lbl_noroot:
	invoke StdOut, addr noroot_capt
	fstp st
	ret
RootSearch endp


Task_31 proc
local l_x:qword
local r_x:qword
local eps:qword
local res:qword
	finit
	invoke StdOut, addr request_abc
	invoke StdIn, addr buf, 256
	invoke StrToFloat, addr buf, addr a_coef
	invoke StdIn, addr buf, 256
	invoke StrToFloat, addr buf, addr b_coef
	invoke StdIn, addr buf, 256
	invoke StrToFloat, addr buf, addr c_coef
	invoke StdOut, addr request_eps
	invoke StdIn, addr buf, 256
	invoke StrToFloat, addr buf, addr eps
	
	fld a_coef
	fchs
	fstp l_x
	fld b_coef
	fstp r_x
	fld l_x
	fcomp r_x
	fstsw ax
	sahf
	jc lbl_noswap
	fld l_x
	fld r_x
	fstp l_x
	fstp r_x
	lbl_noswap:
	invoke RootSearch, l_x, r_x, eps, addr res
	invoke FloatToStr, qword ptr res, addr buf
	invoke StdOut, addr result_capt
	invoke StdOut, addr buf

	lbl_return :
	ret
Task_31 endp

end 