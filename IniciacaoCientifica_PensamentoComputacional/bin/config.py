# Must be divisible by 8 (1 byte) and <= 64
bits_per_instruction = 32
endianess = ">"             # < : little-endian ; > : big-indian
expected_extension = ".x"
appended_extension = ".bt"

INIT_POS = 0
BITS_POS = 1

# Variables used to parse
opcode_init = 0
bits_per_opcode = 6
opcode = [opcode_init, bits_per_opcode]

function_init = 26
bits_per_function = 6
function = [function_init, bits_per_function]

TYPE_POS = 0
VALUE_POS = 1
NEW_VALUE_POS = 2
NAME_POS = 3

# Update format: [ [ [opcode, function], [opcode_value, function_value], [newOpcode, newFunction] ] * n ]
translate_table = [
# 0x0  #000000 => Register encoding.
[[opcode, function], [0b000000, 0b001011], [0b000000, 0b001011], 'movn'],   #0 001010 				if(rt!=0) rd = rs
[[opcode, function], [0b000000, 0b001010], [0b000001, 0b001010], 'movz'],   #1 001010 				if(rt==0) rd = rs
[[opcode, function], [0b000000, 0b100000], [0b000010, 0b100000], 'add'],    #2 100000	ArithLog	$d = $s + $t
[[opcode, function], [0b000000, 0b100001], [0b000011, 0b100001], 'addu'],   #3 100001	ArithLog	$d = $s + $t
[[opcode, function], [0b000000, 0b100100], [0b000100, 0b100100], 'and'],    #4 100100	ArithLog	$d = $s & $t
[[opcode, function], [0b000000, 0b011010], [0b000101, 0b011010], 'div'],    #5 011010  DivMult		lo = $s / $t; hi = $s % $t
[[opcode, function], [0b000000, 0b011011], [0b000110, 0b011011], 'divu'],   #6 011011  DivMult		lo = $s / $t; hi = $s % $t
[[opcode, function], [0b000000, 0b011000], [0b000111, 0b011000], 'mult'],   #7 011000  DivMult		hi:lo = $s * $t
[[opcode, function], [0b000000, 0b011001], [0b001000, 0b011001], 'multu'],  #8 011001	DivMult		hi:lo = $s * $t
[[opcode, function], [0b000000, 0b100111], [0b001001, 0b100111], 'nor'],    #9 100111	ArithLog	$d = ~($s | $t)
[[opcode, function], [0b000000, 0b100101], [0b001010, 0b100101], 'or'],     #10 100101	ArithLog	$d = $s | $t
[[opcode, function], [0b000000, 0b000000], [0b001011, 0b000000], 'sll'],	#11 000000	Shift		$d = $t << a
[[opcode, function], [0b000000, 0b000100], [0b001100, 0b000100], 'sllv'],	#12 000100	ShiftV		$d = $t << $s
[[opcode, function], [0b000000, 0b000011], [0b001101, 0b000011], 'sra'],    #13 000011	Shift		$d = $t >> a
[[opcode, function], [0b000000, 0b000111], [0b001110, 0b000111], 'srav'],   #14 000111	ShiftV		$d = $t >> $s
[[opcode, function], [0b000000, 0b000010], [0b001111, 0b000010], 'srl'],    #15 000010	Shift		$d = $t >>> a
[[opcode, function], [0b000000, 0b000110], [0b010000, 0b000110], 'srlv'],   #16 000110	ShiftV		$d = $t >>> $s
[[opcode, function], [0b000000, 0b100010], [0b010001, 0b100010], 'sub'],    #17 100010	ArithLog	$d = $s - $t
[[opcode, function], [0b000000, 0b100011], [0b010010, 0b100011], 'subu'],   #18 100011	ArithLog	$d = $s - $t
[[opcode, function], [0b000000, 0b100110], [0b010011, 0b100110], 'xor'],    #19 100110  ArithLog	$d = $s ^ $t
[[opcode, function], [0b000000, 0b101010], [0b010100, 0b101010], 'slt'],    #20 101010	ArithLog	$d = ($s < $t)
[[opcode, function], [0b000000, 0b101011], [0b010101, 0b101011], 'sltu'],   #21 101011	ArithLog	$d = ($s < $t)
[[opcode, function], [0b000000, 0b001001], [0b010110, 0b001001], 'jalr'],   #22 001001	JumpR		$31 = pc; pc = $s
[[opcode, function], [0b000000, 0b001000], [0b010111, 0b001000], 'jr'],     #23 001000	JumpR		pc = $s
[[opcode, function], [0b000000, 0b010000], [0b011000, 0b010000], 'mfhi'],   #24 010000	MoveFrom	$d = hi
[[opcode, function], [0b000000, 0b010010], [0b011001, 0b010010], 'mflo'],   #25 010010	MoveFrom	$d = lo
[[opcode, function], [0b000000, 0b010001], [0b011010, 0b010001], 'mthi'],   #26 010001	MoveTo		hi = $s
[[opcode, function], [0b000000, 0b010011], [0b011011, 0b010011], 'mtlo'],   #27 010011	MoveTo		lo = $s
[[opcode, function], [0b000000, 0b001100], [0b011100, 0b001100], 'syscall'],#28 001100	syscall		$2	seen on the .s generated by the ecc compiler
[[opcode], [0b001000], [0b011101], 'addi'],    #29 001000  ArithLogI       $t = $s + SE(i)
[[opcode], [0b001001], [0b011110], 'addiu'],   #30 001001  ArithLogI       $t = $s + SE(i)
[[opcode], [0b001100], [0b011111], 'andi'],    #31 001100  ArithLogI       $t = $s & ZE(i)
[[opcode], [0b001101], [0b100000], 'ori'],     #32 001101  ArithLogI       $t = $s | ZE(i)
[[opcode], [0b001110], [0b100001], 'xori'],    #33 001110  ArithLogI       $d = $s ^ ZE(i)
[[opcode], [0b001111], [0b100010], 'lui'],     #34 001111          Rdest, imm: Load Upper Immediate
[[opcode], [0b011001], [0b100011], 'lhi'],     #35 011001  LoadI   HH ($t) = i
[[opcode], [0b011000], [0b100100], 'llo'],     #36  011000  LoadI   LH ($t) = i
[[opcode], [0b001010], [0b100101], 'slti'],    #37 001010  ArithLogI       $t = ($s < SE(i))
[[opcode], [0b001011], [0b100110], 'sltiu'],   #38 001011  ArithLogI       $t = ($s < SE(i))
[[opcode], [0b000001], [0b100111], 'bgez'],    #39 (bgezal/bltz/beq/bltzal
[[opcode], [0b000001], [0b100111], 'bgezal'],  #40 (bgezal/bltz/beq/bltzal
[[opcode], [0b000001], [0b100111], 'bltz'],    #41 (bgezal/bltz/beq/bltzal
[[opcode], [0b000001], [0b100111], 'bltzal'],  #42 (bgezal/bltz/beq/bltzal
[[opcode], [0b000100], [0b101000], 'beq'],     #43 000100  Branch  if ($s == $t) pc += i << 2
[[opcode], [0b000111], [0b101001], 'bgtz'],    #44 000111  BranchZ if ($s > 0) pc += i << 2
[[opcode], [0b000110], [0b101010], 'blez'],    #45 000110  BranchZ if ($s <= 0) pc += i << 2
[[opcode], [0b000101], [0b101011], 'bne'],     #46 000101  Branch  if ($s != $t) pc += i << 2
[[opcode], [0b100000], [0b101100], 'lb'],      #47 100000  LoadStore       $t = SE (MEM [$s + i]:1)
[[opcode], [0b100100], [0b101101], 'lbu'],     #48 100100  LoadStore       $t = ZE (MEM [$s + i]:1)
[[opcode], [0b100001], [0b101110], 'lh'],      #49 100001  LoadStore       $t = SE (MEM [$s + i]:2)
[[opcode], [0b100101], [0b101111], 'lhu'],     #50 100101  LoadStore       $t = ZE (MEM [$s + i]:2)
[[opcode], [0b100011], [0b110000], 'lw'],      #51 100011  LoadStore       $t = MEM [$s + i]:4
[[opcode], [0b101000], [0b110001], 'sb'],      #52 101000  LoadStore       MEM [$s + i]:1 = LB ($t)
[[opcode], [0b101001], [0b110010], 'sh'],      #53 101001  LoadStore       MEM [$s + i]:2 = LH ($t)
[[opcode], [0b101011], [0b110011], 'sw'],      #54 101011  LoadStore       MEM [$s + i]:4 = $t
[[opcode], [0b000010], [0b110100], 'j'],       #55 000010  Jump    pc = i << 2
[[opcode], [0b000011], [0b110101], 'jal'],     #56 000011  Jump    $31 = pc; pc = i << 2
[[opcode], [0b011010], [0b110110], 'trap'],    #57 011010  Trap    Dependent on operating system;
[[opcode], [0b101010], [0b110111], 'swl'],     #58 Rsrc1, imm(Rsrc2): Store Word Left
[[opcode], [0b101110], [0b111000], 'swr'],     #59 Rsrc1, imm(Rsrc2): Store Word Right
[[opcode], [0b100010], [0b111001], 'lwl'],     #60 Rdest, imm(Rsrc): Load Word Left
[[opcode], [0b100110], [0b111010], 'lwr']      #61 Rdest, imm(Rsrc): Load Word Right
]

