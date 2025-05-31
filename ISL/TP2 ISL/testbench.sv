module testbench;

    reg clk;          // Sinal de clock
    reg reset;        // Sinal de reset
    reg start;        // Gatilho para iniciar o contador
    wire [3:0] count; // Saída do contador (4 bits)
    wire [4:0] timer; // Saída do timer (5 bits)

    // Instância do módulo contador_buffer
    contador_buffer uut (
        .clk(clk),
        .reset(reset),
        .start(start),
        .count(count),
        .timer(timer)
    );

    // Gera o sinal de clock (período de 10 unidades de tempo)
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // Alterna o clock a cada 5 unidades de tempo 
    end

    initial begin
        // Configura a geração do arquivo .vcd
        $dumpfile("dump.vcd");
        $dumpvars(1, uut);

        // Inicializa os sinais
        reset = 0;
        start = 0;

        // Tempo inicial (0s)
        #10;

        // Aciona o start (início do buffer)
        start = 1;

        // Aguarda 7 ciclos (70 unidades de tempo) e aciona o reset
        #70;
        reset = 1;
        #10; // Mantém o reset por 1 ciclo
        reset = 0;

      // Permite que o contador e o timer operem por mais 20 ciclos. O timer não precisa operar indefinidamente.
        #200;

        // Finaliza a simulação
        $finish;
    end

    // Monitoramento das saídas
    initial begin
        $monitor("Time: %0t | Reset: %b | Start: %b | Count: %d | Timer: %d", $time, reset, start, count, timer);
    end
endmodule
