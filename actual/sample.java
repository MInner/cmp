class Factorial {
	public static void main(String[] a) {
		System.out.println(new Fac().ComputeFac(10));
	}
}

class Fac {
	public int ComputeFac(int num) {
		int num_aux;
		bool b;
		b = true;
		if (num < 1){
	  		num_aux = 1;
		}
		else
		{
			b = 3 < 2;
			num_aux = num * (this.ComputeFac(num - 1));
		}
		return num_aux;
	}

	public int test1() {
		int locvar1;
		int locvar2;
		int locvar3;
		return locvar1;
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
		f = d;
		return a; 
	}
}