# codegen related variables

codegen_defines = '''#include "vm.h"
#include "syscall.h"
#include <inttypes.h>
#include <stdio.h>

#define FIX_OP 43
#define INDIRECT_DEBUG 0
#define T_SIZE 110
'''

codegen_global = '''/* Register file. */
extern uint32_t RF[32];
/*VM memory vector*/
extern uint8_t VM_memory[VM_MEMORY_SZ];

extern uint32_t PC;
extern uint32_t nPC;

'''

codegen_signature = 'void vm_cpu_super(uint32_t newPC, int opt)'

codegen_normal_initialisation = '''PC = newPC;
nPC = 4;
RF[0] = 0; //Register $zero must always be zero
RF[31] = 1; //Return default (if the program does not set to zero, should put error)
uint32_t HI = 0, LO = 0;
uint32_t offset = 4;
uint8_t halted = 0;

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

'''

codegen_fetch_initialisation = '''uint32_t instr;
uint8_t op;
'''

codegen_fetch_label = "//FETCH_HERE"
codegen_address_array_name = "static void * array"
codegen_table_size = "T_SIZE"
codegen_address_array =  ["sll",   "error", "srl",   "sra",   "sllv",
				         "error", "srlv",  "srav",  "jr",    "jalr",
				         "movz",  "movn",  "sysc",  "error", "error",
				         "error", "mfhi",  "mthi",  "mflo",  "mtlo",
				         "error", "error", "error", "error", "mult",
				         "multu", "div",   "divu",  "error", "error",
				         "error", "error", "add",   "addu",  "sub",
				         "subu",  "and",   "or",    "xor",   "nor",
				         "error", "error", "slt",   "sltu",  "branch",
				         "jump",  "jal",   "beq",   "bne",   "blez",
				         "bgtz",  "addi",  "addiu", "slti",  "sltiu",
				         "andi",  "ori",   "xori",  "lui",   "error",
				         "error", "error", "error", "error", "error",
				         "error", "error", "llo",   "lhi",   "trap",
				         "error", "error", "error", "error", "error",
				         "lb",    "lh",    "lwl",   "lw",    "lbu",
				         "lhu",   "lwr",   "error", "sb",    "sh",
				         "swl",   "sw",    "error", "error", "swr",
				         "error", "error", "error", "error", "error",
				         "error", "error", "error", "error", "error",
				         "error", "error", "error", "error", "error",
				         "error", "error", "error", "error", "error"]

codegen_opcode_join = "PLUS"

codegen_fetch_calculation = '''instr = (((uint32_t)VM_memory[PC] <<24) | ((uint32_t)VM_memory[PC+1] <<16) | ((uint32_t)VM_memory[PC+2] <<8) | ((uint32_t)VM_memory[PC+3]));
op = (instr >> 26) & 0x3F;
if (op == 0x0) {
  funct = (instr >> 0) & 0x3F;
  op = op + funct;
}
  else {
  op = op + FIX_OP;
}
'''

codegen_PC_variable = "PC"
codegen_nPC_variable = "nPC"
codegen_fetch_goto = '''goto *array'''
codegen_index_variable = "op"

codegen_instructions_code = [
[ "movn",
'''#if INDIRECT_DEBUG
printf("%d|movn\\n",counter);
counter++;
#endif

rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
if (RF[rt] != 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;
'''
],
["movz",
'''#if INDIRECT_DEBUG
printf("%d|movz\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
if (RF[rt] == 0) RF[rd] = RF[rs];
PC  =  nPC;
nPC  += 4;
'''
],
["add",
 '''#if INDIRECT_DEBUG
printf("%d|add\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
'''
],
["addu",
 '''#if INDIRECT_DEBUG
printf("%d|addu\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rs] + RF[rt];
PC  =  nPC;
nPC  += 4;
'''
],
["and",
'''#if INDIRECT_DEBUG
printf("%d|and\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rs] & RF[rt];
PC  =  nPC;
nPC  += 4;
'''
],
["div",
'''#if INDIRECT_DEBUG
printf("%d|div\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
LO = RF[rs] / RF[rt];
HI = RF[rs] % RF[rt];
PC  =  nPC;
nPC  += 4;
'''
],
["divu",
'''#if INDIRECT_DEBUG
printf("%d|divu\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
LO = RF[rs] / RF[rt];
HI = RF[rs] % RF[rt];
PC  =  nPC;
nPC  += 4;
'''
],
["mult",
'''#if INDIRECT_DEBUG
printf("%d|mult\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;
'''
],
["multu",
'''#if INDIRECT_DEBUG
printf("%d|multu\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
mult = (uint64_t)RF[rs] * (uint64_t) RF[rt];
HI = (mult >> 32) & 0xFFFFFFFF;
LO = mult & 0xFFFFFFFF;
PC  =  nPC;
nPC  += 4;
'''
],
["nor",
'''#if INDIRECT_DEBUG
printf("%d|nor\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = ~(RF[rs] | RF[rt]);
PC  =  nPC;
nPC  += 4;
'''
],
["or",
'''#if INDIRECT_DEBUG
printf("%d|or\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rs] | RF[rt];
PC  =  nPC;
nPC  += 4;
'''
],
["sll",
'''#if INDIRECT_DEBUG
printf("%d|sll\\n",counter);
counter++;
#endif
shamt = (instr >> 6) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rt] << shamt;
PC  =  nPC;
nPC  += 4;
'''
],
["sllv",
'''#if INDIRECT_DEBUG
printf("%d|sllv\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rt] << RF[rs];
PC  =  nPC;
nPC  += 4;
'''
],
["sra",
'''#if INDIRECT_DEBUG
printf("%d|sra\\n",counter);
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
'''
],
["srav",
'''#if INDIRECT_DEBUG
printf("%d|srav\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rt] >> RF[rs];
PC  =  nPC;
nPC  += 4;
'''
],
["srl",
'''#if INDIRECT_DEBUG
printf("%d|srl\\n",counter);
counter++;
#endif
shamt = (instr >> 6) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rt] >> shamt;
PC  =  nPC;
nPC  += 4;
'''
],
["srlv",
'''#if INDIRECT_DEBUG
printf("%d|srlv\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rt] >> RF[rs];
PC  =  nPC;
nPC  += 4;
'''
],
["sub",
'''#if INDIRECT_DEBUG
printf("%d|sub\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;
'''
],
["subu",
'''#if INDIRECT_DEBUG
printf("%d|subu\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rs] - RF[rt];
PC  =  nPC;
nPC  += 4;
'''
],
["xor",
'''#if INDIRECT_DEBUG
printf("%d|xor\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = RF[rs] ^ RF[rt];
PC  =  nPC;
nPC  += 4;
'''
],
["slt",
'''#if INDIRECT_DEBUG
printf("%d|slt\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
'''
],
["sltu",
'''#if INDIRECT_DEBUG
printf("%d|sltu\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
rd = (instr >> 11) & 0x1F;
RF[rd] = (RF[rs] < RF[rt])?1:0;
PC  =  nPC;
nPC  += 4;
'''
],
["jalr",
'''#if INDIRECT_DEBUG
printf("%d|jalr\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
RF[31] = PC+8;
PC = nPC;
nPC = RF[rs];
//FETCH_HERE
'''
],
["jr",
'''#if INDIRECT_DEBUG
printf("%d|jr\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
PC = nPC;
nPC = RF[rs];
//FETCH_HERE
'''
],
["mfhi",
'''#if INDIRECT_DEBUG
printf("%d|mfhi\\n",counter);
counter++;
#endif
rd = (instr >> 11) & 0x1F;
RF[rd] = HI;
PC  =  nPC;
nPC  += 4;
'''
],
["mflo",
'''#if INDIRECT_DEBUG
printf("%d|mflo\\n",counter);
counter++;
#endif
rd = (instr >> 11) & 0x1F;
RF[rd] = LO;
PC  =  nPC;
nPC  += 4;
'''
],
["mthi",
'''#if INDIRECT_DEBUG
printf("%d|mthi\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
HI = RF[rs];
PC  =  nPC;
nPC  += 4;
'''
],
["mtlo",
'''#if INDIRECT_DEBUG
printf("%d|mtlo\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
LO = RF[rs];
PC  =  nPC;
nPC  += 4;
'''
],
["sysc",
'''#if INDIRECT_DEBUG
printf("%d|sysc\\n",counter);
counter++;
#endif
if (syscall((uint8_t)RF[2])) //registers $4 and $5 useb by hallcall (sensid and retval respectively)
{
halted = 1; //Syscall returned 1, exit code
goto end;
}
PC  =  nPC;
nPC  += 4;
'''
],
["addi",
'''#if INDIRECT_DEBUG
printf("%d|addi\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = RF[rs] + immediate; //Implementar trap!
PC  =  nPC;
nPC  += 4;
'''
],
["addiu",
'''#if INDIRECT_DEBUG
printf("%d|addiu\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = (RF[rs] + immediate);
PC  =  nPC;
nPC  += 4;
'''
],
["andi",
'''#if INDIRECT_DEBUG
printf("%d|andi\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = RF[rs] & (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
'''
],
["ori",
'''#if INDIRECT_DEBUG
printf("%d|ori\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = RF[rs] | (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
'''
],
["xori",
'''#if INDIRECT_DEBUG
printf("%d|xori\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rd = (instr >> 11) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rd] = RF[rs] ^ (uint32_t)immediate;
PC  =  nPC;
nPC  += 4;
'''
],
["lui",
'''#if INDIRECT_DEBUG
printf("%d|lui\\n",counter);
counter++;
#endif
// NOTHING IMPLEMENTED, COPIED FROM BELOW
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
'''
],
["lhi",
'''#if INDIRECT_DEBUG
printf("%d|lhi\\n",counter);
counter++;
#endif
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)immediate) << 16;
PC  =  nPC;
nPC  += 4;
'''
],
["llo",
'''#if INDIRECT_DEBUG
printf("%d|llo\\n",counter);
counter++;
#endif
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = immediate;
PC  =  nPC;
nPC  += 4;
'''
],
["slti",
'''#if INDIRECT_DEBUG
printf("%d|slti\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
'''
],
["sltiu",
'''#if INDIRECT_DEBUG
printf("%d|sltiu\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = (RF[rs] < immediate)?1:0;
PC  =  nPC;
nPC  += 4;
'''
],
["branch",
'''rt = (instr >> 16) & 0x1F;
if (RF[rt] == 0b00001) //bgez Rsrc, offset: Branch on Greater Than Equal Zero
{
  #if INDIRECT_DEBUG
  printf("%d|bgez\\n",counter);
  counter++;
  #endif
  rs = (instr >> 21) & 0x1F;
  if ((int32_t)RF[rs] >= 0)
  {
    immediate = (instr >> 0) & 0xFFFF;
    PC  =  nPC;
    nPC  += (immediate << 2);
    //FETCH_HERE
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
  printf("%d|bgezal\\n",counter);
  counter++;
  #endif
  rs = (instr >> 21) & 0x1F;
  if ((int32_t)RF[rs] >= 0)
  {
    RF[31] = PC + 8;
    immediate = (instr >> 0) & 0xFFFF;
    PC  =  nPC;
    nPC  += (immediate << 2);
    //FETCH_HERE
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
  printf("%d|bltz\\n",counter);
  counter++;
  #endif
  rs = (instr >> 21) & 0x1F;
  if ((int32_t)RF[rs] < 0)
  {
    immediate = (instr >> 0) & 0xFFFF;
    PC  =  nPC;
    nPC  += (immediate << 2);
    //FETCH_HERE
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
  printf("%d|bltzal\\n",counter);
  counter++;
  #endif
  rs = (instr >> 21) & 0x1F;
  if ((int32_t)RF[rs] < 0)
  {
    RF[31] = PC + 8;
    immediate = (instr >> 0) & 0xFFFF;
    PC  =  nPC;
    nPC  += (immediate << 2);
    //FETCH_HERE
  }
  else
  {
    PC  =  nPC;
    nPC  += 4;
  }
}
'''
],
["beq",
'''#if INDIRECT_DEBUG
printf("%d|beq\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
if (RF[rs] == RF[rt])
{
  immediate = (instr >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
  //FETCH_HERE
}
else
{
  PC  =  nPC;
  nPC  += 4;
}
'''
],
["bgtz",
'''#if INDIRECT_DEBUG
printf("%d|bgtz\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
if ((int32_t)RF[rs] > 0)
{
  immediate = (instr >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
  //FETCH_HERE
}
else
{
  PC  =  nPC;
  nPC  += 4;
}
'''
],
["blez",
'''#if INDIRECT_DEBUG
printf("%d|blez\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
if ((int32_t)RF[rs] <= 0)
{
  immediate = (instr >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
  //FETCH_HERE
}
else
{
  PC  =  nPC;
  nPC  += 4;
}
'''
],
["bne",
'''#if INDIRECT_DEBUG
printf("%d|bne\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
if (RF[rs] != RF[rt])
{
  immediate = (instr >> 0) & 0xFFFF;
  PC  =  nPC;
  nPC  += (immediate << 2);
  //FETCH_HERE
}
else
{
  PC  =  nPC;
  nPC  += 4;
}
'''
],
["lb",
'''#if INDIRECT_DEBUG
printf("%d|lb\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]& 0x7F)  | (uint32_t)(VM_memory[RF[rs] + immediate] & 0x80)<<24; //Load byte carrying signal to the register
PC  =  nPC;
nPC  += 4;
'''
],
["lbu",
'''#if INDIRECT_DEBUG
printf("%d|lbu\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)VM_memory[RF[rs] + immediate]) & 0xFF;
PC  =  nPC;
nPC  += 4;
'''
],
["lh",
'''#if INDIRECT_DEBUG
printf("%d|lh\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<< 16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0x7FFF) | (uint32_t)((VM_memory[RF[rs] + immediate + 1]) & 0x8000) << 16;
PC  =  nPC;
nPC  += 4;
'''
],
["lhu",
'''#if INDIRECT_DEBUG
printf("%d|lhu\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = ((((uint32_t)(VM_memory[RF[rs] + immediate])<<16) | ((uint32_t)VM_memory[RF[rs] + immediate + 1])) & 0xFFFF);
PC  =  nPC;
nPC  += 4;
'''
],
["lw",
'''#if INDIRECT_DEBUG
printf("%d|lw\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16) | ((uint32_t)(VM_memory[RF[rs] + immediate + 2]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate + 3]);
PC  =  nPC;
nPC  += 4;
'''
],
["sb",
'''#if INDIRECT_DEBUG
printf("%d|sb\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
'''
],
["sh",
'''#if INDIRECT_DEBUG
printf("%d|sh\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF00) >> 8);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)(RF[rt] & 0xFF);
PC  =  nPC;
nPC  += 4;
'''
],
["sw",
'''#if INDIRECT_DEBUG
printf("%d|sw\\n",counter);
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
'''
],
["jump",
'''#if INDIRECT_DEBUG
printf("%d|jump\\n",counter);
counter++;
#endif
PC = nPC;
address = (instr >> 0) & 0x3FFFFFF;
nPC = address << 2;
//FETCH_HERE
'''
],
["jal",
'''#if INDIRECT_DEBUG
printf("%d|jal\\n",counter);
counter++;
#endif
RF[31] = PC + 8;
PC = nPC;
address = (instr >> 0) & 0x3FFFFFF;
nPC = address << 2;
//FETCH_HERE
'''
],
["trap",
'''#if INDIRECT_DEBUG
printf("%d|trap\\n",counter);
counter++;
#endif
address = (instr >> 0) & 0x3FFFFFF;
syscall((uint8_t)(address&0xFF));
PC  =  nPC;
nPC  += 4;
'''
],
["swl",
'''#if INDIRECT_DEBUG
printf("%d|swl\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)((RF[rt] & 0xFF000000) >> 24);
VM_memory[RF[rs] + immediate + 1] = (uint8_t)((RF[rt] & 0xFF0000) >> 16);
PC  =  nPC;
nPC  += 4;'''
],
["swr",
'''#if INDIRECT_DEBUG
printf("%d|swr\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
VM_memory[RF[rs] + immediate] = (uint8_t)(RF[rt] & 0xFF);
VM_memory[RF[rs] + immediate - 1] = (uint8_t)(RF[rt] & 0xFF00) >> 8;
PC  =  nPC;
nPC  += 4;
'''
],
["lwl",
'''#if INDIRECT_DEBUG
printf("%d|lwl\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate]) << 24) | ((uint32_t)(VM_memory[RF[rs] + immediate + 1]) << 16);
PC  =  nPC;
nPC  += 4;
'''
],
["lwr",
'''#if INDIRECT_DEBUG
printf("%d|lwr\\n",counter);
counter++;
#endif
rs = (instr >> 21) & 0x1F;
rt = (instr >> 16) & 0x1F;
immediate = (instr >> 0) & 0xFFFF;
RF[rt] = ((uint32_t)(VM_memory[RF[rs] + immediate -1]) << 8) | ((uint32_t)VM_memory[RF[rs] + immediate]);
PC  =  nPC;
nPC  += 4;
'''
],
["error",
'''#if INDIRECT_DEBUG
printf("Error, unknown instruction %d.\\n", instr);
#endif
PC  =  nPC;
nPC  += 4;
'''
]
]

codegen_end = '''end:
if(opt) {
  print_memory();
  print_registers();
}
'''

# Below, variables related to the selective version

codegen_tree_struct_define = '''struct pointer {
  void * code;
  struct pointer * next_level;
};
'''

codegen_tree_array_name = '''struct pointer array'''
codegen_tree_array_name_clean = "array"
codegen_array_type = "struct pointer"
#codegen_tree_aux_array_name = "aux"

codegen_tree_variable = '''struct pointer * p;
'''
codegen_tree_goto_start = '''p = array;
'''


codegen_tree_goto_middle = '''if (p[op].next_level == NULL)
  goto *p[op].code;
else
  p = p[op].next_level;
'''

codegen_tree_goto_end = '''goto *p[op].code;
'''

codegen_tree_goto_opt = '''p = p[op].next_level;
'''
