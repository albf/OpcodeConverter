
#include "vm.h"
#include "syscall.h"
#include <inttypes.h>
#include <stdio.h>

#define FIX_OP 43
#define INDIRECT_DEBUG 0
#define T_SIZE 110
/* Register file. */
extern uint32_t RF[32];
/*VM memory vector*/
extern uint8_t VM_memory[VM_MEMORY_SZ];

extern uint32_t PC;
extern uint32_t nPC;
int32_t mark3[VM_MEMORY_SZ] = {-1};

struct pointer {
  void * code;
  struct pointer * next_level;
};
void vm_cpu_super(uint32_t newPC, int opt) {
  PC = newPC;
  nPC = 4;
  RF[0] = 0; //Register $zero must always be zero
  RF[31] = 1; //Return default (if the program does not set to zero, should put error)
  uint32_t HI = 0, LO = 0;
  uint32_t offset = 4;
  uint8_t halted = 0;
  int ii;
  
  for (ii = 0; ii<VM_MEMORY_SZ; ii++) {
   mark3[ii] = -1; 
  }
  
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  int16_t immediate;
  uint32_t address;
  
  uint8_t shamt;
  uint8_t funct;
  
  uint64_t mult;
  
  #if INDIRECT_DEBUG
  int counter=0;
  #endif
  
  uint32_t instr0;
  uint8_t op0;
  uint32_t instr1;
  uint8_t op1;

struct pointer * p;
struct pointer arraymovn[T_SIZE] = {  { &&movnPLUSsll, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movnPLUSjump, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movnPLUSbne, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movnPLUSaddiu, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movnPLUSandi, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL }  ,  { &&movn, NULL } 
 }; 

struct pointer arraylw[T_SIZE] = {  { &&lwPLUSsll, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSjr, NULL }  ,  { &&lw, NULL } 
 ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL } 
 ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL } 
 ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSaddu, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSxor, NULL }  ,  { &&lw, NULL } 
 ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSslt, NULL }  ,  { &&lwPLUSsltu, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSjump, NULL }  ,  { &&lwPLUSjal, NULL }  ,  { &&lwPLUSbeq, NULL }  ,  { &&lwPLUSbne, NULL }  ,  { &&lwPLUSblez, NULL } 
 ,  { &&lwPLUSbgtz, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSaddiu, NULL }  ,  { &&lwPLUSslti, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSori, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSerror, NULL } 
 ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL } 
 ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSlw, NULL }  ,  { &&lwPLUSlbu, NULL } 
 ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lw, NULL }  ,  { &&lwPLUSsw, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lw, NULL } 
 ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL } 
 ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL }  ,  { &&lwPLUSerror, NULL } 
 }; 

struct pointer arrayjal[T_SIZE] = {  { &&jalPLUSsll, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jalPLUSaddu, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jalPLUSaddiu, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL }  ,  { &&jal, NULL } 
 }; 

struct pointer arraybne[T_SIZE] = {  { &&bnePLUSsll, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bnePLUSaddu, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bnePLUSxor, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bnePLUSaddiu, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bnePLUSsw, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL }  ,  { &&bne, NULL } 
 }; 

struct pointer arraybeq[T_SIZE] = {  { &&beqPLUSsll, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beqPLUSaddu, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beqPLUSaddiu, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beqPLUSsw, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL }  ,  { &&beq, NULL } 
 }; 

struct pointer arraynor[T_SIZE] = {  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&norPLUSsrl, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&norPLUSjr, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL }  ,  { &&nor, NULL } 
 }; 

struct pointer arraymfhi[T_SIZE] = {  { &&mfhiPLUSsll, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhiPLUSsrl, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhiPLUSmult, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhiPLUSaddiu, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL }  ,  { &&mfhi, NULL } 
 }; 

struct pointer arrayblez[T_SIZE] = {  { &&blezPLUSsll, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blezPLUSaddiu, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL }  ,  { &&blez, NULL } 
 }; 

struct pointer arrayjump[T_SIZE] = {  { &&jumpPLUSsll, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jumpPLUSaddu, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jumpPLUSaddiu, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jumpPLUSsw, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL }  ,  { &&jump, NULL } 
 }; 

struct pointer arraysltu[T_SIZE] = {  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltuPLUSmovn, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltuPLUSbeq, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltuPLUSaddiu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltuPLUSlw, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL }  ,  { &&sltu, NULL } 
 }; 

