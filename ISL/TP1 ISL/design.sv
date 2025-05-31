module sensor_mod5 (
  input [3:0] sensor_input,  // entrada de 4 bits
  output [2:0] mod_output    // saída de 3 bits (resto da divisão)
);
  assign mod_output = sensor_input % 5;  // resto da divisão por 5
endmodule
