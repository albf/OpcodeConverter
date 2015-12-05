from config import *
from counter import *

def create_address_array():
    '''
    :return: String with address array C-code.
    '''
    array = "static void *array[] = { "
    start = True
    for translate_entry in translate_table:
        if start:
            start = False
            array = array + "&&" + translate_entry[NAME_POS]
        else:
            array = array + ", &&" + translate_entry[NAME_POS]

    array = array + " };\n"
    return array


def ident(code, level):
    code = '\n'.join(["  "*level + x for x in str(code).split('\n')])
    while code[-1] == ' ':
        code = code[:-1]
    return code

def get_replace_vector(code, nth):
    splitted =  [str(x).split(' ') for x in code.split('\n')]
    vector = []
    for l in splitted:
        if len(l)==2:
            vector.append([l[1].replace(';',''), l[1].replace(';','')+str(nth)])
    return vector


def apply_replace_vector(code, vector):
    for ru in vector:
        code = str(code).replace(ru[0], ru[1])
    return code

def create_array_init(factor, entry=""):
    array_init = " { "
    comma = 0;
    for opcode in codegen_address_array:
        if comma:
            array_init += " , "
        if (factor > 1) and (len(entry) == 0):
            array_init += create_array_init(factor-1, opcode)
        elif (factor > 1) and (len(entry) > 0):
            array_init += create_array_init(factor-1, entry + codegen_opcode_join)
        else:
            array_init += "&&"
            if len(entry):
                array_init += entry + codegen_opcode_join + opcode
            else:
                array_init += opcode

        comma = 1;
    array_init += " } "
    return array_init


def fetch_instructions(factor, tree=False, tree_opt = True):
    fetch = ""
    for i in range(factor):
        if i == 0:
            replace_vector = get_replace_vector(codegen_fetch_initialisation, i)
            fetch += ident(apply_replace_vector(codegen_fetch_calculation, replace_vector),1)
        elif i== 1:
            replace_vector = get_replace_vector(codegen_fetch_initialisation, i)
            tmp = ident(apply_replace_vector(codegen_fetch_calculation, replace_vector),1)
            fetch += str(tmp).replace(codegen_PC_variable, codegen_nPC_variable)
        else:
            replace_vector = get_replace_vector(codegen_fetch_initialisation, i)
            tmp = ident(apply_replace_vector(codegen_fetch_calculation, replace_vector),1)
            fetch += str(tmp).replace(codegen_PC_variable, codegen_nPC_variable + " + " + str(4*(i-1)))
        if tree:
            fetch += "\n"
            replace_vector = get_replace_vector(codegen_fetch_initialisation, i)
            if (i==0):
                fetch += apply_replace_vector(codegen_tree_goto_start, replace_vector)
            if ((i+1) == factor):
                fetch += apply_replace_vector(codegen_tree_goto_end, replace_vector)
            else:
                if tree_opt:
                    fetch += apply_replace_vector(codegen_tree_goto_opt, replace_vector)
                else:
                    fetch += apply_replace_vector(codegen_tree_goto_middle, replace_vector)
            fetch += "\n"

    if not tree:
        fetch += ident(codegen_fetch_goto,1)
        for i in range(factor):
            fetch += "[" + codegen_index_variable + str(i) + "]"
        fetch += ";\n"

    return fetch


def merge_instructions(ins1, ins2, fac1, fac2):
    ins3 = [ins1[0] + codegen_opcode_join + ins2[0]]
    #rep_ins1 = get_replace_vector(codegen_fetch_initialisation, fac1)
    rep_ins2 = get_replace_vector(codegen_fetch_initialisation, fac2)
    #ins3.append(apply_replace_vector(ins1[1], rep_ins1) + "\n" + apply_replace_vector(ins2[1], rep_ins2))
    ins3.append(ins1[1] + "\n" + apply_replace_vector(ins2[1], rep_ins2))
    return ins3


def gen_super_instructions(max_factor, factor, entry=[]):
    result = []

    for ins in codegen_instructions_code:
        #print factor
        if (len(entry) == 0) and (factor <= 1):
            #print "entry 1"
            rep_ins = get_replace_vector(codegen_fetch_initialisation, max_factor-int(factor))
            fix = apply_replace_vector(ins[1], rep_ins)
            result.append([ins[0], fix])
        elif (len(entry) > 0) and (factor <= 1):
            #print "entry 2"
            merged = merge_instructions(entry, ins, max_factor-int(factor)-1, max_factor-int(factor))
            result.append(merged)
        elif (len(entry) > 0) and (factor > 1):
            #print "entry 3"
            merged = merge_instructions(entry, ins, max_factor-int(factor)-1, max_factor-int(factor))
            rec = gen_super_instructions(max_factor, factor-1, merged)
            for rec_ins in rec:
                result.append(rec_ins)
        elif (len(entry) == 0) and (factor > 1):
            #print "entry 4"
            rep_ins1 = get_replace_vector(codegen_fetch_initialisation, 0)
            fix_code = apply_replace_vector(ins[1], rep_ins1)
            fix = [ins[0], fix_code]
            rec = gen_super_instructions(max_factor, factor-1, fix)
            for rec_ins in rec:
                result.append(rec_ins)

    return result


