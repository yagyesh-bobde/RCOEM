class ThreeAddressCodeGenerator:
    def __init__(self):
        self.code = []
        self.temp_var_count = 0
        self.label_count = 0

    def new_temp(self):
        temp_var = f"T{self.temp_var_count}"
        self.temp_var_count += 1
        return temp_var

    def new_label(self):
        label = f"L{self.label_count}"
        self.label_count += 1
        return label

    def emit(self, statement):
        self.code.append(statement)

    def print_code(self):
        for i, statement in enumerate(self.code):
            print(f"{i + 1}. {statement}")

    # Generate TAC for if-then-else construct
    def generate_if_then_else(self, condition, then_block, else_block):
        label_else = self.new_label()
        label_end = self.new_label()
        
        self.emit(f"if {condition} goto {label_else}")
        for stmt in then_block:
            self.emit(stmt)
        self.emit(f"goto {label_end}")
        self.emit(f"{label_else}:")
        for stmt in else_block:
            self.emit(stmt)
        self.emit(f"{label_end}:")

    # Generate TAC for while loop
    def generate_while(self, condition, body_block):
        label_start = self.new_label()
        label_end = self.new_label()
        
        self.emit(f"{label_start}:")
        self.emit(f"if not {condition} goto {label_end}")
        for stmt in body_block:
            self.emit(stmt)
        self.emit(f"goto {label_start}")
        self.emit(f"{label_end}:")

# Example usage:
if __name__ == "__main__":
    tac_gen = ThreeAddressCodeGenerator()

    # if-then-else block:
    condition_if = "A == 1"
    then_block_if = [
        "T1 = C + 1",
        "C = T1"
    ]
    else_block_if = [
        "if A > D goto L1",
        "T2 = A + B",
        "A = T2",
        "goto L1",
        "L1:"
    ]
    tac_gen.generate_if_then_else(condition_if, then_block_if, else_block_if)

    # while loop block:
    condition_while = "A < C and B > D"
    body_block_while = [
        "if A == 1 goto L2",
        "T3 = C + 1",
        "C = T3",
        "goto L3",
        "L2: if A <= D goto L4",
        "T4 = A + B",
        "A = T4",
        "goto L2",
        "L3:"
    ]
    tac_gen.generate_while(condition_while, body_block_while)

    # Output the generated TAC
    tac_gen.print_code()
