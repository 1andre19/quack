#pragma once
#include "vm.h"
#include "instructions.h"

void Memory::push_stack(func_resources &fr) { stack_segment.push(fr); }

void Memory::store_num(Address a, double val) {
    int addr = std::get<int>(a);

    if (addr >= TMP_FLOAT_BASE) {
        stack_segment.top().temp_float[addr - TMP_FLOAT_BASE] = val;
        return;
    }
    if (addr >= TMP_INT_BASE) {
        stack_segment.top().temp_int[addr - TMP_INT_BASE] = (long)val;
        return;
    }
    if (addr >= LOCAL_FLOAT_BASE) {
        stack_segment.top().locals_float[addr - LOCAL_FLOAT_BASE] = val;
        return;
    }
    if (addr >= LOCAL_INT_BASE) {
        stack_segment.top().locals_int[addr - LOCAL_INT_BASE] = (long)val;
        return;
    }
    if (addr >= GLOBAL_FLOAT_BASE) {
        data_segment.globals_float[addr - GLOBAL_FLOAT_BASE] = val;
        return;
    }
    if (addr >= GLOBAL_INT_BASE) {
        data_segment.globals_int[addr - GLOBAL_INT_BASE] = val;
        return;
    }
}

void Memory::prepare_frame(func_resources &fr) { to_push = StackFrame(fr); }
void Memory::push_call() { stack_segment.push(to_push); }

Address VmFuncDirectory::get_param_addr(int n) {
    // maybe some out of bounds chek possibly,
    // but until now everything should be correct,
    // the ast checked the number of params is correct
    return params[n - 1];
}

double Memory::get_num(Address a) {
    int addr = std::get<int>(a);

    if (addr >= CONST_FLOAT_BASE) {
        return data_segment.const_float[addr - CONST_FLOAT_BASE];
    }
    if (addr >= CONST_INT_BASE) {
        return (double)data_segment.const_int[addr - CONST_INT_BASE];
    }
    if (addr >= TMP_FLOAT_BASE) {
        return stack_segment.top().temp_float[addr - TMP_FLOAT_BASE];
    }
    if (addr >= TMP_INT_BASE) {
        return (double)stack_segment.top().temp_int[addr - TMP_INT_BASE];
    }
    if (addr >= LOCAL_FLOAT_BASE) {
        return stack_segment.top().locals_float[addr - LOCAL_FLOAT_BASE];
    }
    if (addr >= LOCAL_INT_BASE) {
        return (double)stack_segment.top().locals_int[addr - LOCAL_INT_BASE];
    }
    if (addr >= GLOBAL_FLOAT_BASE) {
        return data_segment.globals_float[addr - GLOBAL_FLOAT_BASE];
    }
    if (addr >= GLOBAL_INT_BASE) {
        return (double)data_segment.globals_int[addr - GLOBAL_INT_BASE];
    }

    throw std::runtime_error("get_num: invalid address: " +
                             std::to_string(addr));
}

std::string Memory::get_str(Address a) {
    int addr = std::get<int>(a);

    if (addr >= CONST_STR_BASE) {
        return data_segment.const_str[addr - CONST_STR_BASE];
    }
    if (addr >= TMP_STR_BASE && addr < CONST_INT_BASE) {
        return stack_segment.top().temp_str[addr - TMP_STR_BASE];
    }
    if (addr >= LOCAL_STR_BASE && addr < TMP_INT_BASE) {
        return stack_segment.top().locals_str[addr - LOCAL_STR_BASE];
    }
    if (addr >= GLOBAL_STR_BASE && addr < LOCAL_INT_BASE) {
        return data_segment.globals_str[addr - GLOBAL_STR_BASE];
    }

    throw std::runtime_error("get_str: invalid address: " +
                             std::to_string(addr));
}

bool Memory::is_int_address(int addr) {
    return (addr >= GLOBAL_INT_BASE && addr < GLOBAL_FLOAT_BASE) ||
           (addr >= LOCAL_INT_BASE && addr < LOCAL_FLOAT_BASE) ||
           (addr >= TMP_INT_BASE && addr < TMP_FLOAT_BASE) ||
           (addr >= CONST_INT_BASE && addr < CONST_FLOAT_BASE);
}

void Memory::store_num_call_stack(Address a, double val) {
    int addr = std::get<int>(a);

    if (addr >= LOCAL_FLOAT_BASE && addr < LOCAL_STR_BASE) {
        to_push.locals_float[addr - LOCAL_FLOAT_BASE] = val;
        return;
    }

    if (addr >= LOCAL_INT_BASE && addr < LOCAL_FLOAT_BASE) {
        to_push.locals_int[addr - LOCAL_INT_BASE] = (long)val;
        return;
    }

    throw std::runtime_error("store_num_pending: invalid param address: " +
                             std::to_string(addr));
}