def fix_jumps(super_instructions, factor, tree):
    fetch = fetch_instructions(factor, tree)
    # Fix jump, if any.
    fixed = str(super_instructions).replace(codegen_fetch_label, fetch)
    return fixed


def instructions_code(factor, tree=None, gen_all_tree = False):
    code = ""
    if tree:
        all_instructions = gen_super_instructions(1, 1, [])
        for ins in all_instructions:
            code += ins[0] + ":\n" + ins[1]
            code += fetch_instructions(factor, True) + "\n"
        cache = [all_instructions]
        for i in range(1, factor):
            cache.append(gen_super_instructions(i+1, i+1, []))

        if gen_all_tree:
            dont_repeat = {}
            for ins in tree:
                for j in range(1,len(ins)):
                    name = ""
                    for k in range(j):
                        name += ins[k]
                        name += codegen_opcode_join
                    if name not in dont_repeat.keys():
                        dont_repeat[name] = 1
                        for super_ins in cache[j]:
                            if str(super_ins[0]).startswith(name):
                                code += super_ins[0] + ":\n" + super_ins[1]
                                code += fetch_instructions(factor, True) + "\n"
        else:
            for i in tree:
                #print 'i:' + str(i)
                if len(i) > 1:
                    for super_ins in cache[len(i)-1]:
                        #print 'compare:' + str(str(codegen_opcode_join).join(i))
                        #print 'with:' + str(super_ins[0])
                        if str(codegen_opcode_join).join(i) == super_ins[0]:
                            #print 'added i:' + str(i)
                            code += super_ins[0] + ":\n" + super_ins[1]
                            code += fetch_instructions(factor, True) + "\n"
    else:
        all_instructions = gen_super_instructions(factor, factor, [])
        for ins in all_instructions:
            code += ins[0] + ":\n" + ins[1]
            code += fetch_instructions(factor) + "\n"


    # Fix jumps using labels.
    if tree:
        code = fix_jumps(code, factor, True)
    else:
        code = fix_jumps(code, factor, False)
    return code


def gen_code(factor):
    interpreter = ""

    interpreter += codegen_defines
    interpreter += codegen_global
    interpreter += codegen_signature + " {\n"
    interpreter += ident(codegen_normal_initialisation,1)

    # Variables referent to each instruction loaded
    for i in range(factor):
        replace_vector = get_replace_vector(codegen_fetch_initialisation, i)
        interpreter += ident(apply_replace_vector(codegen_fetch_initialisation, replace_vector),1)
    interpreter += '\n'

    # Start table, dimension variable with factor
    interpreter += ident(codegen_address_array_name,1)
    for _ in range(factor):
        interpreter += "[" + codegen_table_size + "]"
    interpreter += " ="

    interpreter += create_array_init(factor, "") + ";\n\n"

    # Fetch first instruction
    interpreter += fetch_instructions(factor)

    # Add instructions code
    super_instructions = instructions_code(factor)

    # End
    interpreter += codegen_end

    interpreter += "\n}"
    return interpreter


def find_match(term, tree, factor):
    if len(term) >= factor:
        return False
    else:
        for i in tree:
            if i[:len(term)] == term:
                return True
        return False


def gen_tree_code(factor, tree):
    interpreter = ""

    interpreter += codegen_defines
    interpreter += codegen_global
    interpreter += codegen_tree_struct_define
    interpreter += codegen_signature + " {\n"
    interpreter += ident(codegen_normal_initialisation,1)

    # Variables referent to each instruction loaded
    for i in range(factor):
        replace_vector = get_replace_vector(codegen_fetch_initialisation, i)
        interpreter += ident(apply_replace_vector(codegen_fetch_initialisation, replace_vector),1)
    interpreter += '\n'

    # Variable used to move in the tree
    interpreter += codegen_tree_variable

    # Auxiliar tables
    visited = {}
    max_len = max(map(len, tree))
    ordered_tree = []

    # Order reverse by size
    for s in  range(0, max_len+1):
        for i in tree:
            if len(i) == s:
                ordered_tree.append(i)
    tree = ordered_tree


    # Do this nasty thing of initializing everyone.
