#include "vm.h"
#include "syscall.h"
#include <inttypes.h>
#include <stdio.h>
#include "HAL.h"

void print_memory(void);
void print_registers(void);

/* Register file. */
extern uint32_t RF[32];
/*VM memory vector*/
extern uint8_t VM_memory[VM_MEMORY_SZ];

extern uint32_t PC;
extern uint32_t nPC;

/*void advance_pc(int32_t offset)
{
	PC  =  nPC;
	nPC  += offset;
} */

void vm_cpu_2(uint32_t newPC,int opt)
{
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

	while (!halted) 
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
/*uint32_t fetch(uint32_t PC)
{
	uint32_t ret_val = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
	return ret_val;
} */

#define FIX_OP 43
#define INDIRECT_DEBUG 0

void vm_cpu_2_indirect(uint32_t newPC,int opt)
{
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
	
#if INDIRECT_DEBUG
	int counter=0;
#endif
	
	// 90 Possibilities        0/5       1/6      2/7      3/8      4/9
	static void *array[] = {  &&sll,   &&error, &&srl,   &&sra,   &&sllv,
				  &&error, &&srlv,  &&srav,  &&jr,    &&jalr,	
				  &&movz,  &&movn,  &&sysc,  &&error, &&error, //10 
				  &&error, &&mfhi,  &&mthi,  &&mflo,  &&mtlo,	
				  &&error, &&error, &&error, &&error, &&mult,  //20 
				  &&multu, &&div,   &&divu,  &&error, &&error,
				  &&error, &&error, &&add,   &&addu,  &&sub,   //30  
				  &&subu,  &&and,   &&or,    &&xor,   &&nor,
				  &&error, &&error, &&slt,   &&sltu,  &&branch,//40  
				  &&jump,  &&jal,   &&beq,   &&bne,   &&blez,	
				  &&bgtz,  &&addi,  &&addiu, &&slti,  &&sltiu, //50  
				  &&andi,  &&ori,   &&xori,  &&lui,   &&error,	
				  &&error, &&error, &&error, &&error, &&error, //60 
				  &&error, &&error, &&llo,   &&lhi,   &&trap,	
				  &&error, &&error, &&error, &&error, &&error, //70
				  &&lb,    &&lh,    &&lwl,   &&lw,    &&lbu,	
				  &&lhu,   &&lwr,   &&error, &&sb,    &&sh,    //80
				  &&swl,   &&sw,    &&error, &&error, &&swr, 
				  &&error, &&error, &&error, &&error, &&error, //90 
				  &&error, &&error, &&error, &&error, &&error,  
				  &&error, &&error, &&error, &&error, &&error, //100 
				  &&error, &&error, &&error, &&error, &&error,  
				  };

//	while (!halted) 
//	{
		// FETCH
		instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
		op = (instr >> 26) & 0x3F;
		if (op == 0x0) {
		  funct = (instr >> 0) & 0x3F;
		  op = op + funct;
		}
		else {
		  op = op + FIX_OP;
		}
		goto *array[op];
		
		// rs, rt, rd, immediatte -> Moved
			
		// offset = 4; // default offset for non-branching instructions, not used
		//TODO Handle events here!
		//switch (op) 
		//{
		//	case 0x0: { // 000000 => Register encoding.
		//		funct = (instr >> 0) & 0x3F;
				// shamt moved
			  
		//		switch (funct) {
		// 0+11 = 11		case 0b001011: { // movn	001010 				if(rt!=0) rd = rs
		movn:
#if INDIRECT_DEBUG
printf("%d|movn\n",counter);
counter++;
#endif
					    
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						if (RF[rt] != 0) RF[rd] = RF[rs];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+10=10		case 0b001010: { // movz	001010 				if(rt==0) rd = rs
		movz:
#if INDIRECT_DEBUG
printf("%d|movz\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						if (RF[rt] == 0) RF[rd] = RF[rs];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+32 = 32		case 0b100000: { // add		100000	ArithLog	$d = $s + $t
		add:
#if INDIRECT_DEBUG
printf("%d|add\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] + RF[rt];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+33 = 33		case 0b100001: { // addu	100001	ArithLog	$d = $s + $t
		addu:
#if INDIRECT_DEBUG
printf("%d|addu\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] + RF[rt];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+36=36		case 0b100100: { // and		100100	ArithLog	$d = $s & $t
		and:
#if INDIRECT_DEBUG
printf("%d|and\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] & RF[rt];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+26=26		case 0b011010: { // div		011010  DivMult		lo = $s / $t; hi = $s % $t
		div:
#if INDIRECT_DEBUG
printf("%d|div\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];
						PC  =  nPC;
						nPC  += 4;

fetch:						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+27=27		case 0b011011: { // divu	011011  DivMult		lo = $s / $t; hi = $s % $t
		divu:
#if INDIRECT_DEBUG
printf("%d|divu\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];  
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+24=24		case 0b011000: { // mult	011000  DivMult		hi:lo = $s * $t
		mult:
#if INDIRECT_DEBUG
printf("%d|mult\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+25=25		case 0b011001: { // multu	011001	DivMult		hi:lo = $s * $t
		multu:
#if INDIRECT_DEBUG
printf("%d|multu\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;  
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+39=39		case 0b100111: { // nor		100111	ArithLog	$d = ~($s | $t)
		nor:
#if INDIRECT_DEBUG
printf("%d|nor\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = ~(RF[rs] | RF[rt]);
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+37=37		case 0b100101: { // or		100101	ArithLog	$d = $s | $t
		or:
#if INDIRECT_DEBUG
printf("%d|or\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] | RF[rt];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+0=0		case 0b000000: { // sll		000000	Shift		$d = $t << a
		sll:
#if INDIRECT_DEBUG
printf("%d|sll\n",counter);
counter++;
#endif
						shamt = (instr >> 6) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] << shamt;
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+4=4		case 0b000100: { // sllv	000100	ShiftV		$d = $t << $s
		sllv:
#if INDIRECT_DEBUG
printf("%d|sllv\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] << RF[rs];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+3=3		case 0b000011: { // sra		000011	Shift		$d = $t >> a 
		sra:
#if INDIRECT_DEBUG
printf("%d|sra\n",counter);
counter++;
#endif
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
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+7=7		case 0b000111: { // srav	000111	ShiftV		$d = $t >> $s
		srav:
#if INDIRECT_DEBUG
printf("%d|srav\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] >> RF[rs];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+2=2		case 0b000010: { // srl		000010	Shift		$d = $t >>> a
		srl:
#if INDIRECT_DEBUG
printf("%d|srl\n",counter);
counter++;
#endif
						shamt = (instr >> 6) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] >> shamt;
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+6=6		case 0b000110: { // srlv	000110	ShiftV		$d = $t >>> $s
		srlv:
#if INDIRECT_DEBUG
printf("%d|srlv\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rt] >> RF[rs];  
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+34=34		case 0b100010: { // sub		100010	ArithLog	$d = $s - $t
		sub:
#if INDIRECT_DEBUG
printf("%d|sub\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] - RF[rt];  
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+35=35		case 0b100011: { // subu	100011	ArithLog	$d = $s - $t
		subu:
#if INDIRECT_DEBUG
printf("%d|subu\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] - RF[rt];    
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+38=38		case 0b100110: { // xor		100110  ArithLog	$d = $s ^ $t
		xor:
#if INDIRECT_DEBUG
printf("%d|xor\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = RF[rs] ^ RF[rt];    
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+42=42		case 0b101010: { // slt		101010	ArithLog	$d = ($s < $t)
		slt:
#if INDIRECT_DEBUG
printf("%d|slt\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+43=43		case 0b101011: { // sltu	101011	ArithLog	$d = ($s < $t)
		sltu:
#if INDIRECT_DEBUG
printf("%d|sltu\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						rt = (instr >> 16) & 0x1F;
						rd = (instr >> 11) & 0x1F;
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+9=9		case 0b001001: { // jalr	001001	JumpR		$31 = pc; pc = $s
		jalr:
#if INDIRECT_DEBUG
printf("%d|jalr\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						RF[31] = PC+8;
						PC = nPC;
						nPC = RF[rs];
						//continue;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+8=8		case 0b001000: { // jr		001000	JumpR		pc = $s 
		jr:
#if INDIRECT_DEBUG
printf("%d|jr\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						PC = nPC;
						nPC = RF[rs];
						//continue;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+16=16		case 0b010000: { // mfhi	010000	MoveFrom	$d = hi
		mfhi:
#if INDIRECT_DEBUG
printf("%d|mfhi\n",counter);
counter++;
#endif
						rd = (instr >> 11) & 0x1F;
						RF[rd] = HI;
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+18=18		case 0b010010: { // mflo	010010	MoveFrom	$d = lo
		mflo:
#if INDIRECT_DEBUG
printf("%d|mflo\n",counter);
counter++;
#endif
						rd = (instr >> 11) & 0x1F;
						RF[rd] = LO;
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+17=17		case 0b010001: { // mthi	010001	MoveTo		hi = $s
		mthi:
#if INDIRECT_DEBUG
printf("%d|mthi\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						HI = RF[rs];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+19=19		case 0b010011: { // mtlo	010011	MoveTo		lo = $s
		mtlo:
#if INDIRECT_DEBUG
printf("%d|mtlo\n",counter);
counter++;
#endif
						rs = (instr >> 21) & 0x1F;
						LO = RF[rs];
						PC  =  nPC;
						nPC  += 4;
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break;
		//			}
		// 0+12=12		case 0b001100: { // syscall 	001100	syscall		$2		seen on the .s generated by the ecc compiler
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
						
						// FETCH
						instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
						op = (instr >> 26) & 0x3F;
						if (op == 0x0) {
						  funct = (instr >> 0) & 0x3F;
						  op = op + funct;
						}
						else {
						  op = op + FIX_OP;
						}
						goto *array[op];
						
		//				break; 
		//			}	
		//			default:
		//			{
		//				if (instr != 0)	printf("\n(ERROR)Invalid instruction %x at PC: %x\n",instr, PC);
		//			}
		//			break;
		//		}      
		//		break; // case 0x0
		//	}
			
			//Immediate encoding
		// 43+8=51	case 0b001000: { //addi    001000  ArithLogI       $t = $s + SE(i)
		addi:
#if INDIRECT_DEBUG
printf("%d|addi\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = RF[rs] + immediate; //Implementar trap!
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+9=52	case 0b001001: { //addiu   001001  ArithLogI       $t = $s + SE(i)
		addiu:
#if INDIRECT_DEBUG
printf("%d|addiu\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = (RF[rs] + immediate);
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+12=55	case 0b001100: { //andi    001100  ArithLogI       $t = $s & ZE(i)
		andi:
#if INDIRECT_DEBUG
printf("%d|andi\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = RF[rs] & (uint32_t)immediate;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+13=56	case 0b001101: { //ori     001101  ArithLogI       $t = $s | ZE(i)
		ori:
#if INDIRECT_DEBUG
printf("%d|ori\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = RF[rs] | (uint32_t)immediate;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+14=57	case 0b001110: { //xori    001110  ArithLogI       $d = $s ^ ZE(i)
		xori:
#if INDIRECT_DEBUG
printf("%d|xori\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rd = (instr >> 11) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rd] = RF[rs] ^ (uint32_t)immediate;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+15=58	case 0b001111: 	 //lui	   001111          Rdest, imm: Load Upper Immediate
		lui:
#if INDIRECT_DEBUG
printf("%d|lui\n",counter);
counter++;
#endif
				// NOTHING IMPLEMENTED, COPIED FROM BELOW
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((uint32_t)immediate) << 16;
				PC  =  nPC;
				nPC  += 4;
			  
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		// 43+25=68	case 0b011001: { //lhi     011001  LoadI   HH ($t) = i 
		lhi:
#if INDIRECT_DEBUG
printf("%d|lhi\n",counter);
counter++;
#endif
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((uint32_t)immediate) << 16;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+24=67	case 0b011000: { //llo     011000  LoadI   LH ($t) = i
		llo:
#if INDIRECT_DEBUG
printf("%d|llo\n",counter);
counter++;
#endif
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = immediate;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+10=53	case 0b001010: { //slti    001010  ArithLogI       $t = ($s < SE(i))
		slti:
#if INDIRECT_DEBUG
printf("%d|slti\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = (RF[rs] < immediate)?1:0;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+11=54	case 0b001011: { //sltiu   001011  ArithLogI       $t = ($s < SE(i)) 
		sltiu:
#if INDIRECT_DEBUG
printf("%d|sltiu\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = (RF[rs] < immediate)?1:0;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+1=44	case 0b000001: {
		branch:
				rt = (instr >> 16) & 0x1F;
				if (RF[rt] == 0b00001) //bgez Rsrc, offset: Branch on Greater Than Equal Zero
				{
#if INDIRECT_DEBUG
printf("%d|bgez\n",counter);
counter++;
#endif
					rs = (instr >> 21) & 0x1F;
					if ((int32_t)RF[rs] >= 0)
					{
						immediate = (instr >> 0) & 0xFFFF;	
						PC  =  nPC;
						nPC  += (immediate << 2);
						//advance_pc(immediate << 2);
						//continue;
						//break;
					}
					else
					{
						PC  =  nPC;
						nPC  += 4;
						//break;
					}
				}
				else if (RF[rt] == 0b10001) //bgezal Rsrc, offset: Branch on Greater Than Equal Zero And Link
				{
#if INDIRECT_DEBUG
printf("%d|bgezal\n",counter);
counter++;
#endif
					rs = (instr >> 21) & 0x1F;
					if ((int32_t)RF[rs] >= 0)
					{
						RF[31] = PC + 8;
						immediate = (instr >> 0) & 0xFFFF;
						PC  =  nPC;
						nPC  += (immediate << 2);
						//advance_pc(immediate << 2);
						//continue;
						//break;
					}
					else
					{
						PC  =  nPC;
						nPC  += 4;
						//break;
					}
				}
				else if (RF[rt] == 0b00000) //bltz Rsrc, offset: Branch on Less Than Zero
				{
#if INDIRECT_DEBUG
printf("%d|bltz\n",counter);
counter++;
#endif
					rs = (instr >> 21) & 0x1F;
					if ((int32_t)RF[rs] < 0)
					{
						immediate = (instr >> 0) & 0xFFFF;
						PC  =  nPC;
						nPC  += (immediate << 2);
						//advance_pc(immediate << 2);
						//continue;
						//break;
					}
					else
					{
						PC  =  nPC;
						nPC  += 4;
						//break;
					}
				}
				else if (RF[rt] == 0b10000) //bltzal Rsrc, offset: Branch on Less Than And Link
				{
#if INDIRECT_DEBUG
printf("%d|bltzal\n",counter);
counter++;
#endif
					rs = (instr >> 21) & 0x1F;
					if ((int32_t)RF[rs] < 0)
					{
						RF[31] = PC + 8;
						immediate = (instr >> 0) & 0xFFFF;
						PC  =  nPC;
						nPC  += (immediate << 2);
						//advance_pc(immediate << 2);
						//continue;
						//break;
					}
					else
					{
						PC  =  nPC;
						nPC  += 4;
						//break;
					}
				}
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+4=47	case 0b000100: { //beq     000100  Branch  if ($s == $t) pc += i << 2
		beq:
#if INDIRECT_DEBUG
printf("%d|beq\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				if (RF[rs] == RF[rt])
				{
					immediate = (instr >> 0) & 0xFFFF;
					PC  =  nPC;
					nPC  += (immediate << 2);
					//advance_pc(immediate << 2);
					//continue;
					//break;
				}
				else
				{
					PC  =  nPC;
					nPC  += 4;
					//break;
				}
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+7=50	case 0b000111: { //bgtz    000111  BranchZ if ($s > 0) pc += i << 2
		bgtz:
#if INDIRECT_DEBUG
printf("%d|bgtz\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				if ((int32_t)RF[rs] > 0)
				{
					immediate = (instr >> 0) & 0xFFFF;
					PC  =  nPC;
					nPC  += (immediate << 2);
					//advance_pc(immediate << 2);
					//continue;
					//break;
				}
				else
				{
					PC  =  nPC;
					nPC  += 4;
					//break;
				}
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+6=49	case 0b000110: { //blez    000110  BranchZ if ($s <= 0) pc += i << 2
		blez:
#if INDIRECT_DEBUG
printf("%d|blez\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				if ((int32_t)RF[rs] <= 0)
				{
					immediate = (instr >> 0) & 0xFFFF;
					PC  =  nPC;
					nPC  += (immediate << 2);
					//advance_pc(immediate << 2);
					//continue;
					//break;
				}
				else
				{
					PC  =  nPC;
					nPC  += 4;
					//break;
				}
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+5=48	case 0b000101: { //bne     000101  Branch  if ($s != $t) pc += i << 2
		bne:
#if INDIRECT_DEBUG
printf("%d|bne\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				if (RF[rs] != RF[rt])
				{
					immediate = (instr >> 0) & 0xFFFF;
					PC  =  nPC;
					nPC  += (immediate << 2);
					//advance_pc(immediate << 2);
					//continue;
					//break;
				}
				else
				{
					PC  =  nPC;
					nPC  += 4;
					//break;
				}
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+32=75	case 0b100000: { //lb      100000  LoadStore       $t = SE (MEM [$s + i]:1)
		lb:
#if INDIRECT_DEBUG
printf("%d|lb\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]& 0x7F)  | (uint32_t)(VM_memory[RF[rs] + immediate] & 0x80)<<24; //Load byte carrying signal to the register
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+36=79	case 0b100100: { //lbu     100100  LoadStore       $t = ZE (MEM [$s + i]:1)
		lbu:
#if INDIRECT_DEBUG
printf("%d|lbu\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+33=76	case 0b100001: { //lh      100001  LoadStore       $t = SE (MEM [$s + i]:2)
		lh:
#if INDIRECT_DEBUG
printf("%d|lh\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<< 16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0x7FFF) | (uint32_t)((VM_memory[RF[rs] + immediate + 1]) & 0x8000) << 16;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+37=80	case 0b100101: { //lhu     100101  LoadStore       $t = ZE (MEM [$s + i]:2)
		lhu:
#if INDIRECT_DEBUG
printf("%d|lhu\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<<16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0xFFFF);
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+35=78	case 0b100011: { //lw      100011  LoadStore       $t = MEM [$s + i]:4
		lw:
#if INDIRECT_DEBUG
printf("%d|lw\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+40=83	case 0b101000: { //sb      101000  Loadtore       MEM [$s + i]:1 = LB ($t)
		sb:
#if INDIRECT_DEBUG
printf("%d|sb\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+41=84	case 0b101001: { //sh      101001  LoadStore       MEM [$s + i]:2 = LH ($t)
		sh:
#if INDIRECT_DEBUG
printf("%d|sh\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)(RF[rt] & 0xFF);
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+43=86	case 0b101011: { //sw      101011  LoadStore       MEM [$s + i]:4 = $t
		sw:
#if INDIRECT_DEBUG
printf("%d|sw\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
			  	VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
	
			//Jump encoding
		// 43+2=45	case 0b000010: { //j       000010  Jump    pc = i << 2
		jump:	
#if INDIRECT_DEBUG
printf("%d|jump\n",counter);
counter++;
#endif
				PC = nPC;
				address = (instr >> 0) & 0x3FFFFFF;
				nPC = address << 2;
				//continue;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+3=46	case 0b000011: { //jal     000011  Jump    $31 = pc; pc = i << 2
		jal:
#if INDIRECT_DEBUG
printf("%d|jal\n",counter);
counter++;
#endif
				RF[31] = PC + 8;
				PC = nPC;
				address = (instr >> 0) & 0x3FFFFFF;
				nPC = address << 2;
				//continue;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+26=69	case 0b011010: { //trap    011010  Trap    Dependent on operating system; different values for immed26 specify different operations. See the list of traps for information on what the different trap codes do.
		trap:
#if INDIRECT_DEBUG
printf("%d|trap\n",counter);
counter++;
#endif
				address = (instr >> 0) & 0x3FFFFFF;
				syscall((uint8_t)(address&0xFF));
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}	
		// 43+42=85	case 0b101010: { //swl Rsrc1, imm(Rsrc2): Store Word Left
		swl:
#if INDIRECT_DEBUG
printf("%d|swl\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+46=89	case 0b101110: { //swr Rsrc1, imm(Rsrc2): Store Word Right
		swr:
#if INDIRECT_DEBUG
printf("%d|swr\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				VM_memory[RF[rs] + immediate - 1] = (uint8_t)(RF[rt] & 0xFF00) >> 8;
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+34=77	case 0b100010: { //lwl Rdest, imm(Rsrc): Load Word Left
		lwl:
#if INDIRECT_DEBUG
printf("%d|lwl\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16);
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
		// 43+38=81	case 0b100110: { //lwr Rdest, imm(Rsrc): Load Word Right
		lwr:
#if INDIRECT_DEBUG
printf("%d|lwr\n",counter);
counter++;
#endif
				rs = (instr >> 21) & 0x1F;
				rt = (instr >> 16) & 0x1F;
				immediate = (instr >> 0) & 0xFFFF;
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate -1]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate]);
				PC  =  nPC;
				nPC  += 4;
						
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
						
		//		break;
		//	}
			//uint8_t op = (instr >> 26) & 0x3F;
		//	break; //op
		//	default:
		//	{
		error:
#if INDIRECT_DEBUG
				printf("Error, unknown instruction %d.\n", instr);
#endif
				PC  =  nPC;
				nPC  += 4;
				// FETCH
				instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
				op = (instr >> 26) & 0x3F;
				if (op == 0x0) {
				  funct = (instr >> 0) & 0x3F;
				  op = op + funct;
				}
				else {
				  op = op + FIX_OP;
				}
				goto *array[op];
		//		break;
		//	}
		//}
		//advance_pc(offset);//Advances the PC
	//}
	
end:
	if(opt) {
	  print_memory();
	  print_registers();
	}
}