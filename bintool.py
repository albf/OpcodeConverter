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
    for i in range(len(translate_entry[TYPE_POS])):
        a_type = translate_entry[TYPE_POS][i]
        mask, shift = create_mask(a_type)
        if ((mask & instruction) >> shift) != translate_entry[VALUE_POS][i]:
            return False
    return True


def match_instruction(instruction, debug=False):
    """
    :param instruction: instruction to match with an entry from table.
    :return: the entry if there is any match, None otherwise.
    """
    for translate_entry in translate_table:
        if try_match(instruction, translate_entry):
            return translate_entry
    if debug:
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
        for i in range(len(translate_entry[TYPE_POS])):
            a_type = translate_entry[TYPE_POS][i]
            mask, shift = create_mask(a_type)
            update = translate_entry[NEW_VALUE_POS][i] << shift
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


def check_arguments():
    """
    :return: False if there is any problem with argument (file). True if file
    is okay.
    """
    min_len = len(expected_extension)
    if len(sys.argv) != 3:
        print 'Error: Exactly two arguments expected (name of binary file).'
        print 'Usage: python bintool.py mode file'
        print 'Modes:'
        print '     c: Convert binary using table.'
        print '     p: Print binary and see if matches'
        print '     v: View the results side by side'
        return False
    elif not os.path.isfile(sys.argv[2]):
        print 'Error: File (' + str(sys.argv[2]) + ') not found'
        return False
    elif sys.argv[1] not in ["c", "p", "v"]:
        print "Error: Mode not available, use c, p or v"
        return False
    elif sys.argv[1] == "c":
        new_filename = str(sys.argv[2]+expected_extension)
        if not os.path.isfile(new_filename):
            print "Error: Binary file (" + str(new_filename) + ") not found."
            return False
    elif (len(sys.argv[2]) < min_len) or \
            (sys.argv[2][-min_len:] != expected_extension):
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
        new_binary.close()


def print_instruction(string):
    """ Just print a instruction in a determined format.
    :param string: String that will be printed.
    """
    sys.stdout.write(str(bin(string))[2:].zfill(bits_per_instruction))


def print_binary_line(original_instruction, match, new_instruction):
    """
    :param original: Original line.
    :param match_status: If should try to match
    :param new: new line.
    """
    #print int(original_instruction)
    #print bin(original_instruction)
    print_instruction(original_instruction)
    if match:
        if match_instruction(original_instruction):
            sys.stdout.write(" -> Matched     ")
        else:
            sys.stdout.write(" -> NOT Matched ")

    if new_instruction:
        sys.stdout.write(" -> ")
        print_instruction(new_instruction)
    sys.stdout.write("\n")


def print_binary(filename, match=True, new_filename=None, struct_type="i"):
    """
    :param filename: Name of first file, must exist.
    :param match: if should try to match with convert table.
    :param new_filename: If should also print the new file converted.
    :return: True if they have the same size, false if not.
    """
    bytes_per_instruction = bits_per_instruction/8
    original_binary = open(filename, "rb")

    if new_filename:
        new_filename = filename + appended_extension
        new_binary = open(new_filename, "rb")
    try:
        original_instruction, = struct.unpack(struct_type,
                                              original_binary.read(bytes_per_instruction))
        if new_filename:
            new_instruction, = struct.unpack(struct_type,
                                             new_binary.read(bytes_per_instruction))
        else:
            new_instruction = None

        while original_instruction != "":
            if new_filename and new_instruction == "":
                print "New binary ended earlier, problem?"
                return False
            print_binary_line(original_instruction, match, new_instruction)
            original_instruction, = struct.unpack(struct_type,
                                                 original_binary.read(bytes_per_instruction))
            if new_filename:
                new_instruction, = struct.unpack(struct_type,
                                                 new_binary.read(bytes_per_instruction))
    finally:
        original_binary.close()
        if new_filename:
            new_binary.close()

    if new_filename and new_instruction != "":
        print "Old binary ended earlier, problem?"
        return False
    else:
        return True


def main():
    """ Normal execution flow."""
    # Check if file exist and it's the only argument.
    if not check_arguments():
        sys.exit()

    # Check if the number of bits is compatible with struct library.
    struct_type = find_struct_type()
    path = sys.argv[2]
    if not struct_type:
        sys.exit()

    if sys.argv[1] == "c":
        translate_binary(struct_type, sys.argv[2])
    elif sys.argv[1] == "p":
        print_binary(path, True, None, struct_type)
    elif sys.argv[1] == "v":
        print_binary(path, True, path+expected_extension, struct_type)

if __name__ == "__main__":
    #main()
    print_binary("bubblesort.x", True, None)

    #test = 0b00100000000000000001010101010101
    #new = convert_instruction(test)
    #print bin(test)
    #print bin(new)

    #test2 = 0b00100111111111111111111111111111
    #new2 = convert_instruction(test2)
    #print bin(test2)
    #print bin(new2)

