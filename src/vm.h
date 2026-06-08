#include "FunctionDirectory.h"
#include "astVisitor.h"
#include "const_table.h"
#include <vector>

const int GLOBAL_INT_BASE = 1000;
const int GLOBAL_FLOAT_BASE = 2500;
const int GLOBAL_STR_BASE = 5000;

const int LOCAL_INT_BASE = 7500;
const int LOCAL_FLOAT_BASE = 10000;
const int LOCAL_STR_BASE = 12500;

const int TMP_INT_BASE = 15000;
const int TMP_FLOAT_BASE = 17500;
const int TMP_STR_BASE = 20000;

const int CONST_INT_BASE = 22500;
const int CONST_FLOAT_BASE = 25000;
const int CONST_STR_BASE = 27500;

class DataSegment {
  public:
    std::vector<long> globals_int;
    std::vector<double> globals_float;
    std::vector<std::string> globals_str;

    std::vector<long> const_int;
    std::vector<double> const_float;
    std::vector<std::string> const_str;

    DataSegment() = default;
    DataSegment(const_table &ct)
        : globals_int(ct.globals_int_count),
          globals_float(ct.globals_float_count),
          globals_str(ct.globals_str_count), const_int(ct.int_consts.size()),
          const_float(ct.float_consts.size()), const_str(ct.str_consts.size()) {
        // populate with consts in the data segment
        for (const auto &[val, addr] : ct.int_consts) {
            const_int[addr - CONST_INT_BASE] = val;
        }
        for (const auto &[val, addr] : ct.float_consts) {
            const_float[addr - CONST_FLOAT_BASE] = val;
        }
        for (const auto &[val, addr] : ct.str_consts) {
            const_str[addr - CONST_STR_BASE] = val;
        }
    }
};

class StackFrame {
  public:
    std::vector<long> locals_int;
    std::vector<double> locals_float;
    std::vector<std::string> locals_str;

    std::vector<long> temp_int;
    std::vector<double> temp_float;
    std::vector<std::string> temp_str;

    int return_quad;

    StackFrame() = default;
    StackFrame(func_resources &fr)
        : locals_int(fr.local_int), locals_float(fr.local_float),
          locals_str(fr.local_string), temp_int(fr.temp_int),
          temp_float(fr.temp_float), temp_str(fr.temp_str) {}
    int get_return_quad() { return return_quad; }
    void set_return_quad(int n) { return_quad = n; }
};
// new struct because we dont need all the info stored
// in the function directory that we use at compile time
class VmFuncDirectory {
  public:
    func_resources resources;
    int start_quad;
    std::vector<Address> params; // map like, index 0 is param 1

    VmFuncDirectory(func_resources fr, int sq, std::vector<Address> p)
        : resources(fr), start_quad(sq), params(p) {}
    VmFuncDirectory() = default;
    func_resources &get_resources() { return resources; }
    Address get_param_addr(int n);
};

class Memory {
  public:
    std::stack<StackFrame> stack_segment; // locals tepms
    DataSegment data_segment;             // globals const
    // on func calls, we need
    StackFrame to_push;

    Memory(const_table &ct) : data_segment(ct) {}
    void push_stack(func_resources &fr);
    void prepare_frame(func_resources &fr);
    void push_call();

    void store_num(Address a, double val);
    double get_num(Address a);
    void store_num_call_stack(
        Address a,
        double val); // for building the stack frame for a function call

    std::string get_str(Address a);
    bool is_int_address(int addr);
};

class VM {
    std::vector<Quadruple> program;
    // memory
    std::unordered_map<std::string, VmFuncDirectory> func_dir;
    Memory mem;

    int ip = 0; // instruction pointer
  public:
    VM(std::vector<Quadruple> prog, FunctionDirectory &fd, const_table &ct)
        : mem(ct), program(prog) {
        // global is an entry in the function directory,
        // worht it to create the stack for it now
        for (const auto &[name, func] : fd.directory) {
            // for PARAM instruction, we map the no of param to the virt
            // so we know where to add it in the stack_frame
            std::vector<Address> params;
            for (const auto &param : func.params) {
                params.push_back(param.virt_addr);
            }
            func_dir[name] = {func.resources, func.start_quad, params};
        }
        mem.push_stack(func_dir["global"].get_resources());
    }
    void execute();
};
