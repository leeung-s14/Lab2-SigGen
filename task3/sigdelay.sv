module sigdelay#(
    parameter   A_WIDTH=8,
                D_WIDTH=8
)(
    input logic clk,
    input logic rst,
    input logic en,
    input logic wr,
    input logic rd,
    input logic [D_WIDTH-1:0] offset,
    input logic [D_WIDTH-1:0] mic_signal,
    output logic [D_WIDTH-1:0] delayed_signal
);

    logic [A_WIDTH-1:0] wr_address;

counter addrcounter(
    .clk(clk),
    .rst(rst),
    .en(en),
    // .offset(offset),
    .count(wr_address)
);

ram audioram(
    .clk(clk),
    .wr_en(wr),
    .rd_en(rd),
    .wr_addr(wr_address),
    .rd_addr(wr_address - offset),
    .din(mic_signal),
    .dout(delayed_signal)
);

endmodule