void VM::execute() {
    double arg1;
    double arg2;
    int param_no;
    int addr; // for checking if int
    std::string func_name;
    while (true) {
        switch (program[ip].op) {
        case Instruction::JMP:
            // need to do this because addresses can be either
            // str or int, str fo era gosub etc..
            // design flaw i think, refactor for later
            ip = std::get<int>(program[ip].result);
            break;
        case Instruction::OP_ADD:
            arg1 = mem.get_num(program[ip].arg1);
            arg2 = mem.get_num(program[ip].arg2);
            mem.store_num(program[ip].result, arg1 + arg2);
            ip++;
            break;
        case Instruction::OP_SUB:
            arg1 = mem.get_num(program[ip].arg1);
            arg2 = mem.get_num(program[ip].arg2);
            mem.store_num(program[ip].result, arg1 - arg2);
            ip++;
            break;
        case Instruction::OP_DIV:
            arg1 = mem.get_num(program[ip].arg1);
            arg2 = mem.get_num(program[ip].arg2);
            mem.store_num(program[ip].result, arg1 / arg2);
            ip++;
            break;
        case Instruction::OP_MUL:
            arg1 = mem.get_num(program[ip].arg1);
            arg2 = mem.get_num(program[ip].arg2);
            mem.store_num(program[ip].result, arg1 * arg2);
            ip++;
            break;
        case Instruction::OP_GT:
            arg1 = mem.get_num(program[ip].arg1);
            arg2 = mem.get_num(program[ip].arg2);

            if (arg1 > arg2) {
                mem.store_num(program[ip].result, 1);
            } else {
                mem.store_num(program[ip].result, 0);
            }
            ip++;
            break;
        case Instruction::OP_LT:
            arg1 = mem.get_num(program[ip].arg1);
            arg2 = mem.get_num(program[ip].arg2);

            if (arg1 < arg2) {
                mem.store_num(program[ip].result, 1);
            } else {
                mem.store_num(program[ip].result, 0);
            }
            ip++;
            break;
        case Instruction::OP_EQ:
            arg1 = mem.get_num(program[ip].arg1);
            arg2 = mem.get_num(program[ip].arg2);

            if (arg1 == arg2) {
                mem.store_num(program[ip].result, 1);
            } else {
                mem.store_num(program[ip].result, 0);
            }
            ip++;
            break;
        case Instruction::OP_NEQ:
            arg1 = mem.get_num(program[ip].arg1);
            arg2 = mem.get_num(program[ip].arg2);

            if (arg1 != arg2) {
                mem.store_num(program[ip].result, 1);
            } else {
                mem.store_num(program[ip].result, 0);
            }
            ip++;
            break;
        case Instruction::MOV:
            // MOV to_move / copy -1 target
            mem.store_num(program[ip].result, mem.get_num(program[ip].arg1));
            ip++;
            break;
        case Instruction::JZ:
            // JZ "bool" -1 target
            if (mem.get_num(program[ip].arg1) <= 0) {
                ip = std::get<int>(program[ip].result);
                break;
            }
            ip++;
            break;
        case Instruction::JG:
            // JZ "bool" -1 target
            if (mem.get_num(program[ip].arg1) > 0) {
                ip = std::get<int>(program[ip].result);
                break;
            }
            ip++;
            break;
        case Instruction::ERA:
            // JZ "bool" -1 target
            func_name = std::get<std::string>(program[ip].result);
            // mem.push_stack(func_dir[func_name].get_resources());
            mem.prepare_frame(func_dir[func_name].get_resources());
            ip++;
            break;
        case Instruction::PARAM:
            // PARAM dir -1 (param no.)
            param_no = std::get<int>(program[ip].result);
            // Address param_addr =
            // func_dir[func_name].get_param_addr(param_no);
            arg1 = mem.get_num(program[ip].arg1);
            mem.store_num_call_stack(
                func_dir[func_name].get_param_addr(param_no), arg1);
            ip++;
            break;
        case Instruction::CALL:
            mem.push_call();

            mem.stack_segment.top().set_return_quad(ip + 1);
            ip = func_dir[func_name].start_quad;
            break;
        case Instruction::RET:
            // RET (global var name as func) -1 (to_store)
            // first store global
            mem.store_num(program[ip].arg1, mem.get_num(program[ip].result));
            ip = mem.stack_segment.top().get_return_quad();
            mem.stack_segment.pop();
            break;
        case Instruction::ENDFUNC:
            ip = mem.stack_segment.top().get_return_quad();
            mem.stack_segment.pop();
            break;
        case Instruction::WRITE:
            addr = std::get<int>(program[ip].result);
            if ((addr >= GLOBAL_STR_BASE && addr < LOCAL_INT_BASE) ||
                (addr >= LOCAL_STR_BASE && addr < TMP_INT_BASE) ||
                (addr >= TMP_STR_BASE && addr < CONST_INT_BASE) ||
                (addr >= CONST_STR_BASE)) {
                std::cout << mem.get_str(program[ip].result) << std::endl;
            } else if (mem.is_int_address(addr)) {
                std::cout << (long)(mem.get_num(program[ip].result))
                          << std::endl;
            } else {
                std::cout << mem.get_num(program[ip].result) << std::endl;
            }
            ip++;
            break;
        case Instruction::END:
            return;
        }
    }
}
