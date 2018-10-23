
module system (
	clk_clk,
	reset_reset_n,
	leds_export,
	sw_sliders_export,
	pushbutton_export,
	hex_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[9:0]	leds_export;
	input	[9:0]	sw_sliders_export;
	input	[3:0]	pushbutton_export;
	output	[47:0]	hex_export;
endmodule
