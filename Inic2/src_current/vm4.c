#ifdef __cplusplus
extern "C" {
#endif

#include "vm.h"
#include "syscall.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "journal.h"
#include "HAL.h"
#include <jit/jit.h>

void print_memory(void);
void print_registers(void);

/* Register file. */
extern uint32_t RF[32];
/*VM memory vector*/
extern uint8_t VM_memory[VM_MEMORY_SZ];

extern uint32_t PC;
extern uint32_t nPC;

// LIBJIT
void vm_cpu_4(uint32_t newPC,int opt, int size)
{
	int i;
	PC = newPC;
	nPC = 4;
	RF[0] = 0; //Register $zero must always be zero
	RF[31] = 1; //Return default (if the program does not set to zero, should put error)
	uint32_t HI = 0, LO = 0;  
	uint32_t offset = 4;
	uint8_t halted = 0;
	
	uint32_t instr;
	uint8_t op;
	uint8_t rs;
	uint8_t rt;
	uint8_t rd;
	int16_t immediate;
	uint32_t address;
	
	uint8_t shamt;
	uint8_t funct;
	
	uint64_t mult; 
	
	/*lib jit variables */
	
	jit_context_t context;
	jit_type_t signature;
        jit_function_t function;
	jit_type_t params[VM_MEMORY_SZ+2];
	jit_int result;
	
	jit_value_t constant_sum;
	jit_value_t constant_while;
	jit_value_t v_it;
	jit_value_t constant_update;
	jit_value_t compare;
	jit_value_t reg[32];		/* Reg */
	jit_value_t mem[VM_MEMORY_SZ];	/* Memory */
	jit_label_t labels[10]; /* Labs for jumping :D */
	jit_value_t sum, t_sum;
	void *args[VM_MEMORY_SZ+2];	/* Args */
	jit_int arg_uint[VM_MEMORY_SZ+2];

	/* Create a context to hold the JIT's primary state */
	context = jit_context_create();	
	
	/* Lock the context while we build and compile the function */
	jit_context_build_start(context);
	
	for(i=0; i<(VM_MEMORY_SZ+2); i++) {
	    params[i] = jit_type_int;
	}
		
	signature = jit_type_create_signature(jit_abi_cdecl, jit_type_int, params, VM_MEMORY_SZ+2, 1);
	
	/* Create the function object */
	function = jit_function_create(context, signature);
	jit_type_free(signature);
	
	// Read memory and start registers
	for(i=0; i<VM_MEMORY_SZ; i++) {
	  //printf("%d\n",i);
	  mem[i] = jit_value_get_param(function, i);
	}
	reg[0] = jit_value_get_param(function, VM_MEMORY_SZ);
	reg[31] = jit_value_get_param(function, VM_MEMORY_SZ+1);

	/*int verify = 0 - 1;
	for (i=1; i<VM_MEMORY_SZ; i++) {
	    if((i%2)==0) {
		verify = verify + (i);
	    }
	    else {
		verify = verify - i;
	    }
	}
	printf("verify %d\n", verify); */

	int l_index;
				
	// Only doing the micro benchmark, for analysis 
	// Addiu
#define loopSize 10000 
#define smallerLoopSize 1000
#define opPerLoop 100
	// v_it = 0 ; constant_while = loopSize ; constant_update = 1
	v_it = jit_value_create(function, jit_type_uint);
	constant_update = jit_value_create_nint_constant(function, jit_type_int, (int)0);
	jit_insn_store(function, v_it, constant_update);
	
	reg[2] = jit_value_create(function, jit_type_uint);
	constant_while = jit_value_create_nint_constant(function, jit_type_int, 0);
	jit_insn_store(function, reg[2], constant_while);
	reg[3] = jit_value_create(function, jit_type_uint);
	constant_while = jit_value_create_nint_constant(function, jit_type_int, 1);
	jit_insn_store(function, reg[3], constant_while);
	
	
	// do while (v_it < constant_while) {
	jit_insn_label(function, &labels[0]);
	
	if (opt == 0) {
	  constant_update = jit_insn_add(function, reg[2], reg[3]);
	}
	else if(opt == 1) {
	  constant_update = jit_insn_xor(function, reg[2], reg[3]);
	}
	else if(opt == 2) {
	  constant_update = jit_insn_load(function, mem[0]);
	}
	for (l_index = 1; l_index < opPerLoop; l_index++) {
	  if (opt == 0) {
	    constant_update = jit_insn_add(function, constant_update, reg[3]);
	  } 
	  else if(opt == 1) {
	    constant_update = jit_insn_xor(function, constant_update, reg[3]);
	  }
	  else if(opt == 2) {
	    constant_update = jit_insn_load(function, mem[l_index % 5]);
	  }
	}
	
	jit_insn_store(function, reg[2], constant_update);
	
	// do while
	constant_update = jit_value_create_nint_constant(function, jit_type_uint, 1);
	constant_sum = jit_insn_add(function, v_it, constant_update);
	jit_insn_store(function, v_it, constant_sum);
	
	if(size > 0) {
	  constant_while = jit_value_create_nint_constant(function, jit_type_uint, loopSize);
	}
	else {
	  constant_while = jit_value_create_nint_constant(function, jit_type_uint, smallerLoopSize);
	}
	compare = jit_insn_gt(function, constant_while, v_it);
	jit_insn_branch_if(function, compare, &labels[0]);
	
	
	// Return 
	//jit_insn_return(function, reg[2]);
	jit_insn_return(function, reg[2]);
	
	// START OF FINAL PART
	
	/* Compile the function */
	jit_function_compile(function);

	/* Unlock the context */
	jit_context_build_end(context);
	
	// Put memory and first registers
	for (i=0; i<VM_MEMORY_SZ; i++) {
	  arg_uint[i] = (int) VM_memory[i];
	  //arg_uint[i] = (int)i;
	  args[i] = &(arg_uint[i]);
	}
	arg_uint[VM_MEMORY_SZ] = 0;
	args[VM_MEMORY_SZ] = &(arg_uint[VM_MEMORY_SZ]);
	arg_uint[VM_MEMORY_SZ+1] = 1;
	args[VM_MEMORY_SZ+1] = &(arg_uint[VM_MEMORY_SZ+1]);
	
	jit_function_apply(function, args, &result);
	//printf("%d\n", result);
	
	return;
	
	/* end lib jit variables */
	
}