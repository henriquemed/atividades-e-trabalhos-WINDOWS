`timescale 1ns/1ps

module testbench();
  reg [3:0] sensor_input;  // entrada simulada de 4 bits
  wire [2:0] mod_output;   // Saída monitorada de 3 bits

  // instanciação do módulo a ser testado
  sensor_mod5 uut (
    .sensor_input(sensor_input),
    .mod_output(mod_output)
  );

  initial begin
    $dumpfile("waveform.vcd");  // arquivo de saída das formas de onda
    $dumpvars(0, testbench);    // variáveis para monitoramento

    // test cases
    sensor_input = 4'b0110;  // 6
    #10;
    $display("Input: %b, Output: %b", sensor_input, mod_output);

    sensor_input = 4'b1101;  // 13
    #10;
    $display("Input: %b, Output: %b", sensor_input, mod_output);

    sensor_input = 4'b1010;  // 10
    #10;
    $display("Input: %b, Output: %b", sensor_input, mod_output);

    sensor_input = 4'b0011;  // 3
    #10;
    $display("Input: %b, Output: %b", sensor_input, mod_output);

    sensor_input = 4'b1001;  // 9
    #10;
    $display("Input: %b, Output: %b", sensor_input, mod_output);

    $finish;  // fim da simulação
  end
endmodule
