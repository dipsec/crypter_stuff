;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;
; Command mutator
;
;IN: EBX = List
;
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�

;旼컴컴컴컴컴컴컴컴컴컴컴쩡컴컴컴컴컴컴컴컴커
;�    not-stack         F�  stack:         F�
;쳐컴컴컴컴컴컴컴컴컴컴컴탠컴컴컴컴컴컴컴컴캑
;�1  mov reg32,mem      0� mov reg32,reg32 0�
;�2  lea reg32,mem      0�                  �
;�3  xchg reg,reg       0�                  �
;�4  dec reg32          1�                  �
;�5  inc reg32          1�                  �
;�6  shl reg32,x        1�                  �
;�7  imul reg32,reg32,x 1�                  �
;�8  neg reg/mem        0�                  �
;�9  sub reg32,x        1�                  �
;�10 add reg32,x        1�                  �
;읕컴컴컴컴컴컴컴컴컴컴컴좔컴컴컴컴컴컴컴컴켸

cmdm:
	
		lea edi,m__temp
		mov esi,[ebx.list_first]

		xor edx,edx
		inc edx

;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
cmdm_main:
		push ebp


		test [esi.one_data.ltmed_desc.lc_flags],LF_RAW	; RAW ?
		jnz cmdm_next					;

;------------------------------------------------------------------------------

                push 10                                         ;커
		push m__seed					; �
                call m__rnd                                     ; �
                add esp,8                                       ; � RANDOMIZE
                or eax,eax                                      ; �   9/10
                jz cmdm_next                                    ;켸

;------------------------------------------------------------------------------


;같 CHECK MUTABLE 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�

		mov AX,2 ptr[esi.one_data.ltmed_desc.lc_mask1]

		cmp AL,__MASK_MOV				; MOV
		je cmdm_MOV                                     ;

		cmp AL,__MASK_LEA				; LEA
		je cmdm_LEA                                     ;

		cmp AL,__MASK_IMUL				; 
		je cmdm_IMUL                                    ;
		                                                ; IMUL
		cmp AL,__MASK_IMUL2                             ;
		je cmdm_IMUL                                    ;

		cmp AL,__MASK_INC40				; INC
		je cmdm_INC40 					;

		cmp AL,__MASK_DEC48                             ; DEC
		je cmdm_DEC48                                   ;

		cmp AL,__MASK_XCHG				; XCHG
		je cmdm_XCHG                                    ;

;-----------------------------------------------------------------------------

		cmp AL,__MASK_80				; ADD / SUB
		je cmdm_80					;

		cmp AL,__MASK_FE				; INC / DEC
		je cmdm_FE                                      ;

		cmp AL,__MASK_C0				; SHL
		je cmdm_C0                                      ;

		cmp AL,__MASK_F6				; NEG
		je cmdm_F6                                      ;

;-----------------------------------------------------------------------------

		jmp cmdm_next

;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께
;� MOV 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께

cmdm_MOV:

		cmp [esi.one_data.ltmed_desc.lc_psize],0	; prefixes ?
		jne cmdm_next

		mov eax,[esi.one_data.ltmed_desc.lc_flags]

		test ax,LF_WV					; W = 0 ?
		jz cmdm_next

;------------------------------------------------------------------------------
		call data_clear

		test eax,LF_BASE
		jz cmdm_mov_rm
		                                                ;   reg1
		mov CL,[esi.one_data.ltmed_desc.lc_base]	; CL = BASE
		jmp cmdm_mov_ro                                 ;    
cmdm_mov_rm:							;    
		mov CL,[esi.one_data.ltmed_desc.lc_rm]		; CL = R/M

cmdm_mov_ro:
		mov CH,[esi.one_data.ltmed_desc.lc_ro]	 	; CH = reg2(r/o)

		test eax,LF_MEM					; memory using ?
		jnz cmdm_mov_mem

;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
;
;CL=REG1,CH=REG2
;EAX = flags

		push 4 ptr [esi.one_data.ltmed_label]
		pop  4 ptr [edi.ltmed_label]

		call list_kill
		dec edx

		test ax,LF_SDV					;
		jz  cmdm_mov_rrd0				; D=1  r/m->r/o

		xchg CL,CH					; CL = r/o
		                                                ; CH = r/w
cmdm_mov_rrd0:

		test m__flags,LTMEF_MSTACK
		jz  cmdm_mov_leareg

;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
;
; MOV REG1,REG2   PUSH REG2 + POP REG1
;
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같

		mov AL,__MASK_PUSH				;
		or AL,CH					; <PUSH REG1>
		mov [edi.ltmed_command],AL                      ;

		inc [edi.ltmed_desc.lc_size]			; size=1
		call list_add
		inc edx

