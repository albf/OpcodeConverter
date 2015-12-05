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

void vm_cpu_4(uint32_t newPC,int opt, int max)
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

	/* Create a context to hold the JIT's primary state */
	context = jit_context_create();	
	
	/* Lock the context while we build and compile the function */
	jit_context_build_start(context);
		
	signature = jit_type_create_signature(jit_abi_cdecl, jit_type_uint, NULL, 0, 0);
	
	/* Create the function object */
	function = jit_function_create(context, signature);
	jit_type_free(signature);
	
	/* end lib jit variables */

	for (i=0; i<max; i++)
	{
		//instr = fetch(PC);
		instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
		op = (instr >> 26) & 0x3F;
		// rs, rt, rd, immediatte -> Moved
			
		// offset = 4; // default offset for non-branching instructions, not used
		//TODO Handle events here!
		switch (op) 
		{
			case 0x0: { // 000000 => Register encoding.
				funct = (instr >> 0) & 0x3F;
				// shamt moved
			  
				switch (funct) {
					case 0b001011: { // movn	001010 				if(rt!=0) rd = rs
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						if (RF[rt] != 0) RF[rd] = RF[rs];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b001010: { // movz	001010 				if(rt==0) rd = rs
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						if (RF[rt] == 0) RF[rd] = RF[rs];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b100000: { // add		100000	ArithLog	$d = $s + $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] + RF[rt];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b100001: { // addu	100001	ArithLog	$d = $s + $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] + RF[rt];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b100100: { // and		100100	ArithLog	$d = $s & $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] & RF[rt];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b011010: { // div		011010  DivMult		lo = $s / $t; hi = $s % $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b011011: { // divu	011011  DivMult		lo = $s / $t; hi = $s % $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];  
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b011000: { // mult	011000  DivMult		hi:lo = $s * $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b011001: { // multu	011001	DivMult		hi:lo = $s * $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;  
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b100111: { // nor		100111	ArithLog	$d = ~($s | $t)
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = ~(RF[rs] | RF[rt]);
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b100101: { // or		100101	ArithLog	$d = $s | $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] | RF[rt];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b000000: { // sll		000000	Shift		$d = $t << a
						shamt = (instr >> 6) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] << shamt;
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b000100: { // sllv	000100	ShiftV		$d = $t << $s
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] << RF[rs];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b000011: { // sra		000011	Shift		$d = $t >> a 
						shamt = (instr >> 6) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						if ((int32_t)RF[rt] < 0 && shamt > 0) {
						  rd = (instr >> 11) & 0x1F;
						  RF[rd] = (int32_t)RF[rt] | ~(~0U >> shamt);
						}
						else {
						  rd = (instr >> 11) & 0x1F;
						  RF[rd] = (int32_t)RF[rt] >> shamt;
						}
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b000111: { // srav	000111	ShiftV		$d = $t >> $s
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] >> RF[rs];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b000010: { // srl		000010	Shift		$d = $t >>> a
						shamt = (instr >> 6) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] >> shamt;
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b000110: { // srlv	000110	ShiftV		$d = $t >>> $s
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] >> RF[rs];  
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b100010: { // sub		100010	ArithLog	$d = $s - $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] - RF[rt];  
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b100011: { // subu	100011	ArithLog	$d = $s - $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] - RF[rt];    
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b100110: { // xor		100110  ArithLog	$d = $s ^ $t
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] ^ RF[rt];    
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b101010: { // slt		101010	ArithLog	$d = ($s < $t)
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b101011: { // sltu	101011	ArithLog	$d = ($s < $t)
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b001001: { // jalr	001001	JumpR		$31 = pc; pc = $s
						rs = (instr >> 21) & 0x1F;
						RF[31] = PC+8;
						PC = nPC;
						nPC = RF[rs];
						//continue;
						break;
					}
					case 0b001000: { // jr		001000	JumpR		pc = $s 
						rs = (instr >> 21) & 0x1F;
						PC = nPC;
						nPC = RF[rs];
						//continue;
						break;
					}
					case 0b010000: { // mfhi	010000	MoveFrom	$d = hi
						rd = (instr >> 11) & 0x1F;
						RF[rd] = HI;
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b010010: { // mflo	010010	MoveFrom	$d = lo
						rd = (instr >> 11) & 0x1F;
						RF[rd] = LO;
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b010001: { // mthi	010001	MoveTo		hi = $s
						rs = (instr >> 21) & 0x1F;
						HI = RF[rs];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b010011: { // mtlo	010011	MoveTo		lo = $s
						rs = (instr >> 21) & 0x1F;
						LO = RF[rs];
						PC  =  nPC;
						nPC  += 4;
						break;
					}
					case 0b001100: { // syscall 	001100	syscall		$2		seen on the .s generated by the ecc compiler
						if (syscall((uint8_t)RF[2])) //registers $4 and $5 useb by hallcall (sensid and retval respectively)
						{
							halted = 1; //Syscall returned 1, exit code
						}
						PC  =  nPC;
						nPC  += 4;
						break; 
					}	
					default:
					{
		#if PRINTING
						if (instr != 0)	printf("\n(ERROR)Invalid instruction %x at PC: %x\n",instr, PC);
		#endif
					}
					break;
				}      
				break; // case 0x0
			}
			
			//Immediate encoding
			case 0b001000: { //addi    001000  ArithLogI       $t = $s + SE(i)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = RF[rs] + immediate; //Implementar trap!
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b001001: { //addiu   001001  ArithLogI       $t = $s + SE(i)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = (RF[rs] + immediate);
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b001100: { //andi    001100  ArithLogI       $t = $s & ZE(i)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = RF[rs] & (uint32_t)immediate;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b001101: { //ori     001101  ArithLogI       $t = $s | ZE(i)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = RF[rs] | (uint32_t)immediate;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b001110: { //xori    001110  ArithLogI       $d = $s ^ ZE(i)
				rs = (instr >> 21) & 0x1F;
				rd = (instr >> 11) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rd] = RF[rs] ^ (uint32_t)immediate;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b001111: 	 //lui	   001111          Rdest, imm: Load Upper Immediate
			case 0b011001: { //lhi     011001  LoadI   HH ($t) = i 
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((uint32_t)immediate) << 16;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b011000: { //llo     011000  LoadI   LH ($t) = i
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = immediate;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b001010: { //slti    001010  ArithLogI       $t = ($s < SE(i))
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = (RF[rs] < immediate)?1:0;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b001011: { //sltiu   001011  ArithLogI       $t = ($s < SE(i)) 
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = (RF[rs] < immediate)?1:0;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b000001: {
				rt = (instr >> 16) & 0x1F;
				if (RF[rt] == 0b00001) //bgez Rsrc, offset: Branch on Greater Than Equal Zero
				{
					rs = (instr >> 21) & 0x1F;
					if ((int32_t)RF[rs] >= 0)
					{
						immediate = (instr >> 0) & 0xFFFF;	
						PC  =  nPC;
						nPC  += (immediate << 2);
						//advance_pc(immediate << 2);
						//continue;
						break;
					}
					else
					{
						PC  =  nPC;
						nPC  += 4;
						break;
					}
				}
				else if (RF[rt] == 0b10001) //bgezal Rsrc, offset: Branch on Greater Than Equal Zero And Link
				{
					rs = (instr >> 21) & 0x1F;
					if ((int32_t)RF[rs] >= 0)
					{
						RF[31] = PC + 8;
						immediate = (instr >> 0) & 0xFFFF;
						PC  =  nPC;
						nPC  += (immediate << 2);
						//advance_pc(immediate << 2);
						//continue;
						break;
					}
					else
					{
						PC  =  nPC;
						nPC  += 4;
						break;
					}
				}
				else if (RF[rt] == 0b00000) //bltz Rsrc, offset: Branch on Less Than Zero
				{
					rs = (instr >> 21) & 0x1F;
					if ((int32_t)RF[rs] < 0)
					{
						immediate = (instr >> 0) & 0xFFFF;
						PC  =  nPC;
						nPC  += (immediate << 2);
						//advance_pc(immediate << 2);
						//continue;
						break;
					}
					else
					{
						PC  =  nPC;
						nPC  += 4;
						break;
					}
				}
				else if (RF[rt] == 0b10000) //bltzal Rsrc, offset: Branch on Less Than And Link
				{
					rs = (instr >> 21) & 0x1F;
					if ((int32_t)RF[rs] < 0)
					{
						RF[31] = PC + 8;
						immediate = (instr >> 0) & 0xFFFF;
						PC  =  nPC;
						nPC  += (immediate << 2);
						//advance_pc(immediate << 2);
						//continue;
						break;
					}
					else
					{
						PC  =  nPC;
						nPC  += 4;
						break;
					}
				}
				break;
			}
			case 0b000100: { //beq     000100  Branch  if ($s == $t) pc += i << 2
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				if (RF[rs] == RF[rt])
				{
					immediate = (instr >> 0) & 0xFFFF;
					PC  =  nPC;
					nPC  += (immediate << 2);
					//advance_pc(immediate << 2);
					//continue;
					break;
				}
				else
				{
					PC  =  nPC;
					nPC  += 4;
					break;
				}
				break;
			}
			case 0b000111: { //bgtz    000111  BranchZ if ($s > 0) pc += i << 2
				rs = (instr >> 21) & 0x1F;
				if ((int32_t)RF[rs] > 0)
				{
					immediate = (instr >> 0) & 0xFFFF;
					PC  =  nPC;
					nPC  += (immediate << 2);
					//advance_pc(immediate << 2);
					//continue;
					break;
				}
				else
				{
					PC  =  nPC;
					nPC  += 4;
					break;
				}
				break;
			}
			case 0b000110: { //blez    000110  BranchZ if ($s <= 0) pc += i << 2
				rs = (instr >> 21) & 0x1F;
				if ((int32_t)RF[rs] <= 0)
				{
					immediate = (instr >> 0) & 0xFFFF;
					PC  =  nPC;
					nPC  += (immediate << 2);
					//advance_pc(immediate << 2);
					//continue;
					break;
				}
				else
				{
					PC  =  nPC;
					nPC  += 4;
					break;
				}
				break;
			}
			case 0b000101: { //bne     000101  Branch  if ($s != $t) pc += i << 2
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				if (RF[rs] != RF[rt])
				{
					immediate = (instr >> 0) & 0xFFFF;
					PC  =  nPC;
					nPC  += (immediate << 2);
					//advance_pc(immediate << 2);
					//continue;
					break;
				}
				else
				{
					PC  =  nPC;
					nPC  += 4;
					break;
				}
				break;
			}
			case 0b100000: { //lb      100000  LoadStore       $t = SE (MEM [$s + i]:1)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]& 0x7F)  | (uint32_t)(VM_memory[RF[rs] + immediate] & 0x80)<<24; //Load byte carrying signal to the register
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b100100: { //lbu     100100  LoadStore       $t = ZE (MEM [$s + i]:1)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b100001: { //lh      100001  LoadStore       $t = SE (MEM [$s + i]:2)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<< 16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0x7FFF) | (uint32_t)((VM_memory[RF[rs] + immediate + 1]) & 0x8000) << 16;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b100101: { //lhu     100101  LoadStore       $t = ZE (MEM [$s + i]:2)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<<16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0xFFFF);
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b100011: { //lw      100011  LoadStore       $t = MEM [$s + i]:4
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b101000: { //sb      101000  LoadStore       MEM [$s + i]:1 = LB ($t)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b101001: { //sh      101001  LoadStore       MEM [$s + i]:2 = LH ($t)
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)(RF[rt] & 0xFF);
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b101011: { //sw      101011  LoadStore       MEM [$s + i]:4 = $t
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
			  	VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
				PC  =  nPC;
				nPC  += 4;
				break;
			}
	
			//Jump encoding
			case 0b000010: { //j       000010  Jump    pc = i << 2
				PC = nPC;
				address = (instr >> 0) & 0x3FFFFFF;
				nPC = address << 2;
				//continue;
				break;
			}
			case 0b000011: { //jal     000011  Jump    $31 = pc; pc = i << 2
#if DEBUGING
				printf(">>RA:%x\tAddress:%x\n", RF[31], address<<2);
#endif
				RF[31] = PC + 8;
				PC = nPC;
				address = (instr >> 0) & 0x3FFFFFF;
				nPC = address << 2;
				//continue;
				break;
			}
			case 0b011010: { //trap    011010  Trap    Dependent on operating system; different values for immed26 specify different operations. See the list of traps for information on what the different trap codes do.
				address = (instr >> 0) & 0x3FFFFFF;
				syscall((uint8_t)(address&0xFF));
				PC  =  nPC;
				nPC  += 4;
				break;
			}	
			case 0b101010: { //swl Rsrc1, imm(Rsrc2): Store Word Left
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b101110: { //swr Rsrc1, imm(Rsrc2): Store Word Right
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				VM_memory[RF[rs] + immediate - 1] = (uint8_t)(RF[rt] & 0xFF00) >> 8;
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b100010: { //lwl Rdest, imm(Rsrc): Load Word Left
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16);
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			case 0b100110: { //lwr Rdest, imm(Rsrc): Load Word Right
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate -1]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate]);
				PC  =  nPC;
				nPC  += 4;
				break;
			}
			//uint8_t op = (instr >> 26) & 0x3F;
			break; //op
			default:
			{
				printf("Error, unknown instruction.\n");
				PC  =  nPC;
				nPC  += 4;
				break;
			}
		}
		//advance_pc(offset);//Advances the PC
	}
	if(opt) {
	  print_memory();
	  print_registers();
	}
}