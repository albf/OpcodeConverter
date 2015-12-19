/***************************************************************************
 *   Copyright (C) 2015 by                                                 *
 *   - Carlos Eduardo Millani (carloseduardomillani@gmail.com)             *
 *   - Edson Borin (edson@ic.unicamp.br)                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*
 * Description: This file implements the virtual machine. 
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "vm.h"
#include "syscall.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "journal.h"

void print_memory(void);
void print_registers(void);

//#include "HAL.h"

/*typedef struct decoded_instruction
{
  uint8_t op;
  union {
    struct R {
      // op == 000000
      uint8_t rs, rt, rd, shamt, funct;
    } R;
    struct I {
      uint8_t rs, rt; 
      uint16_t immediate;
    } I;
    struct J {
      uint32_t address;
    } J;
  };
} decoded_instruction_t;*/


/*
 * Central processing unit. It continuously fetches and executes
 * instructions.
 */

/* Register file. */
uint32_t RF[32];
/*VM memory vector*/
uint8_t VM_memory[VM_MEMORY_SZ] = {0};

uint32_t PC = 0;
uint32_t nPC = 4;

void advance_pc(int32_t offset)
{
	PC  =  nPC;
	nPC  += offset;
}


/*void vm_cpu_init_only(uint32_t newPC, int opt)
{
#if COUNTING
	int instruct_cnt = 0;
#endif
#if COUNTING_STACK
	int max_stack = VM_MEMORY_SZ;
#endif
	PC = newPC;
	nPC = 4;
	RF[0] = 0; //Register $zero must always be zero
	RF[31] = 1; //Return default (if the program does not set to zero, should put error)
	uint32_t HI = 0, LO = 0;  
	uint32_t offset = 4;
	uint8_t halted = 0;
	
	return;
}
*/

