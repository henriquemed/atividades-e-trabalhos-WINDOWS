module contador_buffer (
    input wire clk,          // Sinal de clock
    input wire reset,        // Sinal de reset 
    input wire start,        // Gatilho para iniciar o contador
    output reg [3:0] count,  // Saída do contador (4 bits, de 0 a 12)
    output reg [4:0] timer   // Saída do timer (5 bits, de 0 a 27)
);

    // Inicialização 
    initial begin
        count = 0;
        timer = 0;
    end

    always @(posedge clk) begin
        // Lógica do Timer: O timer conta de 0 a 27 continuamente, sem relação com o reset
        if (start) begin
            if (timer < 27) begin
                timer <= timer + 1;
            end else begin
                timer <= 0; // Reinicia automaticamente ao atingir 27
            end
        end
 
        // Lógica do Contador: Reset controlado pelo sinal de reset
        if (reset) begin
            count <= 0;
        end else if (start) begin
            if (count < 12) begin
                count <= count + 1;
            end else begin 
                count <= 0; // Reseta automaticamente ao atingir 12
            end
        end
    end
endmodule
