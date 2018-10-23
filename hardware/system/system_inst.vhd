	component system is
		port (
			clk_clk           : in  std_logic                     := 'X';             -- clk
			reset_reset_n     : in  std_logic                     := 'X';             -- reset_n
			leds_export       : out std_logic_vector(9 downto 0);                     -- export
			sw_sliders_export : in  std_logic_vector(9 downto 0)  := (others => 'X'); -- export
			pushbutton_export : in  std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			hex_export        : out std_logic_vector(47 downto 0)                     -- export
		);
	end component system;

	u0 : component system
		port map (
			clk_clk           => CONNECTED_TO_clk_clk,           --        clk.clk
			reset_reset_n     => CONNECTED_TO_reset_reset_n,     --      reset.reset_n
			leds_export       => CONNECTED_TO_leds_export,       --       leds.export
			sw_sliders_export => CONNECTED_TO_sw_sliders_export, -- sw_sliders.export
			pushbutton_export => CONNECTED_TO_pushbutton_export, -- pushbutton.export
			hex_export        => CONNECTED_TO_hex_export         --        hex.export
		);