;------------------------------------------------------------------------------

		xor eax,eax
		mov [edi.ltmed_label],eax

		mov AL,__MASK_POP        			;
		or AL,CL					; <POP REG2>
		mov [edi.ltmed_command],AL                      ;

		call list_add	
		jmp cmdm_refresh

cmdm_mov_leareg:
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
;
; MOV REG1,REG2   LEA REG1,[REG2]
;
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같

		xor eax,eax

		mov AL,CL					;
		shl AL,3                                        ; modrm = 
		or AL,01000100b                                 ;   reg2 + SIB
		
		mov AH,CH                                       ; sib = reg1
		or AH,00100000b					;

		shl eax,8
		mov AL,__CMD_LEA

		mov 4 ptr[edi.ltmed_command],EAX
		mov [edi.ltmed_desc.lc_size],4

		call list_add
		jmp cmdm_refresh

;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
;
; MOV REG1,[REG2]  LEA REG1,[REG2] ; MOV REG1,[REG1]
;
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
;
;EAX = flags
;CL=REG1,CH=REG2
cmdm_mov_mem:

		test ax,LF_SDV					; D=1, r/o  [r/w]
		jz cmdm_next

		test eax,LF_OFFSET
		jz cmdm_mov_mem_indx

		cmp [esi.one_data.ltmed_desc.lc_offset],0
		jne cmdm_mov_mem_replace

cmdm_mov_mem_indx:
		
		test eax,LF_INDEX
		jnz cmdm_mov_mem_replace

		cmp CL,CH
		je cmdm_next

cmdm_mov_mem_replace:

		mov [esi.one_data.ltmed_command],__CMD_LEA	; <LEA REG2,[REG1]>
		
;------------------------------------------------------------------------------
		xor eax,eax

		mov AL,CH
		shl AL,3					; 
		or AL,01000100b                                 ; 1-byte offset

		mov AH,00100000b				; SIB
		or AH,CH                                        ;

		shl eax,8
		mov AL,__MASK_MOV or 11b			; D=1 , W=1

		mov 4 ptr[edi.ltmed_command],eax
		mov [edi.ltmed_desc.lc_size],4

		call list_add
		jmp  cmdm_refresh

;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께
;� LEA 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께

;	LEA REG1,[SCALE*INDEX+BASE+OFFSET];
;	LEA REG1,[INDEX*SCALE]
;	LEA REG1,[REG2+BASE]
;	LEA REG1,[REG2+OFFSET]
cmdm_LEA:
		cmp [esi.one_data.ltmed_desc.lc_psize],0	; prefix?
		jne cmdm_next


		mov eax,[esi.one_data.ltmed_desc.lc_flags]

		test eax,LF_BASE
		jz cmdm_lea_rm
		                                                ;   reg1
		mov CL,[esi.one_data.ltmed_desc.lc_base]	; CL = BASE
		jmp cmdm_lea_ro                                 ;    
cmdm_lea_rm:	                                                ;    
		mov CL,[esi.one_data.ltmed_desc.lc_rm]		; CL = R/M

cmdm_lea_ro:
		mov CH,[esi.one_data.ltmed_desc.lc_ro] 		; CH = reg2(r/o)

;------------------------------------------------------------------------------

		cmp CH,100b					; r/o = ESP ?
		je cmdm_next

		cmp CH,CL					; r/o   =  r/w 
		je cmdm_next                                    ;(reg2) = (reg1)

;------------------------------------------------------------------------------

		test eax,LF_INDEX
		jz cmdm_lea_init

		cmp CH,[esi.one_data.ltmed_desc.lc_index]	; INDEX = r/o ?
		je cmdm_next

;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
cmdm_lea_init:

		dec edx						; *prev

		call data_clear

		push 4 ptr [esi.one_data.ltmed_label]
		pop  4 ptr [edi.ltmed_label]

;		mov eax,[esi.one_data.ltmed_desc.lc_flags]


;� INDEX / SCALE 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같

		test eax,LF_INDEX
		jz cmdm_lea_base_1

		mov AL,[esi.one_data.ltmed_desc.lc_index]
		mov AH,[esi.one_data.ltmed_desc.lc_scale]
                                                

                shl AH,6                                        ; ss �     �
                or AH,00000101b                                 ; ss | 000 � * 
                shl AL,3                                        ;    
                or AH,AL                                        ; ss 쿶ndex� *
                                                                    
                mov AL,CH					;
                shl AL,3                                        ; sib+4-byte offset
		or AL,00000100b					;

		shl EAX,8

		mov AL,__CMD_LEA
		mov 4 ptr[edi.ltmed_command],EAX

		xor eax,eax
		mov 4 ptr[edi.ltmed_command+3],EAX		; offset = 0

		mov [edi.ltmed_desc.lc_size],3+4

		call list_add
		inc edx

		call data_clear
		jmp cmdm_lea_base_2