struct pointer arrayaddu[T_SIZE] = {  { &&adduPLUSsll, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSsrl, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL } 
 ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL } 
 ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSmult, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL } 
 ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSaddu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSsubu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSnor, NULL } 
 ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSslt, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSjump, NULL }  ,  { &&adduPLUSjal, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSbne, NULL }  ,  { &&addu, NULL } 
 ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSaddiu, NULL }  ,  { &&adduPLUSslti, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSandi, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSlui, NULL }  ,  { &&adduPLUSerror, NULL } 
 ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL } 
 ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSlw, NULL }  ,  { &&adduPLUSlbu, NULL } 
 ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&addu, NULL }  ,  { &&adduPLUSsw, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&addu, NULL } 
 ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL } 
 ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL }  ,  { &&adduPLUSerror, NULL } 
 }; 

struct pointer arrayxor[T_SIZE] = {  { &&xorPLUSsll, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSsrl, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL } 
 ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL } 
 ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL } 
 ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSxor, NULL }  ,  { &&xorPLUSnor, NULL } 
 ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSbne, NULL }  ,  { &&xor, NULL } 
 ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSaddiu, NULL }  ,  { &&xorPLUSslti, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSandi, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSerror, NULL } 
 ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL } 
 ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL } 
 ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xor, NULL }  ,  { &&xorPLUSsw, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xor, NULL } 
 ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL } 
 ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL }  ,  { &&xorPLUSerror, NULL } 
 }; 

struct pointer arraylui[T_SIZE] = {  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&luiPLUSsrl, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&luiPLUSjal, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&luiPLUSaddiu, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&luiPLUSori, NULL }  ,  { &&lui, NULL }  ,  { &&luiPLUSlui, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&luiPLUSlw, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&luiPLUSsw, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL } 
 ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL }  ,  { &&lui, NULL } 
 }; 

struct pointer arrayerror[T_SIZE] = {  { &&error, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
 ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
 ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL } 
 ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSaddu, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSsubu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
 ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
 ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSaddiu, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSerror, NULL } 
 ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL } 
 ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSlw, NULL }  ,  { &&error, NULL } 
 ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&error, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&error, NULL } 
 ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL } 
 ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL }  ,  { &&errorPLUSerror, NULL } 
 }; 

struct pointer arrayori[T_SIZE] = {  { &&oriPLUSsll, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&oriPLUSmult, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&oriPLUSaddu, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&oriPLUSand, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&oriPLUSaddiu, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&oriPLUSandi, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL }  ,  { &&ori, NULL } 
 }; 

struct pointer arrayaddiu[T_SIZE] = {  { &&addiuPLUSsll, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSsrl, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSjr, NULL }  ,  { &&addiu, NULL } 
 ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSsysc, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL } 
 ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSmult, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL } 
 ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSaddu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSsubu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSxor, NULL }  ,  { &&addiu, NULL } 
 ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSslt, NULL }  ,  { &&addiuPLUSsltu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSjump, NULL }  ,  { &&addiuPLUSjal, NULL }  ,  { &&addiuPLUSbeq, NULL }  ,  { &&addiuPLUSbne, NULL }  ,  { &&addiuPLUSblez, NULL } 
 ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSaddiu, NULL }  ,  { &&addiuPLUSslti, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSandi, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSlui, NULL }  ,  { &&addiuPLUSerror, NULL } 
 ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL } 
 ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSlw, NULL }  ,  { &&addiuPLUSlbu, NULL } 
 ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiu, NULL }  ,  { &&addiuPLUSsw, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiu, NULL } 
 ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL } 
 ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL }  ,  { &&addiuPLUSerror, NULL } 
 }; 

struct pointer arraysra[T_SIZE] = {  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sraPLUSaddu, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL }  ,  { &&sra, NULL } 
 }; 

struct pointer arraysrl[T_SIZE] = {  { &&srlPLUSsll, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSsra, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL } 
 ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL } 
 ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL } 
 ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSaddu, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSor, NULL }  ,  { &&srlPLUSxor, NULL }  ,  { &&srl, NULL } 
 ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSbne, NULL }  ,  { &&srl, NULL } 
 ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSandi, NULL }  ,  { &&srlPLUSori, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSlui, NULL }  ,  { &&srlPLUSerror, NULL } 
 ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL } 
 ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL } 
 ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srl, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srl, NULL } 
 ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL } 
 ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL }  ,  { &&srlPLUSerror, NULL } 
 }; 

