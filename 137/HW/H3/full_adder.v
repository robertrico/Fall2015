module full_adder
(
	input a,b,cin,
	output s,cout
);
wire out1,out2,out3;
xor x1(out1,a,b);
xor x2(s,out1,cin);
nand n1(out2,out1,cin);
nand n2(out3,a,b);
nand n3(cout,out2,out3);

endmodule
