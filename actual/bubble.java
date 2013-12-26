class Bubble {
    public int bubbleSort(int[] arr) {
      boolean swapped = true;
      int j = 0;
      int tmp;
      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < arr.length - j; i++) {                                       
                  if (arr[i] > arr[i + 1]) {                          
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;
                        swapped = true;
                  }
            }                
      }
    }

    public static void main(String[] a) {
	int[] a = new int[10];	
	System.out.println(bubbleSort(a));
    }
}

