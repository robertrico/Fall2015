import java.io.*;
import java.util.Scanner;
//--------------------------------------------
// Recognizer for simple expression grammar
// Written by Scott Gordon  1/03
// minor modifications made 2/04, 9/06, 2/09, 9/11, 2/15
// 
// to run on Athena (linux) -
//    save as:  Recognizer.java
//    compile:  javac Recognizer.java
//    execute:  java Recognizer
//
// EBNF Grammar is -
//           <exp> ::= <atom> | <list>
//          <atom> ::= <digit> | <string>
//          <list> ::= ( <exprlist> )
//      <exprlist> ::= { <exp> }
//         <digit> ::= 0 | 1
//        <string> ::= a | b
//--------------------------------------------

public class Recognizer
{
  static String inputString;
  static int index = 0;
  static int errorflag = 0;

  private char token()
  { return(inputString.charAt(index)); }

  private void advancePtr()
  { if (index < (inputString.length()-1)) index++; }

  private void match(char T)
  { if (T == token()) advancePtr(); else error(); }

  private void error()
  {
    System.out.println("error at position: " + index);
    errorflag = 1;
    advancePtr();
  }
//----------------------
  private void exp()
  { if (token() == '(') list(); else atom(); }

  private void atom()
  { if ((token() == '0')
     || (token() == '1')) digit(); else str(); }

  private void list()
  {
    match('(');
    exprlist();
    match(')');
  }

  private void exprlist()
  { while ((token() == '0')
        || (token() == '1')
        || (token() == 'a')
        || (token() == 'b')
        || (token() == '(')) exp(); }

  private void digit()
  { if ((token() == '0') || (token() == '1')) match(token()); else error(); }

  private void str()
  { if ((token() == 'a') || (token() == 'b')) match(token()); else error(); }

//----------------------
  private void start()
  {
    exp();
    match('$');

    if (errorflag == 0)
      System.out.println("legal." + "\n");
    else
      System.out.println("errors found." + "\n");
  }
//----------------------
  public static void main (String[] args) throws IOException
  {
    Recognizer rec = new Recognizer();

    Scanner input = new Scanner(System.in);

    System.out.print("\n" + "enter an expression: ");
    inputString = input.nextLine();

    rec.start();
  }
}
