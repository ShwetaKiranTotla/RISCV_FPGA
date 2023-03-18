
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 08.10.2022 13:45:42
// Design Name: 
// Module Name: mypwm
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module mypwm(
    input clk,
    
    input [15:0] max_count,
    input [15:0] cmp_val,
   
    output vout

    );
    reg vout_reg;
    // For 10 KHz, counter runs till 10,000 which is 14 bit 14'h2710.
    reg [15:0] counter;
    reg [15:0] max_val;
   
    // 50% duty cycle - So compare reg = 5,000 which is 14'h1388.
    reg [15:0] cmp_reg;
   
    always @(posedge clk) begin
        max_val <= max_count;
        cmp_reg <= cmp_val;
    end
   
    always @(posedge clk) begin
        if(counter < max_val) begin
            counter = counter + 1;
            if(counter >= cmp_reg) begin
                vout_reg = 0;
            end else begin
                vout_reg = vout_reg;
            end
        end else begin
            counter = 0;
            vout_reg <= 1;
        end
    end
   
//    always @(counter) begin
       
//    end
   
    assign vout = vout_reg;
   
endmodule