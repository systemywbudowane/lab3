	system u0 (
		.clk_clk           (<connected-to-clk_clk>),           //        clk.clk
		.reset_reset_n     (<connected-to-reset_reset_n>),     //      reset.reset_n
		.leds_export       (<connected-to-leds_export>),       //       leds.export
		.sw_sliders_export (<connected-to-sw_sliders_export>), // sw_sliders.export
		.pushbutton_export (<connected-to-pushbutton_export>), // pushbutton.export
		.hex_export        (<connected-to-hex_export>)         //        hex.export
	);

