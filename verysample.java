class Main {
	public static void main(String[] a) 
	{
		System.out.println(new C().do());
	}
}

class C {
	public int do() {
		int a;
		int b;
		int c;
		a = 3 + 2;
		b = 10 + a;
		c = 34 + a;
		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		return 1;
	}
}