;� BASE 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�
cmdm_lea_base_1:

;		mov eax,[esi.one_data.ltmed_desc.lc_flags]

		test eax,LF_REG1+LF_BASE
		jz cmdm_lea_offset

		mov AH,CL

	        shl AH,3
                or AH,11000000b                                 ; 11 � r/m � 0
                or AH,CH                                        ; 11 � r/m � r/o

		mov AL,__MASK_MOV or 01b                        ; W = 1 , D = 0
		mov 2 ptr[edi.ltmed_command],AX

		mov [edi.ltmed_desc.lc_size],2
		call list_add
		inc edx

		call data_clear
		jmp cmdm_lea_offset


;� BASE / BASE 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
cmdm_lea_base_2:

		mov eax,[esi.one_data.ltmed_desc.lc_flags]

		test eax,LF_REG1+LF_BASE
		jz cmdm_lea_offset

;-----------------------------------------------------------------------------

		xor eax,eax

		mov AL,CH                                       ;
		shl AL,3                                        ;  01  r/o 100
		or AL,01000100b					;

		mov AH,CH                                       ;
		shl AH,3                                        ;  00  r/o base
		or AH,CL					;

		shl EAX,8

		mov AL,__CMD_LEA
		mov 4 ptr[edi.ltmed_command],EAX

		mov [edi.ltmed_desc.lc_size],3+1

		call list_add
		inc edx

		call data_clear

;� OFFSET 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�
cmdm_lea_offset:

		mov eax,[esi.one_data.ltmed_desc.lc_flags]

		test eax,LF_OFFSET
		jz cmdm_lea_kill

		cmp [esi.one_data.ltmed_desc.lc_offset],0	; offset = 0 ?
		je cmdm_lea_kill

		test eax,LF_REG1+LF_BASE+LF_INDEX		; index-base ?
		jnz cmdm_lea_ib

;� OFFSET MOV 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�

		mov AL,0B0h+08h					; W =1
	        or AL,CH					; r/o

		mov [edi.ltmed_command],AL			; <MOV REG,i32>

		mov eax,[esi.one_data.ltmed_desc.lc_offset]

		cmp [esi.one_data.ltmed_desc.lc_soffset],1
		jne cmdm_lea_offsetMOV4

		movsx eax,al

cmdm_lea_offsetMOV4:

		mov 4 ptr[edi.ltmed_command+1],eax

		mov [edi.ltmed_desc.lc_size],1+4
		call list_add
		inc edx
		jmp cmdm_lea_kill


;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
cmdm_lea_ib:

		mov AH,CH                                       ;
		shl CH,3                                        ;
		or AH,CH                                        ; r/m = r/o
		or AH,10000000b					; 

		mov AL,__CMD_LEA
		mov 2 ptr[edi.ltmed_command],AX


;-----------------------------------------------------------------------------
		mov eax,[esi.one_data.ltmed_desc.lc_offset]

		cmp [esi.one_data.ltmed_desc.lc_soffset],1
		jne cmdm_lea_offset4

		movsx eax,al

cmdm_lea_offset4:
		mov 4 ptr[edi.ltmed_command+2],eax

		mov [edi.ltmed_desc.lc_size],2+4
		call list_add
		inc edx

;-----------------------------------------------------------------------------
cmdm_lea_kill:
		inc edx						; original lea
		call list_kill

		dec edx
		dec edx
		jmp cmdm_refresh


;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;� SHL 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;
;SHL REG32,i8  IMUL REG32,REG32,i32
;
cmdm_C0:
		cmp [esi.one_data.ltmed_desc.lc_ro],00000100b	; <SHL> ?
		jne cmdm_next

;� SHL 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�

		cmp [esi.one_data.ltmed_desc.lc_psize],0
		jne cmdm_next

		mov eax,[esi.one_data.ltmed_desc.lc_flags]

		test eax,LF_MEM					; memory use ?
		jnz cmdm_next                                   ;

		test ax,LF_WV					; W =1 ?
		jz cmdm_next                                    ;

