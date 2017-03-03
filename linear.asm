; -- Machine type PW
; mark_description "Intel(R) C++ Compiler for applications running on IA-32, Version 11.1    Build 20091130 %s";
; mark_description "-c -Ox -Ot -Oy -D WIN32 -D NDEBUG -D _CONSOLE -D _MBCS -EHs -EHc -ML -fp:fast -FAs -Fac:\\Daten\\Visual C\\I";
; mark_description "nterpolatingMemory\\/ -FoRelease/ -W3 -nologo -Wp64 -Zi -Qvc7.1 -Qlocation,link,C:\\Program Files\\Microsoft";
; mark_description " Visual Studio .NET 2003\\Vc7\\bin";
	.686P
 	.387
	OPTION DOTNAME
	ASSUME	CS:FLAT,DS:FLAT,SS:FLAT
_TEXT	SEGMENT PARA PUBLIC FLAT 'CODE'
TXTST0:
; -- Begin  @read_linear@4
; mark_begin;
IF @Version GE 800
  .MMX
ELSEIF @Version GE 612
  .MMX
  MMWORD TEXTEQU <QWORD>
ENDIF
IF @Version GE 800
  .XMM
ELSEIF @Version GE 614
  .XMM
  XMMWORD TEXTEQU <OWORD>
ENDIF
       ALIGN     16
	PUBLIC @read_linear@4
@read_linear@4	PROC NEAR 
; parameter 1(address): ecx
.B1.1:                          ; Preds .B1.0

;;; word_t __fastcall read_linear(address_t address) {

$LN1:
        push      edi                                           ;7.50
$LN3:

;;; 	register word_t rvalue, left_val, right_val;
;;; 	register dword_t value, slope;
;;; 	register address_t left, right;
;;; 	register aword_t subaddress;
;;; 
;;; 	//	keep address in bounds
;;; 	address &= (LOGICAL_SIZE - 1);

        and       ecx, 511                                      ;14.2
$LN5:

;;; 
;;; 	//	find left and right address and location between
;;; 	left = address >> RESOLUTION_LOG2;

        mov       edx, ecx                                      ;17.2
        shr       edx, 4                                        ;17.2
$LN7:

;;;     right = (left + 1) & (PHYSICAL_SIZE - 1);

        lea       edi, DWORD PTR [1+edx]                        ;18.5
$LN9:

;;; 	subaddress = address & (RESOLUTION - 1);
;;; 
;;; 	//	get values from storage
;;; 	left_val = _storage[left];

        mov       edx, DWORD PTR [__storage+edx*4]              ;22.2
$LN11:
        and       edi, 31                                       ;18.5
$LN13:

;;; 	right_val = _storage[right];

        mov       edi, DWORD PTR [__storage+edi*4]              ;23.2
$LN15:
        and       ecx, 15                                       ;19.2
$LN17:

;;; 
;;; 	//	compute slope in full precision
;;; 	slope = right_val - left_val;
;;; 
;;; 	//	compute interpolated value in high precision
;;; 	value = (left_val << RESOLUTION_LOG2) + subaddress * slope;

        mov       eax, edx                                      ;29.2
        shl       eax, 4                                        ;29.2
$LN19:
        sub       edi, edx                                      ;26.2
$LN21:
        imul      ecx, edi                                      ;29.2
        add       eax, ecx                                      ;29.2
$LN23:

;;; 
;;; 	//	scale result back to word_t resolution 
;;; 	return value >> RESOLUTION_LOG2;

        sar       eax, 4                                        ;32.2
        pop       edi                                           ;32.2
        ret                                                     ;32.2
        ALIGN     16
                                ; LOE
; mark_end;
@read_linear@4 ENDP
.LN@read_linear@4:
_TEXT	ENDS
_DATA	SEGMENT DWORD PUBLIC FLAT 'DATA'
_DATA	ENDS
; -- End  @read_linear@4
_DATA	SEGMENT DWORD PUBLIC FLAT 'DATA'
EXTRN	__storage:BYTE
_DATA	ENDS
	END
