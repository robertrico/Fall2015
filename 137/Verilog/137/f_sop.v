module f_sop
(
	/* Expression: xy' + yz */
	/* Instantiate Inputs */
	input x,y,z,
	/* Instantiate Output */
	output cout
);
/* There are three wires including the output wire for the y'*/
wire out1,out2,out3;

/* Not the y gate */
not n1(out1,y);
/* Nand the resulting y' with x */
nand n2(out2,x,out1);
/* Nand the resulting y with z */
nand n3(out3,y,z);
/* Nand the resulting xy' with yz */
nand n4(cout,out2,out3);

endmodule