;-----------------------------------------------------------------------------

		call data_clear

		push 4 ptr[esi.one_data.ltmed_label]
		pop  4 ptr[edi.ltmed_label]

		call list_kill
		dec edx

		mov AL,[esi.one_data.ltmed_desc.lc_rm]
		mov CL,[esi.one_data.ltmed_desc.lc_operand]

		mov AH,11000000b
		or AH,AL
		shl AL,3
		or AH,AL

		mov [edi.ltmed_desc.lc_size],2+4

		mov AL,__CMD_IMUL
		mov 2 ptr[edi.ltmed_command],AX

		xor eax,eax					; EAX = 1
		inc eax                                         ;

		shl eax,CL 					; scale value
		mov 4 ptr[edi.ltmed_command+2],eax

		call list_add
		jmp cmdm_refresh


;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;� IMUL 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;
;     		          N
;       IMUL REG32,REG32,2     SHL REG32,N

cmdm_IMUL:
		cmp [esi.one_data.ltmed_desc.lc_psize],0
		jne cmdm_next

		test [esi.one_data.ltmed_desc.lc_flags],LF_MEM
		jnz cmdm_next

;------------------------------------------------------------------------------

		xor eax,eax
		mov ecx,4 ptr[esi.one_data.ltmed_desc.lc_operand]

cmdm_imul_degree:

		inc eax					
		shr ecx,1
		jnc cmdm_imul_degree

		dec eax
;------------------------------------------------------------------------------

		or ecx,ecx
		jnz cmdm_next

		mov CL,[esi.one_data.ltmed_desc.lc_rm]

		cmp [esi.one_data.ltmed_desc.lc_ro],CL
		jne cmdm_next

;------------------------------------------------------------------------------
		call data_clear

		push 4 ptr[esi.one_data.ltmed_label]
		pop  4 ptr[edi.ltmed_label]

		call list_kill
		dec edx

		shl eax,16

		mov AL,__MASK_C0 or 1                           ; W = 1 <SHL>
	
		mov AH,11100000b				; R/O = 100b 
		or AH,CL                                        ;   MOD=11

		mov [edi.ltmed_desc.lc_size],3
		mov 4 ptr[edi.ltmed_command],EAX
		call list_add

		jmp cmdm_refresh


;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;� ADD / SUB   께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;
; ADD  REG,1  INC REG  
; SUB  REG,1  DEC REG
;
; ADD REG,IM32  SUB REG,IM32
; SUB REG,IM32  ADD REG,IM32

cmdm_80:

		cmp [esi.one_data.ltmed_desc.lc_psize],0
		jne cmdm_next

		mov eax,[esi.one_data.ltmed_desc.lc_flags]

		test eax,LF_MEM					; memory using?
		jnz cmdm_next 					;

		test ax,LF_WV					; W = 1?
		jz  cmdm_next                                   ;

;------------------------------------------------------------------------------

		mov ecx,4 ptr[esi.one_data.ltmed_desc.lc_operand]

		test ax,LF_SDV					; S = 1?
		jz cmdm_80_nos

		movsx ecx,cl		
cmdm_80_nos:

		mov AL,[esi.one_data.ltmed_desc.lc_ro]

		cmp AL,101b					; SUB ?
		jne cmdm_ADD_1                                  ;

		cmp ecx,1
		jne cmdm_AS_SUB_IM

		mov AH,001b	                                ; DEC
		jmp cmdm_AS_dec_inc

;------------------------------------------------------------------------------
cmdm_ADD_1:
		cmp AL,000b
		jne cmdm_next

		cmp ecx,1
		jne cmdm_AS_ADD_IM

		mov AH,000b					; INC

cmdm_AS_dec_inc:


;� SUB/ADD REG,1 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같

		call data_clear

		mov CL,[esi.one_data.ltmed_desc.lc_rm]

		push 4 ptr[esi.one_data.ltmed_label]
		pop  4 ptr[edi.ltmed_label]

		call list_kill
		dec edx

		mov AL,__MASK_FE or 1                           ; < DEC/INC >
								; W = 1 
		shl AH,3
		or AH,CL
		or AH,11000000b
	
		mov [edi.ltmed_desc.lc_size],2
		mov 2 ptr[edi.ltmed_command],AX
	
		call list_add
		jmp cmdm_refresh

;� SUB/ADD REG,IM 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�
cmdm_AS_SUB_IM:
		mov AH,000b					; <ADD>
		jmp cmdm_AS_INVERSE
cmdm_AS_ADD_IM:
		mov AH,101b					; <SUB>
cmdm_AS_INVERSE:
; ECX = operand
		neg ecx						; change operand
		mov 4 ptr[esi.one_data.ltmed_command+2],ecx

		mov AL,[esi.one_data.ltmed_desc.lc_modrm]
		and AL,11000111b
		shl AH,3
		or AL,AH

		mov 1 ptr[esi.one_data.ltmed_command+1],AL
		jmp cmdm_next


