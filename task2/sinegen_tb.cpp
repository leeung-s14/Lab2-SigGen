#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;              //# of cycles to simulate
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vsinegen* top = new Vsinegen;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);
    tfp->open ("counter.vcd");

    //init Vbuddy
    if (vbdOpen()!=1) return (-1);
    vbdHeader("Lab 2: Signal Gen");

    //initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;
    top->incr = 1;

    //run simulation for many clock cycles
    for (i=0; i<1000000;i++) {
        top->incr = vbdValue();
        //dump variables into VCD file and toggle clock
        for (clk =0;clk<2;clk++) { tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval();
        }

        //Send count value to Vbuddy
        // vbdHex(4,(int(top->count) >> 16) & 0xF);
        // vbdHex(3,(int(top->count) >> 8) & 0xF);
        // vbdHex(2,(int(top->count) >> 4) & 0xF);
        // vbdHex(1,(int(top->count)) & 0xF);
        vbdPlot(int(top->dout1), 0, 255);
        vbdPlot(int(top->dout2), 0, 255);
        vbdCycle(i+1);

        
        top->rst = false ;
        top->en = true;
    // either simulation finished, or 'q' is pressed
    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
      exit(0);                // ... exit if finish OR 'q' pressed    
    }

    vbdClose();
    tfp->close();
    exit(0);
}