class Factorial {
	public static void main(String[] a) {
		System.out.println(new Fac().ComputeFac(10));
	}
}

class Fac {
	public int ComputeFac(int num) {
		int num_aux;
		if (num < 1){
	  		num_aux = 1;
		}
		else
		{
			num_aux = num * (this.ComputeFac(num-1));
		}
		return num_aux;
	}

	public int test1(int var1, int var2, int var3) {
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
		f = new Fac();
		f.ComputeFac(5);
		int a;
		return a; 
	}
}