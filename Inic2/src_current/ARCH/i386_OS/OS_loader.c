#include "vm.h"
#include "HAL.h"
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <EH.h>
#include <stdlib.h>

/*File for debug purpose only. To be used in order to load a binary into the vm*/

/* void blah(void)
{
	
} */


int main(int argc, char * argv[])
{
	/*Debugging EH*/
	// print_EH();
// 	eh_init();
// 	print_EH();
// 	register_handler(1, blah);
// 	register_handler(2, blah + 1);
// 	register_handler(2, blah + 2);
// 	register_handler(3, blah + 3);
// 	print_EH();
// 	insert_event(1);
// 	insert_event(2);
// 	insert_event(3);
// 	insert_event(1);
// 	print_EH();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	print_EH();
// 	insert_event(1);
// 	insert_event(2);
// 	insert_event(3);
// 	insert_event(1);
// 	print_EH();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	print_EH();
// 	insert_event(1);
// 	insert_event(2);
// 	insert_event(3);
// 	insert_event(1);
// 	print_EH();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	consume_event();
// 	print_EH();
	/*End Debugging EH*/
	FILE * binary;
	//int j = 0;
	int i = -1;
	uint8_t byte;
	uint32_t byte4;
	
	if (argc < 3) 
	{
		printf("Expected file name and execution type, aborting\n");
		return 1;
	}

	binary = fopen(argv[1], "rb");

	while(fread(&byte,sizeof(uint8_t),1,binary))
	{
		i++;
		VM_memory[i] = byte;
		//if((i%4)==3) {
		//  VM_memory2[i/4] = (((uint32_t)VM_memory[i-3] <<24) | ((uint32_t)VM_memory[i-2] <<16) | ((uint32_t)VM_memory[i-1] <<8) | ((uint32_t)VM_memory[i])); 
		//}
		//printf("%d\n", i);
	}
	
		

	fclose(binary);
/*#if MEASURING
	time_t tic = clock();
#endif */
#if RUN_VM
	// 0 : Count instructions
	// 1 : Normal
	// 2 : Normal and print memory
	// 3 : Optimized
	// 4 : Optimized and print memory
	// 5 : Indirect Thread
	// 6 : Indirect Thread and print memory
	// 7 : Super
	// 10: Normal counting total execution of each instruction
	// 11 : Nothing, to measure init
	/* switch (atoi(argv[2])) {
	  case 0:
	    vm_cpu_count(0);
	    break;
	  case 1:
	    vm_cpu(0, 0);
	    break;
	  case 2:
	    vm_cpu(0, 1); 
	    break;
	  case 3:
	   vm_cpu_2(0, 0);
	   break; 
	  case 4:
	    vm_cpu_2(0, 1);
	    break; 
	  case 5:
	    vm_cpu_2_indirect(0, 0);
	    break;
	  case 6:
	    vm_cpu_super(0, 0);
	    break;
	  case 7:
	    vm_cpu_2_mem2(0,0,i);
	    break;
	  case 8:
	    vm_cpu_2_mem2_all(0,0);
	    break;
	  case 9:
	    vm_cpu_2_indirect_pure(0,0);
	    break;
	  case 10:
	    vm_cpu_identify_instructions(0);
	    break;
	  case 11:
	    vm_cpu_init_only(0, 0);
	    break;
	  case 12:
	    vm_cpu_2_indirect_pure_opt3(0,0);
	    break;
	  case 13:
	    vm_cpu_2_mem2_all_opt4(0,0);
	    break;
	  case 14:
	    vm_cpu_2_indirect_pure_opt4(0,0);
	    break;
	  case 15:
	    vm_cpu_2_pure_with_convertion(0,0);
	    break;
	  case 16:
	    vm_cpu_super_3(0,0);
	    break;
	  case 20:
	    vm_cpu_4(0, 0, 0);
	    break;
	  case 21:
	    vm_cpu_4(0, 1, 0);
	    break;
	  case 22:
	    vm_cpu_4(0, 2, 0);
	    break;
	  case 30:
	    vm_cpu_4(0, 0, 1);
	    break;
	  case 31:
	    vm_cpu_4(0, 1, 1);
	    break;
	  case 32:
	    vm_cpu_4(0, 2, 1);
	    break;
	} */
	vm_cpu(0, 0);
#endif
/*
#if MEASURING	
	time_t toc = clock();
	printf("TIMESPENT.%ld\n", (toc - tic));
#endif
	i = 0;
*/	
	return 0;
}
