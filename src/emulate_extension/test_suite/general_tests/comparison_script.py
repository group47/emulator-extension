import sys
import os
from termcolor import colored

tmp_dir_path = "/tmp/arm_project_no_conflict"

if not os.path.exists(tmp_dir_path):
    os.makedirs(tmp_dir_path)


max_len_of_line = 0
distance_between_block = 5

commands = ["f", "b", "c", "q"]

def get_start_line_of_next_block(output):
    output = output[1:len(output)]
    while len(output) > 0:
        if "r0" in output[0] and "=>" not in output[0] and "??" not in output[0]:
            break
        else:
            output = output[1:len(output)]
    return output

def get_and_remove_test_case(lines):
    #assert len(lines) > 0 or "r0" in lines[0], "the test case block is not in the correct format"
    test_case_block = []
    while len(lines) > 0 and "fpscr" not in lines[0]:
        test_case_block.append(lines[0])
        lines = lines[1:len(lines)]
    return [lines, test_case_block]

def compare_blocks(program_block, gdb_block):
    global max_len_of_line
    num_lines = len(program_block)
    assert num_lines == len(gdb_block), "number of lines in program block and gdb block does not match"
    for i in range(0, num_lines):
        if max_len_of_line < len(program_block[i]):
            max_len_of_line = len(program_block[i])
        if "sp" not in program_block[i] and "pc" not in gdb_block[i]:
            if ''.join(program_block[i].split()) != ''.join(gdb_block[i].split()):
                return False
    return True

def print_test_case_and_difference(program_block, gdb_block):
    assert max_len_of_line > 0, "you should have the most updated max length of line"
    num_lines = len(program_block)
    length_of_one_line = max_len_of_line * 2 + 5
    for i in range(0, num_lines):
        if ''.join(program_block[i].split()) != ''.join(gdb_block[i].split()) and "sp" not in program_block[i] and "pc" not in program_block[i]:
            program_line = colored(program_block[i].rstrip(), 'red', attrs=['reverse', 'blink'])
            gdb_line     = colored(gdb_block[i].rstrip(), 'red', attrs=['reverse', 'blink'])
        else:
            program_line = program_block[i].rstrip()
            gdb_line     = gdb_block[i].rstrip()
        print(program_line, end='')
        print(' '*(length_of_one_line - len(program_block[i].rstrip())), end='')
        print(gdb_line)
    print("\n")



length_of_test_case_block = 18
if len(sys.argv) < 3:
    if sys.argv[1] is "--help" or sys.argv[1] is "-h" or sys.argv[1] is "-help":
        print("Enter three arguments:")
        print("    1. emulate_extension path")
        print("    2. test case binary path")
        print("    3. gdb log file path")
        print("")
        print("Available command:")
        print("    1. f - move to the next test case")
        print("    2. b - move to the previous test case")
        print("    3. c - continue to execute until next fail test case")
        print("    4. q - quit")
    else:
        print("Not enough number of arguments")
else:
    for i in range(1, 4):
        if sys.argv[i].endswith("emulate_extension"):
            emulate_executable = sys.argv[i]
        if sys.argv[i].endswith(".bin2"):
            test_case_binary_path = sys.argv[i]
        if sys.argv[i].endswith(".log"):
            gdb_log_file_path = sys.argv[i]

    #emulate_executable = sys.argv[1]
    #test_case_binary_path = sys.argv[2]
    #gdb_log_file_path = sys.argv[3]
    
    raw_program_output_file_name = (gdb_log_file_path[0:(len(gdb_log_file_path) - 4)] + "_output.log").split('/')
    program_output_file_name = raw_program_output_file_name[len(raw_program_output_file_name)-1]
    program_output =  tmp_dir_path + "/" + program_output_file_name
    gdb_output = gdb_log_file_path
    command = emulate_executable + " " + "--binary=" + test_case_binary_path + " -p --logfile=" + program_output
    
    os.system(command)

    with open(program_output) as f:
        program_output = f.readlines()
    with open(gdb_output) as f:
        gdb_output = f.readlines()

    # remove the warming of pipeline
    if "r0" not in program_output[0]:
        raw_program_output = get_start_line_of_next_block(program_output)

    program_output = get_start_line_of_next_block(program_output)
    program_output = get_start_line_of_next_block(program_output)
    if "r0" not in gdb_output[0]:
        gdb_output = get_start_line_of_next_block(gdb_output)


    # We are testing

    min_length = min(len(program_output), len(gdb_output))

    program_blocks = []
    gdb_blocks = []
    count = 0
    while len(program_output) > 0 and len(gdb_output) > 0:
        if count >= 200:
            print("sth is wrong")
        program_parse_result = get_and_remove_test_case(program_output)
        program_output = get_start_line_of_next_block(program_parse_result[0])
        program_blocks.append(program_parse_result[1])
        gdb_parse_result = get_and_remove_test_case(gdb_output)
        gdb_output = get_start_line_of_next_block(gdb_parse_result[0])
        gdb_blocks.append(gdb_parse_result[1])
        count = count+1

    num_test_cases = min(len(program_blocks), len(gdb_blocks))

    assert num_test_cases == len(gdb_blocks), \
        "either the number of testcases doesn't match or the parsing part is incorrect"

    test_case_index = 0

    show_correct_test_case = False
    while test_case_index < num_test_cases:
        if show_correct_test_case:
            print_test_case_and_difference(program_blocks[test_case_index], gdb_blocks[test_case_index])
            user_input = input()
            while user_input not in commands:
                print("invalid command")
                user_input = input()
            if user_input is "f":
                test_case_index = test_case_index + 1
                show_correct_test_case = True
            elif user_input is "b":
                test_case_index = test_case_index - 1
                show_correct_test_case = True
            elif user_input is "c":
                test_case_index = test_case_index + 1
                show_correct_test_case = False
            elif user_input is "q":
                sys.exit()
            else:
                assert False, "how the hell does this happen?"
                sys.exit()
        else:
            if not compare_blocks(program_blocks[test_case_index], gdb_blocks[test_case_index]):
                print("Test case fail")
                print("Number of test case: " + str(test_case_index + 1))
                print_test_case_and_difference(program_blocks[test_case_index], gdb_blocks[test_case_index])
                user_input = input()
                while user_input not in commands:
                    print("invalid command")
                    user_input = input()
                if user_input is "f":
                    test_case_index = test_case_index + 1
                    show_correct_test_case = True
                elif user_input is "b":
                    test_case_index = test_case_index - 1
                    show_correct_test_case = True
                elif user_input is "c":
                    test_case_index = test_case_index + 1
                    show_correct_test_case = False
                elif user_input is "q":
                    sys.exit()
                else:
                    assert False, "how the hell does this happen?"
                    sys.exit()
            else:
                test_case_index = test_case_index + 1

        print("Current test case index : " + str(test_case_index + 1))
    print("test case successful")
