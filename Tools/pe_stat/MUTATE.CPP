
////////x///////x///////x///////x///////x///////x///////x///////x///////x////

#include "mz.hpp"
#include "pe.hpp"
#include "debug.hpp"

////////x///////x///////x///////x///////x///////x///////x///////x///////x////

void id3() { __emit__( 0xEB,0x02,0xFF,3 ); }

////////x///////x///////x///////x///////x///////x///////x///////x///////x////

void __fastcall x_memcpy(void *dest, void *src, DWORD n);
void __fastcall x_memset(void *dest, int c, DWORD n);

////////x///////x///////x///////x///////x///////x///////x///////x///////x////

// returns:
//     0      --if success
//  non-zero  --if error

int __cdecl my_mutate(
            DWORD           user_arg,
            PE_HEADER*      pe,
            PE_OBJENTRY*    oe,
            hooy*           root,
            int    __cdecl  user_disasm(DWORD,BYTE*),
            void*  __cdecl  user_malloc(DWORD,DWORD),
            DWORD  __cdecl  user_random(DWORD,DWORD)
            )
{
  //

  DWORD t = (DWORD)user_arg+(DWORD)pe+(DWORD)oe+(DWORD)root+
            (DWORD)user_disasm+(DWORD)user_malloc+(DWORD)user_random;
  t *= 0;

  return 666;             // 0==success
}

void __fastcall x_memcpy(void *dest, void *src, DWORD n)
{
  while (n--) *((BYTE*)dest)++ = *((BYTE*)src)++;
}
void __fastcall x_memset(void *dest, int c, DWORD n)
{
  while (n--) *((BYTE*)dest)++ = c;
}

////////x///////x///////x///////x///////x///////x///////x///////x///////x////

void id4() { __emit__( 0xEB,0x02,0xFF,4 ); }

////////x///////x///////x///////x///////x///////x///////x///////x///////x////