;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;� DEC / INC 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;
;DEC REG  ADD REG,1   
;DEC REG  SUB REG,1 
cmdm_FE:
	
		mov CL,[esi.one_data.ltmed_desc.lc_rm]

		mov AL,[esi.one_data.ltmed_desc.lc_ro]

		cmp AL,000b					; INC ?
		je cmdm_INC

		cmp AL,001b					; DEC ?
		jne cmdm_next

;� DEC 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�
cmdm_DEC:
		mov CH,101b                                     ; <SUB>
		jmp cmdm_inc_dec

;� INC 같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같�
cmdm_INC:
		mov CH,000b					; <ADD>
		jmp cmdm_inc_dec

;-----------------------------------------------------------------------------

;� DEC 48 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께

cmdm_DEC48:                                                     
		mov CH,101b                                     ; <SUB>
		jmp cmdm_inc40_dec48                            ;


;� INC 40 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께
cmdm_INC40:
		mov CH,000b					; <ADD>
cmdm_inc40_dec48:
		mov CL,[esi.one_data.ltmed_desc.lc_reg]

;-----------------------------------------------------------------------------

cmdm_inc_dec:

		cmp [esi.one_data.ltmed_desc.lc_psize],0
		jne cmdm_next

		mov eax,[esi.one_data.ltmed_desc.lc_flags]

		test eax,LF_REG
		jnz cmdm_di_simple

		test eax,LF_MEM
		jnz cmdm_next

		test ax,LF_WV
		jz cmdm_next

cmdm_di_simple:
;-----------------------------------------------------------------------------
		call data_clear

		push 4 ptr[esi.one_data.ltmed_label]
		pop  4 ptr[edi.ltmed_label]

		call list_kill
		dec edx


		mov AH,CH
		shl AH,3
		or AH,CL
		or AH,11000000b

		mov AL,__MASK_80 or 1				; SUB/ADD
								; W = 1
;-----------------------------------------------------------------------------

		mov 2 ptr[edi.ltmed_command],AX

		xor eax,eax   					; 
		inc eax                                         ; = 1
		mov 4 ptr[edi.ltmed_command+2],eax

		mov [edi.ltmed_desc.lc_size],2+4
		call list_add

		jmp cmdm_refresh

;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;� XCHG 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
cmdm_XCHG:
		test [esi.one_data.ltmed_desc.lc_flags],LF_MEM
		jnz cmdm_next

;-----------------------------------------------------------------------------

		mov AL,[esi.one_data.ltmed_desc.lc_rm]
		mov AH,[esi.one_data.ltmed_desc.lc_ro]

		shl AL,3
		or AL,AH

		or AL,11000000b

		movzx ecx,[esi.one_data.ltmed_desc.lc_psize]
		mov [esi.one_data.ltmed_command+ecx+1],AL

		jmp cmdm_next

;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;� NEG 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�
cmdm_F6:

	        cmp [esi.one_data.ltmed_desc.lc_ro],011b	; NEG ?
	        jne cmdm_next
		

;� NEG 께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께�

		mov AH,[esi.one_data.ltmed_desc.lc_modrm]
		and AH,11000111b
		
		push eax

		or  AH,00010000b				; <NOT>
		movzx ecx,[esi.one_data.ltmed_desc.lc_psize]

		mov [esi.one_data.ltmed_command+ecx+1],AH

		push esi              				;
		push edi                                        ;
		push ecx                                        ;
		                                                ;
		lea esi,[esi.one_data]                          ;
		opzmov ecx,<SIZE ltmedata>                      ; copy command
		rep movsb                                       ;  to bufer
		                                                ;
		pop ecx                                         ;
		pop edi                                         ;
		pop esi                                         ;

		pop eax

;------------------------------------------------------------------------------
		mov [edi.ltmed_label],0				; remove label

		or  AH,00000000b				; <INC>
		mov AL,__MASK_FE				;
		
		test [esi.one_data.ltmed_desc.lc_flags],LF_WV
		jz cmdm_neg_w0

		or AL,1						; W = 1
cmdm_neg_w0:
		mov 2 ptr[edi.ltmed_command+ecx],AX
		call list_add

		jmp cmdm_refresh

;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
cmdm_refresh:
		inc edx
		call list_get
		xchg esi,eax

cmdm_next:
		pop ebp

		cmp esi,[ebx.list_last]
		je cmdm_exit

		inc edx						;next number
		mov esi,[esi.one_next]
		jmp cmdm_main
cmdm_exit:

