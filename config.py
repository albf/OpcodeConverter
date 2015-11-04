# Must be divisible by 8 (1 byte) and <= 64
bits_per_instruction = 32
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

# Update format: [ [ [opcode, function], [opcode_value, function_value], [newOpcode, newFunction] ] * n ]
translate_table = [
[[opcode], [0b001000], [0b1]],       #addi    001000  ArithLogI       $t = $s + SE(i)
[[opcode], [0b001001], [0b10]],      #addiu   001001  ArithLogI       $t = $s + SE(i)
[[opcode], [0b001100], [0b11]]       #andi    001100  ArithLogI       $t = $s & ZE(i)
]