struct pointer arraysubu[T_SIZE] = {  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subuPLUSaddu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subuPLUSand, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subuPLUSaddiu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subuPLUSsw, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL }  ,  { &&subu, NULL } 
 }; 

struct pointer arraybgtz[T_SIZE] = {  { &&bgtzPLUSsll, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL }  ,  { &&bgtz, NULL } 
 }; 

struct pointer arrayandi[T_SIZE] = {  { &&andiPLUSsll, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andiPLUSjr, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andiPLUSsubu, NULL }  ,  { &&andi, NULL }  ,  { &&andiPLUSor, NULL }  ,  { &&andiPLUSxor, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL } 
 ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL }  ,  { &&andi, NULL } 
 }; 

struct pointer arraymult[T_SIZE] = {  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&multPLUSmfhi, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL }  ,  { &&mult, NULL } 
 }; 

struct pointer arrayslt[T_SIZE] = {  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&sltPLUSaddu, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&sltPLUSbeq, NULL }  ,  { &&sltPLUSbne, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&sltPLUSlw, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL } 
 ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL }  ,  { &&slt, NULL } 
 }; 

struct pointer arrayslti[T_SIZE] = {  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&sltiPLUSmovn, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&sltiPLUSbeq, NULL }  ,  { &&sltiPLUSbne, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&sltiPLUSsw, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL }  ,  { &&slti, NULL } 
 }; 

struct pointer arraysll[T_SIZE] = {  { &&sllPLUSsll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSsrl, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSmult, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSaddu, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSand, NULL }  ,  { &&sllPLUSor, NULL }  ,  { &&sllPLUSxor, NULL }  ,  { &&sll, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSslt, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSjump, NULL }  ,  { &&sllPLUSjal, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSbne, NULL }  ,  { &&sllPLUSblez, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSaddiu, NULL }  ,  { &&sllPLUSslti, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSandi, NULL }  ,  { &&sllPLUSori, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSlui, NULL }  ,  { &&sll, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSlw, NULL }  ,  { &&sllPLUSlbu, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSsb, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sllPLUSsw, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL } 
 ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL }  ,  { &&sll, NULL } 
 }; 

struct pointer arrayand[T_SIZE] = {  { &&andPLUSsll, NULL }  ,  { &&and, NULL }  ,  { &&andPLUSsrl, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&andPLUSor, NULL }  ,  { &&andPLUSxor, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&andPLUSandi, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL }  ,  { &&and, NULL } 
 }; 

struct pointer arraylbu[T_SIZE] = {  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbuPLUSsubu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbuPLUSxor, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbuPLUSbeq, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbuPLUSaddiu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL }  ,  { &&lbu, NULL } 
 }; 

struct pointer arraysysc[T_SIZE] = {  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&syscPLUSjr, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&syscPLUSjal, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL }  ,  { &&sysc, NULL } 
 }; 

struct pointer arrayjr[T_SIZE] = {  { &&jrPLUSsll, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jrPLUSor, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jrPLUSaddiu, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL }  ,  { &&jr, NULL } 
 }; 

struct pointer arraysw[T_SIZE] = {  { &&swPLUSsll, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&swPLUSaddu, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&swPLUSjump, NULL }  ,  { &&swPLUSjal, NULL }  ,  { &&sw, NULL }  ,  { &&swPLUSbne, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&swPLUSaddiu, NULL }  ,  { &&swPLUSslti, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&swPLUSlui, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&swPLUSlw, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&swPLUSsb, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&swPLUSsw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL } 
 ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL }  ,  { &&sw, NULL } 
 }; 

struct pointer arrayor[T_SIZE] = {  { &&orPLUSsll, NULL }  ,  { &&or, NULL }  ,  { &&orPLUSsrl, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&orPLUSaddu, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&orPLUSor, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&orPLUSsltu, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&orPLUSlui, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&orPLUSsw, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL }  ,  { &&or, NULL } 
 }; 

struct pointer arraysh[T_SIZE] = {  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&shPLUSor, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL }  ,  { &&sh, NULL } 
 }; 

struct pointer arraysb[T_SIZE] = {  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sbPLUSjal, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sbPLUSsh, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL }  ,  { &&sb, NULL } 
 }; 

