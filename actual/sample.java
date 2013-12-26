class Factorial {
	public static void main(String[] a) {
		System.out.println(new Fac().ComputeFac(10, 15, new Fac() ));
	}
}

class Fac {
	public int ComputeFac(int num, int l, Fac r) {
		int num_aux;
		bool b;
		b = true;
		if (num < 1){
	  		num_aux = 1;
		}
		else
		{
			b = 3 < 2;
			num_aux = num * (this.ComputeFac(num - 1, num, 10));
		}
		return num_aux;
	}
}

class B
{
	public int do()	{
		Fac f;
		Fac d;
		int a;
		f = new Fac();
		a = f.ComputeFac(5);
		a = f.ComputeFac(5, new Fac(), 10, 43);
		a = f.ComputeFac(5, 10, new Fac());
		a = f.ComputeFac(5, new Fac(), 10, 43);
		f = d;
		return a; 
	}
}