import java.util.Scanner;

/* This program is simply for demonstrating
 * the highlighting of Java syntax.
 */

class Animal { }

class Dog extends Animal { }

public class Example {
  /** Prompts the user for a string and returns what they entered.
   * @param message The message to display to the user.
   * @return The string that the user entered.
   * */
  static String prompt(String message) {

    Scanner scanner = new Scanner(System.in);

    System.out.printf("%s: ", message);

    return scanner.nextLine();
  }
  public static void main(String[] args) {

    double pi = 3.1415;

    String name = prompt("Enter your name");

    System.out.println("Nice to meet you, " + name + "!");
  }
}
