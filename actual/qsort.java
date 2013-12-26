class Qsort {
     public int qSort(int[] array, int l, int r) {
        int i = l;
        int j = r;
        int x = array[l + rand.nextInt(r - l + 1)];
        while (i <= j) {
            while (array[i] < x) {
                i = i + 1;
            }
            while (array[j] > x) {
                j = j - 1;
            }
            if (i <= j) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                i = i + 1;
                j = j - 1;
            }
        }
        if (l<j){
            qSort(array, l, j);
        }
        if(i<r){
            qSort(array, i, r);
        }
	return 0;
    }

    public static void main(String[] a) {
	int[] a = new int[10];	
	System.out.println(qsort(a,0,9));
    }
}