struct pointer array[T_SIZE] = {  { NULL, arraysll }  ,  { NULL, arrayerror }  ,  { NULL, arraysrl }  ,  { NULL, arraysra }  ,  { &&sllv, NULL }  ,  { NULL, arrayerror }  ,  { &&srlv, NULL }  ,  { &&srav, NULL }  ,  { NULL, arrayjr }  ,  { &&jalr, NULL } 
 ,  { &&movz, NULL }  ,  { NULL, arraymovn }  ,  { NULL, arraysysc }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arraymfhi }  ,  { &&mthi, NULL }  ,  { &&mflo, NULL }  ,  { &&mtlo, NULL } 
 ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arraymult }  ,  { &&multu, NULL }  ,  { &&div, NULL }  ,  { &&divu, NULL }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror } 
 ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { &&add, NULL }  ,  { NULL, arrayaddu }  ,  { &&sub, NULL }  ,  { NULL, arraysubu }  ,  { NULL, arrayand }  ,  { NULL, arrayor }  ,  { NULL, arrayxor }  ,  { NULL, arraynor } 
 ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayslt }  ,  { NULL, arraysltu }  ,  { &&branch, NULL }  ,  { NULL, arrayjump }  ,  { NULL, arrayjal }  ,  { NULL, arraybeq }  ,  { NULL, arraybne }  ,  { NULL, arrayblez } 
 ,  { NULL, arraybgtz }  ,  { &&addi, NULL }  ,  { NULL, arrayaddiu }  ,  { NULL, arrayslti }  ,  { &&sltiu, NULL }  ,  { NULL, arrayandi }  ,  { NULL, arrayori }  ,  { &&xori, NULL }  ,  { NULL, arraylui }  ,  { NULL, arrayerror } 
 ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { &&llo, NULL }  ,  { &&lhi, NULL }  ,  { &&trap, NULL } 
 ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { &&lb, NULL }  ,  { &&lh, NULL }  ,  { &&lwl, NULL }  ,  { NULL, arraylw }  ,  { NULL, arraylbu } 
 ,  { &&lhu, NULL }  ,  { &&lwr, NULL }  ,  { NULL, arrayerror }  ,  { NULL, arraysb }  ,  { NULL, arraysh }  ,  { &&swl, NULL }  ,  { NULL, arraysw }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { &&swr, NULL } 
 ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror } 
 ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror }  ,  { NULL, arrayerror } 
 }; 

  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;

movn:
#if INDIRECT_DEBUG
printf("%d|movn\n",counter);
counter++;
#endif

rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
if (RF[rt] != 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


movz:
#if INDIRECT_DEBUG
printf("%d|movz\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
if (RF[rt] == 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


add:
#if INDIRECT_DEBUG
printf("%d|add\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addu:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


and:
#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


div:
#if INDIRECT_DEBUG
printf("%d|div\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
LO = RF[rs] / RF[rt];
HI = RF[rs] % RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


divu:
#if INDIRECT_DEBUG
printf("%d|divu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
LO = RF[rs] / RF[rt];
HI = RF[rs] % RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


mult:
#if INDIRECT_DEBUG
printf("%d|mult\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


multu:
#if INDIRECT_DEBUG
printf("%d|multu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


nor:
#if INDIRECT_DEBUG
printf("%d|nor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = ~(RF[rs] | RF[rt]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


or:
#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sll:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllv:
#if INDIRECT_DEBUG
printf("%d|sllv\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << RF[rs];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sra:
#if INDIRECT_DEBUG
printf("%d|sra\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if ((int32_t)RF[rt] < 0 && shamt > 0) {
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (int32_t)RF[rt] | ~(~0U >> shamt);
}
else {
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (int32_t)RF[rt] >> shamt;
}
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srav:
#if INDIRECT_DEBUG
printf("%d|srav\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> RF[rs];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srl:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlv:
#if INDIRECT_DEBUG
printf("%d|srlv\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> RF[rs];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sub:
#if INDIRECT_DEBUG
printf("%d|sub\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


subu:
#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xor:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


slt:
#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltu:
#if INDIRECT_DEBUG
printf("%d|sltu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jalr:
#if INDIRECT_DEBUG
printf("%d|jalr\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
RF[31] = PC+8;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jr:
#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


mfhi:
#if INDIRECT_DEBUG
printf("%d|mfhi\n",counter);
counter++;
#endif
rd = (instr0 >> 11) & 0x1F;
RF[rd] = HI;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


mflo:
#if INDIRECT_DEBUG
printf("%d|mflo\n",counter);
counter++;
#endif
rd = (instr0 >> 11) & 0x1F;
RF[rd] = LO;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


mthi:
#if INDIRECT_DEBUG
printf("%d|mthi\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
HI = RF[rs];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


mtlo:
#if INDIRECT_DEBUG
printf("%d|mtlo\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
LO = RF[rs];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sysc:
#if INDIRECT_DEBUG
printf("%d|sysc\n",counter);
counter++;
#endif
if (syscall((uint8_t)RF[2])) //registers $4 and $5 useb by hallcall (sensid and retval respectively)
{
halted = 1; //Syscall returned 1, exit code
goto end;
}
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addi:
#if INDIRECT_DEBUG
printf("%d|addi\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] + immediate; //Implementar trap!
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiu:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andi:
#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


ori:
#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xori:
#if INDIRECT_DEBUG
printf("%d|xori\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rd] = RF[rs] ^ (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lui:
#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lhi:
#if INDIRECT_DEBUG
printf("%d|lhi\n",counter);
counter++;
#endif
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


llo:
#if INDIRECT_DEBUG
printf("%d|llo\n",counter);
counter++;
#endif
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


slti:
#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltiu:
#if INDIRECT_DEBUG
printf("%d|sltiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


branch:
rt = (instr0 >> 16) & 0x1F;
if (RF[rt] == 0b00001) //bgez Rsrc, offset: Branch on Greater Than Equal Zero
{
  #if INDIRECT_DEBUG
  printf("%d|bgez\n",counter);
  counter++;
  #endif
  rs = (instr0 >> 21) & 0x1F;
  if ((int32_t)RF[rs] >= 0)
  {
    immediate = (instr0 >> 0) & 0xFFFF;
    PC  =  nPC;
    nPC  += (immediate << 2);
      if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  }
  else
  {
    PC  =  nPC;
    nPC  += 4;
  }
}
else if (RF[rt] == 0b10001) //bgezal Rsrc, offset: Branch on Greater Than Equal Zero And Link
{
  #if INDIRECT_DEBUG
  printf("%d|bgezal\n",counter);
  counter++;
  #endif
  rs = (instr0 >> 21) & 0x1F;
  if ((int32_t)RF[rs] >= 0)
  {
    RF[31] = PC + 8;
    immediate = (instr0 >> 0) & 0xFFFF;
    PC  =  nPC;
    nPC  += (immediate << 2);
      if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  }
  else
  {
    PC  =  nPC;
    nPC  += 4;
  }
}
else if (RF[rt] == 0b00000) //bltz Rsrc, offset: Branch on Less Than Zero
{
  #if INDIRECT_DEBUG
  printf("%d|bltz\n",counter);
  counter++;
  #endif
  rs = (instr0 >> 21) & 0x1F;
  if ((int32_t)RF[rs] < 0)
  {
    immediate = (instr0 >> 0) & 0xFFFF;
    PC  =  nPC;
    nPC  += (immediate << 2);
      if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  }
  else
  {
    PC  =  nPC;
    nPC  += 4;
  }
}
else if (RF[rt] == 0b10000) //bltzal Rsrc, offset: Branch on Less Than And Link
{
  #if INDIRECT_DEBUG
  printf("%d|bltzal\n",counter);
  counter++;
  #endif
  rs = (instr0 >> 21) & 0x1F;
  if ((int32_t)RF[rs] < 0)
  {
    RF[31] = PC + 8;
    immediate = (instr0 >> 0) & 0xFFFF;
    PC  =  nPC;
    nPC  += (immediate << 2);
      if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  }
  else
  {
    PC  =  nPC;
    nPC  += 4;
  }
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


beq:
#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


bgtz:
#if INDIRECT_DEBUG
printf("%d|bgtz\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
if ((int32_t)RF[rs] > 0)
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


blez:
#if INDIRECT_DEBUG
printf("%d|blez\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
if ((int32_t)RF[rs] <= 0)
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


bne:
#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lb:
#if INDIRECT_DEBUG
printf("%d|lb\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]& 0x7F)  | (uint32_t)(VM_memory[RF[rs] + immediate] & 0x80)<<24; //Load byte carrying signal to the register
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lbu:
#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lh:
#if INDIRECT_DEBUG
printf("%d|lh\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<< 16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0x7FFF) | (uint32_t)((VM_memory[RF[rs] + immediate + 1]) & 0x8000) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lhu:
#if INDIRECT_DEBUG
printf("%d|lhu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<<16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0xFFFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lw:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sb:
#if INDIRECT_DEBUG
printf("%d|sb\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sh:
#if INDIRECT_DEBUG
printf("%d|sh\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sw:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jump:
#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr0 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jal:
#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr0 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


trap:
#if INDIRECT_DEBUG
printf("%d|trap\n",counter);
counter++;
#endif
address = (instr0 >> 0) & 0x3FFFFFF;
syscall((uint8_t)(address&0xFF));
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swl:
#if INDIRECT_DEBUG
printf("%d|swl\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
PC  =  nPC;
nPC  += 4;  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swr:
#if INDIRECT_DEBUG
printf("%d|swr\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
VM_memory[RF[rs] + immediate - 1] = (uint8_t)(RF[rt] & 0xFF00) >> 8;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwl:
#if INDIRECT_DEBUG
printf("%d|lwl\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwr:
#if INDIRECT_DEBUG
printf("%d|lwr\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate -1]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


error:
#if INDIRECT_DEBUG
printf("Error, unknown instr0uction %d.\n", instr0);
#endif
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


movnPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|movn\n",counter);
counter++;
#endif

rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
if (RF[rt] != 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSmult:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|mult\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


movnPLUSbne:
#if INDIRECT_DEBUG
printf("%d|movn\n",counter);
counter++;
#endif

rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
if (RF[rt] != 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


mfhiPLUSsrl:
#if INDIRECT_DEBUG
printf("%d|mfhi\n",counter);
counter++;
#endif
rd = (instr0 >> 11) & 0x1F;
RF[rd] = HI;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


orPLUSsrl:
#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSsubu:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltuPLUSmovn:
#if INDIRECT_DEBUG
printf("%d|sltu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|movn\n",counter);
counter++;
#endif

rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
if (RF[rt] != 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltuPLUSbeq:
#if INDIRECT_DEBUG
printf("%d|sltu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sbPLUSsh:
#if INDIRECT_DEBUG
printf("%d|sb\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sh\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


mfhiPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|mfhi\n",counter);
counter++;
#endif
rd = (instr0 >> 11) & 0x1F;
RF[rd] = HI;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSsll:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andiPLUSor:
#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andiPLUSsubu:
#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltPLUSlw:
#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSjump:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


blezPLUSsll:
#if INDIRECT_DEBUG
printf("%d|blez\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
if ((int32_t)RF[rs] <= 0)
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSsw:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


beqPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSbeq:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andPLUSandi:
#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSslt:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


multPLUSmfhi:
#if INDIRECT_DEBUG
printf("%d|mult\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|mfhi\n",counter);
counter++;
#endif
rd = (instr1 >> 11) & 0x1F;
RF[rd] = HI;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSsb:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sb\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSlbu:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSsll:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


mfhiPLUSmult:
#if INDIRECT_DEBUG
printf("%d|mfhi\n",counter);
counter++;
#endif
rd = (instr0 >> 11) & 0x1F;
RF[rd] = HI;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|mult\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSbne:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


syscPLUSjr:
#if INDIRECT_DEBUG
printf("%d|sysc\n",counter);
counter++;
#endif
if (syscall((uint8_t)RF[2])) //registers $4 and $5 useb by hallcall (sensid and retval respectively)
{
halted = 1; //Syscall returned 1, exit code
goto end;
}
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


luiPLUSlw:
#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSsw:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


norPLUSsrl:
#if INDIRECT_DEBUG
printf("%d|nor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = ~(RF[rs] | RF[rt]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSandi:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSbne:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


errorPLUSlw:
#if INDIRECT_DEBUG
printf("Error, unknown instr0uction %d.\n", instr0);
#endif
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltiPLUSmovn:
#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|movn\n",counter);
counter++;
#endif

rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
if (RF[rt] != 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lbuPLUSsubu:
#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andPLUSsll:
#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSsb:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sb\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSslti:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSmult:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|mult\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSlui:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSsrl:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSjal:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sbPLUSjal:
#if INDIRECT_DEBUG
printf("%d|sb\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andPLUSor:
#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


bnePLUSsll:
#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jumpPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr0 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jalPLUSsll:
#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr0 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSbne:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSand:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


luiPLUSsw:
#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSslti:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andPLUSxor:
#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jumpPLUSsll:
#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr0 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jrPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


orPLUSlui:
#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSlui:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSjump:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSerror:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("Error, unknown instr1uction %d.\n", instr1);
#endif
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltiPLUSsw:
#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


orPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSjal:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSmult:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|mult\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSbne:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


blezPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|blez\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
if ((int32_t)RF[rs] <= 0)
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


subuPLUSsw:
#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


bnePLUSsw:
#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSjr:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSjr:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jalPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr0 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSslt:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSsll:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSori:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSsw:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSlw:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSsll:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


errorPLUSaddu:
#if INDIRECT_DEBUG
printf("Error, unknown instr0uction %d.\n", instr0);
#endif
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSjal:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSxor:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltPLUSbne:
#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSlui:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSlbu:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSori:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


bnePLUSxor:
#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSslt:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSnor:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|nor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = ~(RF[rs] | RF[rt]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSbgtz:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bgtz\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
if ((int32_t)RF[rs] > 0)
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSbeq:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


shPLUSor:
#if INDIRECT_DEBUG
printf("%d|sh\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSbne:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSjump:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSandi:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSsubu:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jumpPLUSsw:
#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr0 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSsra:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sra\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if ((int32_t)RF[rt] < 0 && shamt > 0) {
rd = (instr1 >> 11) & 0x1F;
RF[rd] = (int32_t)RF[rt] | ~(~0U >> shamt);
}
else {
rd = (instr1 >> 11) & 0x1F;
RF[rd] = (int32_t)RF[rt] >> shamt;
}
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andiPLUSxor:
#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSblez:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|blez\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
if ((int32_t)RF[rs] <= 0)
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSjal:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


oriPLUSand:
#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSerror:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("Error, unknown instr1uction %d.\n", instr1);
#endif
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


subuPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSslti:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSsltu:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sltu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSlw:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSandi:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andiPLUSsll:
#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


luiPLUSsrl:
#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSlui:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andiPLUSjr:
#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSjal:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSnor:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|nor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = ~(RF[rs] | RF[rt]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSbne:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSxor:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


oriPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


bnePLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


bgtzPLUSsll:
#if INDIRECT_DEBUG
printf("%d|bgtz\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
if ((int32_t)RF[rs] > 0)
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


luiPLUSlui:
#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


luiPLUSjal:
#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSerror:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("Error, unknown instr1uction %d.\n", instr1);
#endif
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


andPLUSsrl:
#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSxor:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sraPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|sra\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if ((int32_t)RF[rt] < 0 && shamt > 0) {
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (int32_t)RF[rt] | ~(~0U >> shamt);
}
else {
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (int32_t)RF[rt] >> shamt;
}
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSerror:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("Error, unknown instr1uction %d.\n", instr1);
#endif
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jrPLUSsll:
#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSxor:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


oriPLUSmult:
#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|mult\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jalPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr0 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


syscPLUSjal:
#if INDIRECT_DEBUG
printf("%d|sysc\n",counter);
counter++;
#endif
if (syscall((uint8_t)RF[2])) //registers $4 and $5 useb by hallcall (sensid and retval respectively)
{
halted = 1; //Syscall returned 1, exit code
goto end;
}
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSandi:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


orPLUSsll:
#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSsw:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


errorPLUSsubu:
#if INDIRECT_DEBUG
printf("Error, unknown instr0uction %d.\n", instr0);
#endif
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


movnPLUSsll:
#if INDIRECT_DEBUG
printf("%d|movn\n",counter);
counter++;
#endif

rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
if (RF[rt] != 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSlbu:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


errorPLUSerror:
#if INDIRECT_DEBUG
printf("Error, unknown instr0uction %d.\n", instr0);
#endif
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("Error, unknown instr1uction %d.\n", instr1);
#endif
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSlbu:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSor:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


errorPLUSaddiu:
#if INDIRECT_DEBUG
printf("Error, unknown instr0uction %d.\n", instr0);
#endif
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltPLUSbeq:
#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSori:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSlw:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSlui:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSsll:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSsll:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSsysc:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sysc\n",counter);
counter++;
#endif
if (syscall((uint8_t)RF[2])) //registers $4 and $5 useb by hallcall (sensid and retval respectively)
{
halted = 1; //Syscall returned 1, exit code
goto end;
}
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lbuPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


beqPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


mfhiPLUSsll:
#if INDIRECT_DEBUG
printf("%d|mfhi\n",counter);
counter++;
#endif
rd = (instr0 >> 11) & 0x1F;
RF[rd] = HI;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jumpPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr0 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


srlPLUSor:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


movnPLUSandi:
#if INDIRECT_DEBUG
printf("%d|movn\n",counter);
counter++;
#endif

rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
if (RF[rt] != 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSsrl:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSslt:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


swPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSlw:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


bnePLUSaddu:
#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSsltu:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sltu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


orPLUSsw:
#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


oriPLUSandi:
#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


norPLUSjr:
#if INDIRECT_DEBUG
printf("%d|nor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = ~(RF[rs] | RF[rt]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


subuPLUSaddu:
#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSsrl:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSblez:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|blez\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
if ((int32_t)RF[rs] <= 0)
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


orPLUSsltu:
#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sltu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


orPLUSor:
#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSblez:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|blez\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
if ((int32_t)RF[rs] <= 0)
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSsrl:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSlw:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltiPLUSbeq:
#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSslti:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSslti:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltiPLUSbne:
#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


addiuPLUSjump:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


luiPLUSori:
#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lbuPLUSxor:
#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


luiPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSsw:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


subuPLUSand:
#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


jrPLUSor:
#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;



#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


movnPLUSjump:
#if INDIRECT_DEBUG
printf("%d|movn\n",counter);
counter++;
#endif

rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
if (RF[rt] != 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSsll:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSerror:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("Error, unknown instr1uction %d.\n", instr1);
#endif
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


beqPLUSsw:
#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSslti:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSsw:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


xorPLUSxor:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


beqPLUSsll:
#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr0 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


oriPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltuPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|sltu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sltuPLUSlw:
#if INDIRECT_DEBUG
printf("%d|sltu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


oriPLUSsll:
#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr1 >> 6) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
rd = (instr1 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


sllPLUSaddiu:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
shamt = (instr0 >> 6) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSjump:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
PC = nPC;
address = (instr1 >> 0) & 0x3FFFFFF;
nPC = address << 2;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lwPLUSbne:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


adduPLUSandi:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
rd = (instr0 >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
immediate = (instr1 >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


lbuPLUSbeq:
#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
rs = (instr0 >> 21) & 0x1F;
rt = (instr0 >> 16) & 0x1F;
immediate = (instr0 >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;

#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
rs = (instr1 >> 21) & 0x1F;
rt = (instr1 >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr1 >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
    if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


}
else
{
  PC  =  nPC;
  nPC  += 4;
}
  if(mark3[PC] < 0) {
  instr0 = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
  op0 = (instr0 >> 26) & 0x3F;
  if(op0 == 0x0) {
    	funct = (instr0 >> 0) & 0x3F;
    	op0 = op0 + funct;
    }
    else {
    	op0 = op0 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[PC]))) = instr0;
    mark3[PC] = op0;
  }
  else {
    instr0 = *((uint32_t *)(&(VM_memory[PC])));
    op0 = mark3[PC];
  }

p = array;
p = p[op0].next_level;

  if(mark3[nPC] < 0) {
  instr1 = (((uint32_t)VM_memory[nPC] <<24) | ((uint32_t)VM_memory[nPC+1] <<16) | ((uint32_t)VM_memory[nPC+2] <<8) | ((uint32_t)VM_memory[nPC+3]));
  op1 = (instr1 >> 26) & 0x3F;
  if(op1 == 0x0) {
    	funct = (instr1 >> 0) & 0x3F;
    	op1 = op1 + funct;
    }
    else {
    	op1 = op1 + FIX_OP;
    }
    *((uint32_t *) (&(VM_memory[nPC]))) = instr1;
    mark3[nPC] = op1;
  }
  else {
    instr1 = *((uint32_t *)(&(VM_memory[nPC])));
    op1 = mark3[nPC];
  }

goto *p[op1].code;


end:
if(opt) {
  print_memory();
  print_registers();
}

}
