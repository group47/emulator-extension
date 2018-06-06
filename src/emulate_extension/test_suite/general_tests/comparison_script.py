import sys

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
            if program_block[i].rstrip() != gdb_block[i].rstrip():
                return False
    return True

def print_test_case_and_difference(program_block, gdb_block):
    assert max_len_of_line > 0, "you should have the most updated max length of line"
    num_lines = len(program_block)
    length_of_one_line = max_len_of_line * 2 + 5
    for i in range(0, num_lines):
        print(program_block[i].rstrip(), end='')
        print(' '*(length_of_one_line - len(program_block[i].rstrip())), end='')
        print(gdb_block[i].rstrip())
    print("\n")



length_of_test_case_block = 18
if len(sys.argv) < 3:
    print("Not enough number of arguments")
else:
    program_output = sys.argv[1]
    gdb_output = sys.argv[2]

    with open(program_output) as f:
        program_output = f.readlines()
    with open(gdb_output) as f:
        gdb_output = f.readlines()

    # remove the warming of pipeline
    if "r0" not in program_output[0]:
        raw_program_output = get_start_line_of_next_block(program_output)

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

    num_test_cases = len(program_blocks)

    assert num_test_cases == len(gdb_blocks), \
        "either the number of testcases doesn't match or the parsing part is incorrect"

    test_case_index = 0

    show_correct_test_case = False
    while test_case_index < num_test_cases:
        if show_correct_test_case:
            print_test_case_and_difference(program_blocks[test_case_index], gdb_output[test_case_index])
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
                while user_input not in commands:
                    print("Invalid command\n")
                    user_input = input()
        else:
            if not compare_blocks(program_blocks[test_case_index], gdb_blocks[test_case_index]):
                print("Test case fail")
                print_test_case_and_difference(program_blocks[test_case_index], gdb_blocks[test_case_index])
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
                    while user_input not in commands:
                        print("Invalid command\n")
                        user_input = input()
            else:
                test_case_index = test_case_index + 1
    print("test case successful")