#    for ins in tree:
        # TODO: FIX THIS ORDER!!!
#        for index in range(min([(len(ins)-1), factor])):
    for index in range(factor-1)[::-1]:
        for ins in tree:
            #print index
            if (len(ins)-1)<index:
                #print ins
                #print "problem"
                continue
            pos_name = str(codegen_opcode_join).join(ins[:(index+1)])
            name = codegen_tree_array_name + pos_name
            if pos_name not in visited.keys():
                visited[pos_name] = 1

                interpreter += name + "[" + codegen_table_size + "] = { "
                first = 1
                count = 0
                for pre_value in codegen_address_array:
                    count += 1
                    if first:
                        first = 0
                    else:
                        interpreter += " , "

                    match = find_match(ins[:(index+1)] + [pre_value], tree, factor)
                    if match:
                        next_name = str(codegen_opcode_join).join(ins[:(index+1)]+[pre_value])
                        next_name = str(codegen_tree_array_name_clean) + next_name
                        interpreter += " { NULL, " + next_name + " } "
                        #interpreter += " { NULL, &" + codegen_tree_array_name + match + " } "
                    else:
                        # Try to find ready function.
                        attempt = ins[:(index+1)] + [pre_value]
                        found = 0
                        for t_entry in tree:
                            #print "Attempt" + str(attempt) + "\n t entry: " + str(t_entry)
                            if t_entry == attempt:
                                #print "---match"
                                found = 1
                                interpreter += " { &&" + str(codegen_opcode_join).join(attempt) + ", NULL } "

                        if not found:
                            interpreter += " { &&" + pos_name + ", NULL } "


                    if count > 9:
                        count = 0
                        interpreter += "\n"

                interpreter += " }; \n\n"

            #for i in range(index+1):
            #    if name:
            #        name += codegen_opcode_join


    # Now, print the root, the entry of the tree.
    name = codegen_tree_array_name
    interpreter += name + "[" + codegen_table_size + "] = { "
    first = 1
    count = 0
    for pre_value in codegen_address_array:
        count += 1
        if first:
            first = 0
        else:
            interpreter += " , "

        match = find_match([pre_value], tree, factor)
        if match:
            next_name = str(codegen_tree_array_name_clean) + str(pre_value)
            interpreter += " { NULL, " + next_name + " } "
            #interpreter += " { NULL, &" + codegen_tree_array_name + match + " } "
        else:
            interpreter += " { &&" + pre_value + ", NULL } "

        if count > 9:
            count = 0
            interpreter += "\n"

    interpreter += " }; \n\n"

    '''# Start table, dimension variable with factor
    interpreter += ident(codegen_tree_array_name,1)


    for _ in range(factor):
        interpreter += "[" + codegen_table_size + "]"
    interpreter += " ="

    interpreter += create_array_init(factor, "") + ";\n\n" '''

    # Fetch first instruction
    interpreter += fetch_instructions(factor, True)

    # Add instructions code
    super_instructions = instructions_code(factor, tree)
    interpreter += super_instructions
    #interpreter += fix_jumps(super_instructions, factor)

    # End
    interpreter += codegen_end

    interpreter += "\n}"
    return interpreter


if __name__ == "__main__":
    #print gen_tree_code(3, [["swl", "swl"],["swl","swl","swl"]])
    #sys.exit()

    #print fetch_instructions(2, True)
    #print gen_code(1)
    benchmarks = ["bellmanford.ins", "crc.ins", "matrix.ins", "sort.ins", "sudoku.ins"]
    #benchmarks = ["bellmanford.ins"]
    benchmarks_dir = "../benchmarks/bin2/"
    bench_fix = []
    for b in benchmarks:
        bench_fix.append(benchmarks_dir+b)

    #print get_tree(bench_fix, 2)
    my_tree = get_tree(bench_fix, 3)
    print my_tree

    print gen_tree_code(3, my_tree)
    #print gen_tree_code(2, [["swl", "swl"]])

    #fetch = fetch_instructions(2)
    #for ins in codegen_instructions_code:
    #    if (ins[0]=='jal'):
    #        ins[1] = str(ins[1]).replace(codegen_fetch_label, fetch)
    #        print ins[1]

    #print instructions_code(1)

    #interpreter = ident(codegen_address_array_name,1)
    #for _ in range(2):
    #    interpreter += "[" + codegen_table_size + "]"
    #interpreter += " ="
    #interpreter += create_array_init(2, "") + ";\n\n"

    #print interpreter