public class Hw{
	public static void main(String args[]){
		story(10);
	}
	public static void story(int base){
		if(base == 0)
			return;
		System.out.println(base);
		story(base-1);
		System.out.println(base);
	}
}
