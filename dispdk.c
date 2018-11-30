#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "emucpu.h"

int main( int argc, const char * argv [] )
{
  int rc;
  if( 2 != argc ) {
    printf("usage: %s input.pdk\n\n", argv[0]);
    return 0;
  }

  struct emuCPU cpu;
  rc=emuCPUloadPDK(&cpu, argv[1]);

  printf("MCU_NAME: %s\n", cpu.hdr.mcu_name);
  printf("OTP_ID: %04X\n", cpu.hdr.otp_id);
  printf("\n");

  if( rc < 0 ) {
    printf("Error reading input file: %d\n",rc); 
    return -1; 
  }

  char buf[64] = "-----";
  uint32_t p;
  for( p=0; p<(cpu.hdr.usable_codesize - cpu.hdr.remain_code_free); p++ )
  {
    if( cpu.fnDisassemble) 
      cpu.fnDisassemble( &cpu, p, buf );
    printf( "0x%04x:   0x%04x    %s\n", p, cpu.eCode[p], buf );
  }
  
  printf("...\n");

  for( p=cpu.hdr.usable_codesize; p<cpu.hdr.codesize; p++ )
  {
    if( cpu.fnDisassemble) 
      cpu.fnDisassemble( &cpu, p, buf );
    printf( "0x%04x:   0x%04x    %s\n", p, cpu.eCode[p], buf );
  }

  return 0;
}
