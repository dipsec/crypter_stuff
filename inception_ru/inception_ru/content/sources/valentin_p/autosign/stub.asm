format PE GUI 4.0
entry main

include 'fasm\INCLUDE\WIN32A.INC'
include 'fasm\include\MACRO\if.inc'
section '.text' code readable executable

proc main
	invoke	GetModuleHandle,0
	mov	[wc.hInstance],eax
	invoke	LoadIcon,0,IDI_APPLICATION
	mov	[wc.hIcon],eax
	invoke	LoadCursor,0,IDC_ARROW
	mov	[wc.hCursor],eax
	invoke	RegisterClass,wc
	test	eax,eax
	jz	error

	invoke	CreateWindowEx,0,_class,_title,WS_VISIBLE+WS_DLGFRAME+WS_SYSMENU,128,128,256,192,NULL,NULL,[wc.hInstance],NULL
	test	eax,eax
	jz	error

  msg_loop:
	invoke	GetMessage,msg,NULL,0,0
	cmp	eax,1
	jb	end_loop
	jne	msg_loop
	invoke	TranslateMessage,msg
	invoke	DispatchMessage,msg
	jmp	msg_loop

  error:
	invoke	MessageBox,NULL,_error,NULL,MB_ICONERROR+MB_OK

  end_loop:
	invoke	ExitProcess,[msg.wParam]
endp
;---------------------------------
include_code4size
;---------------------------------
proc WindowProc uses ebx esi edi, hwnd,wmsg,wparam,lparam
	cmp	[wmsg],WM_DESTROY
	je	.wmdestroy
	cmp	[wmsg],WM_CREATE
	je	.wmdexit
  .defwndproc:
	invoke	DefWindowProc,[hwnd],[wmsg],[wparam],[lparam]
	jmp	.finish
  .wmdexit:
  invoke DestroyWindow,[hwnd]
  jmp	.finish
  .wmdestroy:
	invoke	PostQuitMessage,0
	xor	eax,eax
  .finish:
	ret
endp


section '.idata' import data readable writeable
  library kernel32, 'KERNEL32.DLL',\
	  user32, 'USER32.DLL'
 include 'fasm\include\api\kernel32.inc'
 include 'fasm\include\api\user32.inc'
  


section '.data' data readable writeable
;---------------------------------
include_data4size
;---------------------------------
 _test TCHAR 'fasm test', 0
  _class TCHAR 'FASMWIN32',0
  _title TCHAR 'Win32 program template',0
  _error TCHAR 'Startup failed.',0
  wc WNDCLASS 0,WindowProc,0,0,NULL,NULL,NULL,COLOR_BTNFACE+1,NULL,_class
  msg MSG
 
section '.reloc' data readable discardable fixups
section '.rsrc' data readable resource from 'rsrc.res'




