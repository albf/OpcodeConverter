#!/usr/bin/python
""" Bintool script will convert a binary file using auxiliar config.py using
    translation table, allowing the usage of indirect threading technique when
    using an interpreter.
"""

from config import *
from itertools import repeat
import sys
import os
import struct


def create_mask(a_type):
    """ Create mask used to select only part of instruction.
    :param a_type: any type used in translation table.
    :return: mask used to select this part and value for shift.
    """
    mask = 1
    for _ in repeat(None, a_type[BITS_POS]-1):
    #for i in range(a_type[BITS_POS]-1):
        mask = mask << 1
        mask = mask + 1
    shift = (bits_per_instruction-a_type[INIT_POS]-a_type[BITS_POS])
    mask = mask << shift
    return mask, shift


def try_match(instruction, translate_entry):
    """
    :param instruction: Next instruction.
    :param translate_entry: An entry from translation table.
    :return: True if there it is a match, false if not.
    """
    for i in range(translate_entry[TYPE_POS]):
        a_type = translate_entry[TYPE_POS][i]
        mask, shift = create_mask(a_type)
        if ((mask & instruction) >> shift) != translate_entry[VALUE_POS][i]:
            return False
    return True


def match_instruction(instruction):
    """
    :param instruction: instruction to match with an entry from table.
    :return: the entry if there is any match, None otherwise.
    """
    for translate_entry in translate_table:
        if try_match(instruction, translate_entry):
            return translate_entry
    print 'Unknown instruction'
    print str(instruction)
    return None


def convert_instruction(instruction):
    """
    :param instruction: instruction matched and updated to value specified.
    :return: the new instruction if there is a match and config is correct,
    the instruction unmodified otherwise.
    """
    translate_entry = match_instruction(instruction)
    if translate_entry:
        new_instruction = instruction
        for i in len(translate_entry[TYPE_POS]):
            a_type = translate_entry[TYPE_POS][i]
            mask, shift = create_mask(a_type)
            update = translate_entry[NEW_VALUE_POS] << shift
            new_instruction = (new_instruction & (~ mask)) | update
        return new_instruction
    else:
        return instruction


def find_struct_type():
    """
    :return: Use bits_per_instruction to find argument to struct function.
    Check : https://docs.python.org/3/library/struct.html#struct-format-strings
    """
    if bits_per_instruction == 8:
        return 'c'
    elif bits_per_instruction == 16:
        return 'h'
    elif bits_per_instruction == 32:
        return 'i'
    elif bits_per_instruction == 64:
        return 'q'
    else:
        print 'Error: Number of bits (' + bits_per_instruction + \
              ') not supported'
        return None


def check_argument():
    """
    :return: False if there is any problem with argument (file). True if file
    is okay.
    """
    min_len = len(expected_extension)
    if len(sys.argv) != 2:
        print 'Error: Only one argument expected (name of binary file).'
        return False
    elif not os.path.isfile(sys.argv[1]):
        print 'Error: File not found'
        return False
    elif (len(sys.argv[1]) < min_len) or \
            (sys.argv[-min_len:] != expected_extension):
        print 'Warning: Extension not expected.'
    return True


def translate_binary(struct_type, filename):
    """
    :param struct_type: struct type obtained from find_struct_type().
    :param filename: filename/filepath passed as argument.
    :return: void, save new binary to file.
    """
    new_filename = filename + appended_extension
    bytes_per_instruction = bits_per_instruction/8

    new_binary = open(new_filename, 'wb')
    original_binary = open(filename, "rb")
    try:
        instruction = original_binary.read(bytes_per_instruction)
        while instruction != "":
            new_instruction = convert_instruction(instruction)
            new_binary.write(struct.pack(str(struct_type), new_instruction))
            instruction = original_binary.read(bytes_per_instruction)
    finally:
        original_binary.close()


def main():
    """ Normal execution flow."""
    # Check if file exist and it's the only argument.
    if not check_argument():
        sys.exit()

    # Check if the number of bits is compatible with struct library.
    current_struct_type = find_struct_type()
    if not current_struct_type:
        sys.exit()

    translate_binary(current_struct_type, sys.argv[1])

if __name__ == "__main__":
    #main()
    test = 0b00100000000000000000000000000000
    new = convert_instruction(test)
    print bin(test)
    print bin(new)