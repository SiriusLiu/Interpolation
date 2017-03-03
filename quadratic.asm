; -- Machine type PW
; mark_description "Intel(R) C++ Compiler for applications running on IA-32, Version 11.1    Build 20091130 %s";
; mark_description "-c -O2 -D WIN32 -D NDEBUG -D _CONSOLE -D _MBCS -EHs -EHc -ML -fp:fast -FAs -Fac:\\Daten\\Visual C\\Interpola";
; mark_description "tingMemory\\/ -FoRelease/ -W3 -nologo -Wp64 -Zi -Qvc7.1 -Qlocation,link,C:\\Program Files\\Microsoft Visual ";
; mark_description "Studio .NET 2003\\Vc7\\bin";
	.686P
 	.387
	OPTION DOTNAME
	ASSUME	CS:FLAT,DS:FLAT,SS:FLAT
_TEXT	SEGMENT PARA PUBLIC FLAT 'CODE'
;	COMDAT @read_quadratic@4
TXTST0:
; -- Begin  @read_quadratic@4
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
	PUBLIC @read_quadratic@4
@read_quadratic@4	PROC NEAR 
; parameter 1(address): ecx
.B1.1:                          ; Preds .B1.0

;;; word_t __fastcall read_quadratic(address_t address) {

$LN1:
        push      edi                                           ;7.53
        push      esi                                           ;7.53
        push      ebp                                           ;7.53
$LN3:

;;; 	register dword_t value, b, c;
;;; 	register aword_t z0, z1, z0_by_z1;
;;; 	register word_t	y0, y1, y2;
;;; 	register address_t x0, x1, x2;
;;; 
;;; 	//	keep address in bounds
;;; 	address &= LOGICAL_BITMASK;

        and       ecx, 511                                      ;14.2
$LN5:

;;; 
;;; 	//	compute indices
;;; 	x0 = ((address - RESOLUTION_BY_2) >> RESOLUTION_LOG2) & PHYSICAL_BITMASK;

        lea       edx, DWORD PTR [-8+ecx]                       ;17.2
        shr       edx, 4                                        ;17.2
        and       edx, 31                                       ;17.2
$LN7:

;;; 	x1 = (x0 + 1) & PHYSICAL_BITMASK;

        lea       eax, DWORD PTR [1+edx]                        ;18.2
        and       eax, 31                                       ;18.2
$LN9:

;;; 	x2 = (x0 + 2) & PHYSICAL_BITMASK;

        lea       edi, DWORD PTR [2+edx]                        ;19.2
        and       edi, 31                                       ;19.2
$LN11:

;;; 
;;; 	//	compute shifts
;;; 	z0 = (address & RESOLUTION_BITMASK) | (((~address) & RESOLUTION_BY_2_MSB) << 1);

        mov       esi, ecx                                      ;22.2
        and       esi, 15                                       ;22.2
        not       ecx                                           ;22.2
        and       ecx, 8                                        ;22.2
        add       ecx, ecx                                      ;22.2
        or        esi, ecx                                      ;22.2
$LN13:

;;; 	z1 = z0 - RESOLUTION;
;;; 	z0_by_z1 = z0 * z1;
;;; 
;;; 	//	load three data elements
;;; 	y0 = _storage[x0];

        mov       ecx, DWORD PTR [__storage+edx*4]              ;27.2
$LN15:
        lea       ebp, DWORD PTR [-16+esi]                      ;23.2
$LN17:
        imul      ebp, esi                                      ;24.2
$LN19:

;;; 	y1 = _storage[x1];

        mov       edx, DWORD PTR [__storage+eax*4]              ;28.2
$LN21:

;;; 	y2 = _storage[x2];

        mov       eax, DWORD PTR [__storage+edi*4]              ;29.2
$LN23:

;;; 	
;;; 	//	compute polynomial weights in full precision
;;; 	b = y1 - y0; 

        sub       edx, ecx                                      ;32.2
$LN25:

;;; 	c = y2 - (b << 1) - y0;
;;; 
;;; 	//	evaluate polynomial in full precision and add roundoff
;;; 	value = (y0 << TWO_RESOLUTION_SQUARE_LOG2)

        imul      esi, edx                                      ;36.2
        mov       edi, ecx                                      ;36.2
        shl       edi, 9                                        ;36.2
        shl       esi, 5                                        ;36.2
        add       edi, esi                                      ;36.2
$LN27:
        sub       eax, ecx                                      ;33.2
        add       edx, edx                                      ;33.2
        sub       eax, edx                                      ;33.2
$LN29:
        imul      ebp, eax                                      ;36.2
        lea       eax, DWORD PTR [255+edi+ebp]                  ;36.2
$LN31:

;;; 			+ ((b * z0) << TWO_RESOLUTION_LOG2)
;;; 			+ c * z0_by_z1
;;; 			+ ROUNDOFF;
;;; 
;;; 	//	scale back to output precision
;;; 	return value >> TWO_RESOLUTION_SQUARE_LOG2;

        sar       eax, 9                                        ;42.2
        pop       ebp                                           ;42.2
        pop       esi                                           ;42.2
        pop       edi                                           ;42.2
        ret                                                     ;42.2
        ALIGN     16
                                ; LOE
; mark_end;
@read_quadratic@4 ENDP
.LN@read_quadratic@4:
;@read_quadratic@4	ENDS
_TEXT	ENDS
_DATA	SEGMENT DWORD PUBLIC FLAT 'DATA'
_DATA	ENDS
; -- End  @read_quadratic@4
_DATA	SEGMENT DWORD PUBLIC FLAT 'DATA'
EXTRN	__storage:BYTE
_DATA	ENDS
	END