void vm_cpu(uint32_t newPC, int opt)
{
//#if COUNTING
//	int instruct_cnt = 0;
//#endif
//#if COUNTING_STACK
//	int max_stack = VM_MEMORY_SZ;
//#endif 
	PC = newPC;
	nPC = 4;
	RF[0] = 0; //Register $zero must always be zero
	RF[31] = 1; //Return default (if the program does not set to zero, should put error)
	uint32_t HI = 0, LO = 0;  
	uint32_t offset = 4;
	uint8_t halted = 0;
	
	//return;

	while (!halted) 
	{
//#if COUNTING
//		instruct_cnt++;
//#endif
//#if COUNTING_STACK
//	if (max_stack > RF[29] && RF[29] != 0) max_stack = RF[29]; //Stack == 0 means it`s not yet initialized
//#endif
		uint32_t instr = fetch(PC);
		uint8_t op = (instr >> 26) & 0x3F;
		uint8_t rs = (instr >> 21) & 0x1F;
		uint8_t rt = (instr >> 16) & 0x1F;
		uint8_t rd = (instr >> 11) & 0x1F;
		int16_t immediate = (instr >> 0) & 0xFFFF;
		uint32_t address = (instr >> 0) & 0x3FFFFFF;
		
		offset = 4; //default offset for non-branching instructions
		//TODO Handle events here!
		switch (op) 
		{
			case 0x0: { // 000000 => Register encoding.
				uint8_t shamt = (instr >> 6) & 0x1F;
				uint8_t funct = (instr >> 0) & 0x3F;
			  
				switch (funct) {
					case 0b001011: { // movn	001010 				if(rt!=0) rd = rs
						if (RF[rt] != 0) RF[rd] = RF[rs];
						break;
					}
					case 0b001010: { // movz	001010 				if(rt==0) rd = rs
						if (RF[rt] == 0) RF[rd] = RF[rs];
						break;
					}
					case 0b100000: { // add		100000	ArithLog	$d = $s + $t
						RF[rd] = RF[rs] + RF[rt];
						break;
					}
					case 0b100001: { // addu	100001	ArithLog	$d = $s + $t
						RF[rd] = RF[rs] + RF[rt];
						break;
					}
					case 0b100100: { // and		100100	ArithLog	$d = $s & $t
						RF[rd] = RF[rs] & RF[rt];
						break;
					}
					case 0b011010: { // div		011010  DivMult		lo = $s / $t; hi = $s % $t
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];
						break;
					}
					case 0b011011: { // divu	011011  DivMult		lo = $s / $t; hi = $s % $t
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];  
						break;
					}
					case 0b011000: { // mult	011000  DivMult		hi:lo = $s * $t
						uint64_t mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;
						break;
					}
					case 0b011001: { // multu	011001	DivMult		hi:lo = $s * $t
						uint64_t mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;  
						break;
					}
					case 0b100111: { // nor		100111	ArithLog	$d = ~($s | $t)
						RF[rd] = ~(RF[rs] | RF[rt]);
						break;
					}
					case 0b100101: { // or		100101	ArithLog	$d = $s | $t
						RF[rd] = RF[rs] | RF[rt];
						break;
					}
					case 0b000000: { // sll		000000	Shift		$d = $t << a
						RF[rd] = RF[rt] << shamt;
						break;
					}
					case 0b000100: { // sllv	000100	ShiftV		$d = $t << $s
						RF[rd] = RF[rt] << RF[rs];
						break;
					}
					case 0b000011: { // sra		000011	Shift		$d = $t >> a 
						if ((int32_t)RF[rt] < 0 && shamt > 0)
					        RF[rd] = (int32_t)RF[rt] | ~(~0U >> shamt);
					    else
					        RF[rd] = (int32_t)RF[rt] >> shamt;
						break;
					}
					case 0b000111: { // srav	000111	ShiftV		$d = $t >> $s
						RF[rd] = RF[rt] >> RF[rs];
						break;
					}
					case 0b000010: { // srl		000010	Shift		$d = $t >>> a
						RF[rd] = RF[rt] >> shamt;
						break;
					}
					case 0b000110: { // srlv	000110	ShiftV		$d = $t >>> $s
						RF[rd] = RF[rt] >> RF[rs];  
						break;
					}
					case 0b100010: { // sub		100010	ArithLog	$d = $s - $t
						RF[rd] = RF[rs] - RF[rt];  
						break;
					}
					case 0b100011: { // subu	100011	ArithLog	$d = $s - $t
						RF[rd] = RF[rs] - RF[rt];    
						break;
					}
					case 0b100110: { // xor		100110  ArithLog	$d = $s ^ $t
						RF[rd] = RF[rs] ^ RF[rt];    
						break;
					}
					case 0b101010: { // slt		101010	ArithLog	$d = ($s < $t)
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						break;
					}
					case 0b101011: { // sltu	101011	ArithLog	$d = ($s < $t)
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						break;
					}
					case 0b001001: { // jalr	001001	JumpR		$31 = pc; pc = $s
						RF[31] = PC+8;
						PC = nPC;
						nPC = RF[rs];
						continue;
					}
					case 0b001000: { // jr		001000	JumpR		pc = $s 
						PC = nPC;
						nPC = RF[rs];
						continue;
					}
					case 0b010000: { // mfhi	010000	MoveFrom	$d = hi
						RF[rd] = HI;
						break;
					}
					case 0b010010: { // mflo	010010	MoveFrom	$d = lo
						RF[rd] = LO;
						break;
					}
					case 0b010001: { // mthi	010001	MoveTo		hi = $s
						HI = RF[rs];
						break;
					}
					case 0b010011: { // mtlo	010011	MoveTo		lo = $s
						LO = RF[rs];
						break;
					}
					case 0b001100: { // syscall 	001100	syscall		$2		seen on the .s generated by the ecc compiler
						if (syscall((uint8_t)RF[2])) //registers $4 and $5 useb by hallcall (sensid and retval respectively)
						{
							halted = 1; //Syscall returned 1, exit code
//#if PRINTING
//							printf("Vm stopped by exit signal\n");
//#endif
						}
						break; 
					}	
					default:
					{
//		#if PRINTING
//						if (instr != 0)	printf("\n(ERROR)Invalid instruction %x at PC: %x\n",instr, PC);
//		#endif
					}
					break;
				}      
				break; // case 0x0
			}
			
			//Immediate encoding
			case 0b001000: { //addi    001000  ArithLogI       $t = $s + SE(i)
				RF[rt] = RF[rs] + immediate; //Implementar trap!
				break;
			}
			case 0b001001: { //addiu   001001  ArithLogI       $t = $s + SE(i)
				RF[rt] = (RF[rs] + immediate);
				break;
			}
			case 0b001100: { //andi    001100  ArithLogI       $t = $s & ZE(i)
			    RF[rt] = RF[rs] & (uint32_t)immediate;
				break;
			}
			case 0b001101: { //ori     001101  ArithLogI       $t = $s | ZE(i)
				RF[rt] = RF[rs] | (uint32_t)immediate;
				break;
			}
			case 0b001110: { //xori    001110  ArithLogI       $d = $s ^ ZE(i)
				RF[rd] = RF[rs] ^ (uint32_t)immediate;
				break;
			}
			case 0b001111: 	 //lui	   001111          Rdest, imm: Load Upper Immediate
			case 0b011001: { //lhi     011001  LoadI   HH ($t) = i 
			  	RF[rt] = ((uint32_t)immediate) << 16;
				break;
			}
			case 0b011000: { //llo     011000  LoadI   LH ($t) = i
			  	RF[rt] = immediate;
				break;
			}
			case 0b001010: { //slti    001010  ArithLogI       $t = ($s < SE(i))
			  	RF[rt] = (RF[rs] < immediate)?1:0;
				break;
			}
			case 0b001011: { //sltiu   001011  ArithLogI       $t = ($s < SE(i)) 
				RF[rt] = (RF[rs] < immediate)?1:0;
				break;
			}
			case 0b000001: {
				if (RF[rt] == 0b00001) //bgez Rsrc, offset: Branch on Greater Than Equal Zero
				{
					if ((int32_t)RF[rs] >= 0)
					{
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (RF[rt] == 0b10001) //bgezal Rsrc, offset: Branch on Greater Than Equal Zero And Link
				{
					if ((int32_t)RF[rs] >= 0)
					{
						RF[31] = PC + 8;
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (RF[rt] == 0b00000) //bltz Rsrc, offset: Branch on Less Than Zero
				{
					if ((int32_t)RF[rs] < 0)
					{
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (RF[rt] == 0b10000) //bltzal Rsrc, offset: Branch on Less Than And Link
				{
					if ((int32_t)RF[rs] < 0)
					{
						RF[31] = PC + 8;
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				break;
			}
			case 0b000100: { //beq     000100  Branch  if ($s == $t) pc += i << 2
				if (RF[rs] == RF[rt])
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b000111: { //bgtz    000111  BranchZ if ($s > 0) pc += i << 2
				if ((int32_t)RF[rs] > 0)
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b000110: { //blez    000110  BranchZ if ($s <= 0) pc += i << 2
				if ((int32_t)RF[rs] <= 0)
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b000101: { //bne     000101  Branch  if ($s != $t) pc += i << 2
//#if DEBUGING
//				printf(">>RA:%x\tAddress:%x\n", RF[31], immediate<<2);
//#endif
				if (RF[rs] != RF[rt])
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b100000: { //lb      100000  LoadStore       $t = SE (MEM [$s + i]:1)
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]& 0x7F)  | (uint32_t)(VM_memory[RF[rs] + immediate] & 0x80)<<24; //Load byte carrying signal to the register
				break;
			}
			case 0b100100: { //lbu     100100  LoadStore       $t = ZE (MEM [$s + i]:1)
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
				break;
			}
			case 0b100001: { //lh      100001  LoadStore       $t = SE (MEM [$s + i]:2)
			  	RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<< 16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0x7FFF) | (uint32_t)((VM_memory[RF[rs] + immediate + 1]) & 0x8000) << 16;
				break;
			}
			case 0b100101: { //lhu     100101  LoadStore       $t = ZE (MEM [$s + i]:2)
				RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<<16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0xFFFF);
				break;
			}
			case 0b100011: { //lw      100011  LoadStore       $t = MEM [$s + i]:4
			  	RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
				break;
			}
			case 0b101000: { //sb      101000  LoadStore       MEM [$s + i]:1 = LB ($t)
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				break;
			}
			case 0b101001: { //sh      101001  LoadStore       MEM [$s + i]:2 = LH ($t)
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)(RF[rt] & 0xFF);
				break;
			}
			case 0b101011: { //sw      101011  LoadStore       MEM [$s + i]:4 = $t
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
			  	VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
				break;
			}
	
			//Jump encoding
			
			case 0b000010: { //j       000010  Jump    pc = i << 2
				PC = nPC;
				nPC = address << 2;
				continue;
			}
			case 0b000011: { //jal     000011  Jump    $31 = pc; pc = i << 2
//#if DEBUGING
//				printf(">>RA:%x\tAddress:%x\n", RF[31], address<<2);
//#endif
				RF[31] = PC + 8;
				PC = nPC;
				nPC = address << 2;
				continue;
			}
			case 0b011010: { //trap    011010  Trap    Dependent on operating system; different values for immed26 specify different operations. See the list of traps for information on what the different trap codes do.
				syscall((uint8_t)(address&0xFF));
				break;
			}
			
			
			
			case 0b101010: { //swl Rsrc1, imm(Rsrc2): Store Word Left
				VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
				break;
			}
			case 0b101110: { //swr Rsrc1, imm(Rsrc2): Store Word Right
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				VM_memory[RF[rs] + immediate - 1] = (uint8_t)(RF[rt] & 0xFF00) >> 8;
				break;
			}
			case 0b100010: { //lwl Rdest, imm(Rsrc): Load Word Left
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16);
				break;
			}
			case 0b100110: { //lwr Rdest, imm(Rsrc): Load Word Right
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate -1]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate]);
				break;
			}
			
			//uint8_t op = (instr >> 26) & 0x3F;
			break; //op
			default:
			{
//#if PRINTING
//				if (instr != 0)	printf("\n(ERROR)Invalid instruction %x at PC: %x\n",instr, PC);
//#endif
				break;
			}
		}
		advance_pc(offset);//Advances the PC
	}
	
	if(opt) {
	  print_memory();
	  print_registers();
	}
}
uint32_t fetch(uint32_t PC)
{
#if DEBUGING
	printf("<Will fetch %x\n", PC);
#endif	
	uint32_t ret_val = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
	return ret_val;
}
    
void print_memory(void)
{
	int i;
	for (i = 0; i < VM_MEMORY_SZ; i = i+4)
	{
		printf ("%2x%2x%2x%2x\n", VM_memory[i], VM_memory[i + 1], VM_memory[i + 2], VM_memory[i + 3]);
	}
}
void print_registers(void)
{
	int i;
	for (i = 0; i < 32; i++)
	{
		printf ("%d:%x\n",i+1 ,RF[i]);
	}
}

/* void vm_cpu_count(uint32_t newPC)
{
	int instruct_cnt = 0;
	PC = newPC;
	nPC = 4;
	RF[0] = 0; //Register $zero must always be zero
	RF[31] = 1; //Return default (if the program does not set to zero, should put error)
	uint32_t HI = 0, LO = 0;  
	uint32_t offset = 4;
	uint8_t halted = 0;
	
	while (!halted) 
	{
		instruct_cnt++;
		uint32_t instr = fetch(PC);
		uint8_t op = (instr >> 26) & 0x3F;
		uint8_t rs = (instr >> 21) & 0x1F;
		uint8_t rt = (instr >> 16) & 0x1F;
		uint8_t rd = (instr >> 11) & 0x1F;
		int16_t immediate = (instr >> 0) & 0xFFFF;
		uint32_t address = (instr >> 0) & 0x3FFFFFF;
		
		offset = 4; //default offset for non-branching instructions
		//TODO Handle events here!
		switch (op) 
		{
			case 0x0: { // 000000 => Register encoding.
				uint8_t shamt = (instr >> 6) & 0x1F;
				uint8_t funct = (instr >> 0) & 0x3F;
			  
				switch (funct) {
					case 0b001011: { // movn	001010 				if(rt!=0) rd = rs
						if (RF[rt] != 0) RF[rd] = RF[rs];
						break;
					}
					case 0b001010: { // movz	001010 				if(rt==0) rd = rs
						if (RF[rt] == 0) RF[rd] = RF[rs];
						break;
					}
					case 0b100000: { // add		100000	ArithLog	$d = $s + $t
						RF[rd] = RF[rs] + RF[rt];
						break;
					}
					case 0b100001: { // addu	100001	ArithLog	$d = $s + $t
						RF[rd] = RF[rs] + RF[rt];
						break;
					}
					case 0b100100: { // and		100100	ArithLog	$d = $s & $t
						RF[rd] = RF[rs] & RF[rt];
						break;
					}
					case 0b011010: { // div		011010  DivMult		lo = $s / $t; hi = $s % $t
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];
						break;
					}
					case 0b011011: { // divu	011011  DivMult		lo = $s / $t; hi = $s % $t
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];  
						break;
					}
					case 0b011000: { // mult	011000  DivMult		hi:lo = $s * $t
						uint64_t mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;
						break;
					}
					case 0b011001: { // multu	011001	DivMult		hi:lo = $s * $t
						uint64_t mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;  
						break;
					}
					case 0b100111: { // nor		100111	ArithLog	$d = ~($s | $t)
						RF[rd] = ~(RF[rs] | RF[rt]);
						break;
					}
					case 0b100101: { // or		100101	ArithLog	$d = $s | $t
						RF[rd] = RF[rs] | RF[rt];
						break;
					}
					case 0b000000: { // sll		000000	Shift		$d = $t << a
						RF[rd] = RF[rt] << shamt;
						break;
					}
					case 0b000100: { // sllv	000100	ShiftV		$d = $t << $s
						RF[rd] = RF[rt] << RF[rs];
						break;
					}
					case 0b000011: { // sra		000011	Shift		$d = $t >> a 
						if ((int32_t)RF[rt] < 0 && shamt > 0)
					        RF[rd] = (int32_t)RF[rt] | ~(~0U >> shamt);
					    else
					        RF[rd] = (int32_t)RF[rt] >> shamt;
						break;
					}
					case 0b000111: { // srav	000111	ShiftV		$d = $t >> $s
						RF[rd] = RF[rt] >> RF[rs];
						break;
					}
					case 0b000010: { // srl		000010	Shift		$d = $t >>> a
						RF[rd] = RF[rt] >> shamt;
						break;
					}
					case 0b000110: { // srlv	000110	ShiftV		$d = $t >>> $s
						RF[rd] = RF[rt] >> RF[rs];  
						break;
					}
					case 0b100010: { // sub		100010	ArithLog	$d = $s - $t
						RF[rd] = RF[rs] - RF[rt];  
						break;
					}
					case 0b100011: { // subu	100011	ArithLog	$d = $s - $t
						RF[rd] = RF[rs] - RF[rt];    
						break;
					}
					case 0b100110: { // xor		100110  ArithLog	$d = $s ^ $t
						RF[rd] = RF[rs] ^ RF[rt];    
						break;
					}
					case 0b101010: { // slt		101010	ArithLog	$d = ($s < $t)
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						break;
					}
					case 0b101011: { // sltu	101011	ArithLog	$d = ($s < $t)
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						break;
					}
					case 0b001001: { // jalr	001001	JumpR		$31 = pc; pc = $s
						RF[31] = PC+8;
						PC = nPC;
						nPC = RF[rs];
						continue;
					}
					case 0b001000: { // jr		001000	JumpR		pc = $s 
						PC = nPC;
						nPC = RF[rs];
						continue;
					}
					case 0b010000: { // mfhi	010000	MoveFrom	$d = hi
						RF[rd] = HI;
						break;
					}
					case 0b010010: { // mflo	010010	MoveFrom	$d = lo
						RF[rd] = LO;
						break;
					}
					case 0b010001: { // mthi	010001	MoveTo		hi = $s
						HI = RF[rs];
						break;
					}
					case 0b010011: { // mtlo	010011	MoveTo		lo = $s
						LO = RF[rs];
						break;
					}
					case 0b001100: { // syscall 	001100	syscall		$2		seen on the .s generated by the ecc compiler
						if (syscall((uint8_t)RF[2])) //registers $4 and $5 useb by hallcall (sensid and retval respectively)
						{
							halted = 1; //Syscall returned 1, exit code
						}
						break; 
					}	
					default:
					{
					}
					break;
				}      
				break; // case 0x0
			}
			
			//Immediate encoding
			case 0b001000: { //addi    001000  ArithLogI       $t = $s + SE(i)
				RF[rt] = RF[rs] + immediate; //Implementar trap!
				break;
			}
			case 0b001001: { //addiu   001001  ArithLogI       $t = $s + SE(i)
				RF[rt] = (RF[rs] + immediate);
				break;
			}
			case 0b001100: { //andi    001100  ArithLogI       $t = $s & ZE(i)
			    RF[rt] = RF[rs] & (uint32_t)immediate;
				break;
			}
			case 0b001101: { //ori     001101  ArithLogI       $t = $s | ZE(i)
				RF[rt] = RF[rs] | (uint32_t)immediate;
				break;
			}
			case 0b001110: { //xori    001110  ArithLogI       $d = $s ^ ZE(i)
				RF[rd] = RF[rs] ^ (uint32_t)immediate;
				break;
			}
			case 0b001111: 	 //lui	   001111          Rdest, imm: Load Upper Immediate
			case 0b011001: { //lhi     011001  LoadI   HH ($t) = i 
			  	RF[rt] = ((uint32_t)immediate) << 16;
				break;
			}
			case 0b011000: { //llo     011000  LoadI   LH ($t) = i
			  	RF[rt] = immediate;
				break;
			}
			case 0b001010: { //slti    001010  ArithLogI       $t = ($s < SE(i))
			  	RF[rt] = (RF[rs] < immediate)?1:0;
				break;
			}
			case 0b001011: { //sltiu   001011  ArithLogI       $t = ($s < SE(i)) 
				RF[rt] = (RF[rs] < immediate)?1:0;
				break;
			}
			case 0b000001: {
				if (RF[rt] == 0b00001) //bgez Rsrc, offset: Branch on Greater Than Equal Zero
				{
					if ((int32_t)RF[rs] >= 0)
					{
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (RF[rt] == 0b10001) //bgezal Rsrc, offset: Branch on Greater Than Equal Zero And Link
				{
					if ((int32_t)RF[rs] >= 0)
					{
						RF[31] = PC + 8;
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (RF[rt] == 0b00000) //bltz Rsrc, offset: Branch on Less Than Zero
				{
					if ((int32_t)RF[rs] < 0)
					{
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (RF[rt] == 0b10000) //bltzal Rsrc, offset: Branch on Less Than And Link
				{
					if ((int32_t)RF[rs] < 0)
					{
						RF[31] = PC + 8;
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				break;
			}
			case 0b000100: { //beq     000100  Branch  if ($s == $t) pc += i << 2
				if (RF[rs] == RF[rt])
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b000111: { //bgtz    000111  BranchZ if ($s > 0) pc += i << 2
				if ((int32_t)RF[rs] > 0)
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b000110: { //blez    000110  BranchZ if ($s <= 0) pc += i << 2
				if ((int32_t)RF[rs] <= 0)
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b000101: { //bne     000101  Branch  if ($s != $t) pc += i << 2
				if (RF[rs] != RF[rt])
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b100000: { //lb      100000  LoadStore       $t = SE (MEM [$s + i]:1)
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]& 0x7F)  | (uint32_t)(VM_memory[RF[rs] + immediate] & 0x80)<<24; //Load byte carrying signal to the register
				break;
			}
			case 0b100100: { //lbu     100100  LoadStore       $t = ZE (MEM [$s + i]:1)
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
				break;
			}
			case 0b100001: { //lh      100001  LoadStore       $t = SE (MEM [$s + i]:2)
			  	RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<< 16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0x7FFF) | (uint32_t)((VM_memory[RF[rs] + immediate + 1]) & 0x8000) << 16;
				break;
			}
			case 0b100101: { //lhu     100101  LoadStore       $t = ZE (MEM [$s + i]:2)
				RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<<16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0xFFFF);
				break;
			}
			case 0b100011: { //lw      100011  LoadStore       $t = MEM [$s + i]:4
			  	RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
				break;
			}
			case 0b101000: { //sb      101000  LoadStore       MEM [$s + i]:1 = LB ($t)
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				break;
			}
			case 0b101001: { //sh      101001  LoadStore       MEM [$s + i]:2 = LH ($t)
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)(RF[rt] & 0xFF);
				break;
			}
			case 0b101011: { //sw      101011  LoadStore       MEM [$s + i]:4 = $t
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
			  	VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
				break;
			}
	
			//Jump encoding
			
			case 0b000010: { //j       000010  Jump    pc = i << 2
				PC = nPC;
				nPC = address << 2;
				continue;
			}
			case 0b000011: { //jal     000011  Jump    $31 = pc; pc = i << 2
				RF[31] = PC + 8;
				PC = nPC;
				nPC = address << 2;
				continue;
			}
			case 0b011010: { //trap    011010  Trap    Dependent on operating system; different values for immed26 specify different operations. See the list of traps for information on what the different trap codes do.
				syscall((uint8_t)(address&0xFF));
				break;
			}
			
			
			
			case 0b101010: { //swl Rsrc1, imm(Rsrc2): Store Word Left
				VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
				break;
			}
			case 0b101110: { //swr Rsrc1, imm(Rsrc2): Store Word Right
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				VM_memory[RF[rs] + immediate - 1] = (uint8_t)(RF[rt] & 0xFF00) >> 8;
				break;
			}
			case 0b100010: { //lwl Rdest, imm(Rsrc): Load Word Left
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16);
				break;
			}
			case 0b100110: { //lwr Rdest, imm(Rsrc): Load Word Right
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate -1]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate]);
				break;
			}
			
			//uint8_t op = (instr >> 26) & 0x3F;
			break; //op
			default:
			{
				break;
			}
		}
		advance_pc(offset);//Advances the PC
	}
	printf("%d", instruct_cnt);
	//printnum(instruct_cnt);
} */

//#define NUM_INSTR 64

/*void vm_cpu_identify_instructions(uint32_t newPC)
{
	int instruct_cnt = 0;
	PC = newPC;
	nPC = 4;
	RF[0] = 0; //Register $zero must always be zero
	RF[31] = 1; //Return default (if the program does not set to zero, should put error)
	uint32_t HI = 0, LO = 0;  
	uint32_t offset = 4;
	uint8_t halted = 0;
	
	int usage[NUM_INSTR];
	int i;
	
	struct journal dia;
	struct j_entry * j_entry;
	int j_id;
	char * j_text;
	
	JOURNAL_init(&dia, 1, 0, 0);
	j_id = JOURNAL_get_id(&dia, 'i');
	
	for (i=0; i<NUM_INSTR; i++)
	  usage[i] = 0;

	while (!halted) 
	{
		instruct_cnt++;
		uint32_t instr = fetch(PC);
		uint8_t op = (instr >> 26) & 0x3F;
		uint8_t rs = (instr >> 21) & 0x1F;
		uint8_t rt = (instr >> 16) & 0x1F;
		uint8_t rd = (instr >> 11) & 0x1F;
		int16_t immediate = (instr >> 0) & 0xFFFF;
		uint32_t address = (instr >> 0) & 0x3FFFFFF;
		
		offset = 4; //default offset for non-branching instructions
		//TODO Handle events here!
		switch (op) 
		{
			case 0x0: { // 000000 => Register encoding.
				uint8_t shamt = (instr >> 6) & 0x1F;
				uint8_t funct = (instr >> 0) & 0x3F;
			  
				switch (funct) {
					case 0b001011: { // movn	001010 				if(rt!=0) rd = rs
						//usage[0]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "movn\0");
						if (RF[rt] != 0) RF[rd] = RF[rs];
						break;
					}
					case 0b001010: { // movz	001010 				if(rt==0) rd = rs
						//usage[1]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "movz\0");
						if (RF[rt] == 0) RF[rd] = RF[rs];
						break;
					}
					case 0b100000: { // add		100000	ArithLog	$d = $s + $t
						//usage[2]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "add\0");
						RF[rd] = RF[rs] + RF[rt];
						break;
					}
					case 0b100001: { // addu	100001	ArithLog	$d = $s + $t
						//usage[3]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "addu\0");
						RF[rd] = RF[rs] + RF[rt];
						break;
					}
					case 0b100100: { // and		100100	ArithLog	$d = $s & $t
						//usage[4]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "and\0");
						RF[rd] = RF[rs] & RF[rt];
						break;
					}
					case 0b011010: { // div		011010  DivMult		lo = $s / $t; hi = $s % $t
						//usage[5]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "div\0");
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];
						break;
					}
					case 0b011011: { // divu	011011  DivMult		lo = $s / $t; hi = $s % $t
						//usage[6]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "divu\0");
						LO = RF[rs] / RF[rt];
						HI = RF[rs] % RF[rt];  
						break;
					}
					case 0b011000: { // mult	011000  DivMult		hi:lo = $s * $t
						//usage[7]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "mult\0");
						uint64_t mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;
						break;
					}
					case 0b011001: { // multu	011001	DivMult		hi:lo = $s * $t
						//usage[8]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "multu\0");
						uint64_t mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
						HI = (mult >> 32) & 0xFFFFFFFF;
						LO = mult & 0xFFFFFFFF;  
						break;
					}
					case 0b100111: { // nor		100111	ArithLog	$d = ~($s | $t)
						//usage[9]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "nor\0");
						RF[rd] = ~(RF[rs] | RF[rt]);
						break;
					}
					case 0b100101: { // or		100101	ArithLog	$d = $s | $t
						//usage[10]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "or\0");
						RF[rd] = RF[rs] | RF[rt];
						break;
					}
					case 0b000000: { // sll		000000	Shift		$d = $t << a
						//usage[11]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "sll\0");
						//j_entry = JOURNAL_new_entry(&dia, j_id);
						//char * x[100];
						//sprintf(x, " -PC: %d ; rd: %d ; rt : %d ; shamt : %d", PC, (int)rd, (int)rt, (int)shamt);
						//JOURNAL_insert_text(j_entry, x);
						RF[rd] = RF[rt] << shamt;
						break;
					}
					case 0b000100: { // sllv	000100	ShiftV		$d = $t << $s
						//usage[12]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "sllv\0");
						RF[rd] = RF[rt] << RF[rs];
						break;
					}
					case 0b000011: { // sra		000011	Shift		$d = $t >> a 
					    //usage[13]++;
					    j_entry = JOURNAL_new_entry(&dia, j_id);
					    JOURNAL_insert_text(j_entry, "sra\0");
					    if ((int32_t)RF[rt] < 0 && shamt > 0)
					        RF[rd] = (int32_t)RF[rt] | ~(~0U >> shamt);
					    else
					        RF[rd] = (int32_t)RF[rt] >> shamt;
						break;
					}
					case 0b000111: { // srav	000111	ShiftV		$d = $t >> $s
						//usage[14]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "srav\0");
						RF[rd] = RF[rt] >> RF[rs];
						break;
					}
					case 0b000010: { // srl		000010	Shift		$d = $t >>> a
						//usage[15]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "srl\0");
						RF[rd] = RF[rt] >> shamt;
						break;
					}
					case 0b000110: { // srlv	000110	ShiftV		$d = $t >>> $s
						//usage[16]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "srlv\0");
						RF[rd] = RF[rt] >> RF[rs];  
						break;
					}
					case 0b100010: { // sub		100010	ArithLog	$d = $s - $t
						//usage[17]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "sub\0");
						RF[rd] = RF[rs] - RF[rt];  
						break;
					}
					case 0b100011: { // subu	100011	ArithLog	$d = $s - $t
						//usage[18]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "subu\0");
						RF[rd] = RF[rs] - RF[rt];    
						break;
					}
					case 0b100110: { // xor		100110  ArithLog	$d = $s ^ $t
						//usage[19]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "xor\0");
						RF[rd] = RF[rs] ^ RF[rt];
						break;
					}
					case 0b101010: { // slt		101010	ArithLog	$d = ($s < $t)
						//usage[20]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "slt\0");
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						break;
					}
					case 0b101011: { // sltu	101011	ArithLog	$d = ($s < $t)
						//usage[21]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "sltu\0");
						RF[rd] = (RF[rs] < RF[rt])?1:0;
						break;
					}
					case 0b001001: { // jalr	001001	JumpR		$31 = pc; pc = $s
						//usage[22]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "jumpr1\0");
						RF[31] = PC+8;
						PC = nPC;
						nPC = RF[rs];
						continue;
					}
					case 0b001000: { // jr		001000	JumpR		pc = $s
						//usage[23]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "jumpr2\0");
						PC = nPC;
						nPC = RF[rs];
						continue;
					}
					case 0b010000: { // mfhi	010000	MoveFrom	$d = hi
						//usage[24]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "mhfi\0");
						RF[rd] = HI;
						break;
					}
					case 0b010010: { // mflo	010010	MoveFrom	$d = lo
						//usage[25]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "mflo\0");
						RF[rd] = LO;
						break;
					}
					case 0b010001: { // mthi	010001	MoveTo		hi = $s
						//usage[26]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "mthi\0");
						HI = RF[rs];
						break;
					}
					case 0b010011: { // mtlo	010011	MoveTo		lo = $s
						//usage[27]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "mtlo\0");
						LO = RF[rs];
						break;
					}
					case 0b001100: { // syscall 	001100	syscall		$2		seen on the .s generated by the ecc compiler
						//usage[28]++;
						j_entry = JOURNAL_new_entry(&dia, j_id);
						JOURNAL_insert_text(j_entry, "syscall\0");
						if (syscall((uint8_t)RF[2])) //registers $4 and $5 useb by hallcall (sensid and retval respectively)
						{
							halted = 1; //Syscall returned 1, exit code
						}
						break; 
					}	
					default:
					{
					}
					break;
				}      
				break; // case 0x0
			}
			
			//Immediate encoding
			case 0b001000: { //addi    001000  ArithLogI       $t = $s + SE(i)
				//usage[29]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "addi\0");
				RF[rt] = RF[rs] + immediate; //Implementar trap!
				break;
			}
			case 0b001001: { //addiu   001001  ArithLogI       $t = $s + SE(i)
				//usage[30]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "addiu\0");
				RF[rt] = (RF[rs] + immediate);
				break;
			}
			case 0b001100: { //andi    001100  ArithLogI       $t = $s & ZE(i)
				//usage[31]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "andi\0");
				RF[rt] = RF[rs] & (uint32_t)immediate;
				break;
			}
			case 0b001101: { //ori     001101  ArithLogI       $t = $s | ZE(i)
				//usage[32]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "ori\0");
				RF[rt] = RF[rs] | (uint32_t)immediate;
				break;
			}
			case 0b001110: { //xori    001110  ArithLogI       $d = $s ^ ZE(i)
				//usage[33]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "xori\0");
				RF[rd] = RF[rs] ^ (uint32_t)immediate;
				break;
			}
			case 0b001111: 	 //lui	   001111          Rdest, imm: Load Upper Immediate
				//usage[34]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "lui\0");
			  	RF[rt] = ((uint32_t)immediate) << 16;
				break;
			case 0b011001: { //lhi     011001  LoadI   HH ($t) = i 
				//usage[35]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "lhi\0");
			  	RF[rt] = ((uint32_t)immediate) << 16;
				break;
			}
			case 0b011000: { //llo     011000  LoadI   LH ($t) = i
				//usage[36]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "llo\0");
			  	RF[rt] = immediate;
				break;
			}
			case 0b001010: { //slti    001010  ArithLogI       $t = ($s < SE(i))
				//usage[37]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "slti\0");
			  	RF[rt] = (RF[rs] < immediate)?1:0;
				break;
			}
			case 0b001011: { //sltiu   001011  ArithLogI       $t = ($s < SE(i)) 
				//usage[38]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "sltiu\0");
				RF[rt] = (RF[rs] < immediate)?1:0;
				break;
			}
			case 0b000001: {
				if (RF[rt] == 0b00001) //bgez Rsrc, offset: Branch on Greater Than Equal Zero
				{
					//usage[39]++;
					j_entry = JOURNAL_new_entry(&dia, j_id);
					JOURNAL_insert_text(j_entry, "bgez\0");
					if ((int32_t)RF[rs] >= 0)
					{
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (RF[rt] == 0b10001) //bgezal Rsrc, offset: Branch on Greater Than Equal Zero And Link
				{
					//usage[40]++;
					j_entry = JOURNAL_new_entry(&dia, j_id);
					JOURNAL_insert_text(j_entry, "bgezal\0");
					if ((int32_t)RF[rs] >= 0)
					{
						RF[31] = PC + 8;
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (RF[rt] == 0b00000) //bltz Rsrc, offset: Branch on Less Than Zero
				{
					//usage[41]++;
					j_entry = JOURNAL_new_entry(&dia, j_id);
					JOURNAL_insert_text(j_entry, "bltz\0");
					if ((int32_t)RF[rs] < 0)
					{
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				else if (RF[rt] == 0b10000) //bltzal Rsrc, offset: Branch on Less Than And Link
				{
					//usage[42]++;
					j_entry = JOURNAL_new_entry(&dia, j_id);
					JOURNAL_insert_text(j_entry, "bltzal\0");
					if ((int32_t)RF[rs] < 0)
					{
						RF[31] = PC + 8;
						advance_pc(immediate << 2);
						continue;
					}
					else
					{
						break;
					}
				}
				break;
			}
			case 0b000100: { //beq     000100  Branch  if ($s == $t) pc += i << 2
				//usage[43]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "beq\0");
				if (RF[rs] == RF[rt])
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b000111: { //bgtz    000111  BranchZ if ($s > 0) pc += i << 2
				//usage[44]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "bgtz\0");
				if ((int32_t)RF[rs] > 0)
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b000110: { //blez    000110  BranchZ if ($s <= 0) pc += i << 2
				//usage[45]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "blez\0");
				if ((int32_t)RF[rs] <= 0)
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b000101: { //bne     000101  Branch  if ($s != $t) pc += i << 2
				//usage[46]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "bne\0");
				if (RF[rs] != RF[rt])
				{
					advance_pc(immediate << 2);
					continue;
				}
				else
				{
					break;
				}
				break;
			}
			case 0b100000: { //lb      100000  LoadStore       $t = SE (MEM [$s + i]:1)
				//usage[47]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "lb\0");
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]& 0x7F)  | (uint32_t)(VM_memory[RF[rs] + immediate] & 0x80)<<24; //Load byte carrying signal to the register
				break;
			}
			case 0b100100: { //lbu     100100  LoadStore       $t = ZE (MEM [$s + i]:1)
				//usage[48]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "lbu\0");
			  	RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
				break;
			}
			case 0b100001: { //lh      100001  LoadStore       $t = SE (MEM [$s + i]:2)
				//usage[49]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "lh\0");
			  	RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<< 16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0x7FFF) | (uint32_t)((VM_memory[RF[rs] + immediate + 1]) & 0x8000) << 16;
				break;
			}
			case 0b100101: { //lhu     100101  LoadStore       $t = ZE (MEM [$s + i]:2)
				//usage[50]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "lhu\0");
				RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<<16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0xFFFF);
				break;
			}
			case 0b100011: { //lw      100011  LoadStore       $t = MEM [$s + i]:4
				//usage[51]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "lw\0");
			  	RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
				break;
			}
			case 0b101000: { //sb      101000  LoadStore       MEM [$s + i]:1 = LB ($t)
				//usage[52]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "sb\0");
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				break;
			}
			case 0b101001: { //sh      101001  LoadStore       MEM [$s + i]:2 = LH ($t)
				//usage[53]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "sh\0");
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)(RF[rt] & 0xFF);
				break;
			}
			case 0b101011: { //sw      101011  LoadStore       MEM [$s + i]:4 = $t
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "sw\0");
				//usage[54]++;
			  	VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
			  	VM_memory[RF[rs] + immediate + 2] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
				VM_memory[RF[rs] + immediate + 3] = (uint8_t)(RF[rt] & 0xFF);
				break;
			}
	
			//Jump encoding
			
			case 0b000010: { //j       000010  Jump    pc = i << 2
				//usage[55]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "jump\0");
				PC = nPC;
				nPC = address << 2;
				continue;
			}
			case 0b000011: { //jal     000011  Jump    $31 = pc; pc = i << 2
				//usage[56]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "jal\0");
				RF[31] = PC + 8;
				PC = nPC;
				nPC = address << 2;
				continue;
			}
			case 0b011010: { //trap    011010  Trap    Dependent on operating system; different values for immed26 specify different operations. See the list of traps for information on what the different trap codes do.
				//usage[57]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "trap\0");
				syscall((uint8_t)(address&0xFF));
				break;
			}
			case 0b101010: { //swl Rsrc1, imm(Rsrc2): Store Word Left
				//usage[58]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "swl\0");
				VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
				VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
				break;
			}
			case 0b101110: { //swr Rsrc1, imm(Rsrc2): Store Word Right
				//usage[59]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "swr\0");
			  	VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
				VM_memory[RF[rs] + immediate - 1] = (uint8_t)(RF[rt] & 0xFF00) >> 8;
				break;
			}
			case 0b100010: { //lwl Rdest, imm(Rsrc): Load Word Left
				//usage[60]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "lwl\0");
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16);
				break;
			}
			case 0b100110: { //lwr Rdest, imm(Rsrc): Load Word Right
				//usage[61]++;
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "lwr\0");
				RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate -1]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate]);
				break;
			}
			
			//uint8_t op = (instr >> 26) & 0x3F;
			break; //op
			default:
			{
				j_entry = JOURNAL_new_entry(&dia, j_id);
				JOURNAL_insert_text(j_entry, "#UNKNOWN\0");
				break;
			}
		}
		advance_pc(offset);//Advances the PC
	}

	j_text = JOURNAL_generate_info(&dia, NULL);
	//printf("%s\n", j_text);
	free(j_text);
	JOURNAL_free(&dia);
}*/
	
#ifdef __cplusplus
}
#endif
