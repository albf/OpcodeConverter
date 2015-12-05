import subprocess
import os.path
from counter import *
import matplotlib.pyplot as plt

pin_command = "~/pin/pin -t ~/pin/source/tools/ManualExamples/obj-intel64/inscount0.so -- ./microvm ../benchmarks/bin2/"
original_command = "./microvm ../benchmarks/bin2/"
benchmarks = ["bellmanford.x", "crc.x", "matrix.x", "sort.x", "sudoku.x", "micro_addiu.x", "micro_addu.x", "micro_lw.x", "micro_xor.x"]
ins_suffix = ".ins"
time_command = "time ./microvm ../benchmarks/bin2/"


def execute_command(command):
    """
    :param command: Command to be executed.
    :return: stdout. Only.
    """
    #print command
    process = subprocess.Popen(command, shell=True,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE)
    process.wait();
    out, _ = process.communicate()
    return out;


def get_last_line(text):
    return str(text).split("\n")[-1]


def get_pin_output():
    """
    :return: pin output generated in same folder.
    """
    if not os.path.isfile(os.getcwd()+"/inscount.out"):
        print 'pin output file not found, why? :('
        return None

    with open("inscount.out") as f:
        content = f.readlines()

    return int(str(content[0]).split(" ")[1])


def get_instruction_dump(bench):
    """
    :param name: benchmark name.
    :return: nothing, output saved in a file.
    """
    execute_command(original_command + bench + " 10 > " + bench + ins_suffix)


if __name__ == "__main__":

    for bench in benchmarks:
        print "---------- " + str(bench) + " ----------"
        execute_command(pin_command+bench + " 11")
        init_instructions = get_pin_output()
        print "Init instructions: " + str(init_instructions)

        mips_instructions = get_last_line(execute_command(original_command +bench + " 0"))
        print "Mips instructions executed: " + str(mips_instructions)

        execute_command(pin_command+bench + " 1")
        normal_instructions = get_pin_output()
        print "Normal instructions: " + str(normal_instructions)

        normal_efficiency = (normal_instructions-init_instructions)/float(mips_instructions)
        print "Normal Efficiency: " + str(normal_efficiency)

        execute_command(pin_command+bench + " 5")
        indirect_instructions = get_pin_output()
        print "Indirect instructions: " + str(indirect_instructions)

        indirect_efficiency = (indirect_instructions-init_instructions)/float(mips_instructions)
        print "Indirect Efficiency: " + str(indirect_efficiency)

        speedup_instruction = normal_efficiency/float(indirect_efficiency)
        print "Indirect SpeedUp " + str(speedup_instruction)

        execute_command(pin_command+bench + " 6")
        super_instructions = get_pin_output()
        print "Super instructions: " + str(super_instructions)

        super_efficiency = (super_instructions-init_instructions)/float(mips_instructions)
        print "Super Efficiency: " + str(super_efficiency)

        super_speedup_instruction = normal_efficiency/float(super_efficiency)
        print "Super SpeedUp " + str(super_speedup_instruction)

        get_instruction_dump(bench)
        parsed_table = parse_instructions_from_file(bench+".ins")
        results = count_instructions(parsed_table, 1)
        ordered_results = sorted(results.items(), key=operator.itemgetter(1), reverse=True)
        generate_pie_chart(ordered_results, bench + "_pie.png")
        generate_accumulative_plot(ordered_results, bench + "_plot.png")


        print "---------- ---------- ----------"
