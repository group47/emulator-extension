import random
def gen_register():
    return "r"+str(random.randint(0, 7))
def gen_register_full_range():
    r_val = random.randint(0, 15)
    if r_val is 15:
        return "pc"
    else:
        return "r"+str(r_val)


def form_instruction(args):
    assert len(args) >= 1, "Not enough element to form an instruction"
    instruction = args[0] + " " + args[1]
    return ", ".join([instruction] + args[2:len(args)])

def gen_sharp_expression():
    return "#"+str(random.randint(0, 30))

def thumb_move_shifted_register():
    op = ["lsl", "lsr", "asr"]
    return form_instruction([random.choice(op), gen_register(), gen_register(), gen_sharp_expression()])

def thumb_add_subtract():
    op = ["add", "sub"]
    return form_instruction([random.choice(op), gen_register(), gen_register(), \
                             random.choice([gen_register(), gen_sharp_expression()])])

def thumb_mov_cmp_add_sub_imm():
    op = ["mov", "cmp", "add", "sub"]
    return form_instruction([random.choice(op), gen_register(), gen_sharp_expression()])

def thum_balu():
    op = ["and",
          "eor",
          "lsl",
          "lsr",
          "asr",
          "adc",
          "sbc",
          "ror",
          "tst",
          "neg",
          "cmp",
          "cmn",
          "orr",
          "mul",
          "bic",
          "mvn"]
    return form_instruction([random.choice(op), gen_register(), gen_register()])

def thumb_register_operation():
    op = ["and",
          "eor",
          "lsl",
          "lsr",
          "asr",
          "adc",
          "sbc",
          "ror",
          "tst",
          "neg",
          "cmp",
          "cmn",
          "orr",
          "mul",
          "bic",
          "mvn",
          "bx",]
    opCode = random.choice(op)
    if "bx" in opCode:
        return form_instruction([opCode, gen_register_full_range()])
    else:
        return form_instruction([opCode, gen_register_full_range(), gen_register_full_range()])

def thumb_add_offset_to_stack_pointer():
    return form_instruction(["add", "sp", "#", str(random.choice(["", "-"])),str(random.randint(1, 250))])

def gen():
    for i in range(0, 20):
        print(thumb_move_shifted_register())
    for i in range(21, 40):
        print(thumb_add_subtract())
    for i in range(41, 60):
        print(thumb_move_shifted_register())
    for i in range(61, 100):
        print(thum_balu())
    for i in range(101, 200):
        print(thumb_register_operation())
gen()
