`include "f_sop.v"
module tester();
/* Instantiate the input variables */
reg x,y,z;

/* final output wire to pass to modules */
wire cout;

/* Call the Module logic */
/* Expression: xy' + yz */
f_sop fal(x,y,z,cout);

initial begin
/* Display */
$display("Time x y z | cout");
$monitor("%4d %b %b %b | %b",$time,x,y,z,cout);

x=0; y=0; z = 0; //000, 01 + 00 = 0 
#1 //Wait 1ns
x=0; y=0; z = 1; //001, 01 + 01 = 0
#1
x=0; y=1; z = 0; //000, 00 + 10 = 0
#1
x=0; y=1; z = 1; //011, 00 + 11 = 1
#1
x=1; y=0; z = 0; //100, 11 + 00 = 1
#1
x=1; y=0; z = 1; //101, 11 + 01 = 1
#1
x=1; y=1; z = 0; //110, 10 + 10 = 0
#1
x=1; y=1; z = 1; //111, 10 + 11 = 1
#1

$finish;
end
endmodule
