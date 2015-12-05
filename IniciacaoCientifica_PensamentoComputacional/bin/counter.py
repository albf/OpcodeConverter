from config import *
from itertools import repeat
import operator
import sys
import matplotlib.pyplot as plt

def read_file(filename):
    with open(filename) as f:
        content = f.readlines()
    for i in range(0, len(content)):
        if content[i][-1] == '\n':
            content[i] = content[i][:-1]
    return content


def parse_instructions_from_file(filename):
    content = read_file(filename)
    parsed = []
    for line in content:
        try:
            parsed.append(line.split('|')[1])
        except IndexError:
            print " -- Warning -- Index Error in :" + line
    return parsed


def get_before_list(parsed, instructions):
    before = []
    i = 0
    for _ in repeat(None, instructions-1):
        before.append(parsed[i])
        i += 1
    return before


def update_dictionary(dictionary, entry):
    if entry not in dictionary.keys():
        dictionary[entry] = 1
    else:
        dictionary[entry] += 1


def count_instructions(parsed, instructions):
    if instructions < 1:
        print 'instructions must be at least 1'
        return None

    if instructions > 1:
        before = get_before_list(parsed, instructions)

    results = {}
    for i in range(instructions-1, len(parsed)):
        if instructions == 1:
            entry = parsed[i]
        else:
            entry = "|".join(before) + "|" + parsed[i]
            before = before[1:]
            before.append(parsed[i])

        update_dictionary(results, entry)
    return results


def generate_accumulative_plot(ordered_list, filename=None):
    n_bins = 0
    x = []
    actual = 1

    for item in ordered_list:
        x = x + [actual]*item[1]
        n_bins += 1
        actual += 1

    n, bins, patches = plt.hist(x, n_bins, normed=1,
                                histtype='step', cumulative=True)

    plt.grid(True)
    plt.ylim(0, 1.05)
    plt.title('Cumulative Cover')
    if filename:
        plt.savefig(filename)
        plt.close()
    else:
        plt.show()


def generate_pie_chart(ordered_list, filename=None):
   # The slices will be ordered and plotted counter-clockwise.
    labels = str(ordered_list[0][0]), str(ordered_list[1][0]), str(ordered_list[2][0]), 'Others'

    total = 0
    for item in ordered_list:
        total += item[1]

    y1 = 100*(ordered_list[0][1]/float(total))
    y2 = 100*(ordered_list[1][1]/float(total))
    y3 = 100*(ordered_list[2][1]/float(total))
    sizes = [y1, y2, y3, 100-(y1+y2+y3)]
    colors = ['yellowgreen', 'gold', 'lightskyblue', 'lightcoral']
    explode = (0.1, 0, 0, 0)  # only "explode" the 2nd slice (i.e. 'Hogs')

    plt.pie(sizes, explode=explode, labels=labels, colors=colors,
            autopct='%1.1f%%', shadow=True, startangle=90)
    # Set aspect ratio to be equal so that pie is drawn as a circle.
    plt.axis('equal')

    if filename:
       plt.savefig(filename)
       plt.close()
    else:
       plt.show()


def main():
    if len(sys.argv) != 3:
        print 'Usage: python counter.py filename instruction_number'
        sys.exit()

    parsed_table = parse_instructions_from_file(sys.argv[1])
    results = count_instructions(parsed_table, int(sys.argv[2]))
    ordered_results = sorted(results.items(), key=operator.itemgetter(1), reverse=True)
    print ordered_results


def get_tree(benchmarks, factor):
    tree_dic = {}
    tree = []

    count = 0
    for a_factor in range(1, factor+1):
        for ben in benchmarks:
            count += 1
            parsed_table = parse_instructions_from_file(ben)
            results = count_instructions(parsed_table, int(a_factor))
            #print "COUNT: " + str(count) + " FILE : " + str(ben)
            #print results.keys()
            for r in results.keys():
                #print r
                if r in tree_dic.keys():
                    tree_dic[r] += results[r]
                else:
                    tree_dic[r] = results[r]

    for r in tree_dic.keys():
        if "#UNKNOWN" in r:
            #print r
            r = str(r).replace("#UNKNOWN", "error")
        if "syscall" in r:
            #print r
            r = str(r).replace("syscall", "sysc")
        if "jumpr1" in r:
            r = str(r).replace("jumpr1", "jalr")
        if "jumpr2" in r:
            r = str(r).replace("jumpr2", "jr")
        if "mhfi" in r:
            r = str(r).replace("mhfi", "mfhi")


        tree.append(r.split("|"))

    return tree


if __name__ == "__main__":
    main()
