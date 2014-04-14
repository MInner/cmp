class Factorial {
	public static void main(String[] a) {
		System.out.println(new Fac().ComputeFac(10, 15 ));
	}
}

class Fac {
	public int ComputeFac(int num, int l) {
		int num_aux;
		bool b;
		b = true;
		if (num < 1){
	  		num_aux = 1;
		}
		else
		{
			b = 3 < 2;
			num_aux = num * (this.ComputeFac(num - 1, num));
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
		a = this.ret() + 3;
		f = new Fac();
		a = f.ComputeFac(5, this.ret()) * 2;
		return a;
	}

	public int ret(){
		return 7;
	}
}